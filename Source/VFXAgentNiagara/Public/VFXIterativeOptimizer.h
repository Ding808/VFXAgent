#pragma once

#include "CoreMinimal.h"
#include "VFXRecipe.h"
#include "ILLMProvider.h"
#include "VFXIterativeOptimizer.generated.h"

/**
 * Result of a single optimization iteration
 */
USTRUCT(BlueprintType)
struct FVFXOptimizationResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimization")
	int32 IterationCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimization")
	float QualityScore = 0.0f; // 0-1, where 1 is perfect match

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimization")
	FString FeedbackMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimization")
	bool bShouldContinue = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimization")
	TArray<FString> ImprovementSuggestions;
};

/**
 * Configuration for iterative optimization
 */
USTRUCT(BlueprintType)
struct FVFXOptimizationConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimization")
	int32 MaxIterations = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimization")
	float TargetQualityScore = 0.85f; // Stop when quality reaches this threshold

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimization")
	bool bEnableVisualComparison = false; // Compare with reference image

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimization")
	FString ReferenceImagePath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Optimization")
	FString OriginalPrompt;
};

/**
 * Manages iterative optimization of VFX effects using LLM feedback
 */
UCLASS()
class VFXAGENTNIAGARA_API UVFXIterativeOptimizer : public UObject
{
	GENERATED_BODY()

public:
	/**
	 * Optimize a VFX effect through multiple LLM iterations
	 * @param InitialRecipe Starting recipe
	 * @param Config Optimization configuration
	 * @param LLMProvider Provider for LLM calls
	 * @return Final optimized recipe
	 */
	FVFXRecipe OptimizeEffect(
		const FVFXRecipe& InitialRecipe,
		const FVFXOptimizationConfig& Config,
		class ILLMProvider* LLMProvider);

	/**
	 * Evaluate the quality of a generated effect
	 * @param Recipe Current recipe
	 * @param GeneratedSystem The generated Niagara system
	 * @param Config Optimization configuration
	 * @return Evaluation result with quality score and feedback
	 */
	UFUNCTION()
	FVFXOptimizationResult EvaluateEffect(
		const FVFXRecipe& Recipe,
		class UNiagaraSystem* GeneratedSystem,
		const FVFXOptimizationConfig& Config);

	/**
	 * Generate feedback prompt for LLM based on evaluation
	 */
	FString GenerateRefinementPrompt(
		const FVFXRecipe& CurrentRecipe,
		const FVFXOptimizationResult& EvaluationResult,
		const FVFXOptimizationConfig& Config);

	static FORCEINLINE UVFXIterativeOptimizer* CreateInstance()
	{
		return NewObject<UVFXIterativeOptimizer>();
	}

private:
	/**
	 * Analyze recipe for common issues (too dark, too bright, etc.)
	 */
	void AnalyzeRecipeIssues(const FVFXRecipe& Recipe, FVFXOptimizationResult& Result);

	/**
	 * Compare visual output with reference image if available
	 */
	float CompareWithReferenceImage(
		class UNiagaraSystem* GeneratedSystem,
		const FString& ReferenceImagePath);

	/**
	 * Calculate quality score based on various metrics
	 */
	float CalculateQualityScore(
		const FVFXRecipe& Recipe,
		const FVFXOptimizationResult& Evaluation);
};
