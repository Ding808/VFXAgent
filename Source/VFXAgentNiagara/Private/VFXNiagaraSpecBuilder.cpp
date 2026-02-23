// DEPRECATED: VFXNiagaraSpecBuilder.cpp
// This file has been stubbed out as part of the VFXAgent Python-first architecture refactor.
// C++ no longer assembles Niagara graph nodes directly.
// The LLM now returns executable UE5 Python scripts instead of structured JSON recipes.
#include "VFXNiagaraSpecBuilder.h"
#include "VFXAgentLog.h"

UNiagaraSystem* FVFXNiagaraSpecBuilder::BuildFromSpec(const FVFXEffectSpec& Spec, FNiagaraBuildContext& OutContext)
{
UE_LOG(LogVFXAgent, Warning, TEXT("FVFXNiagaraSpecBuilder::BuildFromSpec is deprecated. Use Python script execution instead."));
OutContext.bSuccess = false;
OutContext.ErrorMessage = TEXT("Deprecated: C++ Niagara assembly removed. Use Python executor.");
return nullptr;
}

UNiagaraSystem* FVFXNiagaraSpecBuilder::BuildFromSpecV2(const FEffectSpecV2& Spec, FNiagaraBuildContextV2& OutContext)
{
UE_LOG(LogVFXAgent, Warning, TEXT("FVFXNiagaraSpecBuilder::BuildFromSpecV2 is deprecated. Use Python script execution instead."));
OutContext.bSuccess = false;
OutContext.ErrorMessage = TEXT("Deprecated: C++ Niagara assembly removed. Use Python executor.");
return nullptr;
}

UNiagaraEmitter* FVFXNiagaraSpecBuilder::BuildEmitter(const FVFXEmitterSpec& EmitterSpec, const FVFXIntent& Intent, FNiagaraBuildContext& OutContext)
{
UE_LOG(LogVFXAgent, Warning, TEXT("FVFXNiagaraSpecBuilder::BuildEmitter is deprecated."));
return nullptr;
}

bool FVFXNiagaraSpecBuilder::ApplyMotionBehavior(UNiagaraEmitter* Emitter, const FMotionBehaviorConfig& MotionConfig, const FVFXIntent& Intent, FNiagaraBuildContext& OutContext)
{
return false;
}

bool FVFXNiagaraSpecBuilder::EnforceConstraints(UNiagaraEmitter* Emitter, const FTemplateSelectionResult& SelectionResult, FNiagaraBuildContext& OutContext)
{
return false;
}

bool FVFXNiagaraSpecBuilder::ValidateAndFixRenderers(UNiagaraEmitter* Emitter, UMaterialInterface* DefaultMaterial, FNiagaraBuildContext& OutContext)
{
return false;
}

void FVFXNiagaraSpecBuilder::LogBuildAction(FNiagaraBuildContext& Context, const FString& Action)
{
Context.BuildLog.Add(Action);
}

void FVFXNiagaraSpecBuilder::LogBuildActionV2(FNiagaraBuildContextV2& Context, const FString& Action)
{
Context.BuildLog.Add(Action);
}

void FVFXNiagaraSpecBuilder::SetupUserParameters(UNiagaraSystem* System, const FVFXEffectSpec& Spec, FNiagaraBuildContext& OutContext)
{
}

UNiagaraEmitter* FVFXNiagaraSpecBuilder::CreateFromTemplate(const FString& TemplatePath, const FString& EmitterName)
{
return nullptr;
}

UNiagaraEmitter* FVFXNiagaraSpecBuilder::CreateFromScratch(const FString& EmitterName)
{
return nullptr;
}

UNiagaraEmitter* FVFXNiagaraSpecBuilder::BuildEmitterV2(const FLayerSpecV2& Layer, FNiagaraBuildContextV2& Context)
{
return nullptr;
}

void FVFXNiagaraSpecBuilder::ConfigureEmitterMotionV2(UNiagaraEmitter* Emitter, const FLayerSpecV2& Layer, FNiagaraBuildContextV2& Context)
{
}
