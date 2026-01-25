#pragma once

#include "CoreMinimal.h"
#include "VFXRecipe.h"

class ILLMProvider
{
public:
	virtual ~ILLMProvider() = default;
	
	virtual FVFXRecipe GenerateRecipe(const FString& Prompt) = 0;
	virtual FVFXRecipe RefineRecipe(const FVFXRecipe& OldRecipe, const FString& RefinementPrompt) = 0;
};