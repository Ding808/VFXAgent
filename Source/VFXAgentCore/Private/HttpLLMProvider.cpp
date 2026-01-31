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
	return TEXT(
		"You are an expert Niagara VFX recipe generator. Output MUST be a single valid JSON object matching the exact schema below.\n\n"
		"=== JSON SCHEMA ===\n"
		"{\n"
		"  \"version\": 1,\n"
		"  \"bLoop\": true,\n"
		"  \"duration\": 0.0,\n"
		"  \"warmupTime\": 0.0,\n"
		"  \"bounds\": {\"x\":100, \"y\":100, \"z\":100},\n"
		"  \"emitters\": [\n"
		"    {\n"
		"      \"name\": \"CoreBurst\",\n"
		"      \"spawnRate\": 50.0,\n"
		"      \"burstCount\": 100,\n"
		"      \"burstTime\": 0.0,\n"
		"      \"rendererType\": \"Sprite\",\n"
		"      \"templateName\": \"OmnidirectionalBurst\",\n"
		"      \"color\": {\"r\":1.0, \"g\":0.5, \"b\":0.0, \"a\":1.0},\n"
		"      \"colorEnd\": {\"r\":0.3, \"g\":0.0, \"b\":0.0, \"a\":0.0},\n"
		"      \"bUseColorGradient\": true,\n"
		"      \"lifetime\": 2.0,\n"
		"      \"lifetimeVariation\": 0.2,\n"
		"      \"size\": 20.0,\n"
		"      \"sizeEnd\": 5.0,\n"
		"      \"bUseSizeOverLife\": true,\n"
		"      \"sizeVariation\": 0.3,\n"
		"      \"velocity\": {\"x\":0, \"y\":0, \"z\":300},\n"
		"      \"velocityVariation\": 0.5,\n"
		"      \"acceleration\": {\"x\":0, \"y\":0, \"z\":-980},\n"
		"      \"drag\": 0.5,\n"
		"      \"initialRotation\": 0.0,\n"
		"      \"rotationRate\": 180.0,\n"
		"      \"rotationRateVariation\": 0.5,\n"
		"      \"bUseGravity\": true,\n"
		"      \"mass\": 1.0,\n"
		"      \"emitShape\": \"Sphere\",\n"
		"      \"shapeSize\": {\"x\":50, \"y\":50, \"z\":50},\n"
		"      \"materialIndex\": 0,\n"
		"      \"sortOrder\": 0,\n"
		"      \"bLocalSpace\": false\n"
		"    }\n"
		"  ],\n"
		"  \"materials\": [\n"
		"    {\n"
		"      \"name\": \"ExplosionCoreMaterial\",\n"
		"      \"description\": \"Bright orange-yellow additive material for explosion core\",\n"
		"      \"bIsAdditive\": true,\n"
		"      \"bIsUnlit\": true,\n"
		"      \"baseMaterialPath\": \"/Engine/EngineMaterials/ParticleSpriteMaterial\",\n"
		"      \"baseColor\": {\"r\":1.0, \"g\":0.8, \"b\":0.5, \"a\":1.0},\n"
		"      \"emissiveColor\": {\"r\":1.0, \"g\":0.5, \"b\":0.0, \"a\":1.0},\n"
		"      \"emissiveStrength\": 3.0,\n"
		"      \"opacity\": 0.8,\n"
		"      \"roughness\": 1.0,\n"
		"      \"metallic\": 0.0,\n"
		"      \"generatedTextures\": [\n"
		"        {\n"
		"          \"name\": \"ExplosionGradient\",\n"
		"          \"type\": \"Gradient\",\n"
		"          \"primaryColor\": {\"r\":1.0, \"g\":1.0, \"b\":1.0, \"a\":1.0},\n"
		"          \"secondaryColor\": {\"r\":0.0, \"g\":0.0, \"b\":0.0, \"a\":0.0},\n"
		"          \"resolution\": 256,\n"
		"          \"description\": \"Radial gradient for soft particles\"\n"
		"        }\n"
		"      ]\n"
		"    }\n"
		"  ],\n"
		"  \"parameters\": {},\n"
		"  \"dependencies\": []\n"
		"}\n\n"
		"=== EMITTER PARAMETERS GUIDE ===\n"
		"All parameters are optional. Only include what's needed for the effect.\n\n"
		"SPAWN:\n"
		"- spawnRate: particles/sec (10-500). Use 0 if using burstCount.\n"
		"- burstCount: instant spawn count (10-500 for bursts, 0 for continuous).\n"
		"- burstTime: when to trigger burst in seconds (0=start, use for delayed effects).\n\n"
		"RENDERER:\n"
		"- rendererType: \"Sprite\" (default), \"Ribbon\" (trails/beams), \"Mesh\" (3D objects).\n"
		"- templateName: \"Fountain\", \"DirectionalBurst\", \"OmnidirectionalBurst\", \"HangingParticulates\", \"UpwardMeshBurst\", \"Beam\".\n\n"
		"COLOR:\n"
		"- color: Start color RGBA (0-1). Use vibrant colors for visible effects.\n"
		"- colorEnd: End color for gradient (set bUseColorGradient=true).\n"
		"- bUseColorGradient: Animate from color to colorEnd over lifetime.\n\n"
		"LIFETIME & SIZE:\n"
		"- lifetime: Particle lifespan in seconds (0.5-10 typical).\n"
		"- lifetimeVariation: Random variation 0-1 (0.2 = ±20%).\n"
		"- size: Initial size in world units (5-100 typical).\n"
		"- sizeEnd: Final size (set bUseSizeOverLife=true for scaling).\n"
		"- bUseSizeOverLife: Animate size from start to end.\n"
		"- sizeVariation: Random size variation 0-1.\n\n"
		"MOVEMENT:\n"
		"- velocity: Initial velocity vector {x,y,z}. Z+ is up. Magnitude 50-500 typical.\n"
		"- velocityVariation: Random velocity variation 0-1.\n"
		"- acceleration: Constant force {x,y,z}. Use {0,0,-980} for gravity.\n"
		"- drag: Air resistance 0-10 (0=none, 1=realistic, 5=heavy drag).\n\n"
		"ROTATION:\n"
		"- initialRotation: Starting rotation in degrees.\n"
		"- rotationRate: Spin speed degrees/sec (90-360 for visible spinning).\n"
		"- rotationRateVariation: Random rotation variation 0-1.\n\n"
		"PHYSICS:\n"
		"- bUseGravity: Apply gravity (uses acceleration if true).\n"
		"- mass: Particle mass (affects physics).\n\n"
		"SHAPE:\n"
		"- emitShape: \"Point\", \"Sphere\", \"Box\", \"Cone\", \"Cylinder\".\n"
		"- shapeSize: Size/radius of emit shape {x,y,z}.\n\n"
		"MATERIAL:\n"
		"- materialIndex: Index into materials array (0-based), -1 for default.\n\n"
		"RENDERING:\n"
		"- sortOrder: Render order (higher=later=on top). Use 0-5.\n"
		"- bLocalSpace: Particles move with emitter if true.\n\n"
		"=== MATERIAL GENERATION GUIDE ===\n"
		"ALWAYS create custom materials for visual quality! Each material should be tailored to its layer.\n\n"
		"MATERIAL PARAMETERS:\n"
		"- name: Descriptive name (e.g., \"FireCoreMaterial\", \"SmokeMaterial\").\n"
		"- description: What this material is for.\n"
		"- bIsAdditive: true for glowing/transparent effects (fire, magic), false for solid.\n"
		"- bIsUnlit: true for self-lit effects (most VFX), false for lit.\n"
		"- baseColor: Base tint color RGBA.\n"
		"- emissiveColor: Glow color RGB.\n"
		"- emissiveStrength: Glow intensity (1-10, use 2-5 for visible glow).\n"
		"- opacity: Transparency 0-1 (0.5-0.8 typical for smoke/fire).\n"
		"- roughness: Surface roughness 0-1 (usually 1 for VFX).\n"
		"- metallic: Metallic look 0-1 (usually 0 for VFX).\n\n"
		"TEXTURE GENERATION:\n"
		"Add generatedTextures array for custom textures:\n"
		"- type: \"Gradient\" (soft particles, fading), \"Noise\" (organic patterns), \"Perlin\" (smoke, clouds).\n"
		"- primaryColor/secondaryColor: Colors to blend.\n"
		"- resolution: 256, 512, or 1024.\n"
		"- noiseScale: For noise types (0.5-2.0).\n"
		"- octaves: Detail layers for noise (2-6).\n\n"
		"=== GENERATION RULES ===\n"
		"1. LAYERED EFFECTS: Use 2-8 emitters for complexity. Each emitter = one visual layer.\n"
		"2. MATERIAL ASSIGNMENT: Create 1 material per visual style, assign via materialIndex.\n"
		"3. REALISTIC PARAMETERS: Use physically plausible values:\n"
		"   - Explosions: High velocity (300-800), short lifetime (0.5-2s), gravity.\n"
		"   - Fire: Medium velocity (50-200), drag, upward acceleration, color gradient orange→red→black.\n"
		"   - Smoke: Low velocity (20-100), high drag, large size growth, low opacity.\n"
		"   - Sparks: High velocity (400-1000), gravity, small size, bright color.\n"
		"   - Magic: Medium velocity, no gravity, color gradients, additive blending.\n"
		"4. COLOR BRIGHTNESS: Use emissiveStrength 2-5 for visibility. Don't make effects too dark!\n"
		"5. VARIATION: Add variation (0.2-0.5) to lifetime, size, velocity for organic look.\n"
		"6. OPTIMIZATION: Use burstCount for one-shot effects, spawnRate for continuous.\n\n"
		"=== EXAMPLES ===\n"
		"Explosion: Core burst (omnidirectional, 200 particles, bright orange, emissive 4), "
		"Sparks (directional burst, 100 particles, yellow, high velocity), "
		"Smoke (continuous spawn, gray, large size growth, drag 2), "
		"Shockwave (ribbon, expanding ring).\n\n"
		"Fire: Flames (upward, orange→red gradient, drag 0.5, additive), "
		"Embers (bursts, small, bright yellow, gravity), "
		"Smoke (slow, gray, size growth, high drag, low opacity).\n\n"
		"Magic Portal: Core ring (ribbon beam, blue glow, rotating), "
		"Energy particles (swirling, blue→purple gradient, no gravity), "
		"Sparkles (small bursts, white, additive), "
		"Runes (floating, slow rotation, emissive 5).\n\n"
		"OUTPUT ONLY THE JSON OBJECT. NO MARKDOWN, NO EXPLANATIONS, NO CODE BLOCKS."
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
		BodyRef->SetNumberField(TEXT("max_tokens"), 4000);  // Increased for complex multi-emitter recipes with materials

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

FVFXRecipe UHttpLLMProvider::GenerateRecipeFromRequest(const FVFXGenerationRequest& Request)
{
	ClearLastError();

	// If we have a reference image, use vision-enabled generation
	if (!Request.ReferenceImagePath.IsEmpty())
	{
		bool bDone = false;
		FVFXRecipe Result;
		FString Error;

		GenerateRecipeFromImageAsync(Request.ReferenceImagePath, Request.TextPrompt,
			[&bDone, &Result, &Error](const FVFXRecipe& Recipe, const FString& InError)
			{
				Result = Recipe;
				Error = InError;
				bDone = true;
			});

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
	if (EffectiveEndpoint.IsEmpty())
	{
		OnComplete(false, FString(), TEXT("LLM endpoint is empty"));
		return;
	}

	// Build vision request (OpenAI GPT-4 Vision format)
	TSharedPtr<FJsonObject> BodyObj = MakeShared<FJsonObject>();
	BodyObj->SetStringField(TEXT("model"), Model.IsEmpty() ? TEXT("gpt-4o") : Model);
	BodyObj->SetNumberField(TEXT("max_tokens"), 500);

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
	Req->SetTimeout(TimeoutSeconds);

	Req->OnProcessRequestComplete().BindLambda([OnComplete](
		FHttpRequestPtr Request,
		FHttpResponsePtr Response,
		bool bSucceeded)
	{
		if (!bSucceeded || !Response.IsValid())
		{
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
