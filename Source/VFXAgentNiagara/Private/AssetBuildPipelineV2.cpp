// DEPRECATED: AssetBuildPipelineV2.cpp
// Stubbed as part of the VFXAgent Python-first architecture refactor.
// C++ no longer builds Niagara assets from EffectSpec V2.
// The LLM now returns executable UE5 Python scripts directly.
#include "AssetBuildPipelineV2.h"
#include "VFXAgentLog.h"

bool FAssetBuildPipelineV2::BuildFromV2Spec(const FEffectSpecV2& Spec, const FString& OutputRootPath, FAssetBuildResult& OutResult)
{
	UE_LOG(LogVFXAgent, Warning, TEXT("FAssetBuildPipelineV2::BuildFromV2Spec is deprecated. Use Python script execution instead."));
	OutResult.bSuccess = false;
	OutResult.Errors.Add(TEXT("Deprecated: C++ V2 pipeline removed. Use Python executor."));
	return false;
}

void FAssetBuildPipelineV2::ApplySpawnConfig(UNiagaraSystem* System, const FString& EmitterName, const FLayerSpawnV2& Spawn) {}
void FAssetBuildPipelineV2::ApplyTimingEnvelope(UNiagaraSystem* System, const FString& EmitterName, const FTimingEnvelopeV2& Timing) {}
void FAssetBuildPipelineV2::ApplyMotionVerb(UNiagaraSystem* System, const FString& EmitterName, const FMotionDescV2& Motion, const FLayerUpdateV2& Update) {}

UMaterialInterface* FAssetBuildPipelineV2::BuildV2Material(const FMaterialSpecV2& MatSpec, const FString& OutputPath, const FString& MaterialName, const FString& EffectName, const FString& LayerName)
{
	return nullptr;
}

void FAssetBuildPipelineV2::ApplyEventBindings(UNiagaraSystem* System, const FEffectSpecV2& Spec, FAssetBuildResult& OutResult) {}

FString FAssetBuildPipelineV2::ResolveOutputFolder(const FString& OutputRootPath, const FString& EffectName, const FString& SpecHash)
{
	return FString();
}
