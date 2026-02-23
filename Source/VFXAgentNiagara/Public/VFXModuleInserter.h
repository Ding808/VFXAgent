#pragma once

#include "CoreMinimal.h"
#include "NiagaraCommon.h"
#include "NiagaraScript.h"
#include "VFXMotionModuleLibrary.h"

class UNiagaraEmitter;
class UNiagaraScript;
class UNiagaraScriptSourceBase;
class UNiagaraGraph;
class UNiagaraNodeOutput;
class UNiagaraNodeFunctionCall;
class UEdGraphPin;
struct FNiagaraTypeDefinition;

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
	static bool InsertModuleByPath(UNiagaraEmitter* Emitter, const FMotionModuleDescriptor& Module, FString& OutError);

private:
	static FString NormalizeModulePath(const FString& InPath);
	static UNiagaraScript* LoadScript(const FString& ModulePath);

	/** Insert a module script into the correct graph layer of the emitter using FNiagaraStackGraphUtilities */
	static bool InsertScriptViaGraphSource(UNiagaraEmitter* Emitter, UNiagaraScript* Script, const FMotionModuleDescriptor& Module, FString& OutError);

	/** Apply default parameter overrides via Rapid Iteration parameters after inserting a module node */
	static void ApplyDefaultParamsToModuleNode(
		UNiagaraNodeFunctionCall* ModuleNode,
		const FMotionModuleDescriptor& Module,
		UNiagaraScript* TargetScript,
		const FString& UniqueEmitterName,
		ENiagaraScriptUsage ScriptUsage);

	/** Map module phase + path to the correct ENiagaraScriptUsage graph section */
	static ENiagaraScriptUsage GetScriptUsageForPhase(EModulePhase Phase, const FString& ModulePath);
};
