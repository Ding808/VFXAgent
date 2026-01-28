#include "NiagaraSystemGenerator.h"
#include "NiagaraSpecExecutor.h"
#include "VFXAgentLog.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"

// Mock LLM repair function for the loop
// In a real scenario, this would call an external service with the RepairReport
FVFXEffectSpec MockLLMRepair(const FVFXEffectSpec& OriginalSpec, const FVFXRepairReport& Report)
{
    FVFXEffectSpec NewSpec = OriginalSpec;
    NewSpec.SystemName += "_Fixed";
    
    // Simple logic to fix common errors reported by SelfCheck
    for (FVFXEmitterSpec& Emitter : NewSpec.Emitters)
    {
        // Fix missing renderer
        bool bRendererError = false;
        for(const FString& Err : Report.Errors) 
        { 
            if(Err.Contains("no renderer")) bRendererError = true; 
        }
        
        // Fix zero spawn
        // If the report says "compile failed" or verify logic found issues
        if(Emitter.Spawn.Rate <= 0.0f && Emitter.Spawn.Burst <= 0)
        {
            Emitter.Spawn.Rate = 20.0f; // Fix: Add spawn rate
        }
        
        // Logic could be more complex here
    }
    return NewSpec;
}

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

    // 3. Execution Loop with Repair
    const int32 MaxRetries = 2;
    UNiagaraSystem* ResultSystem = nullptr;

    for (int32 Attempt = 0; Attempt <= MaxRetries; ++Attempt)
    {
        if (Attempt > 0)
        {
             // Update name for versioning
             // Note: CreateNiagaraSystemAsset uses the name in spec
        }

        UE_LOG(LogVFXAgent, Log, TEXT("Generating System Attempt %d"), Attempt);
        
        ResultSystem = FNiagaraSpecExecutor::CreateSystemFromSpec(Spec);
        
        if (ResultSystem)
        {
            FVFXRepairReport Report;
            if (FNiagaraSpecExecutor::SaveCompileAndSelfCheck(ResultSystem, Report))
            {
                UE_LOG(LogVFXAgent, Log, TEXT("Generation Generation Success! Asset: %s"), *Report.SystemPath);
                return ResultSystem;
            }
            else
            {
                UE_LOG(LogVFXAgent, Warning, TEXT("SelfCheck Failed. Attempting repair..."));
                for(const FString& E : Report.Errors) UE_LOG(LogVFXAgent, Warning, TEXT("Error: %s"), *E);
                
                // Feedback to "LLM"
                Spec = MockLLMRepair(Spec, Report);
            }
        }
    }

    UE_LOG(LogVFXAgent, Error, TEXT("Failed to generate valid system after retries."));
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
