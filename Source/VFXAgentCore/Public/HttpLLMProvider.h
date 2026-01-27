#pragma once

#include "CoreMinimal.h"
#include "ILLMProvider.h"
#include "HttpLLMProvider.generated.h"

UENUM(BlueprintType)
enum class EVFXAgentLLMBackend : uint8
{
	Mock UMETA(DisplayName = "Mock"),
	OpenAIChatCompletions UMETA(DisplayName = "OpenAI Chat Completions"),
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

	// Async variants (recommended for editor UI to avoid blocking the game thread).
	using FOnRecipeComplete = TFunction<void(const FVFXRecipe& /*Recipe*/, const FString& /*Error*/)>;
	void GenerateRecipeAsync(const FString& Prompt, FOnRecipeComplete OnComplete);
	void RefineRecipeAsync(const FVFXRecipe& OldRecipe, const FString& RefinementPrompt, FOnRecipeComplete OnComplete);

	virtual FVFXRecipe GenerateRecipe(const FString& Prompt) override;
	virtual FVFXRecipe RefineRecipe(const FVFXRecipe& OldRecipe, const FString& RefinementPrompt) override;

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
	bool TryRequestRecipeJson(const FString& UserPrompt, FString& OutRecipeJson, FString& OutError) const;
	using FOnRecipeJsonComplete = TFunction<void(bool /*bSuccess*/, const FString& /*RecipeJson*/, const FString& /*Error*/)>;
	void RequestRecipeJsonAsync(const FString& UserPrompt, FOnRecipeJsonComplete OnComplete) const;
	static bool TryParseRecipeJson(const FString& RecipeJson, FVFXRecipe& OutRecipe, FString& OutError);

	void SetLastError(const FString& InError) { LastError = InError; }
	void ClearLastError() { LastError.Reset(); }

	UPROPERTY(VisibleAnywhere, Category = "VFXAgent|LLM")
	FString LastError;
};