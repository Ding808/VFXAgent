#pragma once

#include "CoreMinimal.h"
#include "ILLMProvider.h"
#include "HttpLLMProvider.generated.h"

UENUM(BlueprintType)
enum class EVFXAgentLLMBackend : uint8
{
	Mock UMETA(DisplayName = "Mock"),
	OpenAIChatCompletions UMETA(DisplayName = "OpenAI Chat Completions"),
	OpenAIResponses UMETA(DisplayName = "OpenAI Responses API"),
	OllamaGenerate UMETA(DisplayName = "Ollama /api/generate"),
};

UCLASS(BlueprintType)
class VFXAGENTCORE_API UHttpLLMProvider : public UObject, public ILLMProvider
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "VFXAgent|LLM")
	void Configure(
		EVFXAgentLLMBackend InBackend,
		const FString& InEndpoint,
		const FString& InModel,
		const FString& InApiKey,
		float InTimeoutSeconds = 30.0f);

	UFUNCTION(BlueprintCallable, Category = "VFXAgent|LLM")
	FString GetLastError() const { return LastError; }

	UFUNCTION(BlueprintCallable, Category = "VFXAgent|LLM")
	FString GetLastRawRecipeJson() const { return LastRawRecipeJson; }

	// Director JSON (plan + action list) async request
	using FOnDirectorJsonComplete = TFunction<void(bool /*bSuccess*/, const FString& /*DirectorJson*/, const FString& /*Error*/)>;
	void RequestDirectorJsonAsync(const FString& UserPrompt, const FString& OptionalStyleRefs, FOnDirectorJsonComplete OnComplete) const;
	void RequestDirectorRevisionJsonAsync(const FString& OriginalDirectorJson, const FString& ExecutionReportJson, FOnDirectorJsonComplete OnComplete) const;

	// EffectSpec JSON (strict schema) async request
	using FOnEffectSpecJsonComplete = TFunction<void(bool /*bSuccess*/, const FString& /*EffectSpecJson*/, const FString& /*Error*/)>;
	void RequestEffectSpecJsonAsync(const FString& UserPrompt, const FString& OptionalStyleRefs, FOnEffectSpecJsonComplete OnComplete) const;

	// Async variants (recommended for editor UI to avoid blocking the game thread).
	using FOnRecipeComplete = TFunction<void(const FVFXRecipe& /*Recipe*/, const FString& /*Error*/)>;
	void GenerateRecipeAsync(const FString& Prompt, FOnRecipeComplete OnComplete);
	void GenerateRecipeFromImageAsync(const FString& ImageFilePath, const FString& OptionalPrompt, FOnRecipeComplete OnComplete);
	void RefineRecipeAsync(const FVFXRecipe& OldRecipe, const FString& RefinementPrompt, FOnRecipeComplete OnComplete);

	using FOnAskComplete = TFunction<void(bool /*bSuccess*/, const FString& /*Response*/, const FString& /*Error*/)>;
	void AskAsync(const FString& Prompt, FOnAskComplete OnComplete) const;

	virtual FVFXRecipe GenerateRecipe(const FString& Prompt) override;
	virtual FVFXRecipe RefineRecipe(const FVFXRecipe& OldRecipe, const FString& RefinementPrompt) override;
	
	// New methods for enhanced functionality
	virtual FVFXRecipe GenerateRecipeFromRequest(const FVFXGenerationRequest& Request) override;
	virtual FString AnalyzeReferenceImage(const FString& ImagePath) override;
	virtual FString CompareWithReference(
		const FVFXRecipe& GeneratedRecipe,
		const FString& ReferenceImagePath,
		const FString& OriginalPrompt) override;

	/**
	 * Send a request with a custom system prompt, returning the raw JSON text.
	 * Used by the V2 multi-candidate pipeline to inject the VFX Grammar/Style Bible.
	 */
	void RequestDirectorJsonInternalAsync(const FString& UserPrompt, const FString& SystemPrompt, FOnDirectorJsonComplete OnComplete) const;

private:
	UPROPERTY(EditAnywhere, Category = "VFXAgent|LLM")
	EVFXAgentLLMBackend Backend = EVFXAgentLLMBackend::OpenAIChatCompletions;

	UPROPERTY(EditAnywhere, Category = "VFXAgent|LLM")
	FString Endpoint;

	UPROPERTY(EditAnywhere, Category = "VFXAgent|LLM")
	FString Model;

	UPROPERTY(EditAnywhere, Category = "VFXAgent|LLM")
	FString ApiKey;

	UPROPERTY(EditAnywhere, Category = "VFXAgent|LLM")
	float TimeoutSeconds = 30.0f;

	FString BuildSystemPrompt() const;
	FString BuildDirectorSystemPrompt() const;
	FString BuildEffectSpecSystemPrompt() const;
	FString BuildDirectorRevisionPrompt(const FString& OriginalDirectorJson, const FString& ExecutionReportJson) const;
	FString BuildVisionSystemPrompt() const;
	FString BuildVisionUserPrompt(const FString& OptionalPrompt) const;
	FString BuildImageAnalysisPrompt() const;
	FString EncodeImageToBase64(const FString& ImagePath) const;
	bool TryRequestRecipeJson(const FString& UserPrompt, FString& OutRecipeJson, FString& OutError) const;
	using FOnRecipeJsonComplete = TFunction<void(bool /*bSuccess*/, const FString& /*RecipeJson*/, const FString& /*Error*/)>;
	void RequestRecipeJsonAsync(const FString& UserPrompt, FOnRecipeJsonComplete OnComplete) const;
	void RequestRecipeJsonWithImageAsync(const FString& ImageFilePath, const FString& OptionalPrompt, FOnRecipeJsonComplete OnComplete) const;
	void RequestRecipeJsonWithImageDataAsync(const FString& ImageDataOrBase64, const FString& OptionalPrompt, FOnRecipeJsonComplete OnComplete) const;
	void RequestImageAnalysisAsync(const FString& ImagePath, TFunction<void(bool, const FString&, const FString&)> OnComplete) const;
	static bool TryParseRecipeJson(const FString& RecipeJson, FVFXRecipe& OutRecipe, FString& OutError);

	void SetLastError(const FString& InError) { LastError = InError; }
	void ClearLastError() { LastError.Reset(); }

	UPROPERTY(VisibleAnywhere, Category = "VFXAgent|LLM")
	FString LastError;

	UPROPERTY(VisibleAnywhere, Category = "VFXAgent|LLM")
	mutable FString LastRawRecipeJson;
};