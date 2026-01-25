#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "VFXAgentSettings.generated.h"

UCLASS(config=VFXAgent, defaultconfig)
class VFXAGENTEDITOR_API UVFXAgentSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, config, Category = "LLM")
	FString LLMEndpoint = "http://localhost:11434/api/generate";

	UPROPERTY(EditAnywhere, config, Category = "LLM")
	FString LLMModel = "llama2";

	UPROPERTY(EditAnywhere, config, Category = "Generation")
	FString DefaultOutputPath = "/Game/VFXAgent/Generated";

	UPROPERTY(EditAnywhere, config, Category = "Generation")
	FString DefaultTemplatePath = "/Game/VFXAgent/Templates/SimpleSpriteSystem";

	UPROPERTY(EditAnywhere, config, Category = "Generation")
	FString AssetNamePrefix = "VFX_";

	virtual FName GetCategoryName() const override { return FName(TEXT("VFXAgent")); }
	virtual FText GetSectionText() const override { return FText::FromString(TEXT("VFX Agent Settings")); }
};