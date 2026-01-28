#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "VFXAgentSettings.generated.h"

UCLASS(config=VFXAgent, defaultconfig)
class VFXAGENTEDITOR_API UVFXAgentSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, config, Category = "LLM", meta=(DisplayName="LLM Endpoint"))
	FString LLMEndpoint = "https://api.openai.com/v1/chat/completions";

	UPROPERTY(EditAnywhere, config, Category = "LLM", meta=(DisplayName="LLM Model"))
	FString LLMModel = "gpt-4o-mini";

	// For OpenAI-compatible endpoints (e.g. https://api.openai.com/v1/chat/completions)
	UPROPERTY(EditAnywhere, config, Category = "LLM", meta=(DisplayName="LLM API Key", PasswordField="true"))
	FString LLMApiKey = "";

	UPROPERTY(EditAnywhere, config, Category = "LLM", meta=(DisplayName="LLM Backend"))
	FString LLMBackend = "OpenAI"; // Mock | OpenAI | Ollama | ChatGPT

	UPROPERTY(EditAnywhere, config, Category = "LLM", meta=(DisplayName="LLM Timeout Seconds", ClampMin="1.0"))
	float LLMTimeoutSeconds = 60.0f;

	UPROPERTY(EditAnywhere, config, Category = "Generation")
	FString DefaultOutputPath = "/Game/VFXAgent/Generated";

	UPROPERTY(EditAnywhere, config, Category = "Generation")
	FString DefaultTemplatePath = "/Game/VFXAgent/Templates/SimpleSpriteSystem.SimpleSpriteSystem";

	// If false, generator will create emitters without using templates.
	UPROPERTY(EditAnywhere, config, Category = "Generation")
	bool bUseTemplates = true;

	UPROPERTY(EditAnywhere, config, Category = "Generation")
	FString AssetNamePrefix = "VFX_";

	virtual FName GetCategoryName() const override { return FName(TEXT("VFXAgent")); }
	virtual FText GetSectionText() const override { return FText::FromString(TEXT("VFX Agent Settings")); }
};