#include "HttpLLMProvider.h"
#include "VFXAgentLog.h"

#include "Dom/JsonObject.h"
#include "JsonObjectConverter.h"
#include "Misc/DateTime.h"
#include "Misc/ScopeLock.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/Base64.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

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
	Model = InModel;
	ApiKey = InApiKey;
	TimeoutSeconds = FMath::Max(1.0f, InTimeoutSeconds);
}

FString UHttpLLMProvider::BuildSystemPrompt() const
{
	// Keep this strict: model must output JSON only.
	return TEXT(
		"You are a Niagara VFX recipe generator. Output MUST be a single JSON object and nothing else. "
		"The JSON must match this schema:\n"
		"{\n"
		"  \"version\": 1,\n"
		"  \"bLoop\": true,\n"
		"  \"duration\": 0.0,\n"
		"  \"warmupTime\": 0.0,\n"
		"  \"bounds\": {\"x\":100,\"y\":100,\"z\":100},\n"
		"  \"emitters\": [\n"
		"    {\"name\":\"Core\",\"spawnRate\":10,\"burstCount\":0,\"rendererType\":\"Sprite\",\"templateName\":\"Fountain\",\"color\":{\"r\":1,\"g\":1,\"b\":1,\"a\":1},\"lifetime\":5,\"size\":10,\"velocity\":{\"x\":0,\"y\":0,\"z\":100}}\n"
		"  ],\n"
		"  \"parameters\": {\"Color\":\"Blue\", \"Intensity\":\"1.0\"},\n"
		"  \"materials\": [{\"description\":\"Basic additive material\",\"bIsAdditive\":true,\"baseMaterialPath\":\"/Engine/EngineMaterials/ParticleSpriteMaterial\"}],\n"
		"  \"dependencies\": []\n"
		"}\n"
		"Rules:\n"
		"- rendererType must be one of Sprite|Ribbon|Mesh.\n"
		"- templateName should be one of: 'Fountain', 'DirectionalBurst', 'OmnidirectionalBurst', 'HangingParticulates', 'UpwardMeshBurst', 'Beam'. Default to 'Fountain' if unsure.\n"
		"- IMPORTANT: Generate a layered Niagara system by using MULTIPLE emitters unless the user explicitly asks for a single emitter.\n"
		"- Choose the number of emitters based on the prompt's layers (usually 2-6, sometimes up to 8 for complex effects). Do NOT always output exactly 3.\n"
		"- Each emitter should represent ONE layer/purpose and should set a meaningful 'name' (e.g. CoreBurst, Sparks, Smoke, Shockwave, Trails, Glows) and select the appropriate templateName.\n"
		"- Split layers into separate emitters, e.g.:\n"
		"  explosion: core burst (Sprite, OmnidirectionalBurst), sparks (Sprite, DirectionalBurst), smoke (Sprite, Fountain), shockwave (Ribbon, Omni).\n"
		"  magic/electric: arcs (Ribbon, Beam), glow particles (Sprite, HangingParticulates), secondary smoke/dust (Sprite, Fountain).\n"
		"  fire: flames (Sprite), embers (Sprite), smoke (Sprite).\n"
		"- size: particle size in world units (1-100 typical). Adjust based on effect scale.\n"
		"- velocity: {x,y,z} direction and speed of particles. Positive z is up. Use values like 50-500 for typical effects.\n"
		"- spawnRate: particles per second (10-200 typical for continuous, 0 if using burstCount).\n"
		"- burstCount: number of particles to spawn instantly (0 for continuous, 10-500 for bursts).\n"
		"- lifetime: how long each particle lives in seconds (0.5-10 typical).\n"
		"- color: RGBA values (0-1 range). Use appropriate colors for the effect (e.g. orange/red for fire, blue for electricity).\n"
		"- Use numeric values in sensible ranges and ensure emitters array length reflects the layers."
	);
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
	// Try direct struct conversion first.
	if (FJsonObjectConverter::JsonObjectStringToUStruct(RecipeJson, &OutRecipe, 0, 0))
	{
		return true;
	}

	// Fallback: sometimes models wrap the payload under a key.
	TSharedPtr<FJsonObject> Root;
	if (!ParseJsonObject(RecipeJson, Root, OutError))
	{
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
			return true;
		}
	}

	OutError = TEXT("JSON did not match FVFXRecipe schema");
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
	if (EffectiveEndpoint.IsEmpty())
	{
		OnComplete(false, FString(), TEXT("LLM endpoint is empty"));
		return;
	}

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
	else
	{
		// OpenAI-compatible chat completions.
		BodyRef->SetStringField(TEXT("model"), Model.IsEmpty() ? TEXT("gpt-4o-mini") : Model);
		BodyRef->SetNumberField(TEXT("temperature"), 0.2);
		BodyRef->SetNumberField(TEXT("max_tokens"), 800);

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
	Req->OnProcessRequestComplete().BindLambda([
		OnComplete,
		EffectiveBackend
	](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded)
	{
		if (!bSucceeded || !Response.IsValid())
		{
			const FString StatusStr = Request.IsValid() ? HttpRequestStatusToString(Request->GetStatus()) : TEXT("<null>");
			OnComplete(false, FString(), FString::Printf(TEXT("HTTP request failed (status=%s)"), *StatusStr));
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

	if (!Req->ProcessRequest())
	{
		OnComplete(false, FString(), TEXT("Failed to start HTTP request"));
		return;
	}
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

	FVFXRecipe Parsed;
	if (!TryParseRecipeJson(RecipeJson, Parsed, Error))
	{
		UE_LOG(LogVFXAgent, Error, TEXT("HttpLLMProvider: Failed to parse recipe JSON: %s. Raw: %s"), *Error, *RecipeJson.Left(400));
		SetLastError(Error);
		return FVFXRecipe();
	}

	Parsed.Version = FMath::Max(1, Parsed.Version);
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

void UHttpLLMProvider::RequestRecipeJsonWithImageAsync(const FString& ImageFilePath, const FString& OptionalPrompt, FOnRecipeJsonComplete OnComplete) const
{
	LastRawRecipeJson.Reset();
	if (!OnComplete)
	{
		return;
	}

	if (Backend != EVFXAgentLLMBackend::OpenAIChatCompletions)
	{
		OnComplete(false, FString(), TEXT("Image analysis is only supported on OpenAI-compatible chat completions backend."));
		return;
	}

	FString EffectiveEndpoint = Endpoint;
	if (EffectiveEndpoint.IsEmpty())
	{
		OnComplete(false, FString(), TEXT("LLM endpoint is empty"));
		return;
	}

	TArray<uint8> ImageBytes;
	if (!FFileHelper::LoadFileToArray(ImageBytes, *ImageFilePath))
	{
		OnComplete(false, FString(), TEXT("Failed to read image file"));
		return;
	}

	const FString MimeType = GetImageMimeTypeFromExtension(ImageFilePath);
	const FString Base64 = FBase64::Encode(ImageBytes);
	const FString DataUrl = FString::Printf(TEXT("data:%s;base64,%s"), *MimeType, *Base64);

	TSharedPtr<FJsonObject> BodyObj = MakeShared<FJsonObject>();
	TSharedRef<FJsonObject> BodyRef = BodyObj.ToSharedRef();
	BodyRef->SetStringField(TEXT("model"), Model.IsEmpty() ? TEXT("gpt-4o-mini") : Model);
	BodyRef->SetNumberField(TEXT("temperature"), 0.2);
	BodyRef->SetNumberField(TEXT("max_tokens"), 900);

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

	// Best-effort strict JSON response (supported by many OpenAI-compatible endpoints).
	TSharedPtr<FJsonObject> ResponseFormat = MakeShared<FJsonObject>();
	ResponseFormat->SetStringField(TEXT("type"), TEXT("json_object"));
	BodyRef->SetObjectField(TEXT("response_format"), ResponseFormat);

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
	Req->SetTimeout(TimeoutSeconds);

	Req->OnProcessRequestComplete().BindLambda([
		this,
		OnComplete
	](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded)
	{
		if (!bSucceeded || !Response.IsValid())
		{
			const FString StatusStr = Request.IsValid() ? HttpRequestStatusToString(Request->GetStatus()) : TEXT("<null>");
			OnComplete(false, FString(), FString::Printf(TEXT("HTTP request failed (status=%s)"), *StatusStr));
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