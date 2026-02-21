#include "VFXModuleInserter.h"
#include "VFXAgentLog.h"
#include "NiagaraEmitter.h"
#include "NiagaraSystem.h"
#include "NiagaraScript.h"
#include "UObject/UnrealType.h"
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
		if (InsertModuleByPath(Emitter, Module.ModulePath, Module.Phase, Module.Priority, Error))
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

bool FVFXModuleInserter::InsertModuleByPath(UNiagaraEmitter* Emitter, const FString& ModulePath, EModulePhase Phase, int32 Priority, FString& OutError)
{
	if (!Emitter)
	{
		OutError = TEXT("Null emitter");
		return false;
	}

	UNiagaraScript* Script = LoadScript(ModulePath);
	if (!Script)
	{
		OutError = FString::Printf(TEXT("Script not found: %s"), *ModulePath);
		return false;
	}

	const FName StackName = GetStackNameForPhase(Phase);
	if (!InsertScriptWithOrdering(Emitter, StackName, Script, Phase))
	{
		OutError = FString::Printf(TEXT("Insert failed in stack: %s"), *StackName.ToString());
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

bool FVFXModuleInserter::InsertScriptWithOrdering(UNiagaraEmitter* Emitter, const FName& ArrayPropName, UNiagaraScript* Script, EModulePhase Phase)
{
	if (!Emitter || !Script) return false;
	FArrayProperty* ArrayProp = FindFProperty<FArrayProperty>(UNiagaraEmitter::StaticClass(), ArrayPropName);
	if (!ArrayProp) return false;

	FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(Emitter));

	if (FStructProperty* StructProp = CastField<FStructProperty>(ArrayProp->Inner))
	{
		UStruct* StructType = StructProp->Struct;
		for (int32 i = 0; i < Helper.Num(); ++i)
		{
			void* ElemPtr = Helper.GetRawPtr(i);
			UNiagaraScript* Existing = GetScriptFromEntry(ElemPtr, StructType);
			if (Existing == Script)
			{
				return true; // already present
			}
		}
	}

	int32 InsertIndex = FindInsertIndexForPhase(Emitter, ArrayPropName, Phase);
	Helper.InsertValues(InsertIndex, 1);
	void* ElemPtr = Helper.GetRawPtr(InsertIndex);
	if (FStructProperty* StructProp = CastField<FStructProperty>(ArrayProp->Inner))
	{
		UStruct* StructType = StructProp->Struct;
		if (!SetStructObjectField(ElemPtr, StructType, TEXT("Script"), Script))
		{
			SetStructObjectField(ElemPtr, StructType, TEXT("ScriptObject"), Script);
			SetStructObjectField(ElemPtr, StructType, TEXT("GeneratorScript"), Script);
			SetStructObjectField(ElemPtr, StructType, TEXT("EventScript"), Script);
		}

		UE_LOG(LogVFXAgent, Verbose, TEXT("InsertScriptWithOrdering uses script-prop injection; UE5.5 stack graph pin wiring should be validated in editor if module inputs are missing."));
	}

	return true;
}

int32 FVFXModuleInserter::FindInsertIndexForPhase(UNiagaraEmitter* Emitter, const FName& ArrayPropName, EModulePhase Phase)
{
	FArrayProperty* ArrayProp = FindFProperty<FArrayProperty>(UNiagaraEmitter::StaticClass(), ArrayPropName);
	if (!ArrayProp) return INDEX_NONE;
	FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(Emitter));

	if (FStructProperty* StructProp = CastField<FStructProperty>(ArrayProp->Inner))
	{
		UStruct* StructType = StructProp->Struct;
		for (int32 i = 0; i < Helper.Num(); ++i)
		{
			void* ElemPtr = Helper.GetRawPtr(i);
			UNiagaraScript* Script = GetScriptFromEntry(ElemPtr, StructType);
			const EModulePhase Other = ClassifyScriptPhase(Script);
			if ((int32)Other > (int32)Phase)
			{
				return i;
			}
		}
	}

	return Helper.Num();
}

UNiagaraScript* FVFXModuleInserter::GetScriptFromEntry(void* ElemPtr, UStruct* StructType)
{
	if (!ElemPtr || !StructType) return nullptr;
	const FName Fields[] = { TEXT("Script"), TEXT("ScriptObject"), TEXT("GeneratorScript"), TEXT("EventScript") };
	for (const FName& Field : Fields)
	{
		FProperty* Prop = StructType->FindPropertyByName(Field);
		if (FObjectPropertyBase* ObjProp = CastField<FObjectPropertyBase>(Prop))
		{
			if (UObject* Obj = ObjProp->GetObjectPropertyValue_InContainer(ElemPtr))
			{
				return Cast<UNiagaraScript>(Obj);
			}
		}
	}
	return nullptr;
}

bool FVFXModuleInserter::SetStructObjectField(void* StructPtr, UStruct* StructType, const FName& FieldName, UObject* Value)
{
	if (!StructPtr || !StructType) return false;
	FProperty* Prop = StructType->FindPropertyByName(FieldName);
	if (FObjectPropertyBase* ObjProp = CastField<FObjectPropertyBase>(Prop))
	{
		ObjProp->SetObjectPropertyValue_InContainer(StructPtr, Value);
		return true;
	}
	return false;
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
