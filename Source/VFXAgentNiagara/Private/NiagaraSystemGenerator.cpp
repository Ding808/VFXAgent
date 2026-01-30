#include "NiagaraSystemGenerator.h"
#include "NiagaraSpecExecutor.h"
#include "VFXAgentLog.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"

// NOTE: Removed automatic repair/retry logic that appended "_Fixed" to the system name.
// Generation now performs a single Create + Save/Compile + SelfCheck pass.

UNiagaraSystem* UNiagaraSystemGenerator::GenerateNiagaraSystem(
    const FString& SystemName,
    const FString& OutputPath,
    const FVFXRecipe& Recipe,
    const FString& TemplateSystemPath)
{
    UE_LOG(LogVFXAgent, Log, TEXT("Starting Niagara Generation Refactor for: %s"), *SystemName);

    // 1. Convert Legacy Recipe to New Spec
    FVFXEffectSpec Spec;
    Spec.SystemName = SystemName;
    Spec.TargetPath = OutputPath;

    if (Recipe.Emitters.Num() > 0)
    {
        for (const FVFXEmitterRecipe& SrcEmitter : Recipe.Emitters)
        {
            FVFXEmitterSpec EmitterSpec;
            EmitterSpec.Name = SrcEmitter.Name.IsEmpty() ? TEXT("Emitter") : SrcEmitter.Name;
            EmitterSpec.TemplatePath = FString();
            if (!SrcEmitter.TemplateName.IsEmpty())
            {
                EmitterSpec.TemplateId = SrcEmitter.TemplateName;
            }
            else if (!TemplateSystemPath.IsEmpty())
            {
                EmitterSpec.TemplatePath = TemplateSystemPath;
            }
            
            if (SrcEmitter.RendererType == "Ribbon") EmitterSpec.RendererType = EVFXRendererType::Ribbon;
            else if (SrcEmitter.RendererType == "Light") EmitterSpec.RendererType = EVFXRendererType::Light;
            else EmitterSpec.RendererType = EVFXRendererType::Sprite;

            EmitterSpec.Spawn.Rate = SrcEmitter.SpawnRate;
            EmitterSpec.Spawn.Burst = SrcEmitter.BurstCount;
            EmitterSpec.Color = SrcEmitter.Color;
            EmitterSpec.Lifetime = SrcEmitter.Lifetime;
            EmitterSpec.Size = SrcEmitter.Size;
            EmitterSpec.Velocity = SrcEmitter.Velocity;

            Spec.Emitters.Add(EmitterSpec);
        }
    }
    else
    {
        // Fallback for empty recipe or legacy single-emitter interpretation
        FVFXEmitterSpec EmitterSpec;
        EmitterSpec.Name = TEXT("MainEmitter");
        EmitterSpec.TemplateId = "Fountain";
        EmitterSpec.RendererType = EVFXRendererType::Sprite;
        Spec.Emitters.Add(EmitterSpec);
    }
    
    // 2. Validate
    FString SpecError;
    if (!FNiagaraSpecExecutor::ValidateSpec(Spec, SpecError))
    {
        UE_LOG(LogVFXAgent, Error, TEXT("Spec Validation Failed: %s"), *SpecError);
        return nullptr;
    }

    // 3. Single-pass execution: create, save/compile and self-check once.
    UE_LOG(LogVFXAgent, Log, TEXT("Generating System (single attempt)"));
    UNiagaraSystem* ResultSystem = FNiagaraSpecExecutor::CreateSystemFromSpec(Spec);
    if (!ResultSystem)
    {
        UE_LOG(LogVFXAgent, Error, TEXT("Failed to create system from spec: %s"), *Spec.SystemName);
        return nullptr;
    }

    FVFXRepairReport Report;
    if (FNiagaraSpecExecutor::SaveCompileAndSelfCheck(ResultSystem, Report))
    {
        UE_LOG(LogVFXAgent, Log, TEXT("Generation Success! Asset: %s"), *Report.SystemPath);
        return ResultSystem;
    }

    UE_LOG(LogVFXAgent, Warning, TEXT("SelfCheck Failed for system '%s' but automatic repair/retry is disabled."), *Spec.SystemName);
    for (const FString& E : Report.Errors)
    {
        UE_LOG(LogVFXAgent, Warning, TEXT("Error: %s"), *E);
    }

    // Return the generated system even if self-check failed; caller can decide further action.
    return ResultSystem;
}

bool UNiagaraSystemGenerator::UpdateNiagaraSystem(UNiagaraSystem* System, const FVFXRecipe& Recipe)
{
    // Simplified update using Executor's Configure
    if (!System) return false;
    
    // We only update if we have at least one emitter in the recipe
    if(Recipe.Emitters.Num() == 0) return false;

    const FVFXEmitterRecipe& SrcEmitter = Recipe.Emitters[0];

    FVFXEmitterSpec EmitterSpec;
    EmitterSpec.Spawn.Rate = SrcEmitter.SpawnRate;
    EmitterSpec.Lifetime = SrcEmitter.Lifetime;
    EmitterSpec.Spawn.Burst = SrcEmitter.BurstCount;
    EmitterSpec.Color = SrcEmitter.Color;
    
    // Assumes we update the first emitter or matching name
    FString EmitterName = SrcEmitter.Name.IsEmpty() ? "MainEmitter" : SrcEmitter.Name;
    FNiagaraSpecExecutor::ConfigureEmitter(System, EmitterName, EmitterSpec);
    return true;
}

// Private dummy implementations to satisfy linker/header
UNiagaraEmitter* UNiagaraSystemGenerator::CreateBasicEmitter(const FVFXEmitterRecipe& EmitterRecipe, UNiagaraSystem* ParentSystem)
{
    return nullptr;
}

bool UNiagaraSystemGenerator::BindMaterialToEmitter(class UNiagaraEmitter* Emitter, const FVFXMaterialRecipe& MaterialRecipe)
{
    return false;
}

class UMaterialInstanceConstant* UNiagaraSystemGenerator::GetOrCreateBasicMaterial(const FString& Path, const FVFXMaterialRecipe& MaterialRecipe)
{
    return nullptr;
}
