#include "HttpLLMProvider.h"
#include "VFXAgentLog.h"

#include "Dom/JsonObject.h"
#include "JsonObjectConverter.h"
#include "Misc/DateTime.h"
#include "Misc/ScopeLock.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/Base64.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "Modules/ModuleManager.h"

#if WITH_EDITOR
#include "AssetRegistry/AssetRegistryModule.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceConstant.h"
#endif

#include "HttpModule.h"
#include "HttpManager.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

static const TCHAR* HttpRequestStatusToString(EHttpRequestStatus::Type Status)
{
	switch (Status)
	{
	case EHttpRequestStatus::NotStarted: return TEXT("NotStarted");
	case EHttpRequestStatus::Processing: return TEXT("Processing");
	case EHttpRequestStatus::Failed: return TEXT("Failed");
	case EHttpRequestStatus::Succeeded: return TEXT("Succeeded");
	default: return TEXT("Unknown");
	}
}

void UHttpLLMProvider::Configure(
	EVFXAgentLLMBackend InBackend,
	const FString& InEndpoint,
	const FString& InModel,
	const FString& InApiKey,
	float InTimeoutSeconds)
{
	Backend = InBackend;
	Endpoint = InEndpoint;
	Endpoint.TrimStartAndEndInline();
	Model = InModel;
	Model.TrimStartAndEndInline();
	ApiKey = InApiKey;
	ApiKey.TrimStartAndEndInline();
	TimeoutSeconds = FMath::Max(1.0f, InTimeoutSeconds);
}

static bool IsPlaceholderApiKey(const FString& InKey)
{
	FString Key = InKey;
	Key.TrimStartAndEndInline();
	return Key.IsEmpty() || Key.Equals(TEXT("set"), ESearchCase::IgnoreCase) || Key.Equals(TEXT("<set>"), ESearchCase::IgnoreCase);
}

/** Build a detailed error string from a failed HTTP request/response. */
static FString BuildHttpFailureMessage(const FString& Tag, FHttpRequestPtr Request, FHttpResponsePtr Response)
{
	const FString StatusStr = Request.IsValid() ? HttpRequestStatusToString(Request->GetStatus()) : TEXT("<null>");
	const FString UrlStr = Request.IsValid() ? Request->GetURL() : TEXT("<null>");
	const int32 RespCode = Response.IsValid() ? Response->GetResponseCode() : 0;
	const FString RespBody = Response.IsValid() ? Response->GetContentAsString().Left(500) : TEXT("<no response>");
	UE_LOG(LogVFXAgent, Error, TEXT("%s HTTP failed. Status=%s URL=%s Code=%d Body=%s"), *Tag, *StatusStr, *UrlStr, RespCode, *RespBody);
	return FString::Printf(TEXT("HTTP request failed (status=%s). URL=%s"), *StatusStr, *UrlStr);
}

/** Returns true if the effective backend should use the OpenAI Responses API format. */
static bool IsResponsesAPI(EVFXAgentLLMBackend Backend, const FString& Endpoint)
{
	if (Backend == EVFXAgentLLMBackend::OpenAIResponses)
	{
		return true;
	}
	// Auto-detect from endpoint URL when the user sets backend to OpenAIChatCompletions
	// but the endpoint actually points at the Responses API.
	if (Backend == EVFXAgentLLMBackend::OpenAIChatCompletions)
	{
		return Endpoint.Contains(TEXT("/v1/responses"));
	}
	return false;
}

/** Try to extract the text content from an OpenAI Responses API response object.
 *  The Responses API returns: { "output": [ { "type":"message", "content": [ { "type":"output_text", "text":"..." } ] } ] }
 */
static bool TryExtractResponsesAPIContent(const TSharedPtr<FJsonObject>& Root, FString& OutContent, FString& OutError)
{
	const TArray<TSharedPtr<FJsonValue>>* OutputArray = nullptr;
	if (!Root->TryGetArrayField(TEXT("output"), OutputArray) || !OutputArray || OutputArray->Num() == 0)
	{
		OutError = TEXT("Responses API response missing 'output' array");
		return false;
	}

	for (const TSharedPtr<FJsonValue>& OutputItem : *OutputArray)
	{
		const TSharedPtr<FJsonObject> ItemObj = OutputItem->AsObject();
		if (!ItemObj.IsValid()) continue;

		FString ItemType;
		ItemObj->TryGetStringField(TEXT("type"), ItemType);
		if (ItemType != TEXT("message")) continue;

		const TArray<TSharedPtr<FJsonValue>>* ContentArray = nullptr;
		if (!ItemObj->TryGetArrayField(TEXT("content"), ContentArray) || !ContentArray) continue;

		for (const TSharedPtr<FJsonValue>& ContentItem : *ContentArray)
		{
			const TSharedPtr<FJsonObject> ContentObj = ContentItem->AsObject();
			if (!ContentObj.IsValid()) continue;

			FString ContentType;
			ContentObj->TryGetStringField(TEXT("type"), ContentType);
			if (ContentType == TEXT("output_text"))
			{
				if (ContentObj->TryGetStringField(TEXT("text"), OutContent))
				{
					return true;
				}
			}
		}
	}

	OutError = TEXT("Responses API response has no output_text content");
	return false;
}

#if WITH_EDITOR
static TArray<FString> GetMaterialLibraryPathsFromConfig()
{
	TArray<FString> Paths;
	const TCHAR* Section = TEXT("/Script/VFXAgentEditor.VFXAgentSettings");
	const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
	for (const FString& File : ConfigFiles)
	{
		if (GConfig && GConfig->GetArray(Section, TEXT("MaterialLibraryPaths"), Paths, File) && Paths.Num() > 0)
		{
			break;
		}
	}
	if (Paths.Num() == 0)
	{
		Paths.Add(TEXT("/Game/VFXAgent/Materials"));
	}
	return Paths;
}

static void CollectMaterialLibraryAssets(const TArray<FString>& RootPaths, TArray<FAssetData>& OutAssets)
{
	if (RootPaths.Num() == 0)
	{
		return;
	}

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FARFilter Filter;
	Filter.ClassPaths.Add(UMaterial::StaticClass()->GetClassPathName());
	Filter.ClassPaths.Add(UMaterialInstance::StaticClass()->GetClassPathName());
	Filter.ClassPaths.Add(UMaterialInstanceConstant::StaticClass()->GetClassPathName());
	Filter.bRecursivePaths = true;
	for (const FString& Path : RootPaths)
	{
		Filter.PackagePaths.Add(*Path);
	}

	AssetRegistryModule.Get().GetAssets(Filter, OutAssets);
}

static void AppendMaterialLibraryNamesToPrompt(FString& Prompt)
{
	TArray<FString> Paths = GetMaterialLibraryPathsFromConfig();
	TArray<FAssetData> Assets;
	CollectMaterialLibraryAssets(Paths, Assets);
	if (Assets.Num() == 0)
	{
		return;
	}

	TSet<FString> UniqueNames;
	UniqueNames.Reserve(Assets.Num());
	for (const FAssetData& Asset : Assets)
	{
		UniqueNames.Add(Asset.AssetName.ToString());
	}

	TArray<FString> Names = UniqueNames.Array();
	Names.Sort();

	Prompt += TEXT("\n\nMaterial library names (prefer these; choose closest match when naming materials): ");
	Prompt += FString::Join(Names, TEXT(", "));
}
#endif

FString UHttpLLMProvider::BuildSystemPrompt() const
{
	// -------------------------------------------------------------------------
	// Python-First System Prompt - VFXAgent Architecture V3
	// Provides verified, working UE5 Python APIs with a concrete template.
	// The LLM MUST use only the APIs listed here — no hallucination.
	// -------------------------------------------------------------------------
	return TEXT(
		"You are a professional Unreal Engine 5 Technical Artist generating a Niagara VFX system via Python.\n"
		"The user will describe an effect. Your job is to output a directly executable Python script.\n\n"

		"=== VERIFIED WORKING UE5 PYTHON APIS (use ONLY these) ===\n\n"

		"# 1. Imports\n"
		"import unreal\n\n"

		"# 2. Ensure output directory exists\n"
		"OUTPUT_PATH = \"/Game/VFXAgent/Generated\"\n"
		"if not unreal.EditorAssetLibrary.does_directory_exist(OUTPUT_PATH):\n"
		"    unreal.EditorAssetLibrary.make_directory(OUTPUT_PATH)\n\n"

		"# 3. Create a Niagara System asset\n"
		"asset_tools = unreal.AssetToolsHelpers.get_asset_tools()\n"
		"factory = unreal.NiagaraSystemFactoryNew()\n"
		"system = asset_tools.create_asset(\"NS_EffectName\", OUTPUT_PATH, unreal.NiagaraSystem, factory)\n\n"

		"# 4. (Optional) Duplicate an existing emitter asset as a starting point\n"
		"#    Use only assets known to exist. Safe built-in emitter templates:\n"
		"#      /Niagara/Templates/NT_SpriteEmitter.NT_SpriteEmitter\n"
		"#      /Niagara/Templates/NT_GPUSprites.NT_GPUSprites\n"
		"#    If unsure whether a template exists, SKIP emitter duplication entirely.\n"
		"# emitter_asset = unreal.load_asset(\"/Niagara/Templates/NT_SpriteEmitter.NT_SpriteEmitter\")\n"
		"# if emitter_asset:\n"
		"#     dup = asset_tools.duplicate_asset(\"E_Main\", OUTPUT_PATH, emitter_asset)\n\n"

		"# 5. Save and open the system\n"
		"if system:\n"
		"    unreal.EditorAssetLibrary.save_asset(system.get_path_name())\n"
		"    unreal.get_editor_subsystem(unreal.AssetEditorSubsystem).open_editor_for_assets([system])\n"
		"    print(\"Created: \" + system.get_path_name())\n"
		"else:\n"
		"    print(\"ERROR: Failed to create Niagara System\")\n\n"

		"=== STRICT RULES ===\n"
		"- Use ONLY the APIs shown above. Do NOT invent methods like add_emitter(), create_emitter(),\n"
		"  set_parameter(), NiagaraFunctionLibrary, or any other API not shown here.\n"
		"- Do NOT reference asset paths you are not certain exist on disk.\n"
		"  Unsafe example: /Niagara/DefaultAssets/DefaultEmptyEmitter (may not exist — DO NOT USE)\n"
		"  Safe example: /Niagara/Templates/NT_SpriteEmitter (standard engine template)\n"
		"- The asset name must start with NS_ and be derived from the effect description.\n"
		"- If the requested effect cannot be built with only the APIs above, create a basic\n"
		"  empty NiagaraSystem and add a Python comment describing what should be configured manually.\n\n"

		"=== OUTPUT FORMAT ===\n"
		"- Return ONLY raw Python code — no markdown fences, no commentary, no preamble.\n"
		"- Your entire output is passed verbatim to exec() inside the UE5 editor.\n"
		"- First line must be: import unreal\n"
	);
}

FString UHttpLLMProvider::BuildDirectorSystemPrompt() const
{
	return TEXT(
		"You are a VFX Director. Output ONLY valid JSON (no markdown, no commentary).\n"
		"Your output MUST match this schema exactly:\n"
		"{\n"
		"  \"version\": \"1.0\",\n"
		"  \"style\": {\n"
		"    \"keywords\": [\"...\"],\n"
		"    \"colorTheme\": {\"primary\":\"#RRGGBB\",\"secondary\":\"#RRGGBB\",\"accent\":\"#RRGGBB\"},\n"
		"    \"intensity\": 0.0,\n"
		"    \"scale\": 1.0\n"
		"  },\n"
		"  \"layers\": [\n"
		"    {\n"
		"      \"name\": \"LayerName\",\n"
		"      \"archetypeTag\": \"smoke|sparks|trail|explosion|distortion|...\",\n"
		"      \"emitters\": [\n"
		"        {\"alias\":\"E_Name\", \"template\":\"/Game/VFX/Archetypes/Template\", \"role\":\"role\"}\n"
		"      ],\n"
		"      \"events\": [\n"
		"        {\"source\":\"E_A\", \"event\":\"OnBurst|Collision\", \"target\":\"E_B\", \"handler\":\"SpawnFromEvent\"}\n"
		"      ]\n"
		"    }\n"
		"  ],\n"
		"  \"actions\": [\n"
		"    {\"type\":\"CreateSystem\",\"name\":\"NS_Name\",\"path\":\"/Game/VFX/Generated\"},\n"
		"    {\"type\":\"AddEmitterFromTemplate\",\"system\":\"NS_Name\",\"template\":\"/Game/VFX/Archetypes/Template\",\"alias\":\"E_Name\"},\n"
		"    {\"type\":\"SetParam\",\"target\":\"E_Name.Spawn\",\"name\":\"SpawnRate\",\"value\":1200},\n"
		"    {\"type\":\"EnableDrag\",\"target\":\"E_Name\",\"dragCoef\":2.2,\"inheritVel\":0.35},\n"
		"    {\"type\":\"CreateMaterialInstance\",\"parent\":\"/Game/VFX/Materials/M_Master\",\"out\":\"/Game/VFX/Generated/MI_01\",\"params\":{\"Emissive\":6.0,\"Opacity\":0.7}},\n"
		"    {\"type\":\"AssignRendererMaterial\",\"target\":\"E_Name.Renderer.Sprite\",\"material\":\"/Game/VFX/Generated/MI_01\"},\n"
		"    {\"type\":\"CompileAndValidate\",\"system\":\"NS_Name\"},\n"
		"    {\"type\":\"RenderThumbnail\",\"system\":\"NS_Name\",\"out\":\"Saved/VFXThumbs/001.png\",\"cameraPreset\":\"iso_close\"}\n"
		"  ],\n"
		"  \"validationTargets\": {\n"
		"    \"bounds\": [[-200,-200,-50],[200,200,300]],\n"
		"    \"particleCountRange\": [500, 15000]\n"
		"  }\n"
		"}\n"
		"Rules:\n"
		"- Use /Game/VFX/Archetypes/* emitter templates when possible.\n"
		"- Actions must be deterministic and ordered.\n"
		"- Do not include commentary or markdown.\n"
	);
}

FString UHttpLLMProvider::BuildEffectSpecSystemPrompt() const
{
	return TEXT(
		"You are a VFX specification generator. Output ONLY strict JSON matching EffectSpec v1.\n"
		"No prose, no markdown. Required fields: effect_name, layers.\n"
		"Each layer must include: id, name, role, renderer_type (sprite|ribbon|mesh), spawn, init, update, material.\n"
		"material.hlsl_custom.enabled can be true with code, inputs, texture_inputs, outputs, contract.\n"
		"If unsure, keep optional fields minimal but valid.\n"
	);
}

FString UHttpLLMProvider::BuildDirectorRevisionPrompt(const FString& OriginalDirectorJson, const FString& ExecutionReportJson) const
{
	return FString::Printf(
		TEXT("You are revising a failed Niagara execution. Output ONLY a corrected Director JSON (same schema).\n\nOriginalDirectorJson:\n%s\n\nExecutionReport:\n%s\n\nConstraints:\n- Keep existing system and emitters when possible.\n- Use actions to patch or adjust (no full regeneration).\n- Ensure CompileAndValidate passes.\n"),
		*OriginalDirectorJson,
		*ExecutionReportJson);
}

static bool ParseJsonObject(const FString& JsonText, TSharedPtr<FJsonObject>& OutObj, FString& OutError)
{
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonText);
	if (!FJsonSerializer::Deserialize(Reader, OutObj) || !OutObj.IsValid())
	{
		OutError = TEXT("Failed to parse JSON object");
		return false;
	}
	return true;
}

bool UHttpLLMProvider::TryParseRecipeJson(const FString& RecipeJson, FVFXRecipe& OutRecipe, FString& OutError)
{
	// Extract JSON from markdown code blocks if present (common LLM behavior)
	FString CleanedJson = RecipeJson;
	CleanedJson.TrimStartAndEndInline();
	
	// Remove markdown code blocks: ```json ... ``` or ``` ... ```
	if (CleanedJson.StartsWith(TEXT("```")))
	{
		int32 FirstNewline = CleanedJson.Find(TEXT("\n"), ESearchCase::IgnoreCase, ESearchDir::FromStart, 3);
		if (FirstNewline != INDEX_NONE)
		{
			CleanedJson = CleanedJson.Mid(FirstNewline + 1);
		}
		else
		{
			CleanedJson = CleanedJson.Mid(3); // Just remove ```
		}
		
		int32 LastBackticks = CleanedJson.Find(TEXT("```"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
		if (LastBackticks != INDEX_NONE)
		{
			CleanedJson = CleanedJson.Left(LastBackticks);
		}
		CleanedJson.TrimStartAndEndInline();
	}
	
	// Try direct struct conversion first
	if (FJsonObjectConverter::JsonObjectStringToUStruct(CleanedJson, &OutRecipe, 0, 0))
	{
		UE_LOG(LogVFXAgent, Log, TEXT("Successfully parsed recipe JSON (direct conversion)"));
		return true;
	}

	// Fallback: sometimes models wrap the payload under a key
	TSharedPtr<FJsonObject> Root;
	if (!ParseJsonObject(CleanedJson, Root, OutError))
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to parse JSON: %s. Content: %s"), *OutError, *CleanedJson.Left(500));
		return false;
	}

	const TSharedPtr<FJsonObject>* RecipeObjPtr = nullptr;
	if (Root->TryGetObjectField(TEXT("recipe"), RecipeObjPtr) && RecipeObjPtr && RecipeObjPtr->IsValid())
	{
		FString Inner;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Inner);
		FJsonSerializer::Serialize((*RecipeObjPtr).ToSharedRef(), Writer);
		if (FJsonObjectConverter::JsonObjectStringToUStruct(Inner, &OutRecipe, 0, 0))
		{
			UE_LOG(LogVFXAgent, Log, TEXT("Successfully parsed recipe JSON (nested under 'recipe' key)"));
			return true;
		}
	}

	// Log detailed error with the problematic JSON
	OutError = FString::Printf(TEXT("JSON did not match FVFXRecipe schema. JSON: %s"), *CleanedJson.Left(1000));
	UE_LOG(LogVFXAgent, Error, TEXT("Failed to parse recipe: %s"), *OutError);
	return false;
}

static bool WaitForHttp(FHttpRequestPtr Request, float TimeoutSeconds)
{
	const double Start = FPlatformTime::Seconds();
	while (Request.IsValid() && Request->GetStatus() == EHttpRequestStatus::Processing)
	{
		// Avoid deadlocking the editor/game thread: UE's HTTP manager is normally ticked on the game thread.
		// If a caller blocks the game thread waiting for completion, the request can never finish.
		if (IsInGameThread())
		{
			FHttpModule::Get().GetHttpManager().Tick(0.01f);
		}
		else
		{
			FPlatformProcess::Sleep(0.01f);
		}
		if ((FPlatformTime::Seconds() - Start) > TimeoutSeconds)
		{
			return false;
		}
	}
	return true;
}

void UHttpLLMProvider::RequestRecipeJsonAsync(const FString& UserPrompt, FOnRecipeJsonComplete OnComplete) const
{
	if (!OnComplete)
	{
		return;
	}

	FString EffectiveEndpoint = Endpoint;
	EffectiveEndpoint.TrimStartAndEndInline();
	if (EffectiveEndpoint.IsEmpty())
	{
		OnComplete(false, FString(), TEXT("LLM endpoint is empty"));
		return;
	}

	const bool bOpenAIBackend = (Backend == EVFXAgentLLMBackend::OpenAIChatCompletions || Backend == EVFXAgentLLMBackend::OpenAIResponses);
	if (bOpenAIBackend && IsPlaceholderApiKey(ApiKey))
	{
		OnComplete(false, FString(), TEXT("OpenAI API key is missing or placeholder"));
		return;
	}

	const bool bUseResponsesAPI = IsResponsesAPI(Backend, EffectiveEndpoint);

	TSharedPtr<FJsonObject> BodyObj = MakeShared<FJsonObject>();
	TSharedRef<FJsonObject> BodyRef = BodyObj.ToSharedRef();

	FString ContentType = TEXT("application/json");
	TMap<FString, FString> ExtraHeaders;

	if (Backend == EVFXAgentLLMBackend::OllamaGenerate)
	{
		BodyRef->SetStringField(TEXT("model"), Model.IsEmpty() ? TEXT("llama2") : Model);
		BodyRef->SetStringField(TEXT("prompt"), BuildSystemPrompt() + TEXT("\n\nUSER_PROMPT:\n") + UserPrompt);
		BodyRef->SetBoolField(TEXT("stream"), false);
	}
	else if (bUseResponsesAPI)
	{
		// OpenAI Responses API format (/v1/responses).
		BodyRef->SetStringField(TEXT("model"), Model.IsEmpty() ? TEXT("gpt-4o-mini") : Model);
		BodyRef->SetStringField(TEXT("instructions"), BuildSystemPrompt());
		// Responses API requires the word "json" in the input when text.format.type=json_object.
		BodyRef->SetStringField(TEXT("input"), UserPrompt + TEXT("\nRespond with JSON."));

		// Responses API uses text.format instead of response_format.
		TSharedPtr<FJsonObject> TextObj = MakeShared<FJsonObject>();
		TSharedPtr<FJsonObject> FormatObj = MakeShared<FJsonObject>();
		FormatObj->SetStringField(TEXT("type"), TEXT("json_object"));
		TextObj->SetObjectField(TEXT("format"), FormatObj);
		BodyRef->SetObjectField(TEXT("text"), TextObj);

		if (!ApiKey.IsEmpty())
		{
			ExtraHeaders.Add(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *ApiKey));
		}
	}
	else
	{
		// OpenAI-compatible chat completions.
		BodyRef->SetStringField(TEXT("model"), Model.IsEmpty() ? TEXT("gpt-4o-mini") : Model);
		BodyRef->SetNumberField(TEXT("max_completion_tokens"), 4096);

		TArray<TSharedPtr<FJsonValue>> Messages;
		{
			TSharedPtr<FJsonObject> Sys = MakeShared<FJsonObject>();
			Sys->SetStringField(TEXT("role"), TEXT("system"));
			Sys->SetStringField(TEXT("content"), BuildSystemPrompt());
			Messages.Add(MakeShared<FJsonValueObject>(Sys));
		}
		{
			TSharedPtr<FJsonObject> User = MakeShared<FJsonObject>();
			User->SetStringField(TEXT("role"), TEXT("user"));
			User->SetStringField(TEXT("content"), UserPrompt);
			Messages.Add(MakeShared<FJsonValueObject>(User));
		}
		BodyRef->SetArrayField(TEXT("messages"), Messages);

		// Best-effort strict JSON response (supported by many OpenAI-compatible endpoints).
		TSharedPtr<FJsonObject> ResponseFormat = MakeShared<FJsonObject>();
		ResponseFormat->SetStringField(TEXT("type"), TEXT("json_object"));
		BodyRef->SetObjectField(TEXT("response_format"), ResponseFormat);

		if (!ApiKey.IsEmpty())
		{
			ExtraHeaders.Add(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *ApiKey));
		}
	}

	FString BodyText;
	{
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyText);
		FJsonSerializer::Serialize(BodyRef, Writer);
	}

	FHttpModule& Http = FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Req = Http.CreateRequest();
	Req->SetURL(EffectiveEndpoint);
	Req->SetVerb(TEXT("POST"));
	Req->SetHeader(TEXT("Content-Type"), ContentType);
	Req->SetHeader(TEXT("Accept"), TEXT("application/json"));
	Req->SetHeader(TEXT("User-Agent"), TEXT("VFXAgent/1.0 (UnrealEngine)"));
	for (const TPair<FString, FString>& KV : ExtraHeaders)
	{
		Req->SetHeader(KV.Key, KV.Value);
	}
	Req->SetContentAsString(BodyText);
	Req->SetTimeout(TimeoutSeconds);

	const EVFXAgentLLMBackend EffectiveBackend = Backend;
	const bool bResponsesAPI = bUseResponsesAPI;
	Req->OnProcessRequestComplete().BindLambda([
		OnComplete,
		EffectiveBackend,
		bResponsesAPI
	](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded)
	{
		if (!bSucceeded || !Response.IsValid())
		{
			OnComplete(false, FString(), BuildHttpFailureMessage(TEXT("RequestRecipeJson"), Request, Response));
			return;
		}

		const int32 Code = Response->GetResponseCode();
		const FString ResponseText = Response->GetContentAsString();
		if (Code < 200 || Code >= 300)
		{
			OnComplete(false, FString(), FString::Printf(TEXT("LLM returned HTTP %d: %s"), Code, *ResponseText.Left(800)));
			return;
		}

		TSharedPtr<FJsonObject> Root;
		FString JsonError;
		if (!ParseJsonObject(ResponseText, Root, JsonError))
		{
			OnComplete(false, FString(), FString::Printf(TEXT("LLM response is not JSON: %s"), *ResponseText.Left(200)));
			return;
		}

		FString OutRecipeJson;
		if (EffectiveBackend == EVFXAgentLLMBackend::OllamaGenerate)
		{
			FString Resp;
			if (!Root->TryGetStringField(TEXT("response"), Resp))
			{
				OnComplete(false, FString(), TEXT("Ollama response missing 'response' field"));
				return;
			}
			OutRecipeJson = Resp;
			OnComplete(true, OutRecipeJson, FString());
			return;
		}

		// Responses API: output[].content[].text
		if (bResponsesAPI)
		{
			FString ExtractError;
			if (!TryExtractResponsesAPIContent(Root, OutRecipeJson, ExtractError))
			{
				OnComplete(false, FString(), ExtractError);
				return;
			}
			OnComplete(true, OutRecipeJson, FString());
			return;
		}

		// OpenAI chat completions: choices[0].message.content
		const TArray<TSharedPtr<FJsonValue>>* Choices = nullptr;
		if (!Root->TryGetArrayField(TEXT("choices"), Choices) || !Choices || Choices->Num() == 0)
		{
			OnComplete(false, FString(), TEXT("OpenAI response missing 'choices' array"));
			return;
		}

		TSharedPtr<FJsonObject> Choice0 = (*Choices)[0]->AsObject();
		if (!Choice0.IsValid())
		{
			OnComplete(false, FString(), TEXT("OpenAI response choice[0] is not an object"));
			return;
		}

		const TSharedPtr<FJsonObject> Msg = Choice0->GetObjectField(TEXT("message"));
		if (!Msg.IsValid())
		{
			OnComplete(false, FString(), TEXT("OpenAI response missing message object"));
			return;
		}

		FString Content;
		if (!Msg->TryGetStringField(TEXT("content"), Content))
		{
			OnComplete(false, FString(), TEXT("OpenAI response missing message.content"));
			return;
		}

		OutRecipeJson = Content;
		OnComplete(true, OutRecipeJson, FString());
	});

	UE_LOG(LogVFXAgent, Log, TEXT("RequestRecipeJsonAsync: Sending POST to %s (model=%s, bodyLen=%d, timeout=%.1fs)"),
		*EffectiveEndpoint, *Model, BodyText.Len(), TimeoutSeconds);

	if (!Req->ProcessRequest())
	{
		OnComplete(false, FString(), TEXT("Failed to start HTTP request"));
		return;
	}
}

void UHttpLLMProvider::RequestDirectorJsonInternalAsync(const FString& UserPrompt, const FString& SystemPrompt, FOnDirectorJsonComplete OnComplete) const
{
	if (!OnComplete)
	{
		return;
	}

	FString EffectiveEndpoint = Endpoint;
	EffectiveEndpoint.TrimStartAndEndInline();
	if (EffectiveEndpoint.IsEmpty())
	{
		OnComplete(false, FString(), TEXT("LLM endpoint is empty"));
		return;
	}

	const bool bOpenAIBackend = (Backend == EVFXAgentLLMBackend::OpenAIChatCompletions || Backend == EVFXAgentLLMBackend::OpenAIResponses);
	if (bOpenAIBackend && IsPlaceholderApiKey(ApiKey))
	{
		OnComplete(false, FString(), TEXT("OpenAI API key is missing or placeholder"));
		return;
	}

	const bool bUseResponsesAPI = IsResponsesAPI(Backend, EffectiveEndpoint);

	TSharedPtr<FJsonObject> BodyObj = MakeShared<FJsonObject>();
	TSharedRef<FJsonObject> BodyRef = BodyObj.ToSharedRef();

	FString ContentType = TEXT("application/json");
	TMap<FString, FString> ExtraHeaders;

	if (Backend == EVFXAgentLLMBackend::OllamaGenerate)
	{
		BodyRef->SetStringField(TEXT("model"), Model.IsEmpty() ? TEXT("llama2") : Model);
		BodyRef->SetStringField(TEXT("prompt"), SystemPrompt + TEXT("\n\nUSER_PROMPT:\n") + UserPrompt);
		BodyRef->SetBoolField(TEXT("stream"), false);
	}
	else if (bUseResponsesAPI)
	{
		// OpenAI Responses API format (/v1/responses).
		BodyRef->SetStringField(TEXT("model"), Model.IsEmpty() ? TEXT("gpt-4o-mini") : Model);
		BodyRef->SetStringField(TEXT("instructions"), SystemPrompt);
		// Responses API requires the word "json" in the input when text.format.type=json_object.
		BodyRef->SetStringField(TEXT("input"), UserPrompt + TEXT("\nRespond with JSON."));

		TSharedPtr<FJsonObject> TextObj = MakeShared<FJsonObject>();
		TSharedPtr<FJsonObject> FormatObj = MakeShared<FJsonObject>();
		FormatObj->SetStringField(TEXT("type"), TEXT("json_object"));
		TextObj->SetObjectField(TEXT("format"), FormatObj);
		BodyRef->SetObjectField(TEXT("text"), TextObj);

		if (!ApiKey.IsEmpty())
		{
			ExtraHeaders.Add(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *ApiKey));
		}
	}
	else
	{
		BodyRef->SetStringField(TEXT("model"), Model.IsEmpty() ? TEXT("gpt-4o-mini") : Model);
		BodyRef->SetNumberField(TEXT("max_completion_tokens"), 4096);

		TArray<TSharedPtr<FJsonValue>> Messages;
		{
			TSharedPtr<FJsonObject> Sys = MakeShared<FJsonObject>();
			Sys->SetStringField(TEXT("role"), TEXT("system"));
			Sys->SetStringField(TEXT("content"), SystemPrompt);
			Messages.Add(MakeShared<FJsonValueObject>(Sys));
		}
		{
			TSharedPtr<FJsonObject> User = MakeShared<FJsonObject>();
			User->SetStringField(TEXT("role"), TEXT("user"));
			User->SetStringField(TEXT("content"), UserPrompt);
			Messages.Add(MakeShared<FJsonValueObject>(User));
		}
		BodyRef->SetArrayField(TEXT("messages"), Messages);

		TSharedPtr<FJsonObject> ResponseFormat = MakeShared<FJsonObject>();
		ResponseFormat->SetStringField(TEXT("type"), TEXT("json_object"));
		BodyRef->SetObjectField(TEXT("response_format"), ResponseFormat);

		if (!ApiKey.IsEmpty())
		{
			ExtraHeaders.Add(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *ApiKey));
		}
	}

	FString BodyText;
	{
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyText);
		FJsonSerializer::Serialize(BodyRef, Writer);
	}

	FHttpModule& Http = FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Req = Http.CreateRequest();
	Req->SetURL(EffectiveEndpoint);
	Req->SetVerb(TEXT("POST"));
	Req->SetHeader(TEXT("Content-Type"), ContentType);
	Req->SetHeader(TEXT("Accept"), TEXT("application/json"));
	Req->SetHeader(TEXT("User-Agent"), TEXT("VFXAgent/1.0 (UnrealEngine)"));
	for (const TPair<FString, FString>& KV : ExtraHeaders)
	{
		Req->SetHeader(KV.Key, KV.Value);
	}
	Req->SetContentAsString(BodyText);
	Req->SetTimeout(TimeoutSeconds);

	// Capture retry parameters in case we need to fall back from Responses API to Chat Completions
	const FString CapturedModel = Model;
	const FString CapturedApiKey = ApiKey;
	const float CapturedTimeout = TimeoutSeconds;
	const FString CapturedUserPrompt = UserPrompt;
	const FString CapturedSystemPrompt = SystemPrompt;

	const EVFXAgentLLMBackend EffectiveBackend = Backend;
	const bool bResponsesAPI = bUseResponsesAPI;
	Req->OnProcessRequestComplete().BindLambda([
		OnComplete,
		EffectiveBackend,
		bResponsesAPI,
		CapturedModel,
		CapturedApiKey,
		CapturedTimeout,
		CapturedUserPrompt,
		CapturedSystemPrompt
	](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded)
	{
		if (!bSucceeded || !Response.IsValid())
		{
			FString FirstError = BuildHttpFailureMessage(TEXT("RequestDirectorJson"), Request, Response);

			// If Responses API failed at connection level, retry with Chat Completions
			if (bResponsesAPI)
			{
				UE_LOG(LogVFXAgent, Warning, TEXT("Responses API connection failed, falling back to Chat Completions API. Error: %s"), *FirstError);

				// Build Chat Completions request
				FString FallbackEndpoint = TEXT("https://api.openai.com/v1/chat/completions");

				TSharedPtr<FJsonObject> FallbackBody = MakeShared<FJsonObject>();
				TSharedRef<FJsonObject> FallbackRef = FallbackBody.ToSharedRef();
				FallbackRef->SetStringField(TEXT("model"), CapturedModel.IsEmpty() ? TEXT("gpt-4o-mini") : CapturedModel);
				FallbackRef->SetNumberField(TEXT("max_completion_tokens"), 4096);

				TArray<TSharedPtr<FJsonValue>> Messages;
				{
					TSharedPtr<FJsonObject> Sys = MakeShared<FJsonObject>();
					Sys->SetStringField(TEXT("role"), TEXT("system"));
					Sys->SetStringField(TEXT("content"), CapturedSystemPrompt);
					Messages.Add(MakeShared<FJsonValueObject>(Sys));
				}
				{
					TSharedPtr<FJsonObject> User = MakeShared<FJsonObject>();
					User->SetStringField(TEXT("role"), TEXT("user"));
					User->SetStringField(TEXT("content"), CapturedUserPrompt);
					Messages.Add(MakeShared<FJsonValueObject>(User));
				}
				FallbackRef->SetArrayField(TEXT("messages"), Messages);

				TSharedPtr<FJsonObject> ResponseFormat = MakeShared<FJsonObject>();
				ResponseFormat->SetStringField(TEXT("type"), TEXT("json_object"));
				FallbackRef->SetObjectField(TEXT("response_format"), ResponseFormat);

				FString FallbackBodyText;
				{
					TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&FallbackBodyText);
					FJsonSerializer::Serialize(FallbackRef, Writer);
				}

				FHttpModule& FallbackHttp = FHttpModule::Get();
				TSharedRef<IHttpRequest, ESPMode::ThreadSafe> FallbackReq = FallbackHttp.CreateRequest();
				FallbackReq->SetURL(FallbackEndpoint);
				FallbackReq->SetVerb(TEXT("POST"));
				FallbackReq->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
				FallbackReq->SetHeader(TEXT("Accept"), TEXT("application/json"));
				FallbackReq->SetHeader(TEXT("User-Agent"), TEXT("VFXAgent/1.0 (UnrealEngine)"));
				if (!CapturedApiKey.IsEmpty())
				{
					FallbackReq->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *CapturedApiKey));
				}
				FallbackReq->SetContentAsString(FallbackBodyText);
				FallbackReq->SetTimeout(CapturedTimeout);

				FallbackReq->OnProcessRequestComplete().BindLambda([
					OnComplete, FirstError
				](FHttpRequestPtr FbReq, FHttpResponsePtr FbResp, bool bFbSucceeded)
				{
					if (!bFbSucceeded || !FbResp.IsValid())
					{
						FString FallbackError = BuildHttpFailureMessage(TEXT("ChatCompletions-Fallback"), FbReq, FbResp);
						OnComplete(false, FString(), FString::Printf(TEXT("Both Responses API and Chat Completions failed.\n  Responses API: %s\n  Chat Completions: %s"), *FirstError, *FallbackError));
						return;
					}

					const int32 FbCode = FbResp->GetResponseCode();
					const FString FbResponseText = FbResp->GetContentAsString();
					if (FbCode < 200 || FbCode >= 300)
					{
						OnComplete(false, FString(), FString::Printf(TEXT("Chat Completions fallback returned HTTP %d: %s"), FbCode, *FbResponseText.Left(800)));
						return;
					}

					TSharedPtr<FJsonObject> FbRoot;
					FString FbJsonError;
					if (!ParseJsonObject(FbResponseText, FbRoot, FbJsonError))
					{
						OnComplete(false, FString(), FString::Printf(TEXT("Fallback response is not JSON: %s"), *FbResponseText.Left(200)));
						return;
					}

					const TArray<TSharedPtr<FJsonValue>>* Choices = nullptr;
					if (!FbRoot->TryGetArrayField(TEXT("choices"), Choices) || !Choices || Choices->Num() == 0)
					{
						OnComplete(false, FString(), TEXT("Fallback response missing 'choices' array"));
						return;
					}

					TSharedPtr<FJsonObject> Choice0 = (*Choices)[0]->AsObject();
					if (!Choice0.IsValid())
					{
						OnComplete(false, FString(), TEXT("Fallback response choice[0] is not an object"));
						return;
					}

					const TSharedPtr<FJsonObject> Msg = Choice0->GetObjectField(TEXT("message"));
					if (!Msg.IsValid())
					{
						OnComplete(false, FString(), TEXT("Fallback response missing message object"));
						return;
					}

					FString Content;
					if (!Msg->TryGetStringField(TEXT("content"), Content))
					{
						OnComplete(false, FString(), TEXT("Fallback response missing message.content"));
						return;
					}

					UE_LOG(LogVFXAgent, Log, TEXT("Chat Completions fallback succeeded."));
					OnComplete(true, Content, FString());
				});

				if (!FallbackReq->ProcessRequest())
				{
					OnComplete(false, FString(), FString::Printf(TEXT("Responses API failed: %s. Fallback also failed to start."), *FirstError));
				}
				return;
			}

			OnComplete(false, FString(), FirstError);
			return;
		}

		const int32 Code = Response->GetResponseCode();
		const FString ResponseText = Response->GetContentAsString();
		if (Code < 200 || Code >= 300)
		{
			OnComplete(false, FString(), FString::Printf(TEXT("LLM returned HTTP %d: %s"), Code, *ResponseText.Left(800)));
			return;
		}

		TSharedPtr<FJsonObject> Root;
		FString JsonError;
		if (!ParseJsonObject(ResponseText, Root, JsonError))
		{
			OnComplete(false, FString(), FString::Printf(TEXT("LLM response is not JSON: %s"), *ResponseText.Left(200)));
			return;
		}

		FString OutJson;
		if (EffectiveBackend == EVFXAgentLLMBackend::OllamaGenerate)
		{
			FString Resp;
			if (!Root->TryGetStringField(TEXT("response"), Resp))
			{
				OnComplete(false, FString(), TEXT("Ollama response missing 'response' field"));
				return;
			}
			OutJson = Resp;
			OnComplete(true, OutJson, FString());
			return;
		}

		// Responses API: output[].content[].text
		if (bResponsesAPI)
		{
			FString ExtractError;
			if (!TryExtractResponsesAPIContent(Root, OutJson, ExtractError))
			{
				OnComplete(false, FString(), ExtractError);
				return;
			}
			OnComplete(true, OutJson, FString());
			return;
		}

		const TArray<TSharedPtr<FJsonValue>>* Choices = nullptr;
		if (!Root->TryGetArrayField(TEXT("choices"), Choices) || !Choices || Choices->Num() == 0)
		{
			OnComplete(false, FString(), TEXT("OpenAI response missing 'choices' array"));
			return;
		}

		TSharedPtr<FJsonObject> Choice0 = (*Choices)[0]->AsObject();
		if (!Choice0.IsValid())
		{
			OnComplete(false, FString(), TEXT("OpenAI response choice[0] is not an object"));
			return;
		}

		const TSharedPtr<FJsonObject> Msg = Choice0->GetObjectField(TEXT("message"));
		if (!Msg.IsValid())
		{
			OnComplete(false, FString(), TEXT("OpenAI response missing message object"));
			return;
		}

		FString Content;
		if (!Msg->TryGetStringField(TEXT("content"), Content))
		{
			OnComplete(false, FString(), TEXT("OpenAI response missing message.content"));
			return;
		}

		OutJson = Content;
		OnComplete(true, OutJson, FString());
	});

	if (!Req->ProcessRequest())
	{
		OnComplete(false, FString(), TEXT("Failed to start HTTP request"));
		return;
	}
}

void UHttpLLMProvider::RequestDirectorJsonAsync(const FString& UserPrompt, const FString& OptionalStyleRefs, FOnDirectorJsonComplete OnComplete) const
{
	FString Combined = UserPrompt;
	if (!OptionalStyleRefs.IsEmpty())
	{
		Combined += TEXT("\n\nStyleRefs:\n");
		Combined += OptionalStyleRefs;
	}
	RequestDirectorJsonInternalAsync(Combined, BuildDirectorSystemPrompt(), OnComplete);
}

void UHttpLLMProvider::RequestEffectSpecJsonAsync(const FString& UserPrompt, const FString& OptionalStyleRefs, FOnEffectSpecJsonComplete OnComplete) const
{
	FString Combined = UserPrompt;
	if (!OptionalStyleRefs.IsEmpty())
	{
		Combined += TEXT("\n\nStyleRefs:\n");
		Combined += OptionalStyleRefs;
	}
	const FString LogDir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("VFXAgent"), TEXT("Logs"));
	IFileManager::Get().MakeDirectory(*LogDir, true);
	FFileHelper::SaveStringToFile(Combined, *(FPaths::Combine(LogDir, TEXT("effectspec_request.txt"))));
	RequestDirectorJsonInternalAsync(Combined, BuildEffectSpecSystemPrompt(), OnComplete);
}

void UHttpLLMProvider::RequestDirectorRevisionJsonAsync(const FString& OriginalDirectorJson, const FString& ExecutionReportJson, FOnDirectorJsonComplete OnComplete) const
{
	const FString SystemPrompt = BuildDirectorRevisionPrompt(OriginalDirectorJson, ExecutionReportJson);
	RequestDirectorJsonInternalAsync(TEXT("Revise the plan using the execution report."), SystemPrompt, OnComplete);
}

bool UHttpLLMProvider::TryRequestRecipeJson(const FString& UserPrompt, FString& OutRecipeJson, FString& OutError) const
{
	bool bDone = false;
	bool bOk = false;
	FString RecipeJson;
	FString Error;

	RequestRecipeJsonAsync(UserPrompt, [
		&bDone,
		&bOk,
		&RecipeJson,
		&Error
	](bool bSuccess, const FString& InRecipeJson, const FString& InError)
	{
		bOk = bSuccess;
		RecipeJson = InRecipeJson;
		Error = InError;
		bDone = true;
	});

	// If called on the game thread, we tick the HTTP manager to avoid deadlocks.
	const double Start = FPlatformTime::Seconds();
	while (!bDone)
	{
		if ((FPlatformTime::Seconds() - Start) > TimeoutSeconds)
		{
			OutError = TEXT("HTTP request timed out");
			return false;
		}
		if (IsInGameThread())
		{
			FHttpModule::Get().GetHttpManager().Tick(0.01f);
		}
		FPlatformProcess::Sleep(0.01f);
	}

	if (!bOk)
	{
		OutError = Error.IsEmpty() ? TEXT("HTTP request failed") : Error;
		return false;
	}

	OutRecipeJson = RecipeJson;
	return true;
}

void UHttpLLMProvider::GenerateRecipeAsync(const FString& Prompt, FOnRecipeComplete OnComplete)
{
	ClearLastError();
	RequestRecipeJsonAsync(Prompt, [this, OnComplete](bool bSuccess, const FString& RecipeJson, const FString& Error)
	{
		if (!OnComplete)
		{
			return;
		}

		if (!bSuccess)
		{
			SetLastError(Error);
			OnComplete(FVFXRecipe(), Error);
			return;
		}

		FVFXRecipe Parsed;
		FString ParseError;
		if (!TryParseRecipeJson(RecipeJson, Parsed, ParseError))
		{
			SetLastError(ParseError);
			OnComplete(FVFXRecipe(), ParseError);
			return;
		}

		Parsed.Version = FMath::Max(1, Parsed.Version);
		OnComplete(Parsed, FString());
	});
}

void UHttpLLMProvider::RefineRecipeAsync(const FVFXRecipe& OldRecipe, const FString& RefinementPrompt, FOnRecipeComplete OnComplete)
{
	ClearLastError();
	FString OldJson;
	FJsonObjectConverter::UStructToJsonObjectString(OldRecipe, OldJson);

	const FString CombinedPrompt = FString::Printf(
		TEXT("Here is the current recipe JSON:\n%s\n\nRefinement request: %s\n\nReturn the FULL updated recipe JSON."),
		*OldJson,
		*RefinementPrompt);

	RequestRecipeJsonAsync(CombinedPrompt, [this, OnComplete, OldRecipe](bool bSuccess, const FString& RecipeJson, const FString& Error)
	{
		if (!OnComplete)
		{
			return;
		}

		if (!bSuccess)
		{
			SetLastError(Error);
			OnComplete(OldRecipe, Error);
			return;
		}

		FVFXRecipe Parsed;
		FString ParseError;
		if (!TryParseRecipeJson(RecipeJson, Parsed, ParseError))
		{
			SetLastError(ParseError);
			OnComplete(OldRecipe, ParseError);
			return;
		}

		Parsed.Version = OldRecipe.Version + 1;
		OnComplete(Parsed, FString());
	});
}

FVFXRecipe UHttpLLMProvider::GenerateRecipe(const FString& Prompt)
{
	ClearLastError();
	FString RecipeJson;
	FString Error;
	if (!TryRequestRecipeJson(Prompt, RecipeJson, Error))
	{
		UE_LOG(LogVFXAgent, Error, TEXT("HttpLLMProvider: GenerateRecipe failed: %s"), *Error);
		SetLastError(Error);
		return FVFXRecipe();
	}

	UE_LOG(LogVFXAgent, Log, TEXT("Received recipe JSON (%d chars): %s"), RecipeJson.Len(), *RecipeJson.Left(500));

	FVFXRecipe Parsed;
	if (!TryParseRecipeJson(RecipeJson, Parsed, Error))
	{
		UE_LOG(LogVFXAgent, Error, TEXT("HttpLLMProvider: Failed to parse recipe JSON: %s. Raw JSON (first 1000 chars): %s"), *Error, *RecipeJson.Left(1000));
		SetLastError(Error);
		return FVFXRecipe();
	}

	Parsed.Version = FMath::Max(1, Parsed.Version);
	UE_LOG(LogVFXAgent, Log, TEXT("Successfully generated recipe with %d emitters and %d materials"), 
		Parsed.Emitters.Num(), Parsed.Materials.Num());
	return Parsed;
}

FVFXRecipe UHttpLLMProvider::RefineRecipe(const FVFXRecipe& OldRecipe, const FString& RefinementPrompt)
{
	ClearLastError();
	// Simple refinement strategy: provide previous recipe as JSON and ask for an updated JSON.
	FString OldJson;
	FJsonObjectConverter::UStructToJsonObjectString(OldRecipe, OldJson);

	const FString CombinedPrompt = FString::Printf(
		TEXT("Here is the current recipe JSON:\n%s\n\nRefinement request: %s\n\nReturn the FULL updated recipe JSON."),
		*OldJson,
		*RefinementPrompt);

	FString RecipeJson;
	FString Error;
	if (!TryRequestRecipeJson(CombinedPrompt, RecipeJson, Error))
	{
		UE_LOG(LogVFXAgent, Error, TEXT("HttpLLMProvider: RefineRecipe failed: %s"), *Error);
		SetLastError(Error);
		return OldRecipe;
	}

	FVFXRecipe Parsed;
	if (!TryParseRecipeJson(RecipeJson, Parsed, Error))
	{
		UE_LOG(LogVFXAgent, Error, TEXT("HttpLLMProvider: Failed to parse refined recipe JSON: %s. Raw: %s"), *Error, *RecipeJson.Left(400));
		SetLastError(Error);
		return OldRecipe;
	}

	Parsed.Version = OldRecipe.Version + 1;
	return Parsed;
}

FString UHttpLLMProvider::BuildVisionUserPrompt(const FString& OptionalPrompt) const
{
	FString Prompt = TEXT(
		"Analyze the provided VFX reference image and infer a layered Niagara effect. "
		"Identify the main visual layers (core, sparks, smoke, trails, glow, shockwave, etc.) and map each layer to a separate emitter. "
		"Return ONLY the JSON object that matches the schema from the system prompt. Do not include any markdown or extra text."
	);

	if (!OptionalPrompt.IsEmpty())
	{
		Prompt += TEXT("\n\nUser guidance: ");
		Prompt += OptionalPrompt;
	}

#if WITH_EDITOR
	AppendMaterialLibraryNamesToPrompt(Prompt);
#endif

	return Prompt;
}

static FString GetImageMimeTypeFromExtension(const FString& ImageFilePath)
{
	FString Ext = FPaths::GetExtension(ImageFilePath).ToLower();
	if (Ext == TEXT("jpg") || Ext == TEXT("jpeg"))
	{
		return TEXT("image/jpeg");
	}
	if (Ext == TEXT("webp"))
	{
		return TEXT("image/webp");
	}
	// default
	return TEXT("image/png");
}

static FString NormalizeImageDataToDataUrl(const FString& ImageDataOrBase64, const FString& DefaultMimeType)
{
	if (ImageDataOrBase64.StartsWith(TEXT("data:")))
	{
		return ImageDataOrBase64;
	}
	const FString MimeType = DefaultMimeType.IsEmpty() ? TEXT("image/png") : DefaultMimeType;
	return FString::Printf(TEXT("data:%s;base64,%s"), *MimeType, *ImageDataOrBase64);
}

void UHttpLLMProvider::RequestRecipeJsonWithImageAsync(const FString& ImageFilePath, const FString& OptionalPrompt, FOnRecipeJsonComplete OnComplete) const
{
	LastRawRecipeJson.Reset();
	if (!OnComplete)
	{
		return;
	}

	if (Backend != EVFXAgentLLMBackend::OpenAIChatCompletions && Backend != EVFXAgentLLMBackend::OpenAIResponses)
	{
		OnComplete(false, FString(), TEXT("Image analysis is only supported on OpenAI-compatible chat completions backend."));
		return;
	}
	if (IsPlaceholderApiKey(ApiKey))
	{
		OnComplete(false, FString(), TEXT("OpenAI API key is missing or placeholder"));
		return;
	}

	FString EffectiveEndpoint = Endpoint;
	EffectiveEndpoint.TrimStartAndEndInline();
	if (EffectiveEndpoint.IsEmpty())
	{
		OnComplete(false, FString(), TEXT("LLM endpoint is empty"));
		return;
	}

	const bool bUseResponsesAPI = IsResponsesAPI(Backend, EffectiveEndpoint);

	TArray<uint8> ImageBytes;
	if (!FFileHelper::LoadFileToArray(ImageBytes, *ImageFilePath))
	{
		OnComplete(false, FString(), TEXT("Failed to read image file"));
		return;
	}

	const FString MimeType = GetImageMimeTypeFromExtension(ImageFilePath);
	const FString Base64 = FBase64::Encode(ImageBytes);
	const FString DataUrl = NormalizeImageDataToDataUrl(Base64, MimeType);

	TSharedPtr<FJsonObject> BodyObj = MakeShared<FJsonObject>();
	TSharedRef<FJsonObject> BodyRef = BodyObj.ToSharedRef();
	BodyRef->SetStringField(TEXT("model"), Model.IsEmpty() ? TEXT("gpt-4o-mini") : Model);

	if (bUseResponsesAPI)
	{
		// OpenAI Responses API format with image input.
		BodyRef->SetStringField(TEXT("instructions"), BuildSystemPrompt());

		TArray<TSharedPtr<FJsonValue>> InputArray;
		{
			TSharedPtr<FJsonObject> TextInput = MakeShared<FJsonObject>();
			TextInput->SetStringField(TEXT("type"), TEXT("message"));
			TextInput->SetStringField(TEXT("role"), TEXT("user"));
			TArray<TSharedPtr<FJsonValue>> ContentArr;
			{
				TSharedPtr<FJsonObject> TextPart = MakeShared<FJsonObject>();
				TextPart->SetStringField(TEXT("type"), TEXT("input_text"));
				TextPart->SetStringField(TEXT("text"), BuildVisionUserPrompt(OptionalPrompt));
				ContentArr.Add(MakeShared<FJsonValueObject>(TextPart));
			}
			{
				TSharedPtr<FJsonObject> ImagePart = MakeShared<FJsonObject>();
				ImagePart->SetStringField(TEXT("type"), TEXT("input_image"));
				ImagePart->SetStringField(TEXT("image_url"), DataUrl);
				ContentArr.Add(MakeShared<FJsonValueObject>(ImagePart));
			}
			TextInput->SetArrayField(TEXT("content"), ContentArr);
			InputArray.Add(MakeShared<FJsonValueObject>(TextInput));
		}
		BodyRef->SetArrayField(TEXT("input"), InputArray);

		TSharedPtr<FJsonObject> TextObj = MakeShared<FJsonObject>();
		TSharedPtr<FJsonObject> FormatObj = MakeShared<FJsonObject>();
		FormatObj->SetStringField(TEXT("type"), TEXT("json_object"));
		TextObj->SetObjectField(TEXT("format"), FormatObj);
		BodyRef->SetObjectField(TEXT("text"), TextObj);
	}
	else
	{
		BodyRef->SetNumberField(TEXT("max_completion_tokens"), 16384);

		TArray<TSharedPtr<FJsonValue>> Messages;
		{
			TSharedPtr<FJsonObject> Sys = MakeShared<FJsonObject>();
			Sys->SetStringField(TEXT("role"), TEXT("system"));
			Sys->SetStringField(TEXT("content"), BuildSystemPrompt());
			Messages.Add(MakeShared<FJsonValueObject>(Sys));
		}
		{
			TSharedPtr<FJsonObject> User = MakeShared<FJsonObject>();
			User->SetStringField(TEXT("role"), TEXT("user"));

			TArray<TSharedPtr<FJsonValue>> Content;
			{
				TSharedPtr<FJsonObject> TextObj = MakeShared<FJsonObject>();
				TextObj->SetStringField(TEXT("type"), TEXT("text"));
				TextObj->SetStringField(TEXT("text"), BuildVisionUserPrompt(OptionalPrompt));
				Content.Add(MakeShared<FJsonValueObject>(TextObj));
			}
			{
				TSharedPtr<FJsonObject> ImageUrlObj = MakeShared<FJsonObject>();
				ImageUrlObj->SetStringField(TEXT("type"), TEXT("image_url"));
				TSharedPtr<FJsonObject> ImageUrl = MakeShared<FJsonObject>();
				ImageUrl->SetStringField(TEXT("url"), DataUrl);
				ImageUrlObj->SetObjectField(TEXT("image_url"), ImageUrl);
				Content.Add(MakeShared<FJsonValueObject>(ImageUrlObj));
			}

			User->SetArrayField(TEXT("content"), Content);
			Messages.Add(MakeShared<FJsonValueObject>(User));
		}
		BodyRef->SetArrayField(TEXT("messages"), Messages);

		TSharedPtr<FJsonObject> ResponseFormat = MakeShared<FJsonObject>();
		ResponseFormat->SetStringField(TEXT("type"), TEXT("json_object"));
		BodyRef->SetObjectField(TEXT("response_format"), ResponseFormat);
	}

	FString BodyText;
	{
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyText);
		FJsonSerializer::Serialize(BodyRef, Writer);
	}

	FHttpModule& Http = FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Req = Http.CreateRequest();
	Req->SetURL(EffectiveEndpoint);
	Req->SetVerb(TEXT("POST"));
	Req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Req->SetHeader(TEXT("Accept"), TEXT("application/json"));
	Req->SetHeader(TEXT("User-Agent"), TEXT("VFXAgent/1.0 (UnrealEngine)"));
	if (!ApiKey.IsEmpty())
	{
		Req->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *ApiKey));
	}
	Req->SetContentAsString(BodyText);
	Req->SetTimeout(FMath::Max(TimeoutSeconds, 120.0f));

	const bool bResponsesAPI = bUseResponsesAPI;
	Req->OnProcessRequestComplete().BindLambda([
		this,
		OnComplete,
		bResponsesAPI
	](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded)
	{
		if (!bSucceeded || !Response.IsValid())
		{
			OnComplete(false, FString(), BuildHttpFailureMessage(TEXT("RequestRecipeJsonWithImage"), Request, Response));
			return;
		}

		const int32 Code = Response->GetResponseCode();
		const FString ResponseText = Response->GetContentAsString();
		if (Code < 200 || Code >= 300)
		{
			OnComplete(false, FString(), FString::Printf(TEXT("LLM returned HTTP %d: %s"), Code, *ResponseText.Left(800)));
			return;
		}

		TSharedPtr<FJsonObject> Root;
		FString JsonError;
		if (!ParseJsonObject(ResponseText, Root, JsonError))
		{
			OnComplete(false, FString(), FString::Printf(TEXT("LLM response is not JSON: %s"), *ResponseText.Left(200)));
			return;
		}

		// Responses API: output[].content[].text
		if (bResponsesAPI)
		{
			FString Content;
			FString ExtractError;
			if (!TryExtractResponsesAPIContent(Root, Content, ExtractError))
			{
				OnComplete(false, FString(), ExtractError);
				return;
			}
			LastRawRecipeJson = Content;
			OnComplete(true, Content, FString());
			return;
		}

		// OpenAI chat completions: choices[0].message.content
		const TArray<TSharedPtr<FJsonValue>>* Choices = nullptr;
		if (!Root->TryGetArrayField(TEXT("choices"), Choices) || !Choices || Choices->Num() == 0)
		{
			OnComplete(false, FString(), TEXT("OpenAI response missing 'choices' array"));
			return;
		}

		TSharedPtr<FJsonObject> Choice0 = (*Choices)[0]->AsObject();
		if (!Choice0.IsValid())
		{
			OnComplete(false, FString(), TEXT("OpenAI response choice[0] is not an object"));
			return;
		}

		const TSharedPtr<FJsonObject> Msg = Choice0->GetObjectField(TEXT("message"));
		if (!Msg.IsValid())
		{
			OnComplete(false, FString(), TEXT("OpenAI response missing message object"));
			return;
		}

		FString Content;
		if (!Msg->TryGetStringField(TEXT("content"), Content))
		{
			OnComplete(false, FString(), TEXT("OpenAI response missing message.content"));
			return;
		}

		LastRawRecipeJson = Content;

		OnComplete(true, Content, FString());
	});

	if (!Req->ProcessRequest())
	{
		OnComplete(false, FString(), TEXT("Failed to start HTTP request"));
		return;
	}
}

void UHttpLLMProvider::RequestRecipeJsonWithImageDataAsync(const FString& ImageDataOrBase64, const FString& OptionalPrompt, FOnRecipeJsonComplete OnComplete) const
{
	LastRawRecipeJson.Reset();
	if (!OnComplete)
	{
		return;
	}

	if (Backend != EVFXAgentLLMBackend::OpenAIChatCompletions && Backend != EVFXAgentLLMBackend::OpenAIResponses)
	{
		OnComplete(false, FString(), TEXT("Image analysis is only supported on OpenAI-compatible chat completions backend."));
		return;
	}
	if (IsPlaceholderApiKey(ApiKey))
	{
		OnComplete(false, FString(), TEXT("OpenAI API key is missing or placeholder"));
		return;
	}

	FString EffectiveEndpoint = Endpoint;
	EffectiveEndpoint.TrimStartAndEndInline();
	if (EffectiveEndpoint.IsEmpty())
	{
		OnComplete(false, FString(), TEXT("LLM endpoint is empty"));
		return;
	}

	if (ImageDataOrBase64.IsEmpty())
	{
		OnComplete(false, FString(), TEXT("Image data is empty"));
		return;
	}

	const bool bUseResponsesAPI = IsResponsesAPI(Backend, EffectiveEndpoint);
	const FString DataUrl = NormalizeImageDataToDataUrl(ImageDataOrBase64, TEXT("image/png"));

	TSharedPtr<FJsonObject> BodyObj = MakeShared<FJsonObject>();
	TSharedRef<FJsonObject> BodyRef = BodyObj.ToSharedRef();
	BodyRef->SetStringField(TEXT("model"), Model.IsEmpty() ? TEXT("gpt-4o-mini") : Model);

	if (bUseResponsesAPI)
	{
		// OpenAI Responses API format with image input.
		BodyRef->SetStringField(TEXT("instructions"), BuildSystemPrompt());

		TArray<TSharedPtr<FJsonValue>> InputArray;
		{
			TSharedPtr<FJsonObject> MsgInput = MakeShared<FJsonObject>();
			MsgInput->SetStringField(TEXT("type"), TEXT("message"));
			MsgInput->SetStringField(TEXT("role"), TEXT("user"));
			TArray<TSharedPtr<FJsonValue>> ContentArr;
			{
				TSharedPtr<FJsonObject> TextPart = MakeShared<FJsonObject>();
				TextPart->SetStringField(TEXT("type"), TEXT("input_text"));
				TextPart->SetStringField(TEXT("text"), BuildVisionUserPrompt(OptionalPrompt));
				ContentArr.Add(MakeShared<FJsonValueObject>(TextPart));
			}
			{
				TSharedPtr<FJsonObject> ImagePart = MakeShared<FJsonObject>();
				ImagePart->SetStringField(TEXT("type"), TEXT("input_image"));
				ImagePart->SetStringField(TEXT("image_url"), DataUrl);
				ContentArr.Add(MakeShared<FJsonValueObject>(ImagePart));
			}
			MsgInput->SetArrayField(TEXT("content"), ContentArr);
			InputArray.Add(MakeShared<FJsonValueObject>(MsgInput));
		}
		BodyRef->SetArrayField(TEXT("input"), InputArray);

		TSharedPtr<FJsonObject> TextObj = MakeShared<FJsonObject>();
		TSharedPtr<FJsonObject> FormatObj = MakeShared<FJsonObject>();
		FormatObj->SetStringField(TEXT("type"), TEXT("json_object"));
		TextObj->SetObjectField(TEXT("format"), FormatObj);
		BodyRef->SetObjectField(TEXT("text"), TextObj);
	}
	else
	{
		BodyRef->SetNumberField(TEXT("max_completion_tokens"), 4096);

		TArray<TSharedPtr<FJsonValue>> Messages;
		{
			TSharedPtr<FJsonObject> Sys = MakeShared<FJsonObject>();
			Sys->SetStringField(TEXT("role"), TEXT("system"));
			Sys->SetStringField(TEXT("content"), BuildSystemPrompt());
			Messages.Add(MakeShared<FJsonValueObject>(Sys));
		}
		{
			TSharedPtr<FJsonObject> User = MakeShared<FJsonObject>();
			User->SetStringField(TEXT("role"), TEXT("user"));

			TArray<TSharedPtr<FJsonValue>> Content;
			{
				TSharedPtr<FJsonObject> TextObj = MakeShared<FJsonObject>();
				TextObj->SetStringField(TEXT("type"), TEXT("text"));
				TextObj->SetStringField(TEXT("text"), BuildVisionUserPrompt(OptionalPrompt));
				Content.Add(MakeShared<FJsonValueObject>(TextObj));
			}
			{
				TSharedPtr<FJsonObject> ImageUrlObj = MakeShared<FJsonObject>();
				ImageUrlObj->SetStringField(TEXT("type"), TEXT("image_url"));
				TSharedPtr<FJsonObject> ImageUrl = MakeShared<FJsonObject>();
				ImageUrl->SetStringField(TEXT("url"), DataUrl);
				ImageUrlObj->SetObjectField(TEXT("image_url"), ImageUrl);
				Content.Add(MakeShared<FJsonValueObject>(ImageUrlObj));
			}

			User->SetArrayField(TEXT("content"), Content);
			Messages.Add(MakeShared<FJsonValueObject>(User));
		}
		BodyRef->SetArrayField(TEXT("messages"), Messages);

		TSharedPtr<FJsonObject> ResponseFormat = MakeShared<FJsonObject>();
		ResponseFormat->SetStringField(TEXT("type"), TEXT("json_object"));
		BodyRef->SetObjectField(TEXT("response_format"), ResponseFormat);
	}

	FString BodyText;
	{
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyText);
		FJsonSerializer::Serialize(BodyRef, Writer);
	}

	FHttpModule& Http = FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Req = Http.CreateRequest();
	Req->SetURL(EffectiveEndpoint);
	Req->SetVerb(TEXT("POST"));
	Req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Req->SetHeader(TEXT("Accept"), TEXT("application/json"));
	Req->SetHeader(TEXT("User-Agent"), TEXT("VFXAgent/1.0 (UnrealEngine)"));
	if (!ApiKey.IsEmpty())
	{
		Req->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *ApiKey));
	}
	Req->SetContentAsString(BodyText);
	Req->SetTimeout(FMath::Max(TimeoutSeconds, 120.0f));

	const bool bResponsesAPI = bUseResponsesAPI;
	Req->OnProcessRequestComplete().BindLambda([
		this,
		OnComplete,
		bResponsesAPI
	](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded)
	{
		if (!bSucceeded || !Response.IsValid())
		{
			OnComplete(false, FString(), BuildHttpFailureMessage(TEXT("RequestRecipeJsonWithImageData"), Request, Response));
			return;
		}

		const int32 Code = Response->GetResponseCode();
		const FString ResponseText = Response->GetContentAsString();
		if (Code < 200 || Code >= 300)
		{
			OnComplete(false, FString(), FString::Printf(TEXT("LLM returned HTTP %d: %s"), Code, *ResponseText.Left(800)));
			return;
		}

		TSharedPtr<FJsonObject> Root;
		FString JsonError;
		if (!ParseJsonObject(ResponseText, Root, JsonError))
		{
			OnComplete(false, FString(), FString::Printf(TEXT("LLM response is not JSON: %s"), *ResponseText.Left(200)));
			return;
		}

		// Responses API: output[].content[].text
		if (bResponsesAPI)
		{
			FString Content;
			FString ExtractError;
			if (!TryExtractResponsesAPIContent(Root, Content, ExtractError))
			{
				OnComplete(false, FString(), ExtractError);
				return;
			}
			LastRawRecipeJson = Content;
			OnComplete(true, Content, FString());
			return;
		}

		// OpenAI chat completions: choices[0].message.content
		const TArray<TSharedPtr<FJsonValue>>* Choices = nullptr;
		if (!Root->TryGetArrayField(TEXT("choices"), Choices) || !Choices || Choices->Num() == 0)
		{
			OnComplete(false, FString(), TEXT("OpenAI response missing 'choices' array"));
			return;
		}

		TSharedPtr<FJsonObject> Choice0 = (*Choices)[0]->AsObject();
		if (!Choice0.IsValid())
		{
			OnComplete(false, FString(), TEXT("OpenAI response choice[0] is not an object"));
			return;
		}

		const TSharedPtr<FJsonObject> Msg = Choice0->GetObjectField(TEXT("message"));
		if (!Msg.IsValid())
		{
			OnComplete(false, FString(), TEXT("OpenAI response missing message object"));
			return;
		}

		FString Content;
		if (!Msg->TryGetStringField(TEXT("content"), Content))
		{
			OnComplete(false, FString(), TEXT("OpenAI response missing message.content"));
			return;
		}

		LastRawRecipeJson = Content;

		OnComplete(true, Content, FString());
	});

	if (!Req->ProcessRequest())
	{
		OnComplete(false, FString(), TEXT("Failed to start HTTP request"));
		return;
	}
}

void UHttpLLMProvider::GenerateRecipeFromImageAsync(const FString& ImageFilePath, const FString& OptionalPrompt, FOnRecipeComplete OnComplete)
{
	ClearLastError();
	LastRawRecipeJson.Reset();
	RequestRecipeJsonWithImageAsync(ImageFilePath, OptionalPrompt, [this, OnComplete](bool bSuccess, const FString& RecipeJson, const FString& Error)
	{
		if (!OnComplete)
		{
			return;
		}

		if (!bSuccess)
		{
			SetLastError(Error);
			OnComplete(FVFXRecipe(), Error);
			return;
		}

		FVFXRecipe Parsed;
		FString ParseError;
		if (!TryParseRecipeJson(RecipeJson, Parsed, ParseError))
		{
			SetLastError(ParseError);
			OnComplete(FVFXRecipe(), ParseError);
			return;
		}

		Parsed.Version = FMath::Max(1, Parsed.Version);
		OnComplete(Parsed, FString());
	});
}

FVFXRecipe UHttpLLMProvider::GenerateRecipeFromRequest(const FVFXGenerationRequest& Request)
{
	ClearLastError();

	// If we have a reference image (path or base64), use vision-enabled generation
	if (!Request.ReferenceImageData.IsEmpty() || !Request.ReferenceImagePath.IsEmpty())
	{
		bool bDone = false;
		FVFXRecipe Result;
		FString Error;

		if (!Request.ReferenceImageData.IsEmpty())
		{
			RequestRecipeJsonWithImageDataAsync(Request.ReferenceImageData, Request.TextPrompt,
				[this, &bDone, &Result, &Error](bool bSuccess, const FString& RecipeJson, const FString& InError)
				{
					if (!bSuccess)
					{
						Error = InError;
						bDone = true;
						return;
					}

					FVFXRecipe Parsed;
					FString ParseError;
					if (!TryParseRecipeJson(RecipeJson, Parsed, ParseError))
					{
						Error = ParseError;
						bDone = true;
						return;
					}

					Parsed.Version = FMath::Max(1, Parsed.Version);
					Result = Parsed;
					bDone = true;
				});
		}
		else
		{
			GenerateRecipeFromImageAsync(Request.ReferenceImagePath, Request.TextPrompt,
				[&bDone, &Result, &Error](const FVFXRecipe& Recipe, const FString& InError)
				{
					Result = Recipe;
					Error = InError;
					bDone = true;
				});
		}

		// Wait for completion
		const double Start = FPlatformTime::Seconds();
		while (!bDone)
		{
			if ((FPlatformTime::Seconds() - Start) > TimeoutSeconds)
			{
				SetLastError(TEXT("Request timed out"));
				return FVFXRecipe();
			}
			if (IsInGameThread())
			{
				FHttpModule::Get().GetHttpManager().Tick(0.01f);
			}
			FPlatformProcess::Sleep(0.01f);
		}

		if (!Error.IsEmpty())
		{
			SetLastError(Error);
			return FVFXRecipe();
		}

		return Result;
	}

	// Otherwise use text-only generation
	FString EnhancedPrompt = Request.TextPrompt;
	if (!Request.AdditionalContext.IsEmpty())
	{
		EnhancedPrompt += TEXT("\n\nAdditional context: ") + Request.AdditionalContext;
	}

#if WITH_EDITOR
	if (Request.bGenerateMaterials)
	{
		AppendMaterialLibraryNamesToPrompt(EnhancedPrompt);
	}
#endif

	if (Request.bGenerateMaterials)
	{
		EnhancedPrompt += TEXT("\n\nPlease include custom materials with appropriate colors and properties.");
	}

	if (!Request.TargetStyle.IsEmpty() && Request.TargetStyle != TEXT("realistic"))
	{
		EnhancedPrompt += FString::Printf(TEXT("\n\nTarget style: %s"), *Request.TargetStyle);
	}

	return GenerateRecipe(EnhancedPrompt);
}

FString UHttpLLMProvider::AnalyzeReferenceImage(const FString& ImagePath)
{
	ClearLastError();

	bool bDone = false;
	FString Result;
	FString Error;

	RequestImageAnalysisAsync(ImagePath,
		[&bDone, &Result, &Error](bool bSuccess, const FString& Description, const FString& InError)
		{
			if (bSuccess)
			{
				Result = Description;
			}
			else
			{
				Error = InError;
			}
			bDone = true;
		});

	// Wait for completion
	const double Start = FPlatformTime::Seconds();
	while (!bDone)
	{
		if ((FPlatformTime::Seconds() - Start) > TimeoutSeconds)
		{
			SetLastError(TEXT("Image analysis timed out"));
			return TEXT("Analysis timed out");
		}
		if (IsInGameThread())
		{
			FHttpModule::Get().GetHttpManager().Tick(0.01f);
		}
		FPlatformProcess::Sleep(0.01f);
	}

	if (!Error.IsEmpty())
	{
		SetLastError(Error);
		return FString::Printf(TEXT("Error analyzing image: %s"), *Error);
	}

	return Result;
}

FString UHttpLLMProvider::CompareWithReference(
	const FVFXRecipe& GeneratedRecipe,
	const FString& ReferenceImagePath,
	const FString& OriginalPrompt)
{
	// Analyze the reference image
	FString ImageDescription = AnalyzeReferenceImage(ReferenceImagePath);
	
	if (ImageDescription.StartsWith(TEXT("Error")))
	{
		return ImageDescription;
	}

	// Generate feedback by comparing the recipe with image description
	FString RecipeJson;
	FJsonObjectConverter::UStructToJsonObjectString(GeneratedRecipe, RecipeJson);

	FString ComparisonPrompt = FString::Printf(
		TEXT("Compare this VFX recipe with the reference image description and provide improvement suggestions.\n\n")
		TEXT("Original request: %s\n\n")
		TEXT("Reference image shows: %s\n\n")
		TEXT("Current recipe: %s\n\n")
		TEXT("Provide specific suggestions to make the recipe match the reference image better."),
		*OriginalPrompt,
		*ImageDescription,
		*RecipeJson);

	// Use a simple text request for comparison feedback
	bool bDone = false;
	FString Feedback;

	RequestRecipeJsonAsync(ComparisonPrompt,
		[&bDone, &Feedback](bool bSuccess, const FString& Response, const FString& Error)
		{
			if (bSuccess)
			{
				Feedback = Response;
			}
			else
			{
				Feedback = FString::Printf(TEXT("Comparison failed: %s"), *Error);
			}
			bDone = true;
		});

	// Wait for completion
	const double Start = FPlatformTime::Seconds();
	while (!bDone)
	{
		if ((FPlatformTime::Seconds() - Start) > TimeoutSeconds)
		{
			return TEXT("Comparison timed out");
		}
		if (IsInGameThread())
		{
			FHttpModule::Get().GetHttpManager().Tick(0.01f);
		}
		FPlatformProcess::Sleep(0.01f);
	}

	return Feedback;
}

FString UHttpLLMProvider::BuildVisionSystemPrompt() const
{
	return TEXT(
		"You are a VFX expert analyzing images to create Niagara particle effects. "
		"When given an image showing a visual effect, describe it in detail including:\n"
		"- Overall effect type (explosion, magic, fire, electricity, etc.)\n"
		"- Number and types of visual layers\n"
		"- Colors and color transitions\n"
		"- Particle behavior (burst, continuous, trails, etc.)\n"
		"- Scale and intensity\n"
		"- Any special characteristics\n\n"
		"Then generate a complete VFX recipe JSON matching the FVFXRecipe schema.");
}

FString UHttpLLMProvider::BuildImageAnalysisPrompt() const
{
	return TEXT(
		"Analyze this image and describe the visual effect shown. Focus on:\n"
		"- Type of effect (explosion, fire, magic, smoke, etc.)\n"
		"- Visual layers and components\n"
		"- Color palette\n"
		"- Movement and behavior\n"
		"- Overall aesthetic and style\n"
		"Provide a detailed description suitable for recreating this effect.");
}

FString UHttpLLMProvider::EncodeImageToBase64(const FString& ImagePath) const
{
	TArray<uint8> FileData;
	if (!FFileHelper::LoadFileToArray(FileData, *ImagePath))
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to load image file: %s"), *ImagePath);
		return FString();
	}

	return FBase64::Encode(FileData);
}

void UHttpLLMProvider::RequestImageAnalysisAsync(
	const FString& ImagePath,
	TFunction<void(bool, const FString&, const FString&)> OnComplete) const
{
	if (!OnComplete)
	{
		return;
	}

	if (IsPlaceholderApiKey(ApiKey))
	{
		OnComplete(false, FString(), TEXT("OpenAI API key is missing or placeholder"));
		return;
	}

	FString ImageBase64 = EncodeImageToBase64(ImagePath);
	if (ImageBase64.IsEmpty())
	{
		OnComplete(false, FString(), TEXT("Failed to encode image"));
		return;
	}

	// Determine image type
	FString Extension = FPaths::GetExtension(ImagePath).ToLower();
	FString MimeType = TEXT("image/jpeg");
	if (Extension == TEXT("png"))
	{
		MimeType = TEXT("image/png");
	}
	else if (Extension == TEXT("webp"))
	{
		MimeType = TEXT("image/webp");
	}

	FString EffectiveEndpoint = Endpoint;
	EffectiveEndpoint.TrimStartAndEndInline();
	if (EffectiveEndpoint.IsEmpty())
	{
		OnComplete(false, FString(), TEXT("LLM endpoint is empty"));
		return;
	}

	// Build vision request
	const bool bUseResponsesAPI = IsResponsesAPI(Backend, EffectiveEndpoint);
	TSharedPtr<FJsonObject> BodyObj = MakeShared<FJsonObject>();
	BodyObj->SetStringField(TEXT("model"), Model.IsEmpty() ? TEXT("gpt-4o") : Model);

	const FString ImageDataUrl = FString::Printf(TEXT("data:%s;base64,%s"), *MimeType, *ImageBase64);

	if (bUseResponsesAPI)
	{
		// OpenAI Responses API format with image input.
		BodyObj->SetStringField(TEXT("instructions"), BuildImageAnalysisPrompt());

		TArray<TSharedPtr<FJsonValue>> InputArray;
		{
			TSharedPtr<FJsonObject> MsgInput = MakeShared<FJsonObject>();
			MsgInput->SetStringField(TEXT("type"), TEXT("message"));
			MsgInput->SetStringField(TEXT("role"), TEXT("user"));
			TArray<TSharedPtr<FJsonValue>> ContentArr;
			{
				TSharedPtr<FJsonObject> TextInput = MakeShared<FJsonObject>();
				TextInput->SetStringField(TEXT("type"), TEXT("input_text"));
				TextInput->SetStringField(TEXT("text"), TEXT("Please analyze this image."));
				ContentArr.Add(MakeShared<FJsonValueObject>(TextInput));
			}
			{
				TSharedPtr<FJsonObject> ImgInput = MakeShared<FJsonObject>();
				ImgInput->SetStringField(TEXT("type"), TEXT("input_image"));
				ImgInput->SetStringField(TEXT("image_url"), ImageDataUrl);
				ContentArr.Add(MakeShared<FJsonValueObject>(ImgInput));
			}
			MsgInput->SetArrayField(TEXT("content"), ContentArr);
			InputArray.Add(MakeShared<FJsonValueObject>(MsgInput));
		}
		BodyObj->SetArrayField(TEXT("input"), InputArray);
	}
	else
	{
		BodyObj->SetNumberField(TEXT("max_completion_tokens"), 4096);

		TArray<TSharedPtr<FJsonValue>> Messages;

		// User message with image
		TSharedPtr<FJsonObject> UserMsg = MakeShared<FJsonObject>();
		UserMsg->SetStringField(TEXT("role"), TEXT("user"));

		TArray<TSharedPtr<FJsonValue>> ContentArray;

		// Text part
		TSharedPtr<FJsonObject> TextPart = MakeShared<FJsonObject>();
		TextPart->SetStringField(TEXT("type"), TEXT("text"));
		TextPart->SetStringField(TEXT("text"), BuildImageAnalysisPrompt());
		ContentArray.Add(MakeShared<FJsonValueObject>(TextPart));

		// Image part
		TSharedPtr<FJsonObject> ImagePart = MakeShared<FJsonObject>();
		ImagePart->SetStringField(TEXT("type"), TEXT("image_url"));
		TSharedPtr<FJsonObject> ImageUrl = MakeShared<FJsonObject>();
		ImageUrl->SetStringField(TEXT("url"), ImageDataUrl);
		ImagePart->SetObjectField(TEXT("image_url"), ImageUrl);
		ContentArray.Add(MakeShared<FJsonValueObject>(ImagePart));

		UserMsg->SetArrayField(TEXT("content"), ContentArray);
		Messages.Add(MakeShared<FJsonValueObject>(UserMsg));

		BodyObj->SetArrayField(TEXT("messages"), Messages);
	}

	FString BodyText;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyText);
	FJsonSerializer::Serialize(BodyObj.ToSharedRef(), Writer);

	FHttpModule& Http = FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Req = Http.CreateRequest();
	Req->SetURL(EffectiveEndpoint);
	Req->SetVerb(TEXT("POST"));
	Req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Req->SetHeader(TEXT("Accept"), TEXT("application/json"));
	if (!ApiKey.IsEmpty())
	{
		Req->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *ApiKey));
	}
	Req->SetContentAsString(BodyText);
	Req->SetTimeout(FMath::Max(TimeoutSeconds, 120.0f));

	const bool bResponsesAPI = bUseResponsesAPI;
	Req->OnProcessRequestComplete().BindLambda([OnComplete, bResponsesAPI](
		FHttpRequestPtr Request,
		FHttpResponsePtr Response,
		bool bSucceeded)
	{
		if (!bSucceeded || !Response.IsValid())
		{
			OnComplete(false, FString(), BuildHttpFailureMessage(TEXT("RequestImageAnalysis"), Request, Response));
			return;
		}

		const int32 Code = Response->GetResponseCode();
		if (Code < 200 || Code >= 300)
		{
			OnComplete(false, FString(), FString::Printf(TEXT("HTTP %d: %s"),
				Code, *Response->GetContentAsString().Left(200)));
			return;
		}

		TSharedPtr<FJsonObject> Root;
		FString JsonError;
		if (!ParseJsonObject(Response->GetContentAsString(), Root, JsonError))
		{
			OnComplete(false, FString(), TEXT("Failed to parse response"));
			return;
		}

		// Responses API: output[].content[].text
		if (bResponsesAPI)
		{
			FString Content;
			FString ExtractError;
			if (!TryExtractResponsesAPIContent(Root, Content, ExtractError))
			{
				OnComplete(false, FString(), ExtractError);
				return;
			}
			OnComplete(true, Content, FString());
			return;
		}

		// Extract content from choices[0].message.content
		const TArray<TSharedPtr<FJsonValue>>* Choices = nullptr;
		if (!Root->TryGetArrayField(TEXT("choices"), Choices) || !Choices || Choices->Num() == 0)
		{
			OnComplete(false, FString(), TEXT("No choices in response"));
			return;
		}

		TSharedPtr<FJsonObject> Choice = (*Choices)[0]->AsObject();
		if (!Choice.IsValid())
		{
			OnComplete(false, FString(), TEXT("Invalid choice object"));
			return;
		}

		const TSharedPtr<FJsonObject> Message = Choice->GetObjectField(TEXT("message"));
		if (!Message.IsValid())
		{
			OnComplete(false, FString(), TEXT("No message in choice"));
			return;
		}

		FString Content;
		if (!Message->TryGetStringField(TEXT("content"), Content))
		{
			OnComplete(false, FString(), TEXT("No content in message"));
			return;
		}

		OnComplete(true, Content, FString());
	});

	if (!Req->ProcessRequest())
	{
		OnComplete(false, FString(), TEXT("Failed to start request"));
	}
}

void UHttpLLMProvider::AskAsync(const FString& Prompt, FOnAskComplete OnComplete) const
{
	// Just use the internal RequestDirectorJsonInternalAsync but with a generic system prompt
	FString SystemPrompt = TEXT("You are a helpful VFX assistant. Answer the user's question about Unreal Engine VFX, Niagara, or general VFX concepts.");
	
	RequestDirectorJsonInternalAsync(Prompt, SystemPrompt, [OnComplete](bool bSuccess, const FString& Response, const FString& Error)
	{
		OnComplete(bSuccess, Response, Error);
	});
}

// ---------------------------------------------------------------------------
// RequestPythonScriptAsync - Python-First VFX Generation (Architecture V3)
// Sends a plain-text (no response_format:json_object) request so the LLM
// can return raw executable UE5 Python. Pass result to FVFXPythonExecutor.
// ---------------------------------------------------------------------------
void UHttpLLMProvider::RequestPythonScriptAsync(const FString& UserPrompt, FOnPythonScriptComplete OnComplete) const
{
	if (!OnComplete)
	{
		return;
	}

	FString EffectiveEndpoint = Endpoint;
	EffectiveEndpoint.TrimStartAndEndInline();
	if (EffectiveEndpoint.IsEmpty())
	{
		OnComplete(false, FString(), TEXT("LLM endpoint is empty"));
		return;
	}

	const bool bOpenAIBackend = (Backend == EVFXAgentLLMBackend::OpenAIChatCompletions || Backend == EVFXAgentLLMBackend::OpenAIResponses);
	if (bOpenAIBackend && IsPlaceholderApiKey(ApiKey))
	{
		OnComplete(false, FString(), TEXT("OpenAI API key is missing or placeholder"));
		return;
	}

	const FString SystemPrompt = BuildSystemPrompt();
	const bool bUseResponsesAPI = IsResponsesAPI(Backend, EffectiveEndpoint);

	TSharedPtr<FJsonObject> BodyObj = MakeShared<FJsonObject>();
	TSharedRef<FJsonObject> BodyRef = BodyObj.ToSharedRef();
	TMap<FString, FString> ExtraHeaders;

	if (Backend == EVFXAgentLLMBackend::OllamaGenerate)
	{
		BodyRef->SetStringField(TEXT("model"), Model.IsEmpty() ? TEXT("llama2") : Model);
		BodyRef->SetStringField(TEXT("prompt"), SystemPrompt + TEXT("\n\nUSER_PROMPT:\n") + UserPrompt);
		BodyRef->SetBoolField(TEXT("stream"), false);
	}
	else if (bUseResponsesAPI)
	{
		// Responses API — plain text output (no text.format.type=json_object)
		BodyRef->SetStringField(TEXT("model"), Model.IsEmpty() ? TEXT("gpt-4o-mini") : Model);
		BodyRef->SetStringField(TEXT("instructions"), SystemPrompt);
		BodyRef->SetStringField(TEXT("input"), UserPrompt);
		if (!ApiKey.IsEmpty())
		{
			ExtraHeaders.Add(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *ApiKey));
		}
	}
	else
	{
		// Chat Completions — plain text output (NO response_format:json_object)
		BodyRef->SetStringField(TEXT("model"), Model.IsEmpty() ? TEXT("gpt-4o-mini") : Model);
		BodyRef->SetNumberField(TEXT("max_completion_tokens"), 4096);

		TArray<TSharedPtr<FJsonValue>> Messages;
		{
			TSharedPtr<FJsonObject> Sys = MakeShared<FJsonObject>();
			Sys->SetStringField(TEXT("role"), TEXT("system"));
			Sys->SetStringField(TEXT("content"), SystemPrompt);
			Messages.Add(MakeShared<FJsonValueObject>(Sys));
		}
		{
			TSharedPtr<FJsonObject> User = MakeShared<FJsonObject>();
			User->SetStringField(TEXT("role"), TEXT("user"));
			User->SetStringField(TEXT("content"), UserPrompt);
			Messages.Add(MakeShared<FJsonValueObject>(User));
		}
		BodyRef->SetArrayField(TEXT("messages"), Messages);
		// Intentionally omitting response_format — Python output is plain text, not JSON.

		if (!ApiKey.IsEmpty())
		{
			ExtraHeaders.Add(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *ApiKey));
		}
	}

	FString BodyText;
	{
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyText);
		FJsonSerializer::Serialize(BodyRef, Writer);
	}

	FHttpModule& Http = FHttpModule::Get();
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Req = Http.CreateRequest();
	Req->SetURL(EffectiveEndpoint);
	Req->SetVerb(TEXT("POST"));
	Req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Req->SetHeader(TEXT("Accept"), TEXT("application/json"));
	Req->SetHeader(TEXT("User-Agent"), TEXT("VFXAgent/1.0 (UnrealEngine)"));
	for (const TPair<FString, FString>& KV : ExtraHeaders)
	{
		Req->SetHeader(KV.Key, KV.Value);
	}
	Req->SetContentAsString(BodyText);
	Req->SetTimeout(TimeoutSeconds);

	const bool bResponsesAPI = bUseResponsesAPI;
	Req->OnProcessRequestComplete().BindLambda([OnComplete, bResponsesAPI]
		(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded)
	{
		if (!bSucceeded || !Response.IsValid())
		{
			FString Err = BuildHttpFailureMessage(TEXT("RequestPythonScriptAsync"), Request, Response);
			OnComplete(false, FString(), Err);
			return;
		}

		const int32 Code = Response->GetResponseCode();
		const FString ResponseText = Response->GetContentAsString();

		if (Code < 200 || Code >= 300)
		{
			OnComplete(false, FString(), FString::Printf(TEXT("LLM returned HTTP %d: %s"), Code, *ResponseText.Left(800)));
			return;
		}

		TSharedPtr<FJsonObject> Root;
		FString JsonErr;
		if (!ParseJsonObject(ResponseText, Root, JsonErr))
		{
			// The model may have returned plain text directly (some local backends).
			// Treat the whole response as the script.
			OnComplete(true, ResponseText, FString());
			return;
		}

		FString Content;

		// OpenAI Responses API: output[0].content[0].text
		if (bResponsesAPI)
		{
			const TArray<TSharedPtr<FJsonValue>>* OutputArr = nullptr;
			if (Root->TryGetArrayField(TEXT("output"), OutputArr) && OutputArr && OutputArr->Num() > 0)
			{
				TSharedPtr<FJsonObject> Out0 = (*OutputArr)[0]->AsObject();
				if (Out0.IsValid())
				{
					const TArray<TSharedPtr<FJsonValue>>* ContentArr = nullptr;
					if (Out0->TryGetArrayField(TEXT("content"), ContentArr) && ContentArr && ContentArr->Num() > 0)
					{
						TSharedPtr<FJsonObject> C0 = (*ContentArr)[0]->AsObject();
						if (C0.IsValid())
						{
							C0->TryGetStringField(TEXT("text"), Content);
						}
					}
				}
			}
		}
		else
		{
			// Chat Completions: choices[0].message.content
			const TArray<TSharedPtr<FJsonValue>>* Choices = nullptr;
			if (Root->TryGetArrayField(TEXT("choices"), Choices) && Choices && Choices->Num() > 0)
			{
				TSharedPtr<FJsonObject> Choice0 = (*Choices)[0]->AsObject();
				if (Choice0.IsValid())
				{
					TSharedPtr<FJsonObject> Msg = Choice0->GetObjectField(TEXT("message"));
					if (Msg.IsValid())
					{
						Msg->TryGetStringField(TEXT("content"), Content);
					}
				}
			}
		}

		if (Content.IsEmpty())
		{
			OnComplete(false, FString(), FString::Printf(TEXT("Could not extract content from LLM response: %s"), *ResponseText.Left(400)));
			return;
		}

		OnComplete(true, Content, FString());
	});

	Req->ProcessRequest();
}

