#pragma once

#include "CoreMinimal.h"

class UNiagaraEmitter;
class UNiagaraScript;

/**
 * Module Stripper - Removes forbidden modules from Niagara emitter stacks
 * Can match modules by:
 *  - Script asset path
 *  - Module display name patterns
 *  - Module class/type
 */

struct FModuleStripResult
{
	int32 ModulesRemoved = 0;
	TArray<FString> RemovedModuleNames;
	TArray<FString> FailedToRemove; // Modules that matched but couldn't be removed
	bool bSuccess = true;
	FString ErrorMessage;
};

class VFXAGENTNIAGARA_API FVFXModuleStripper
{
public:
	/**
	 * Remove modules matching any of the patterns from the emitter
	 * @param Emitter - The emitter to modify
	 * @param Patterns - Array of patterns to match (e.g., "Add Velocity", "Gravity", etc.)
	 * @return Strip result with count and details
	 */
	static FModuleStripResult StripModulesByPattern(UNiagaraEmitter* Emitter, const TArray<FString>& Patterns);

	/**
	 * Remove modules matching exact script asset paths
	 */
	static FModuleStripResult StripModulesByPath(UNiagaraEmitter* Emitter, const TArray<FString>& ScriptPaths);

	/**
	 * Remove modules matching script class names
	 */
	static FModuleStripResult StripModulesByClassName(UNiagaraEmitter* Emitter, const TArray<FString>& ClassNames);
	
	/**
	 * Remove specific module categories
	 */
	static FModuleStripResult StripAllVelocityModules(UNiagaraEmitter* Emitter);
	static FModuleStripResult StripGravityModules(UNiagaraEmitter* Emitter);
	static FModuleStripResult StripNoiseModules(UNiagaraEmitter* Emitter);
	static FModuleStripResult StripConeVelocityModules(UNiagaraEmitter* Emitter);
	
	/**
	 * Remove a specific module by script reference
	 */
	static bool RemoveModuleByScript(UNiagaraEmitter* Emitter, UNiagaraScript* ScriptToRemove);
	
	/**
	 * Check if a module matches a pattern
	 */
	static bool ModuleMatchesPattern(UNiagaraScript* Module, const FString& Pattern);

	/**
	 * Check if a module matches a class name
	 */
	static bool ModuleMatchesClass(UNiagaraScript* Module, const FString& ClassName);
	
	/**
	 * Get all modules in an emitter (from all stacks)
	 */
	static TArray<UNiagaraScript*> GetAllModules(UNiagaraEmitter* Emitter);

private:
	static bool RemoveFromStack(UNiagaraEmitter* Emitter, const FName& StackArrayName, UNiagaraScript* Script);
	static void GetModulesFromStack(UNiagaraEmitter* Emitter, const FName& StackArrayName, TArray<UNiagaraScript*>& OutModules);
};
