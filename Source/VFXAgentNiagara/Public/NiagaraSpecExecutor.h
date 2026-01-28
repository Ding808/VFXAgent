#pragma once

#include "CoreMinimal.h"
#include "VFXRecipe.h"
#include "NiagaraSystem.h"

class VFXAGENTNIAGARA_API FNiagaraSpecExecutor
{
public:
	// Helper to validate the spec before execution
	static bool ValidateSpec(const FVFXEffectSpec& Spec, FString& OutError);

	// Main entry point to create the system from spec
	static UNiagaraSystem* CreateSystemFromSpec(const FVFXEffectSpec& Spec);

	// Individual steps (exposed for fine-grained control if needed)
	static UNiagaraSystem* CreateNiagaraSystemAsset(const FString& TargetPath, const FString& SystemName);
	static bool AddEmitterFromTemplate(UNiagaraSystem* System, const FString& TemplatePath, const FString& EmitterName);
	static void ConfigureEmitter(UNiagaraSystem* System, const FString& EmitterName, const FVFXEmitterSpec& Spec);
	
	// Returns true if compilation succeeded and semantic checks passed
	static bool SaveCompileAndSelfCheck(UNiagaraSystem* System, FVFXRepairReport& OutReport);

private:
	static void SetVariableFloat(UNiagaraSystem* System, const FString& EmitterName, const FString& VarName, float Value);
	static void SetVariableVec3(UNiagaraSystem* System, const FString& EmitterName, const FString& VarName, FVector Value);
	static void SetVariableLinearColor(UNiagaraSystem* System, const FString& EmitterName, const FString& VarName, FLinearColor Value);
};
