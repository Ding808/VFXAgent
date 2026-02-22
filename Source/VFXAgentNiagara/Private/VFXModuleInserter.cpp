#include "VFXModuleInserter.h"
#include "VFXAgentLog.h"
#include "NiagaraEmitter.h"
#include "NiagaraSystem.h"
#include "NiagaraScript.h"
#include "NiagaraScriptSourceBase.h"
#include "NiagaraScriptSource.h"
#include "NiagaraGraph.h"
#include "NiagaraNodeOutput.h"
#include "NiagaraNodeFunctionCall.h"
#include "NiagaraNode.h"
#include "ViewModels/Stack/NiagaraStackGraphUtilities.h"
#include "ViewModels/Stack/NiagaraParameterHandle.h"
#include "EdGraphSchema_Niagara.h"
#include "AssetRegistry/AssetData.h"
#include "Misc/Paths.h"

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

	const FString ModulePath = Module.ModulePath;
	const EModulePhase Phase = Module.Phase;
	const int32 Priority = Module.Priority;

	UNiagaraScript* Script = LoadScript(ModulePath);
	if (!Script)
	{
		OutError = FString::Printf(TEXT("Script not found: %s"), *ModulePath);
		return false;
	}

	const FName StackName = GetStackNameForPhase(Phase);
	if (!InsertScriptViaGraphSource(Emitter, Script, Module, OutError))
	{
		if (OutError.IsEmpty())
		{
			OutError = FString::Printf(TEXT("Insert failed in stack: %s"), *StackName.ToString());
		}
		return false;
	}

	Emitter->Modify();
	Emitter->PostEditChange();
	Emitter->MarkPackageDirty();
	Emitter->CacheFromCompiledData();

	if (UNiagaraSystem* OwnerSystem = Emitter->GetTypedOuter<UNiagaraSystem>())
	{
		OwnerSystem->MarkPackageDirty();
#if WITH_EDITOR
		OwnerSystem->RequestCompile(true);
		OwnerSystem->WaitForCompilationComplete(true, true);
#endif
	}

	UE_LOG(LogVFXAgent, Verbose, TEXT("InsertModuleByPath succeeded for '%s' and triggered dirty/recompile refresh"), *ModulePath);
	return true;
}

FString FVFXModuleInserter::NormalizeModulePath(const FString& InPath)
{
	if (InPath.IsEmpty())
	{
		return InPath;
	}
	if (InPath.Contains(TEXT(".")))
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

FNiagaraParameterHandle FVFXModuleInserter::MakeAliasedInputHandle(const FString& RawInputName, UNiagaraNodeFunctionCall* ModuleNode)
{
	const FString FullInputName = RawInputName.Contains(TEXT(".")) ? RawInputName : FString::Printf(TEXT("Module.%s"), *RawInputName);
	return FNiagaraParameterHandle::CreateAliasedModuleParameterHandle(FName(*FullInputName), ModuleNode->GetFunctionName());
}

UEdGraphPin* FVFXModuleInserter::ResolveOrCreateOverridePin(UNiagaraNodeFunctionCall* ModuleNode, const FString& RawInputName, const FNiagaraTypeDefinition& ValueTypeDef)
{
	if (!ModuleNode || RawInputName.IsEmpty())
	{
		return nullptr;
	}

	const FNiagaraParameterHandle AliasedHandle = MakeAliasedInputHandle(RawInputName, ModuleNode);
	UEdGraphPin* OverridePin = FNiagaraStackGraphUtilities::GetStackFunctionInputOverridePin(*ModuleNode, AliasedHandle);
	if (!OverridePin)
	{
		OverridePin = &FNiagaraStackGraphUtilities::GetOrCreateStackFunctionInputOverridePin(
			*ModuleNode,
			AliasedHandle,
			ValueTypeDef,
			FGuid(),
			FGuid()
		);
	}

	if (OverridePin && OverridePin->LinkedTo.Num() > 0)
	{
		FNiagaraStackGraphUtilities::RemoveNodesForStackFunctionInputOverridePin(*OverridePin);
	}

	return OverridePin;
}

ENiagaraScriptUsage FVFXModuleInserter::ResolveScriptUsageForInsert(const FString& ModulePath, EModulePhase Phase)
{
	const FString LowerPath = ModulePath.ToLower();

	if (Phase == EModulePhase::EventWrite)
	{
		return ENiagaraScriptUsage::ParticleEventScript;
	}

	if (Phase == EModulePhase::PreSim)
	{
		if (LowerPath.Contains(TEXT("spawnrate")) || LowerPath.Contains(TEXT("spawnburst")) || LowerPath.Contains(TEXT("emitter")))
		{
			return ENiagaraScriptUsage::EmitterSpawnScript;
		}
		return ENiagaraScriptUsage::ParticleSpawnScript;
	}

	return ENiagaraScriptUsage::ParticleUpdateScript;
}

UNiagaraNodeOutput* FVFXModuleInserter::FindBestOutputNode(UNiagaraGraph* Graph, ENiagaraScriptUsage PreferredUsage)
{
	if (!Graph)
	{
		return nullptr;
	}

	if (UNiagaraNodeOutput* Preferred = Graph->FindOutputNode(PreferredUsage, FGuid()))
	{
		return Preferred;
	}

	if (PreferredUsage == ENiagaraScriptUsage::EmitterSpawnScript)
	{
		if (UNiagaraNodeOutput* ParticleSpawn = Graph->FindOutputNode(ENiagaraScriptUsage::ParticleSpawnScript, FGuid()))
		{
			return ParticleSpawn;
		}
	}

	if (UNiagaraNodeOutput* ParticleUpdate = Graph->FindOutputNode(ENiagaraScriptUsage::ParticleUpdateScript, FGuid()))
	{
		return ParticleUpdate;
	}

	return Graph->FindOutputNode(ENiagaraScriptUsage::ParticleSpawnScript, FGuid());
}

bool FVFXModuleInserter::InsertScriptViaGraphSource(UNiagaraEmitter* Emitter, UNiagaraScript* Script, const FMotionModuleDescriptor& Module, FString& OutError)
{
	if (!Emitter)
	{
		OutError = TEXT("Null emitter");
		return false;
	}

	if (!Script)
	{
		OutError = TEXT("Null script");
		return false;
	}

	UNiagaraScriptSourceBase* GraphSource = Emitter->GetGraphSource();
	if (!GraphSource)
	{
		OutError = TEXT("Emitter has no graph source");
		return false;
	}

	UNiagaraScriptSource* NiagaraScriptSource = Cast<UNiagaraScriptSource>(GraphSource);
	if (!NiagaraScriptSource || !NiagaraScriptSource->NodeGraph)
	{
		OutError = TEXT("Emitter graph source is not a valid UNiagaraScriptSource/NodeGraph");
		return false;
	}

	UNiagaraGraph* Graph = NiagaraScriptSource->NodeGraph;
	const EModulePhase Phase = Module.Phase;
	const int32 Priority = Module.Priority;
	const FString& ModulePath = Module.ModulePath;
	const ENiagaraScriptUsage TargetUsage = ResolveScriptUsageForInsert(ModulePath, Phase);
	UNiagaraNodeOutput* TargetOutput = FindBestOutputNode(Graph, TargetUsage);
	if (!TargetOutput)
	{
		OutError = FString::Printf(TEXT("No stack output node found for usage %d"), (int32)TargetUsage);
		return false;
	}

	const FAssetData ModuleAssetData(Script);
	if (!ModuleAssetData.IsValid())
	{
		OutError = TEXT("Invalid module asset data");
		return false;
	}

	FAddScriptModuleToStackArgs AddArgs(ModuleAssetData, *TargetOutput);
	AddArgs.TargetIndex = Priority >= 0 ? Priority : INDEX_NONE;
	AddArgs.SuggestedName = Script->GetName();
	AddArgs.bFixupTargetIndex = true;

	UNiagaraNodeFunctionCall* AddedNode = FNiagaraStackGraphUtilities::AddScriptModuleToStack(AddArgs);
	if (!AddedNode)
	{
		OutError = FString::Printf(TEXT("AddScriptModuleToStack failed for %s"), *Script->GetPathName());
		return false;
	}

	ApplyDefaultParamsToModuleNode(AddedNode, Module);

	GraphSource->Modify();
	NiagaraScriptSource->NodeGraph->NotifyGraphNeedsRecompile();
	UE_LOG(LogVFXAgent, Verbose, TEXT("Inserted module node '%s' into usage=%d (Phase=%d, Priority=%d, Stack=%s)"), *Script->GetPathName(), (int32)TargetUsage, (int32)Phase, Priority, *GetStackNameForPhase(Phase).ToString());

	return true;
}

void FVFXModuleInserter::ApplyDefaultParamsToModuleNode(UNiagaraNodeFunctionCall* ModuleNode, const FMotionModuleDescriptor& Module)
{
	if (!ModuleNode)
	{
		return;
	}

	TArray<FString> BoundFloatParams;
	TArray<FString> BoundIntParams;
	TArray<FString> BoundBoolParams;
	TArray<FString> BoundVectorParams;
	TArray<FString> MissingOverridePins;

	const UEdGraphSchema_Niagara* NiagaraSchema = GetDefault<UEdGraphSchema_Niagara>();
	if (!NiagaraSchema)
	{
		return;
	}

	auto SetPinDefault = [&](UEdGraphPin* OverridePin, const FString& ValueString)
	{
		if (!OverridePin)
		{
			return false;
		}

		NiagaraSchema->TrySetDefaultValue(*OverridePin, ValueString, true);

		if (UNiagaraNode* OwningNode = Cast<UNiagaraNode>(OverridePin->GetOwningNode()))
		{
			OwningNode->MarkNodeRequiresSynchronization(TEXT("VFXAgent default param override"), true);
		}

		return true;
	};

	for (const TPair<FString, float>& Param : Module.DefaultParams)
	{
		if (Param.Key.IsEmpty())
		{
			continue;
		}

		UEdGraphPin* OverridePin = ResolveOrCreateOverridePin(ModuleNode, Param.Key, FNiagaraTypeDefinition::GetFloatDef());
		if (!OverridePin)
		{
			MissingOverridePins.Add(FString::Printf(TEXT("float:%s"), *Param.Key));
			continue;
		}
		if (SetPinDefault(OverridePin, FString::SanitizeFloat(Param.Value)))
		{
			BoundFloatParams.Add(Param.Key);
		}
	}

	for (const TPair<FString, int32>& Param : Module.DefaultParamsInt)
	{
		if (Param.Key.IsEmpty())
		{
			continue;
		}

		UEdGraphPin* OverridePin = ResolveOrCreateOverridePin(ModuleNode, Param.Key, FNiagaraTypeDefinition::GetIntDef());
		if (!OverridePin)
		{
			MissingOverridePins.Add(FString::Printf(TEXT("int:%s"), *Param.Key));
			continue;
		}
		if (SetPinDefault(OverridePin, FString::FromInt(Param.Value)))
		{
			BoundIntParams.Add(Param.Key);
		}
	}

	for (const TPair<FString, bool>& Param : Module.DefaultParamsBool)
	{
		if (Param.Key.IsEmpty())
		{
			continue;
		}

		UEdGraphPin* OverridePin = ResolveOrCreateOverridePin(ModuleNode, Param.Key, FNiagaraTypeDefinition::GetBoolDef());
		if (!OverridePin)
		{
			MissingOverridePins.Add(FString::Printf(TEXT("bool:%s"), *Param.Key));
			continue;
		}
		if (SetPinDefault(OverridePin, Param.Value ? TEXT("true") : TEXT("false")))
		{
			BoundBoolParams.Add(Param.Key);
		}
	}

	for (const TPair<FString, FVector>& Param : Module.DefaultParamsVector)
	{
		if (Param.Key.IsEmpty())
		{
			continue;
		}

		UEdGraphPin* OverridePin = ResolveOrCreateOverridePin(ModuleNode, Param.Key, FNiagaraTypeDefinition::GetVec3Def());
		if (!OverridePin)
		{
			MissingOverridePins.Add(FString::Printf(TEXT("vector:%s"), *Param.Key));
			continue;
		}
		const FVector& Value = Param.Value;
		const FString VectorString = FString::Printf(TEXT("(X=%s,Y=%s,Z=%s)"),
			*FString::SanitizeFloat(Value.X),
			*FString::SanitizeFloat(Value.Y),
			*FString::SanitizeFloat(Value.Z));
		if (SetPinDefault(OverridePin, VectorString))
		{
			BoundVectorParams.Add(Param.Key);
		}
	}

	UE_LOG(
		LogVFXAgent,
		Log,
		TEXT("[ParamBind] Module=%s Float=[%s] Int=[%s] Bool=[%s] Vector=[%s]"),
		*ModuleNode->GetFunctionName().ToString(),
		*FString::Join(BoundFloatParams, TEXT(", ")),
		*FString::Join(BoundIntParams, TEXT(", ")),
		*FString::Join(BoundBoolParams, TEXT(", ")),
		*FString::Join(BoundVectorParams, TEXT(", "))
	);

	if (MissingOverridePins.Num() > 0)
	{
		UE_LOG(
			LogVFXAgent,
			Warning,
			TEXT("[ParamBindMissingPin] Module=%s Missing=[%s]"),
			*ModuleNode->GetFunctionName().ToString(),
			*FString::Join(MissingOverridePins, TEXT(", "))
		);
	}

	if (ModuleNode->GetNiagaraGraph())
	{
		FNiagaraStackGraphUtilities::RelayoutGraph(*ModuleNode->GetNiagaraGraph());
	}
}

FName FVFXModuleInserter::GetStackNameForPhase(EModulePhase Phase)
{
	switch (Phase)
	{
		case EModulePhase::PreSim:
			return TEXT("SpawnScriptProps");
		case EModulePhase::EventWrite:
			return TEXT("EventHandlerScriptProps");
		default:
			return TEXT("UpdateScriptProps");
	}
}
