#include "HttpLLMProvider.h"
#include "VFXAgentLog.h"

FVFXRecipe UHttpLLMProvider::GenerateRecipe(const FString& Prompt)
{
	UE_LOG(LogVFXAgent, Log, TEXT("HttpLLMProvider: GenerateRecipe not implemented yet. Prompt: %s"), *Prompt);
	return FVFXRecipe();
}

FVFXRecipe UHttpLLMProvider::RefineRecipe(const FVFXRecipe& OldRecipe, const FString& RefinementPrompt)
{
	UE_LOG(LogVFXAgent, Log, TEXT("HttpLLMProvider: RefineRecipe not implemented yet. Refinement: %s"), *RefinementPrompt);
	return OldRecipe;
}