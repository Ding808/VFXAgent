// DEPRECATED: VFXTemplateSelector.cpp
// Stubbed as part of the VFXAgent Python-first architecture refactor.
// C++ no longer selects Niagara templates or construction strategies.
#include "VFXTemplateSelector.h"
#include "VFXAgentLog.h"

FTemplateSelectionResult FVFXTemplateSelector::SelectStrategy(const FVFXIntent& Intent, const FVFXEmitterSpec& EmitterSpec)
{
UE_LOG(LogVFXAgent, Warning, TEXT("FVFXTemplateSelector is deprecated. Use Python script execution instead."));
FTemplateSelectionResult Result;
Result.Strategy = EConstructionStrategy::BuildFromScratch;
Result.bMustStripAllVelocity = false;
Result.bMustStripGravity = false;
Result.bMustStripNoise = false;
return Result;
}

bool FVFXTemplateSelector::ShouldBuildFromScratch(const FVFXIntent& Intent, const FMotionBehaviorConfig& MotionConfig)
{
return true;
}

FString FVFXTemplateSelector::GetTemplatePathForStrategy(EConstructionStrategy Strategy, const FVFXIntent& Intent)
{
return FString();
}

bool FVFXTemplateSelector::IsTemplateCompatible(const FString& TemplatePath, const FMotionBehaviorConfig& MotionConfig)
{
return false;
}

EConstructionStrategy FVFXTemplateSelector::DetermineStrategyForArchetype(EVFXArchetype Archetype, EVFXMotionModel MotionModel)
{
return EConstructionStrategy::BuildFromScratch;
}

FString FVFXTemplateSelector::GetReasonForStrategy(EConstructionStrategy Strategy, const FVFXIntent& Intent)
{
return TEXT("Deprecated: Use Python executor");
}
