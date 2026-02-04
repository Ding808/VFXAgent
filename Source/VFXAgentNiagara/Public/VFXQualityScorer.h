#pragma once

#include "CoreMinimal.h"
#include "VFXRecipe.h"
#include "VFXMotionModuleLibrary.h"

class UNiagaraSystem;
class UNiagaraEmitter;

/**
 * VFX Quality Scorer - Evaluates generated Niagara systems based on structural quality
 * 
 * Scoring criteria:
 *  - Forbidden modules removed
 *  - Required motion modules present
 *  - Valid renderers with materials
 *  - Proper module stack organization
 */

struct FQualityScoreBreakdown
{
	float TotalScore = 0.0f;          // 0.0 to 1.0
	float RendererScore = 0.0f;       // 0.0 to 1.0
	float ModuleScore = 0.0f;         // 0.0 to 1.0
	float ConstraintScore = 0.0f;     // 0.0 to 1.0
	float MotionScore = 0.0f;         // 0.0 to 1.0
	
	int32 ForbiddenModulesFound = 0;
	int32 RequiredModulesMissing = 0;
	int32 InvalidRenderers = 0;
	
	TArray<FString> Issues;           // Human-readable list of problems
	TArray<FString> Strengths;        // What went well
	
	FString Summary;
	bool bPassesMinimumQuality = false; // Score >= 0.6
};

class VFXAGENTNIAGARA_API FVFXQualityScorer
{
public:
	/**
	 * Score a generated Niagara system based on intent and selection result
	 * @param System - The generated system to score
	 * @param Intent - The original intent/requirements
	 * @param MotionConfig - The motion configuration used
	 * @return Quality score breakdown with details
	 */
	static FQualityScoreBreakdown ScoreSystem(
		UNiagaraSystem* System,
		const FVFXIntent& Intent,
		const FMotionBehaviorConfig& MotionConfig
	);
	
	/**
	 * Score a single emitter
	 */
	static FQualityScoreBreakdown ScoreEmitter(
		UNiagaraEmitter* Emitter,
		const FVFXIntent& Intent,
		const FMotionBehaviorConfig& MotionConfig
	);
	
	/**
	 * Check if system passes minimum quality threshold for iteration to stop
	 * @param Score - Current quality score
	 * @param TargetScore - Desired target score (default 0.75)
	 * @return True if quality is acceptable
	 */
	static bool PassesQualityThreshold(const FQualityScoreBreakdown& Score, float TargetScore = 0.75f);

private:
	static float ScoreRenderers(UNiagaraEmitter* Emitter, FQualityScoreBreakdown& OutBreakdown);
	static float ScoreModuleStack(UNiagaraEmitter* Emitter, const FMotionBehaviorConfig& MotionConfig, FQualityScoreBreakdown& OutBreakdown);
	static float ScoreConstraintCompliance(UNiagaraEmitter* Emitter, const FVFXIntent& Intent, FQualityScoreBreakdown& OutBreakdown);
	static float ScoreMotionBehavior(UNiagaraEmitter* Emitter, const FMotionBehaviorConfig& MotionConfig, FQualityScoreBreakdown& OutBreakdown);
	
	static bool HasForbiddenModule(UNiagaraEmitter* Emitter, const FString& Pattern);
	static bool HasRequiredModule(UNiagaraEmitter* Emitter, const FString& ModulePath);
};
