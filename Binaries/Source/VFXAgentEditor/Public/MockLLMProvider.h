#pragma once

#include "CoreMinimal.h"
#include "ILLMProvider.h"
#include "MockLLMProvider.generated.h"

UCLASS()
class VFXAGENTEDITOR_API UMockLLMProvider : public UObject, public ILLMProvider
{
	GENERATED_BODY()

public:
	virtual FVFXRecipe GenerateRecipe(const FString& Prompt) override;
	virtual FVFXRecipe RefineRecipe(const FVFXRecipe& OldRecipe, const FString& RefinementPrompt) override;
};