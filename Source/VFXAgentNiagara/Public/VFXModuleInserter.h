#pragma once

#include "CoreMinimal.h"
#include "VFXMotionModuleLibrary.h"

class UNiagaraEmitter;
class UNiagaraScript;

struct FModuleInsertResult
{
	int32 ModulesInserted = 0;
	TArray<FString> InsertedModuleNames;
	TArray<FString> FailedModules;
	bool bSuccess = true;
	FString ErrorMessage;
};

/**
 * Module Inserter - Inserts required modules into Niagara emitter stacks
 * Uses deterministic phase anchors: Forces -> Damping -> Collision -> EventWrite -> Curves -> RenderPrep -> Kill
 */
class VFXAGENTNIAGARA_API FVFXModuleInserter
{
public:
	/**
	 * Insert a list of motion modules into the emitter
	 */
	static FModuleInsertResult InsertModules(UNiagaraEmitter* Emitter, const TArray<FMotionModuleDescriptor>& Modules, const FString& DebugTag);

	/**
	 * Insert a single module by script path
	 */
	static bool InsertModuleByPath(UNiagaraEmitter* Emitter, const FString& ModulePath, EModulePhase Phase, int32 Priority, FString& OutError);

private:
	static FString NormalizeModulePath(const FString& InPath);
	static UNiagaraScript* LoadScript(const FString& ModulePath);
	static bool InsertScriptWithOrdering(UNiagaraEmitter* Emitter, const FName& ArrayPropName, UNiagaraScript* Script, EModulePhase Phase);
	static int32 FindInsertIndexForPhase(UNiagaraEmitter* Emitter, const FName& ArrayPropName, EModulePhase Phase);
	static UNiagaraScript* GetScriptFromEntry(void* ElemPtr, UStruct* StructType);
	static bool SetStructObjectField(void* StructPtr, UStruct* StructType, const FName& FieldName, UObject* Value);
	static FName GetStackNameForPhase(EModulePhase Phase);
};
