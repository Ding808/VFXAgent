#pragma once

#include "CoreMinimal.h"
#include "EffectSpecV2.h"

class UHttpLLMProvider;

// ---------------------------------------------------------------------------
// Candidate result from a single generation attempt
// ---------------------------------------------------------------------------
struct FVFXCandidate
{
	int32 Index = 0;
	FEffectSpecV2 Spec;
	float Score = 0.0f;          // 0-1 quality score
	TArray<FString> Strengths;
	TArray<FString> Issues;
	bool bValid = false;          // Passed parsing + validation
	FString RawJson;              // Raw JSON from LLM
};

// ---------------------------------------------------------------------------
// Pipeline configuration
// ---------------------------------------------------------------------------
struct FMultiCandidateConfig
{
	int32 NumCandidates = 3;           // How many specs to generate
	int32 MaxRevisionPasses = 2;       // How many iterative revision attempts
	float MinAcceptScore = 0.6f;       // Minimum score to accept a candidate
	float TargetScore = 0.85f;         // Stop revising if score >= this
	bool bAutoSelectBest = true;       // Automatically pick highest-scoring candidate
};

// ---------------------------------------------------------------------------
// Pipeline result
// ---------------------------------------------------------------------------
struct FMultiCandidatePipelineResult
{
	bool bSuccess = false;
	int32 SelectedIndex = -1;
	FVFXCandidate SelectedCandidate;
	TArray<FVFXCandidate> AllCandidates;
	int32 TotalLLMCalls = 0;
	TArray<FString> PipelineLog;
};

// ---------------------------------------------------------------------------
// Scoring function: evaluates a spec without building Niagara assets
// ---------------------------------------------------------------------------
class VFXAGENTCORE_API FVFXSpecScorer
{
public:
	/**
	 * Score a V2 spec based on structural quality, archetype compliance,
	 * layer diversity, material richness, and feature coverage.
	 * Returns 0.0-1.0.
	 */
	static float Score(const FEffectSpecV2& Spec, TArray<FString>& OutStrengths, TArray<FString>& OutIssues);

private:
	static float ScoreLayerDiversity(const FEffectSpecV2& Spec, TArray<FString>& S, TArray<FString>& I);
	static float ScoreTimingRhythm(const FEffectSpecV2& Spec, TArray<FString>& S, TArray<FString>& I);
	static float ScoreMaterialRichness(const FEffectSpecV2& Spec, TArray<FString>& S, TArray<FString>& I);
	static float ScoreMotionLanguage(const FEffectSpecV2& Spec, TArray<FString>& S, TArray<FString>& I);
	static float ScoreFeatureCoverage(const FEffectSpecV2& Spec, TArray<FString>& S, TArray<FString>& I);
	static float ScoreArchetypeCompliance(const FEffectSpecV2& Spec, TArray<FString>& S, TArray<FString>& I);
};

// ---------------------------------------------------------------------------
// Multi-Candidate Pipeline (async interface)
// ---------------------------------------------------------------------------
class VFXAGENTCORE_API FVFXMultiCandidatePipeline
{
public:
	using FOnPipelineComplete = TFunction<void(const FMultiCandidatePipelineResult& Result)>;

	/**
	 * Run the full multi-candidate pipeline:
	 *   1. Generate N candidates via LLM
	 *   2. Parse + validate each
	 *   3. Score each
	 *   4. Select best
	 *   5. Optionally revise best if below target score
	 */
	static void RunAsync(
		UHttpLLMProvider* Provider,
		const FString& UserPrompt,
		const FMultiCandidateConfig& Config,
		FOnPipelineComplete OnComplete);

	/**
	 * Build the V2 system prompt that incorporates the VFX Grammar/Style Bible.
	 */
	static FString BuildV2SystemPrompt(EVFXBehaviorArchetype Archetype);

	/**
	 * Build a revision prompt from issues list.
	 */
	static FString BuildRevisionPrompt(const FEffectSpecV2& Spec, const TArray<FString>& Issues);
};
