#pragma once

#include "CoreMinimal.h"
#include "ILLMProvider.h"

class UHttpLLMProvider : public UObject, public ILLMProvider
{
public:
	virtual FVFXRecipe GenerateRecipe(const FString& Prompt) override;
	virtual FVFXRecipe RefineRecipe(const FVFXRecipe& OldRecipe, const FString& RefinementPrompt) override;

private:
	// TODO: Implement HTTP calls
};