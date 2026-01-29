#include "MockLLMProvider.h"
#include "VFXAgentLog.h"

FVFXRecipe UMockLLMProvider::GenerateRecipe(const FString& Prompt)
{
	UE_LOG(LogVFXAgent, Log, TEXT("MockLLMProvider: Generating recipe for prompt: %s"), *Prompt);

	FVFXRecipe Recipe;
	Recipe.bLoop = true;
	Recipe.Duration = 0.0f;
	Recipe.WarmupTime = 0.0f;
	Recipe.Bounds = FVector(100.0f, 100.0f, 100.0f);

	FVFXEmitterRecipe Emitter;
	Emitter.SpawnRate = 10.0f;
	Emitter.BurstCount = 0;
	Emitter.RendererType = "Sprite";
	Emitter.Color = FLinearColor::Blue;
	Emitter.Lifetime = 5.0f;
	Recipe.Emitters.Add(Emitter);

	Recipe.Parameters.Add("Color", "Blue");
	Recipe.Parameters.Add("Intensity", "1.0");

	FVFXMaterialRecipe Material;
	Material.Description = "Additive sprite material";
	Material.bIsAdditive = true;
	Recipe.Materials.Add(Material);

	Recipe.Version = 1;

	return Recipe;
}


FVFXRecipe UMockLLMProvider::RefineRecipe(const FVFXRecipe& OldRecipe, const FString& RefinementPrompt)
{
	UE_LOG(LogVFXAgent, Log, TEXT("MockLLMProvider: Refining recipe with prompt: %s"), *RefinementPrompt);

	FVFXRecipe NewRecipe = OldRecipe;
	NewRecipe.Version = OldRecipe.Version + 1;

	// Simple mock refinement: change color to red if prompt contains "red"
	if (RefinementPrompt.Contains("red", ESearchCase::IgnoreCase))
	{
		if (NewRecipe.Emitters.Num() > 0)
		{
			NewRecipe.Emitters[0].Color = FLinearColor::Red;
		}
		NewRecipe.Parameters["Color"] = "Red";
	}

	return NewRecipe;
}