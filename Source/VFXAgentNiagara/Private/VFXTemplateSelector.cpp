#include "VFXTemplateSelector.h"
#include "VFXAgentLog.h"

FTemplateSelectionResult FVFXTemplateSelector::SelectStrategy(const FVFXIntent& Intent, const FVFXEmitterSpec& EmitterSpec)
{
	FTemplateSelectionResult Result;
	
	// Get motion configuration
	EMotionArchetype MotionArchetype = FVFXMotionModuleLibrary::DetermineMotionArchetype(Intent);
	FMotionBehaviorConfig MotionConfig = FVFXMotionModuleLibrary::GetMotionConfigByArchetype(MotionArchetype);
	
	// Check if spec specifies a custom template (Note: FVFXEmitterSpec may not have TemplateName)
	// For now, proceed with strategy determination
	if (false) // Placeholder - FVFXEmitterSpec doesn't have TemplateName field
	{
		Result.Strategy = EConstructionStrategy::Custom;
		Result.TemplatePath = TEXT("");
		Result.StrategyReason = TEXT("Custom template");
	}
	// Check if we should build from scratch (complex constraints)
	else if (ShouldBuildFromScratch(Intent, MotionConfig))
	{
		Result.Strategy = EConstructionStrategy::BuildFromScratch;
		Result.TemplatePath = TEXT(""); // No template
		Result.StrategyReason = GetReasonForStrategy(Result.Strategy, Intent);
	}
	else
	{
		// Determine strategy based on archetype and motion
		Result.Strategy = DetermineStrategyForArchetype(Intent.Archetype, Intent.Motion.PrimaryModel);
		Result.TemplatePath = GetTemplatePathForStrategy(Result.Strategy, Intent);
		Result.StrategyReason = GetReasonForStrategy(Result.Strategy, Intent);
	}
	
	// Build list of modules to strip based on motion config
	Result.ModulesToStrip = MotionConfig.ForbiddenModulePatterns;
	Result.bMustStripGravity = MotionConfig.bForbidsGravity || Intent.Avoidance.bAvoidUniformGravity;
	Result.bMustStripAllVelocity = (MotionArchetype == EMotionArchetype::Static);
	Result.bMustStripNoise = MotionConfig.bForbidsNoise;
	
	// Add forbidden patterns from intent avoidance
	if (Intent.Avoidance.bAvoidConeVelocity)
	{
		Result.ModulesToStrip.AddUnique(TEXT("Add Velocity In Cone"));
	}
	if (Intent.Avoidance.bAvoidRadialExplosion && MotionArchetype != EMotionArchetype::RadialOutward)
	{
		Result.ModulesToStrip.AddUnique(TEXT("Radial"));
	}
	
	// Build list of modules to add
	Result.ModulesToAdd = MotionConfig.RequiredModules;
	
	UE_LOG(LogVFXAgent, Log, TEXT("Template Selection: Strategy=%s, Template=%s, Reason=%s"),
		StrategyToString(Result.Strategy),
		*Result.TemplatePath,
		*Result.StrategyReason);
	
	return Result;
}

bool FVFXTemplateSelector::ShouldBuildFromScratch(const FVFXIntent& Intent, const FMotionBehaviorConfig& MotionConfig)
{
	// Build from scratch if:
	// 1. Multiple complex avoidance constraints
	int32 AvoidanceCount = 0;
	if (Intent.Avoidance.bAvoidConeVelocity) AvoidanceCount++;
	if (Intent.Avoidance.bAvoidRadialExplosion) AvoidanceCount++;
	if (Intent.Avoidance.bAvoidUniformGravity) AvoidanceCount++;
	if (Intent.Avoidance.bAvoidUniformRotation) AvoidanceCount++;
	
	if (AvoidanceCount >= 3)
		return true;
	
	// 2. Static motion with many constraints
	if (Intent.Motion.PrimaryModel == EVFXMotionModel::Static && AvoidanceCount >= 2)
		return true;
	
	// 3. Tornado/Vortex with strict no-cone requirement
	if ((Intent.Archetype == EVFXArchetype::Tornado || Intent.Motion.PrimaryModel == EVFXMotionModel::Vortex) &&
		Intent.Avoidance.bAvoidConeVelocity)
		return true;
	
	// 4. More than 4 forbidden module patterns
	if (MotionConfig.ForbiddenModulePatterns.Num() > 4)
		return true;
	
	return false;
}

EConstructionStrategy FVFXTemplateSelector::DetermineStrategyForArchetype(EVFXArchetype Archetype, EVFXMotionModel MotionModel)
{
	// Map archetype + motion to strategy
	
	switch (MotionModel)
	{
		case EVFXMotionModel::Static:
			return EConstructionStrategy::TemplateMinimal; // Minimal has least assumptions
		
		case EVFXMotionModel::Orbit:
		case EVFXMotionModel::Vortex:
			return EConstructionStrategy::TemplateMinimal; // Tornado needs custom setup
		
		case EVFXMotionModel::RadialInward:
			return EConstructionStrategy::TemplateMinimal; // Attraction is custom
		
		case EVFXMotionModel::Vertical:
			return EConstructionStrategy::TemplateMinimal; // Updraft is custom

		case EVFXMotionModel::Radial:
			return EConstructionStrategy::TemplateMinimal; // Avoid burst template by default
		
		default:
			break;
	}
	
	// Fallback to archetype
	switch (Archetype)
	{
		case EVFXArchetype::Trail:
			return EConstructionStrategy::BuildFromScratch;
		
		case EVFXArchetype::Tornado:
		case EVFXArchetype::Aura:
		case EVFXArchetype::Smoke:
		case EVFXArchetype::Fire:
		case EVFXArchetype::Dust:
			return EConstructionStrategy::TemplateMinimal;

		case EVFXArchetype::Explosion:
		case EVFXArchetype::Impact:
		case EVFXArchetype::Fountain:
		case EVFXArchetype::Beam:
			return EConstructionStrategy::TemplateMinimal;
		
		default:
			return EConstructionStrategy::TemplateMinimal; // Safe default
	}
}

FString FVFXTemplateSelector::GetTemplatePathForStrategy(EConstructionStrategy Strategy, const FVFXIntent& Intent)
{
	switch (Strategy)
	{
		case EConstructionStrategy::BuildFromScratch:
			return TEXT(""); // No template
		
		case EConstructionStrategy::TemplateMinimal:
			return TEXT("/Niagara/DefaultAssets/Templates/Emitters/Minimal.Minimal");
		
		case EConstructionStrategy::Custom:
		default:
			return TEXT("/Niagara/DefaultAssets/Templates/Emitters/Minimal.Minimal");
	}
}

bool FVFXTemplateSelector::IsTemplateCompatible(const FString& TemplatePath, const FMotionBehaviorConfig& MotionConfig)
{
	// Check if template name suggests incompatible behaviors
	const FString Name = TemplatePath.ToLower();
	
	for (const FString& Forbidden : MotionConfig.ForbiddenModulePatterns)
	{
		if (Name.Contains(Forbidden.ToLower()))
			return false;
	}
	
	// Fountain template has cone velocity - incompatible if that's forbidden
	if (Name.Contains(TEXT("fountain")) && MotionConfig.ForbiddenModulePatterns.Contains(TEXT("Cone")))
		return false;
	
	return true;
}

FString FVFXTemplateSelector::GetReasonForStrategy(EConstructionStrategy Strategy, const FVFXIntent& Intent)
{
	switch (Strategy)
	{
		case EConstructionStrategy::BuildFromScratch:
			return FString::Printf(TEXT("BuildFromScratch: Complex constraints for %s with %s motion"),
				*UEnum::GetValueAsString(Intent.Archetype),
				*UEnum::GetValueAsString(Intent.Motion.PrimaryModel));
		
		case EConstructionStrategy::TemplateMinimal:
			return FString::Printf(TEXT("TemplateMinimal: Clean base for %s"),
				*UEnum::GetValueAsString(Intent.Archetype));
		
		case EConstructionStrategy::TemplateFountain:
			return TEXT("TemplateFountain: Directional spray effect");
		
		case EConstructionStrategy::TemplateBurst:
			return TEXT("TemplateBurst: Explosion/burst effect");
		
		case EConstructionStrategy::TemplateRibbon:
			return TEXT("TemplateRibbon: Trail effect");
		
		case EConstructionStrategy::Custom:
			return TEXT("Custom: User-specified template");
		
		default:
			return TEXT("Default strategy");
	}
}
