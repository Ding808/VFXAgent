#include "VFXQualityScorer.h"
#include "VFXAgentLog.h"
#include "VFXRendererValidationFixer.h"
#include "VFXModuleStripper.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"

FQualityScoreBreakdown FVFXQualityScorer::ScoreSystem(
	UNiagaraSystem* System,
	const FVFXIntent& Intent,
	const FMotionBehaviorConfig& MotionConfig)
{
	FQualityScoreBreakdown TotalScore;
	
	if (!System)
	{
		TotalScore.Issues.Add(TEXT("Null system"));
		TotalScore.TotalScore = 0.0f;
		return TotalScore;
	}
	
	// Score each emitter and average
	const TArray<FNiagaraEmitterHandle>& Emitters = System->GetEmitterHandles();
	int32 ValidEmitters = 0;
	
	for (const FNiagaraEmitterHandle& Handle : Emitters)
	{
		UNiagaraEmitter* Emitter = Handle.GetInstance().Emitter;
		if (!Emitter) continue;
		
		FQualityScoreBreakdown EmitterScore = ScoreEmitter(Emitter, Intent, MotionConfig);
		
		// Accumulate scores
		TotalScore.RendererScore += EmitterScore.RendererScore;
		TotalScore.ModuleScore += EmitterScore.ModuleScore;
		TotalScore.ConstraintScore += EmitterScore.ConstraintScore;
		TotalScore.MotionScore += EmitterScore.MotionScore;
		TotalScore.ForbiddenModulesFound += EmitterScore.ForbiddenModulesFound;
		TotalScore.RequiredModulesMissing += EmitterScore.RequiredModulesMissing;
		TotalScore.InvalidRenderers += EmitterScore.InvalidRenderers;
		
		TotalScore.Issues.Append(EmitterScore.Issues);
		TotalScore.Strengths.Append(EmitterScore.Strengths);
		
		ValidEmitters++;
	}
	
	if (ValidEmitters > 0)
	{
		TotalScore.RendererScore /= ValidEmitters;
		TotalScore.ModuleScore /= ValidEmitters;
		TotalScore.ConstraintScore /= ValidEmitters;
		TotalScore.MotionScore /= ValidEmitters;
	}
	
	// Calculate total score (weighted average)
	TotalScore.TotalScore = 
		(TotalScore.RendererScore * 0.3f) +      // 30% - Renderers must work
		(TotalScore.ModuleScore * 0.25f) +       // 25% - Module stack quality
		(TotalScore.ConstraintScore * 0.25f) +   // 25% - Constraint compliance
		(TotalScore.MotionScore * 0.2f);         // 20% - Motion behavior
	
	TotalScore.bPassesMinimumQuality = (TotalScore.TotalScore >= 0.6f);
	
	TotalScore.Summary = FString::Printf(
		TEXT("Quality: %.2f (R:%.2f M:%.2f C:%.2f Mo:%.2f) - %d forbidden, %d missing, %d bad renderers"),
		TotalScore.TotalScore,
		TotalScore.RendererScore,
		TotalScore.ModuleScore,
		TotalScore.ConstraintScore,
		TotalScore.MotionScore,
		TotalScore.ForbiddenModulesFound,
		TotalScore.RequiredModulesMissing,
		TotalScore.InvalidRenderers
	);
	
	UE_LOG(LogVFXAgent, Log, TEXT("Quality Score: %s"), *TotalScore.Summary);
	
	return TotalScore;
}

FQualityScoreBreakdown FVFXQualityScorer::ScoreEmitter(
	UNiagaraEmitter* Emitter,
	const FVFXIntent& Intent,
	const FMotionBehaviorConfig& MotionConfig)
{
	FQualityScoreBreakdown Score;
	
	if (!Emitter)
	{
		Score.Issues.Add(TEXT("Null emitter"));
		return Score;
	}
	
	// Score different aspects
	Score.RendererScore = ScoreRenderers(Emitter, Score);
	Score.ModuleScore = ScoreModuleStack(Emitter, MotionConfig, Score);
	Score.ConstraintScore = ScoreConstraintCompliance(Emitter, Intent, Score);
	Score.MotionScore = ScoreMotionBehavior(Emitter, MotionConfig, Score);
	
	// Calculate total
	Score.TotalScore = 
		(Score.RendererScore * 0.3f) +
		(Score.ModuleScore * 0.25f) +
		(Score.ConstraintScore * 0.25f) +
		(Score.MotionScore * 0.2f);
	
	Score.bPassesMinimumQuality = (Score.TotalScore >= 0.6f);
	
	return Score;
}

bool FVFXQualityScorer::PassesQualityThreshold(const FQualityScoreBreakdown& Score, float TargetScore)
{
	return Score.TotalScore >= TargetScore;
}

float FVFXQualityScorer::ScoreRenderers(UNiagaraEmitter* Emitter, FQualityScoreBreakdown& OutBreakdown)
{
	if (!Emitter)
		return 0.0f;
	
	int32 ValidRenderers = FVFXRendererValidationFixer::CountValidRenderers(Emitter);
	
	if (ValidRenderers == 0)
	{
		OutBreakdown.Issues.Add(TEXT("No valid renderers"));
		OutBreakdown.InvalidRenderers++;
		return 0.0f;
	}
	
	// Check for invalid renderers
	FRendererValidationReport Report = FVFXRendererValidationFixer::ValidateAndFixRenderers(Emitter, nullptr);
	OutBreakdown.InvalidRenderers = Report.InvalidRenderersRemoved;
	
	float Score = (ValidRenderers > 0) ? 1.0f : 0.0f;
	if (Report.InvalidRenderersRemoved > 0)
	{
		OutBreakdown.Issues.Add(FString::Printf(TEXT("%d invalid renderers found"), Report.InvalidRenderersRemoved));
		Score -= 0.2f * Report.InvalidRenderersRemoved;
	}
	
	if (ValidRenderers > 0)
	{
		OutBreakdown.Strengths.Add(FString::Printf(TEXT("%d valid renderer(s)"), ValidRenderers));
	}
	
	return FMath::Clamp(Score, 0.0f, 1.0f);
}

float FVFXQualityScorer::ScoreModuleStack(UNiagaraEmitter* Emitter, const FMotionBehaviorConfig& MotionConfig, FQualityScoreBreakdown& OutBreakdown)
{
	if (!Emitter)
		return 0.0f;
	
	float Score = 1.0f;
	
	// Check for forbidden modules
	int32 ForbiddenCount = 0;
	for (const FString& ForbiddenPattern : MotionConfig.ForbiddenModulePatterns)
	{
		if (HasForbiddenModule(Emitter, ForbiddenPattern))
		{
			ForbiddenCount++;
			OutBreakdown.ForbiddenModulesFound++;
			OutBreakdown.Issues.Add(FString::Printf(TEXT("Forbidden module found: %s"), *ForbiddenPattern));
			Score -= 0.2f; // Penalize each forbidden module
		}
	}
	
	// Check for required modules
	int32 MissingCount = 0;
	for (const FMotionModuleDescriptor& RequiredModule : MotionConfig.RequiredModules)
	{
		if (RequiredModule.bRequired)
		{
			if (!HasRequiredModule(Emitter, RequiredModule.ModulePath))
			{
				MissingCount++;
				OutBreakdown.RequiredModulesMissing++;
				OutBreakdown.Issues.Add(FString::Printf(TEXT("Required module missing: %s"), *RequiredModule.DisplayName));
				Score -= 0.15f; // Penalize missing required modules
			}
		}
	}
	
	if (ForbiddenCount == 0 && MissingCount == 0)
	{
		OutBreakdown.Strengths.Add(TEXT("Module stack correct"));
	}
	
	return FMath::Clamp(Score, 0.0f, 1.0f);
}

float FVFXQualityScorer::ScoreConstraintCompliance(UNiagaraEmitter* Emitter, const FVFXIntent& Intent, FQualityScoreBreakdown& OutBreakdown)
{
	if (!Emitter)
		return 0.0f;
	
	float Score = 1.0f;
	
	// Check avoidance constraints
	if (Intent.Avoidance.bAvoidConeVelocity)
	{
		if (HasForbiddenModule(Emitter, TEXT("Add Velocity In Cone")))
		{
			OutBreakdown.Issues.Add(TEXT("Cone velocity present (forbidden by intent)"));
			Score -= 0.25f;
		}
	}
	
	if (Intent.Avoidance.bAvoidUniformGravity)
	{
		if (HasForbiddenModule(Emitter, TEXT("Gravity")))
		{
			OutBreakdown.Issues.Add(TEXT("Gravity present (forbidden by intent)"));
			Score -= 0.25f;
		}
	}
	
	if (Intent.Motion.PrimaryModel == EVFXMotionModel::Static)
	{
		// Static motion should have no velocity modules
		if (HasForbiddenModule(Emitter, TEXT("Add Velocity")))
		{
			OutBreakdown.Issues.Add(TEXT("Velocity module in static motion"));
			Score -= 0.3f;
		}
	}
	
	return FMath::Clamp(Score, 0.0f, 1.0f);
}

float FVFXQualityScorer::ScoreMotionBehavior(UNiagaraEmitter* Emitter, const FMotionBehaviorConfig& MotionConfig, FQualityScoreBreakdown& OutBreakdown)
{
	if (!Emitter)
		return 0.0f;
	
	// This is a simplified motion behavior check
	// In a full implementation, you'd validate motion curves, parameters, etc.
	
	float Score = 0.5f; // Start with neutral score
	
	// Bonus points for having required motion modules
	int32 RequiredModulesPresent = 0;
	for (const FMotionModuleDescriptor& RequiredModule : MotionConfig.RequiredModules)
	{
		if (RequiredModule.bRequired)
		{
			if (HasRequiredModule(Emitter, RequiredModule.ModulePath))
			{
				RequiredModulesPresent++;
				Score += 0.2f;
			}
		}
	}
	
	if (RequiredModulesPresent > 0)
	{
		OutBreakdown.Strengths.Add(FString::Printf(TEXT("%d motion module(s) present"), RequiredModulesPresent));
	}
	
	return FMath::Clamp(Score, 0.0f, 1.0f);
}

bool FVFXQualityScorer::HasForbiddenModule(UNiagaraEmitter* Emitter, const FString& Pattern)
{
	if (!Emitter || Pattern.IsEmpty())
		return false;
	
	TArray<UNiagaraScript*> Modules = FVFXModuleStripper::GetAllModules(Emitter);
	
	for (UNiagaraScript* Module : Modules)
	{
		if (FVFXModuleStripper::ModuleMatchesPattern(Module, Pattern))
		{
			return true;
		}
	}
	
	return false;
}

bool FVFXQualityScorer::HasRequiredModule(UNiagaraEmitter* Emitter, const FString& ModulePath)
{
	if (!Emitter || ModulePath.IsEmpty())
		return false;
	
	TArray<UNiagaraScript*> Modules = FVFXModuleStripper::GetAllModules(Emitter);
	
	for (UNiagaraScript* Module : Modules)
	{
		if (!Module) continue;
		
		FString ModulePathStr = Module->GetPathName();
		if (ModulePathStr.Contains(ModulePath, ESearchCase::IgnoreCase))
		{
			return true;
		}
	}
	
	return false;
}
