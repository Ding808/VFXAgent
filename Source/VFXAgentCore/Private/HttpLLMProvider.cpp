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

FString UHttpLLMProvider::BuildSystemPrompt() const
{
	return TEXT(
		"=== YOU ARE A VFX DIRECTOR, NOT A NIAGARA PROGRAMMER ===\n\n"
		"Your task is NOT to generate random Niagara parameters.\n"
		"Your task is to UNDERSTAND what the user is asking for, and describe it structurally.\n\n"
		"STAGE 1: SEMANTIC ANALYSIS (Director's Brain)\n"
		"---\n"
		"First, analyze the requested effect and output a VFX Intent JSON.\n"
		"This describes WHAT the effect should be, not HOW to build it.\n\n"
		"VFX INTENT SCHEMA (output this first!):\n"
		"{\n"
		"  \"intent\": {\n"
		"    \"archetype\": \"Tornado|Explosion|Fire|Smoke|Aura|Trail|Beam|Dust|Sparks|Impact|Custom\",\n"
		"    \"motion\": {\n"
		"      \"primaryModel\": \"Radial|RadialInward|Orbit|Vortex|Directional|Vertical|Turbulent|Static\",\n"
		"      \"motionAxis\": {\"x\": 0, \"y\": 0, \"z\": 1},\n"
		"      \"bRadiusDependsOnHeight\": false,\n"
		"      \"bAngularVelocityIncreases\": false,\n"
		"      \"bCentripetal\": false,\n"
		"      \"bHeightDriven\": false\n"
		"    },\n"
		"    \"hierarchy\": {\n"
		"      \"dominantElement\": \"what is the main visual part?\",\n"
		"      \"secondaryElements\": [\"supporting elements\"]\n"
		"    },\n"
		"    \"avoidance\": {\n"
		"      \"bAvoidConeVelocity\": false,\n"
		"      \"bAvoidRadialExplosion\": false,\n"
		"      \"bAvoidUniformGravity\": false,\n"
		"      \"bAvoidUniformRotation\": false\n"
		"    },\n"
		"    \"requiredLayers\": [\"core\", \"secondary\"],\n"
		"    \"requiredForces\": [\"vortex\", \"centripetal\", \"lift\"],\n"
		"    \"suggestedEmitterCount\": 3,\n"
		"    \"description\": \"Brief VFX analysis\"\n"
		"  },\n"
		"  \"emitters\": [...]\n"
		"}\n\n"
		"ARCHETYPE UNDERSTANDING (Critical!):\n"
		"---\n"
		"TORNADO:\n"
		"  - Motion: VORTEX rotating around vertical axis\n"
		"  - MUST: bCentripetal=true, bAngularVelocityIncreases=true\n"
		"  - MUST AVOID: Radial outward velocity, cone spray, uniform gravity down\n"
		"  - Layers: 3 minimum (core_funnel, debris, dust)\n"
		"  - Forces: Vortex, Centripetal attraction, Vertical lift\n"
		"  - 100% WRONG if it looks like radial burst + gravity\n\n"
		"EXPLOSION:\n"
		"  - Motion: RADIAL outward from center\n"
		"  - Forces: Radial velocity, gravity, drag\n"
		"  - AVOID: Inward motion, orbit, vortex\n"
		"  - Layers: 2-4 (core, secondary, debris, smoke)\n\n"
		"FIRE:\n"
		"  - Motion: VERTICAL upward (not radial)\n"
		"  - Forces: Upward lift, drag, turbulence\n"
		"  - AVOID: Downward gravity, cone outward\n"
		"  - Requires color gradient: orange/yellow → red → smoke\n\n"
		"AURA/ORBIT:\n"
		"  - Motion: ORBIT or Directional floating\n"
		"  - Forces: No gravity, circular motion\n"
		"  - AVOID: Gravity, cone spray\n"
		"  - Style: Magical, ethereal, no impact\n\n"
		"STAGE 2: NIAGARA RECIPE (After intent is defined)\n"
		"---\n"
		"THEN create the Niagara recipe matching the intent.\n"
		"Reference the intent fields to guide parameter selection.\n\n"
		"EMITTER RECIPE SCHEMA:\n"
		"  - name: Layer role (\"core_funnel\", \"debris\", \"dust\")\n"
		"  - rendererType: \"Sprite\", \"Ribbon\", \"Mesh\"\n"
		"  - templateName: \"Fountain\", \"DirectionalBurst\", \"OmnidirectionalBurst\", \"Beam\"\n"
		"  - spawnRate / burstCount: Spawn behavior\n"
		"  - velocity, acceleration: Movement\n"
		"  - drag: Air resistance\n"
		"  - size, lifetime: Particle properties\n"
		"  - color, emissiveStrength: Appearance\n\n"
		"FORCE GUIDELINES (based on archetype):\n"
		"---\n"
		"For TORNADO (archetype: tornado):\n"
		"  - Do NOT use: AddVelocityCone outward\n"
		"  - DO use: Orbit/Vortex around Z-axis\n"
		"  - DO use: Centripetal force toward axis\n"
		"  - DO use: Height-dependent parameters\n"
		"  - DO use: Multiple emitters (3+) for visual complexity\n\n"
		"For EXPLOSION (archetype: explosion):\n"
		"  - DO use: Radial velocity outward\n"
		"  - DO use: Gravity or drag\n"
		"  - DO use: Color gradient core→darker\n\n"
		"For FIRE (archetype: fire):\n"
		"  - DO use: Upward velocity\n"
		"  - DO use: Drag to slow particles\n"
		"  - DO use: Color gradient orange→red→black\n"
		"  - DO NOT use: Heavy gravity downward\n\n"
		"=== EMITTER PARAMETERS GUIDE ===\n"
		"SPAWN:\n"
		"- spawnRate: particles/sec (10-500). Use 0 if using burstCount.\n"
		"- burstCount: instant spawn count (10-500 for bursts, 0 for continuous).\n"
		"- burstTime: when to trigger burst in seconds (0=start).\n\n"
		"VELOCITY & FORCES:\n"
		"- velocity: Initial velocity vector {x,y,z}. Z+ is up.\n"
		"- velocityVariation: Random variation 0-1.\n"
		"- acceleration: Constant force {x,y,z}. Use {0,0,-980} for gravity.\n"
		"- drag: Air resistance 0-10 (0=none, 1=realistic, 5=heavy).\n\n"
		"LIFETIME & SIZE:\n"
		"- lifetime: Particle lifespan in seconds (0.5-10).\n"
		"- lifetimeVariation: Random variation 0-1.\n"
		"- size: Initial size in world units (5-100).\n"
		"- sizeEnd: Final size (set bUseSizeOverLife=true).\n"
		"- bUseSizeOverLife: Animate size over lifetime.\n"
		"- sizeVariation: Random size variation 0-1.\n\n"
		"COLOR:\n"
		"- color: Start color RGBA (0-1).\n"
		"- colorEnd: End color for gradient.\n"
		"- bUseColorGradient: Animate from color to colorEnd.\n\n"
		"ROTATION:\n"
		"- initialRotation: Starting rotation degrees.\n"
		"- rotationRate: Spin speed degrees/sec.\n"
		"- rotationRateVariation: Random variation 0-1.\n\n"
		"SHAPE & MATERIAL:\n"
		"- emitShape: \"Point\", \"Sphere\", \"Box\", \"Cone\", \"Cylinder\".\n"
		"- shapeSize: Size/radius {x,y,z}.\n"
		"- materialIndex: Material reference (-1 for default).\n\n"
		"MATERIAL GENERATION GUIDE:\n"
		"---\n"
		"Create materials tailored to effect archetype!\n"
		"- name: Descriptive (\"TornadoCoreMaterial\", \"FireCoreMaterial\").\n"
		"- bIsAdditive: true for glow (fire, magic), false for solid.\n"
		"- bIsUnlit: true for self-lit (most VFX).\n"
		"- emissiveColor: Glow color RGB.\n"
		"- emissiveStrength: Glow intensity (1-10, use 2-5 for visible effect).\n"
		"- opacity: Transparency 0-1 (0.5-0.8 typical).\n"
		"- generatedTextures: Custom textures (Gradient, Noise, Perlin).\n\n"
		"GENERATION RULES:\n"
		"---\n"
		"1. Output BOTH intent and recipe JSON\n"
		"2. Match recipe parameters to intent.archetype\n"
		"3. For tornado specifically: 3 emitters (core_funnel, debris, dust)\n"
		"4. Apply archetype-specific avoidances\n"
		"5. Use realistic, physically-plausible parameters\n"
		"6. Add variation (0.2-0.5) for organic look\n"
		"7. Create custom materials for visual quality\n\n"
		"OUTPUT FORMAT:\n"
		"---\n"
		"Output a COMPLETE JSON with both intent and recipe:\n"
		"{\n"
		"  \"intent\": { ... VFX Intent structure ... },\n"
		"  \"version\": 1,\n"
		"  \"bLoop\": true,\n"
		"  \"duration\": 0.0,\n"
		"  \"warmupTime\": 0.0,\n"
		"  \"bounds\": {\"x\": 100, \"y\": 100, \"z\": 100},\n"
		"  \"emitters\": [ ... ],\n"
		"  \"materials\": [ ... ]\n"
		"}\n\n"
		"OUTPUT ONLY THE JSON. NO MARKDOWN, NO EXPLANATIONS, NO CODE BLOCKS."
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

	const bool bOpenAIBackend = (Backend == EVFXAgentLLMBackend::OpenAIChatCompletions);
	if (bOpenAIBackend && IsPlaceholderApiKey(ApiKey))
	{
		OnComplete(false, FString(), TEXT("OpenAI API key is missing or placeholder"));
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
		BodyRef->SetNumberField(TEXT("max_tokens"), 4096);  // Keep within typical provider limits

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
			const FString UrlStr = Request.IsValid() ? Request->GetURL() : TEXT("<null>");
			UE_LOG(LogVFXAgent, Error, TEXT("HTTP request failed. Status=%s URL=%s"), *StatusStr, *UrlStr);
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

	const bool bOpenAIBackend = (Backend == EVFXAgentLLMBackend::OpenAIChatCompletions);
	if (bOpenAIBackend && IsPlaceholderApiKey(ApiKey))
	{
		OnComplete(false, FString(), TEXT("OpenAI API key is missing or placeholder"));
		return;
	}

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
	else
	{
		BodyRef->SetStringField(TEXT("model"), Model.IsEmpty() ? TEXT("gpt-4o-mini") : Model);
		BodyRef->SetNumberField(TEXT("temperature"), 0.1);
		BodyRef->SetNumberField(TEXT("max_tokens"), 4096);

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

	const EVFXAgentLLMBackend EffectiveBackend = Backend;
	Req->OnProcessRequestComplete().BindLambda([
		OnComplete,
		EffectiveBackend
	](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded)
	{
		if (!bSucceeded || !Response.IsValid())
		{
			const FString StatusStr = Request.IsValid() ? HttpRequestStatusToString(Request->GetStatus()) : TEXT("<null>");
			const FString UrlStr = Request.IsValid() ? Request->GetURL() : TEXT("<null>");
			UE_LOG(LogVFXAgent, Error, TEXT("HTTP request failed. Status=%s URL=%s"), *StatusStr, *UrlStr);
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

	if (Backend != EVFXAgentLLMBackend::OpenAIChatCompletions)
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
	BodyRef->SetNumberField(TEXT("temperature"), 0.2);
	BodyRef->SetNumberField(TEXT("max_tokens"), 16384);  // Keep within typical provider limits

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
	Req->SetTimeout(FMath::Max(TimeoutSeconds, 120.0f));

	Req->OnProcessRequestComplete().BindLambda([
		this,
		OnComplete
	](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded)
	{
		if (!bSucceeded || !Response.IsValid())
		{
			const FString StatusStr = Request.IsValid() ? HttpRequestStatusToString(Request->GetStatus()) : TEXT("<null>");
			const FString UrlStr = Request.IsValid() ? Request->GetURL() : TEXT("<null>");
			UE_LOG(LogVFXAgent, Error, TEXT("HTTP request failed. Status=%s URL=%s"), *StatusStr, *UrlStr);
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

void UHttpLLMProvider::RequestRecipeJsonWithImageDataAsync(const FString& ImageDataOrBase64, const FString& OptionalPrompt, FOnRecipeJsonComplete OnComplete) const
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

	const FString DataUrl = NormalizeImageDataToDataUrl(ImageDataOrBase64, TEXT("image/png"));

	TSharedPtr<FJsonObject> BodyObj = MakeShared<FJsonObject>();
	TSharedRef<FJsonObject> BodyRef = BodyObj.ToSharedRef();
	BodyRef->SetStringField(TEXT("model"), Model.IsEmpty() ? TEXT("gpt-4o-mini") : Model);
	BodyRef->SetNumberField(TEXT("temperature"), 0.2);
	BodyRef->SetNumberField(TEXT("max_tokens"), 4096);  // Keep within typical provider limits

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
	Req->SetTimeout(FMath::Max(TimeoutSeconds, 120.0f));

	Req->OnProcessRequestComplete().BindLambda([
		this,
		OnComplete
	](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded)
	{
		if (!bSucceeded || !Response.IsValid())
		{
			const FString StatusStr = Request.IsValid() ? HttpRequestStatusToString(Request->GetStatus()) : TEXT("<null>");
			const FString UrlStr = Request.IsValid() ? Request->GetURL() : TEXT("<null>");
			UE_LOG(LogVFXAgent, Error, TEXT("HTTP request failed. Status=%s URL=%s"), *StatusStr, *UrlStr);
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

	// Build vision request (OpenAI GPT-4 Vision format)
	TSharedPtr<FJsonObject> BodyObj = MakeShared<FJsonObject>();
	BodyObj->SetStringField(TEXT("model"), Model.IsEmpty() ? TEXT("gpt-4o") : Model);
	BodyObj->SetNumberField(TEXT("max_tokens"), 4096);

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
	ImageUrl->SetStringField(TEXT("url"), FString::Printf(TEXT("data:%s;base64,%s"), *MimeType, *ImageBase64));
	ImagePart->SetObjectField(TEXT("image_url"), ImageUrl);
	ContentArray.Add(MakeShared<FJsonValueObject>(ImagePart));

	UserMsg->SetArrayField(TEXT("content"), ContentArray);
	Messages.Add(MakeShared<FJsonValueObject>(UserMsg));

	BodyObj->SetArrayField(TEXT("messages"), Messages);

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

	Req->OnProcessRequestComplete().BindLambda([OnComplete](
		FHttpRequestPtr Request,
		FHttpResponsePtr Response,
		bool bSucceeded)
	{
		if (!bSucceeded || !Response.IsValid())
		{
			const FString StatusStr = Request.IsValid() ? HttpRequestStatusToString(Request->GetStatus()) : TEXT("<null>");
			const FString UrlStr = Request.IsValid() ? Request->GetURL() : TEXT("<null>");
			UE_LOG(LogVFXAgent, Error, TEXT("HTTP request failed. Status=%s URL=%s"), *StatusStr, *UrlStr);
			OnComplete(false, FString(), TEXT("HTTP request failed"));
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
