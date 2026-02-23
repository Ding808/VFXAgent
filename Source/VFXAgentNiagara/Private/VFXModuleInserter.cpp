#include "VFXModuleInserter.h"
#include "VFXAgentLog.h"
#include "Misc/Paths.h"
#include "Runtime/Launch/Resources/Version.h"

// Niagara Runtime
#include "NiagaraCommon.h"
#include "NiagaraEmitter.h"
#include "NiagaraSystem.h"
#include "NiagaraScript.h"
#include "NiagaraTypes.h"
#include "NiagaraParameterStore.h"

// Niagara Editor (graph layer - accessible because VFXAgentNiagara is an Editor module)
#include "NiagaraScriptSource.h"
#include "NiagaraGraph.h"
#include "NiagaraNodeOutput.h"
#include "NiagaraNodeFunctionCall.h"
#include "ViewModels/Stack/NiagaraStackGraphUtilities.h"
#include "ViewModels/Stack/NiagaraParameterHandle.h"

// ============================================================
// Internal Helpers
// ============================================================

FModuleInsertResult FVFXModuleInserter::InsertModules(UNiagaraEmitter* Emitter, const TArray<FMotionModuleDescriptor>& Modules, const FString& DebugTag)
{
	FModuleInsertResult Result;
	if (!Emitter)
	{
		Result.bSuccess = false;
		Result.ErrorMessage = TEXT("Null emitter");
		return Result;
	}

	for (const FMotionModuleDescriptor& Module : Modules)
	{
		if (Module.ModulePath.IsEmpty())
		{
			Result.FailedModules.Add(Module.DisplayName.IsEmpty() ? TEXT("UnknownModule") : Module.DisplayName);
			continue;
		}

		FString Error;
		if (InsertModuleByPath(Emitter, Module, Error))
		{
			Result.ModulesInserted++;
			Result.InsertedModuleNames.Add(Module.DisplayName.IsEmpty() ? Module.ModulePath : Module.DisplayName);
		}
		else
		{
			const FString Name = Module.DisplayName.IsEmpty() ? Module.ModulePath : Module.DisplayName;
			Result.FailedModules.Add(Name);
			UE_LOG(LogVFXAgent, Warning, TEXT("Module insert failed (%s): %s"), *DebugTag, *Error);
			UE_LOG(LogVFXAgent, Warning, TEXT("MOTION_NOT_SUPPORTED: %s"), *Name);
		}
	}

	if (Result.FailedModules.Num() > 0)
	{
		Result.bSuccess = false;
		Result.ErrorMessage = FString::Printf(TEXT("Failed to insert %d module(s)"), Result.FailedModules.Num());
	}

	return Result;
}

bool FVFXModuleInserter::InsertModuleByPath(UNiagaraEmitter* Emitter, const FMotionModuleDescriptor& Module, FString& OutError)
{
	if (!Emitter)
	{
		OutError = TEXT("Null emitter");
		return false;
	}

	UNiagaraScript* Script = LoadScript(Module.ModulePath);
	if (!Script)
	{
		OutError = FString::Printf(TEXT("Script not found: %s"), *Module.ModulePath);
		return false;
	}

	if (!InsertScriptViaGraphSource(Emitter, Script, Module, OutError))
	{
		return false;
	}

	Emitter->Modify();
	Emitter->PostEditChange();
	Emitter->MarkPackageDirty();

	if (UNiagaraSystem* OwnerSystem = Emitter->GetTypedOuter<UNiagaraSystem>())
	{
		OwnerSystem->MarkPackageDirty();
#if WITH_EDITOR
		OwnerSystem->RequestCompile(true);
		OwnerSystem->WaitForCompilationComplete(true, true);
#endif
	}

	UE_LOG(LogVFXAgent, Verbose, TEXT("InsertModuleByPath OK for '%s'"), *Module.ModulePath);
	return true;
}

FString FVFXModuleInserter::NormalizeModulePath(const FString& InPath)
{
	if (InPath.IsEmpty() || InPath.Contains(TEXT(".")))
	{
		return InPath;
	}
	const FString AssetName = FPaths::GetCleanFilename(InPath);
	if (AssetName.IsEmpty())
	{
		return InPath;
	}
	return FString::Printf(TEXT("%s.%s"), *InPath, *AssetName);
}

UNiagaraScript* FVFXModuleInserter::LoadScript(const FString& ModulePath)
{
	const FString Normalized = NormalizeModulePath(ModulePath);
	return LoadObject<UNiagaraScript>(nullptr, *Normalized);
}

ENiagaraScriptUsage FVFXModuleInserter::GetScriptUsageForPhase(EModulePhase Phase, const FString& ModulePath)
{
	if (Phase == EModulePhase::EventWrite)
	{
		return ENiagaraScriptUsage::ParticleEventScript;
	}

	if (Phase == EModulePhase::PreSim)
	{
		const FString LowerPath = ModulePath.ToLower();

		// SpawnBurstInstant executes once at emitter SPAWN time
		if (LowerPath.Contains(TEXT("spawnburstinstant")) || LowerPath.Contains(TEXT("spawnburst")))
		{
			return ENiagaraScriptUsage::EmitterSpawnScript;
		}

		// SpawnRate and other per-frame emitter-level spawn control → EmitterUpdateScript
		if (LowerPath.Contains(TEXT("spawnrate")) ||
			LowerPath.Contains(TEXT("emitterstate")) ||
			(LowerPath.Contains(TEXT("/emitter/")) && !LowerPath.Contains(TEXT("spawnburst"))))
		{
			return ENiagaraScriptUsage::EmitterUpdateScript;
		}

		// Default PreSim → Particle Spawn (InitializeParticle, AddVelocity in spawn, etc.)
		return ENiagaraScriptUsage::ParticleSpawnScript;
	}

	// Forces / Damping / Integrate / Curves / RenderPrep / Kill → ParticleUpdateScript
	return ENiagaraScriptUsage::ParticleUpdateScript;
}

bool FVFXModuleInserter::InsertScriptViaGraphSource(
	UNiagaraEmitter* Emitter,
	UNiagaraScript* Script,
	const FMotionModuleDescriptor& Module,
	FString& OutError)
{
	if (!Emitter || !Script)
	{
		OutError = TEXT("Null emitter or script");
		return false;
	}

	// Determine the correct graph section for this module phase
	const ENiagaraScriptUsage TargetUsage = GetScriptUsageForPhase(Module.Phase, Module.ModulePath);

#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5
	FVersionedNiagaraEmitterData* EmitterData = Emitter->GetLatestEmitterData();
	if (!EmitterData)
	{
		OutError = TEXT("GetLatestEmitterData() returned null");
		return false;
	}

	// Retrieve the target script for this usage (handles EmitterSpawn/Update too via WITH_EDITORONLY_DATA)
	UNiagaraScript* TargetScript = EmitterData->GetScript(TargetUsage, FGuid());
#else
	UNiagaraScript* TargetScript = nullptr;
	switch (TargetUsage)
	{
		case ENiagaraScriptUsage::ParticleSpawnScript:
		case ENiagaraScriptUsage::ParticleSpawnScriptInterpolated:
			TargetScript = Emitter->SpawnScriptProps.Script;
			break;
		case ENiagaraScriptUsage::ParticleUpdateScript:
			TargetScript = Emitter->UpdateScriptProps.Script;
			break;
		default:
			break;
	}
#endif

	if (!TargetScript)
	{
		OutError = FString::Printf(
			TEXT("No script found for usage %d in emitter '%s'. Make sure the emitter was properly initialised with a graph."),
			(int32)TargetUsage, *Emitter->GetName());
		return false;
	}

	// Access the Niagara graph via the script's source (NiagaraEditor module)
	UNiagaraScriptSource* ScriptSource = Cast<UNiagaraScriptSource>(TargetScript->GetLatestSource());
	if (!ScriptSource || !ScriptSource->NodeGraph)
	{
		OutError = FString::Printf(
			TEXT("Script '%s' has no NodeGraph. Emitter may not have been initialised with a graph (tip: duplicate a template emitter instead of NewObject)."),
			*TargetScript->GetName());
		return false;
	}

	// Find the output node for this usage (NIAGARAEDITOR_API FindEquivalentOutputNode)
	UNiagaraNodeOutput* OutputNode = ScriptSource->NodeGraph->FindEquivalentOutputNode(TargetUsage);
	if (!OutputNode)
	{
		OutError = FString::Printf(
			TEXT("No output node found for usage %d in graph '%s'"),
			(int32)TargetUsage, *ScriptSource->NodeGraph->GetName());
		return false;
	}

	// Insert module via the NIAGARAEDITOR_API overload (handles duplicates / ordering)
	const int32 InsertIndex = (Module.Priority >= 0) ? Module.Priority : INDEX_NONE;
	UNiagaraNodeFunctionCall* FuncCallNode = FNiagaraStackGraphUtilities::AddScriptModuleToStack(
		Script,
		*OutputNode,
		InsertIndex,
		Module.DisplayName.IsEmpty() ? FString() : Module.DisplayName);

	if (!FuncCallNode)
	{
		// AddScriptModuleToStack returning null usually means the module is already in the stack
		UE_LOG(LogVFXAgent, Log,
			TEXT("AddScriptModuleToStack returned null for '%s' (module may already exist in stack) – continuing"),
			*Script->GetName());
		return true;
	}

	UE_LOG(LogVFXAgent, Log,
		TEXT("  [GraphInsert] '%s' → usage %d (index %d)"),
		*FuncCallNode->GetFunctionName(), (int32)TargetUsage, InsertIndex);

	// Apply default parameter overrides via Rapid Iteration parameters
	ApplyDefaultParamsToModuleNode(
		FuncCallNode,
		Module,
		TargetScript,
		Emitter->GetUniqueEmitterName(),
		TargetUsage);

	return true;
}

// ============================================================
// Rapid Iteration Parameter Overrides
// ============================================================

void FVFXModuleInserter::ApplyDefaultParamsToModuleNode(
	UNiagaraNodeFunctionCall* ModuleNode,
	const FMotionModuleDescriptor& Module,
	UNiagaraScript*              TargetScript,
	const FString&               UniqueEmitterName,
	ENiagaraScriptUsage          ScriptUsage)
{
	if (!ModuleNode || !TargetScript)
	{
		return;
	}

	const bool bHasAnyParam =
		Module.DefaultParams.Num()       > 0 ||
		Module.DefaultParamsInt.Num()    > 0 ||
		Module.DefaultParamsBool.Num()   > 0 ||
		Module.DefaultParamsVector.Num() > 0;

	if (!bHasAnyParam)
	{
		return;
	}

	// Build an aliased Rapid Iteration variable for a given input name + type.
	// The naming convention: Constants.<EmitterName>.<ModuleFunctionName>.<InputName>
	auto BuildRIVar = [&](const FString& ParamName, const FNiagaraTypeDefinition& TypeDef) -> FNiagaraVariable
	{
		// 1. Create the module-namespace handle: "Module.<ParamName>"
		FNiagaraParameterHandle InputHandle =
			FNiagaraParameterHandle::CreateModuleParameterHandle(FName(*ParamName));
		// 2. Alias it to the concrete function name: "<FuncName>.<ParamName>"
		FNiagaraParameterHandle AliasedHandle =
			FNiagaraParameterHandle::CreateAliasedModuleParameterHandle(InputHandle, ModuleNode);
		// 3. Wrap in a variable and convert to the RI constant naming scheme
		FNiagaraVariable InputVar(TypeDef, AliasedHandle.GetParameterHandleString());
		return FNiagaraUtilities::ConvertVariableToRapidIterationConstantName(
			InputVar, *UniqueEmitterName, ScriptUsage);
	};

	// ── Float ───────────────────────────────────────────────────────────────
	for (const auto& Pair : Module.DefaultParams)
	{
		FNiagaraVariable RIVar = BuildRIVar(Pair.Key, FNiagaraTypeDefinition::GetFloatDef());
		const float Val = Pair.Value;
		RIVar.SetValue<float>(Val);
		TargetScript->RapidIterationParameters.SetParameterData(
			RIVar.GetData(), RIVar, /*bAdd=*/true);
		UE_LOG(LogVFXAgent, Verbose, TEXT("    RI float '%s' = %f"),
			*RIVar.GetName().ToString(), Val);
	}

	// ── Int ─────────────────────────────────────────────────────────────────
	for (const auto& Pair : Module.DefaultParamsInt)
	{
		FNiagaraVariable RIVar = BuildRIVar(Pair.Key, FNiagaraTypeDefinition::GetIntDef());
		const int32 Val = Pair.Value;
		RIVar.SetValue<int32>(Val);
		TargetScript->RapidIterationParameters.SetParameterData(
			RIVar.GetData(), RIVar, /*bAdd=*/true);
		UE_LOG(LogVFXAgent, Verbose, TEXT("    RI int '%s' = %d"),
			*RIVar.GetName().ToString(), Val);
	}

	// ── Bool ────────────────────────────────────────────────────────────────
	for (const auto& Pair : Module.DefaultParamsBool)
	{
		FNiagaraVariable RIVar = BuildRIVar(Pair.Key, FNiagaraTypeDefinition::GetBoolDef());
		FNiagaraBool BoolVal(Pair.Value);
		RIVar.SetValue<FNiagaraBool>(BoolVal);
		TargetScript->RapidIterationParameters.SetParameterData(
			RIVar.GetData(), RIVar, /*bAdd=*/true);
		UE_LOG(LogVFXAgent, Verbose, TEXT("    RI bool '%s' = %s"),
			*RIVar.GetName().ToString(), Pair.Value ? TEXT("true") : TEXT("false"));
	}

	// ── Vector (FVector3f) ──────────────────────────────────────────────────
	for (const auto& Pair : Module.DefaultParamsVector)
	{
		FNiagaraVariable RIVar = BuildRIVar(Pair.Key, FNiagaraTypeDefinition::GetVec3Def());
		const FVector3f Val(
			static_cast<float>(Pair.Value.X),
			static_cast<float>(Pair.Value.Y),
			static_cast<float>(Pair.Value.Z));
		RIVar.SetValue<FVector3f>(Val);
		TargetScript->RapidIterationParameters.SetParameterData(
			RIVar.GetData(), RIVar, /*bAdd=*/true);
		UE_LOG(LogVFXAgent, Verbose, TEXT("    RI vec '%s' = %s"),
			*RIVar.GetName().ToString(), *Pair.Value.ToString());
	}
}

