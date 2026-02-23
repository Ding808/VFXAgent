#include "VFXModuleInserter.h"
#include "VFXAgentLog.h"
#include "Misc/Paths.h"
#include "AssetRegistry/AssetData.h"
#include "NiagaraCommon.h"
#include "UObject/UnrealType.h"

// Niagara Base
#include "NiagaraEmitter.h"
#include "NiagaraSystem.h"
#include "NiagaraScript.h"
#include "Runtime/Launch/Resources/Version.h"

#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5
#include "NiagaraEmitter.h"
#endif

static bool SetStructObjectField(void* StructPtr, UStruct* StructType, const FName& FieldName, UObject* Value)
{
	if (!StructPtr || !StructType)
	{
		return false;
	}

	FProperty* Prop = StructType->FindPropertyByName(FieldName);
	if (FObjectProperty* ObjProp = CastField<FObjectProperty>(Prop))
	{
		ObjProp->SetObjectPropertyValue_InContainer(StructPtr, Value);
		return true;
	}

	if (FSoftObjectProperty* SoftObjProp = CastField<FSoftObjectProperty>(Prop))
	{
		SoftObjProp->SetPropertyValue_InContainer(StructPtr, FSoftObjectPtr(Value));
		return true;
	}

	return false;
}

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
			const FString StackNameStr = StackName.ToString();
			OutError = FString::Printf(TEXT("Insert failed in stack: %s"), *StackNameStr);
		}
		return false;
	}

#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5
	if (FVersionedNiagaraEmitterData* EmitterData = Emitter->GetLatestEmitterData())
	{
		// EmitterData->Modify(); // FVersionedNiagaraEmitterData is a struct, not a UObject
	}
#endif

	Emitter->Modify();
	Emitter->PostEditChange();
	Emitter->MarkPackageDirty();
	// Emitter->CacheFromCompiledData(); // Removed or replaced in UE 5.x

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

	const FName StackPropName = GetStackNameForPhase(Module.Phase);
	
	void* TargetContainer = Emitter;
	FArrayProperty* ArrayProp = FindFProperty<FArrayProperty>(Emitter->GetClass(), StackPropName);

#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5
	if (!ArrayProp)
	{
		if (FVersionedNiagaraEmitterData* EmitterData = Emitter->GetLatestEmitterData())
		{
			TargetContainer = EmitterData;
			ArrayProp = FindFProperty<FArrayProperty>(FVersionedNiagaraEmitterData::StaticStruct(), StackPropName);
		}
	}
#endif

	if (!ArrayProp)
	{
		OutError = FString::Printf(TEXT("Emitter does not expose stack property: %s"), *StackPropName.ToString());
		return false;
	}

	FStructProperty* StructProp = CastField<FStructProperty>(ArrayProp->Inner);
	if (!StructProp || !StructProp->Struct)
	{
		OutError = FString::Printf(TEXT("Stack property '%s' is not a struct array"), *StackPropName.ToString());
		return false;
	}

	FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(TargetContainer));

	for (int32 Index = 0; Index < Helper.Num(); ++Index)
	{
		void* ElemPtr = Helper.GetRawPtr(Index);
		UObject* ExistingScript = nullptr;

		if (FObjectProperty* ScriptProp = FindFProperty<FObjectProperty>(StructProp->Struct, TEXT("Script")))
		{
			ExistingScript = ScriptProp->GetObjectPropertyValue_InContainer(ElemPtr);
		}

		if (!ExistingScript)
		{
			if (FObjectProperty* ScriptObjProp = FindFProperty<FObjectProperty>(StructProp->Struct, TEXT("ScriptObject")))
			{
				ExistingScript = ScriptObjProp->GetObjectPropertyValue_InContainer(ElemPtr);
			}
		}

		if (ExistingScript == Script)
		{
			return true;
		}
	}

	const int32 InsertIndex = (Module.Priority >= 0) ? FMath::Min(Module.Priority, Helper.Num()) : Helper.Num();
	Helper.InsertValues(InsertIndex, 1);
	void* NewElemPtr = Helper.GetRawPtr(InsertIndex);

	const bool bAssigned =
		SetStructObjectField(NewElemPtr, StructProp->Struct, TEXT("Script"), Script) ||
		SetStructObjectField(NewElemPtr, StructProp->Struct, TEXT("ScriptObject"), Script) ||
		SetStructObjectField(NewElemPtr, StructProp->Struct, TEXT("GeneratorScript"), Script) ||
		SetStructObjectField(NewElemPtr, StructProp->Struct, TEXT("EventScript"), Script);

	if (!bAssigned)
	{
		Helper.RemoveValues(InsertIndex, 1);
		OutError = FString::Printf(TEXT("Failed to write script into stack '%s' element"), *StackPropName.ToString());
		return false;
	}

	ApplyDefaultParamsToModuleNode(nullptr, Module);
	return true;
}

void FVFXModuleInserter::ApplyDefaultParamsToModuleNode(UNiagaraNodeFunctionCall* ModuleNode, const FMotionModuleDescriptor& Module)
{
	(void)ModuleNode;
	if (Module.DefaultParams.Num() > 0 || Module.DefaultParamsInt.Num() > 0 || Module.DefaultParamsBool.Num() > 0 || Module.DefaultParamsVector.Num() > 0)
	{
		UE_LOG(LogVFXAgent, Verbose, TEXT("Param default overrides are skipped in reflection insertion path."));
	}
}

FName FVFXModuleInserter::GetStackNameForPhase(EModulePhase Phase)
{
	switch (Phase)
	{
		case EModulePhase::PreSim:
			return TEXT("ParticleSpawnScriptProps");
		case EModulePhase::EventWrite:
			return TEXT("EventHandlerScriptProps");
		default:
			return TEXT("ParticleUpdateScriptProps");
	}
}
