#include "VFXIterativeOptimizer.h"
#include "VFXAgentLog.h"
#include "ILLMProvider.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"

FVFXRecipe UVFXIterativeOptimizer::OptimizeEffect(
	const FVFXRecipe& InitialRecipe,
	const FVFXOptimizationConfig& Config,
	ILLMProvider* LLMProvider)
{
	if (!LLMProvider)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("LLMProvider is null, cannot optimize"));
		return InitialRecipe;
	}

	UE_LOG(LogVFXAgent, Log, TEXT("Starting iterative optimization, max iterations: %d"), Config.MaxIterations);

	FVFXRecipe CurrentRecipe = InitialRecipe;
	FVFXRecipe BestRecipe = InitialRecipe;
	float BestScore = 0.0f;

	for (int32 Iteration = 0; Iteration < Config.MaxIterations; Iteration++)
	{
		UE_LOG(LogVFXAgent, Log, TEXT("Optimization Iteration %d/%d"), Iteration + 1, Config.MaxIterations);

		// Evaluate current recipe
		FVFXOptimizationResult EvaluationResult;
		EvaluationResult.IterationCount = Iteration + 1;
		
		// Analyze the recipe for issues
		AnalyzeRecipeIssues(CurrentRecipe, EvaluationResult);

		// Calculate quality score
		EvaluationResult.QualityScore = CalculateQualityScore(CurrentRecipe, EvaluationResult);

		UE_LOG(LogVFXAgent, Log, TEXT("Current quality score: %.2f"), EvaluationResult.QualityScore);

		// Track best result
		if (EvaluationResult.QualityScore > BestScore)
		{
			BestScore = EvaluationResult.QualityScore;
			BestRecipe = CurrentRecipe;
			UE_LOG(LogVFXAgent, Log, TEXT("New best score: %.2f"), BestScore);
		}

		// Check if we've reached target quality
		if (EvaluationResult.QualityScore >= Config.TargetQualityScore)
		{
			UE_LOG(LogVFXAgent, Log, TEXT("Target quality reached! Final score: %.2f"), EvaluationResult.QualityScore);
			return CurrentRecipe;
		}

		// Generate refinement prompt
		FString RefinementPrompt = GenerateRefinementPrompt(CurrentRecipe, EvaluationResult, Config);
		
		UE_LOG(LogVFXAgent, Log, TEXT("Refinement prompt: %s"), *RefinementPrompt);

		// Get refined recipe from LLM
		CurrentRecipe = LLMProvider->RefineRecipe(CurrentRecipe, RefinementPrompt);
	}

	UE_LOG(LogVFXAgent, Log, TEXT("Optimization complete. Best score: %.2f"), BestScore);
	return BestRecipe;
}

FVFXOptimizationResult UVFXIterativeOptimizer::EvaluateEffect(
	const FVFXRecipe& Recipe,
	UNiagaraSystem* GeneratedSystem,
	const FVFXOptimizationConfig& Config)
{
	FVFXOptimizationResult Result;

	// Analyze recipe for common issues
	AnalyzeRecipeIssues(Recipe, Result);

	// If we have a reference image and visual comparison is enabled
	if (Config.bEnableVisualComparison && !Config.ReferenceImagePath.IsEmpty() && GeneratedSystem)
	{
		float VisualScore = CompareWithReferenceImage(GeneratedSystem, Config.ReferenceImagePath);
		Result.QualityScore = VisualScore;
		
		if (VisualScore < 0.5f)
		{
			Result.ImprovementSuggestions.Add(TEXT("Visual appearance differs significantly from reference"));
		}
	}
	else
	{
		// Calculate score based on recipe analysis
		Result.QualityScore = CalculateQualityScore(Recipe, Result);
	}

	Result.bShouldContinue = Result.QualityScore < 0.85f;

	return Result;
}

FString UVFXIterativeOptimizer::GenerateRefinementPrompt(
	const FVFXRecipe& CurrentRecipe,
	const FVFXOptimizationResult& EvaluationResult,
	const FVFXOptimizationConfig& Config)
{
	FString Prompt = TEXT("Please refine the VFX recipe based on the following analysis:\n\n");
	Prompt += FString::Printf(TEXT("Original request: %s\n\n"), *Config.OriginalPrompt);
	Prompt += FString::Printf(TEXT("Current quality score: %.2f (target: %.2f)\n\n"),
		EvaluationResult.QualityScore, Config.TargetQualityScore);

	if (EvaluationResult.ImprovementSuggestions.Num() > 0)
	{
		Prompt += TEXT("Issues identified:\n");
		for (const FString& Suggestion : EvaluationResult.ImprovementSuggestions)
		{
			Prompt += FString::Printf(TEXT("- %s\n"), *Suggestion);
		}
		Prompt += TEXT("\n");
	}

	Prompt += TEXT("Please adjust the recipe to address these issues. ");
	Prompt += TEXT("Focus on improving visual impact, color vibrancy, and overall effect quality. ");
	Prompt += TEXT("You may adjust emitter parameters, materials, colors, textures, and add new emitters if needed.");

	return Prompt;
}

void UVFXIterativeOptimizer::AnalyzeRecipeIssues(
	const FVFXRecipe& Recipe,
	FVFXOptimizationResult& Result)
{
	// Check for very low emissive values (effect might be too dark)
	bool bHasLowEmissive = false;
	bool bHasLowOpacity = false;
	bool bHasLowParticleCount = false;
	bool bHasNoMaterials = Recipe.Materials.Num() == 0;

	for (const FVFXEmitterRecipe& Emitter : Recipe.Emitters)
	{
		// Check color brightness
		float Brightness = (Emitter.Color.R + Emitter.Color.G + Emitter.Color.B) / 3.0f;
		if (Brightness < 0.3f)
		{
			bHasLowEmissive = true;
		}

		// Check opacity
		if (Emitter.Color.A < 0.5f)
		{
			bHasLowOpacity = true;
		}

		// Check particle count
		if (Emitter.SpawnRate < 5.0f && Emitter.BurstCount < 10)
		{
			bHasLowParticleCount = true;
		}
	}

	// Generate suggestions
	if (bHasLowEmissive)
	{
		Result.ImprovementSuggestions.Add(TEXT("Some emitters have low brightness. Consider increasing emissive color values."));
	}

	if (bHasLowOpacity)
	{
		Result.ImprovementSuggestions.Add(TEXT("Some emitters have low opacity. Increase alpha values for better visibility."));
	}

	if (bHasLowParticleCount)
	{
		Result.ImprovementSuggestions.Add(TEXT("Low particle count detected. Consider increasing spawn rate or burst count."));
	}

	if (bHasNoMaterials)
	{
		Result.ImprovementSuggestions.Add(TEXT("No custom materials defined. Consider adding materials for better visual quality."));
	}

	// Check for variety
	if (Recipe.Emitters.Num() == 1)
	{
		Result.ImprovementSuggestions.Add(TEXT("Single emitter effect. Consider adding more layers for richness."));
	}

	// Check if all emitters use same color
	if (Recipe.Emitters.Num() > 1)
	{
		bool bAllSameColor = true;
		FLinearColor FirstColor = Recipe.Emitters[0].Color;
		for (int32 i = 1; i < Recipe.Emitters.Num(); i++)
		{
			if (!Recipe.Emitters[i].Color.Equals(FirstColor, 0.1f))
			{
				bAllSameColor = false;
				break;
			}
		}

		if (bAllSameColor)
		{
			Result.ImprovementSuggestions.Add(TEXT("All emitters use similar colors. Add color variation for visual interest."));
		}
	}
}

float UVFXIterativeOptimizer::CompareWithReferenceImage(
	UNiagaraSystem* GeneratedSystem,
	const FString& ReferenceImagePath)
{
	// This is a placeholder for visual comparison
	// In a full implementation, you would:
	// 1. Render the Niagara system to a texture
	// 2. Load the reference image
	// 3. Compare using perceptual metrics (SSIM, MSE, etc.)
	// 4. Return a similarity score

	UE_LOG(LogVFXAgent, Warning, TEXT("Visual comparison not yet implemented"));
	
	// For now, return a neutral score
	return 0.5f;
}

float UVFXIterativeOptimizer::CalculateQualityScore(
	const FVFXRecipe& Recipe,
	const FVFXOptimizationResult& Evaluation)
{
	float Score = 1.0f;

	// Deduct points for each issue
	float PenaltyPerIssue = 0.15f;
	Score -= Evaluation.ImprovementSuggestions.Num() * PenaltyPerIssue;

	// Bonus for having materials
	if (Recipe.Materials.Num() > 0)
	{
		Score += 0.1f;
	}

	// Bonus for multiple emitters
	if (Recipe.Emitters.Num() > 1)
	{
		Score += 0.1f;
	}

	// Bonus for color variety
	if (Recipe.Emitters.Num() > 1)
	{
		TSet<FColor> UniqueColors;
		for (const FVFXEmitterRecipe& Emitter : Recipe.Emitters)
		{
			UniqueColors.Add(Emitter.Color.ToFColor(false));
		}
		
		if (UniqueColors.Num() > 1)
		{
			Score += 0.1f;
		}
	}

	// Clamp to 0-1 range
	return FMath::Clamp(Score, 0.0f, 1.0f);
}
