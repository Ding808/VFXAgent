#include "HttpLLMProvider.h"
#include "VFXAgentLog.h"

#include "Dom/JsonObject.h"
#include "JsonObjectConverter.h"
#include "Misc/DateTime.h"
#include "Misc/ScopeLock.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

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
		"    {\"spawnRate\":10,\"burstCount\":0,\"rendererType\":\"Sprite\",\"color\":{\"r\":1,\"g\":1,\"b\":1,\"a\":1},\"lifetime\":5}\n"
		"  ],\n"
		"  \"parameters\": {\"Color\":\"Blue\", \"Intensity\":\"1.0\"},\n"
		"  \"materials\": [{\"description\":\"Basic additive material\",\"bIsAdditive\":true,\"baseMaterialPath\":\"/Engine/EngineMaterials/ParticleSpriteMaterial\"}],\n"
		"  \"dependencies\": []\n"
		"}\n"
		"Rules:\n"
		"- rendererType must be one of Sprite|Ribbon|Mesh.\n"
		"- IMPORTANT: Generate a layered Niagara system by using MULTIPLE emitters (typically 2-5) unless the user explicitly asks for a single emitter.\n"
		"- Split layers into separate emitters, e.g.:\n"
		"  explosion: core burst (Sprite burstCount), sparks (Sprite spawnRate), smoke (Sprite long lifetime), shockwave (Ribbon burst).\n"
		"  magic/electric: arcs (Ribbon), glow particles (Sprite), secondary smoke/dust (Sprite).\n"
		"  fire: flames (Sprite), embers (Sprite), smoke (Sprite).\n"
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
		FPlatformProcess::Sleep(0.01f);
		if ((FPlatformTime::Seconds() - Start) > TimeoutSeconds)
		{
			return false;
		}
	}
	return true;
}

bool UHttpLLMProvider::TryRequestRecipeJson(const FString& UserPrompt, FString& OutRecipeJson, FString& OutError) const
{
	FString EffectiveEndpoint = Endpoint;
	if (EffectiveEndpoint.IsEmpty())
	{
		OutError = TEXT("LLM endpoint is empty");
		return false;
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
	for (const TPair<FString, FString>& KV : ExtraHeaders)
	{
		Req->SetHeader(KV.Key, KV.Value);
	}
	Req->SetContentAsString(BodyText);
	Req->SetTimeout(TimeoutSeconds);

	FString ResponseText;
	int32 ResponseCode = 0;
	bool bOk = false;

	Req->OnProcessRequestComplete().BindLambda([
		&ResponseText,
		&ResponseCode,
		&bOk
	](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded)
	{
		bOk = bSucceeded && Response.IsValid();
		if (Response.IsValid())
		{
			ResponseCode = Response->GetResponseCode();
			ResponseText = Response->GetContentAsString();
		}
	});

	if (!Req->ProcessRequest())
	{
		OutError = TEXT("Failed to start HTTP request");
		return false;
	}

	if (!WaitForHttp(Req, TimeoutSeconds))
	{
		OutError = TEXT("HTTP request timed out");
		return false;
	}

	if (!bOk)
	{
		OutError = FString::Printf(TEXT("HTTP request failed (code=%d)"), ResponseCode);
		return false;
	}

	if (ResponseCode < 200 || ResponseCode >= 300)
	{
		OutError = FString::Printf(TEXT("LLM returned HTTP %d: %s"), ResponseCode, *ResponseText.Left(500));
		return false;
	}

	// Extract the recipe JSON from backend-specific response envelope.
	TSharedPtr<FJsonObject> Root;
	if (!ParseJsonObject(ResponseText, Root, OutError))
	{
		OutError = FString::Printf(TEXT("LLM response is not JSON: %s"), *ResponseText.Left(200));
		return false;
	}

	if (Backend == EVFXAgentLLMBackend::OllamaGenerate)
	{
		FString Resp;
		if (!Root->TryGetStringField(TEXT("response"), Resp))
		{
			OutError = TEXT("Ollama response missing 'response' field");
			return false;
		}
		OutRecipeJson = Resp;
		return true;
	}

	// OpenAI chat completions: choices[0].message.content
	const TArray<TSharedPtr<FJsonValue>>* Choices = nullptr;
	if (!Root->TryGetArrayField(TEXT("choices"), Choices) || !Choices || Choices->Num() == 0)
	{
		OutError = TEXT("OpenAI response missing 'choices' array");
		return false;
	}

	TSharedPtr<FJsonObject> Choice0 = (*Choices)[0]->AsObject();
	if (!Choice0.IsValid())
	{
		OutError = TEXT("OpenAI response choice[0] is not an object");
		return false;
	}

	TSharedPtr<FJsonObject> Msg = Choice0->GetObjectField(TEXT("message"));
	if (!Msg.IsValid())
	{
		OutError = TEXT("OpenAI response missing message object");
		return false;
	}

	FString Content;
	if (!Msg->TryGetStringField(TEXT("content"), Content))
	{
		OutError = TEXT("OpenAI response missing message.content");
		return false;
	}

	OutRecipeJson = Content;
	return true;
}

FVFXRecipe UHttpLLMProvider::GenerateRecipe(const FString& Prompt)
{
	FString RecipeJson;
	FString Error;
	if (!TryRequestRecipeJson(Prompt, RecipeJson, Error))
	{
		UE_LOG(LogVFXAgent, Error, TEXT("HttpLLMProvider: GenerateRecipe failed: %s"), *Error);
		return FVFXRecipe();
	}

	FVFXRecipe Parsed;
	if (!TryParseRecipeJson(RecipeJson, Parsed, Error))
	{
		UE_LOG(LogVFXAgent, Error, TEXT("HttpLLMProvider: Failed to parse recipe JSON: %s. Raw: %s"), *Error, *RecipeJson.Left(400));
		return FVFXRecipe();
	}

	Parsed.Version = FMath::Max(1, Parsed.Version);
	return Parsed;
}

FVFXRecipe UHttpLLMProvider::RefineRecipe(const FVFXRecipe& OldRecipe, const FString& RefinementPrompt)
{
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
		return OldRecipe;
	}

	FVFXRecipe Parsed;
	if (!TryParseRecipeJson(RecipeJson, Parsed, Error))
	{
		UE_LOG(LogVFXAgent, Error, TEXT("HttpLLMProvider: Failed to parse refined recipe JSON: %s. Raw: %s"), *Error, *RecipeJson.Left(400));
		return OldRecipe;
	}

	Parsed.Version = OldRecipe.Version + 1;
	return Parsed;
}