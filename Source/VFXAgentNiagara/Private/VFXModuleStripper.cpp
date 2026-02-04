#include "VFXModuleStripper.h"
#include "VFXAgentLog.h"
#include "NiagaraEmitter.h"
#include "NiagaraScript.h"
#include "UObject/UnrealType.h"

FModuleStripResult FVFXModuleStripper::StripModulesByPattern(UNiagaraEmitter* Emitter, const TArray<FString>& Patterns)
{
	FModuleStripResult Result;
	
	if (!Emitter)
	{
		Result.bSuccess = false;
		Result.ErrorMessage = TEXT("Null emitter");
		return Result;
	}
	
	if (Patterns.Num() == 0)
	{
		return Result; // Nothing to do
	}
	
	TArray<UNiagaraScript*> AllModules = GetAllModules(Emitter);
	
	UE_LOG(LogVFXAgent, Log, TEXT("StripModulesByPattern: Found %d total modules in emitter"), AllModules.Num());
	
	for (UNiagaraScript* Module : AllModules)
	{
		if (!Module) continue;
		
		bool bMatches = false;
		for (const FString& Pattern : Patterns)
		{
			if (ModuleMatchesPattern(Module, Pattern))
			{
				bMatches = true;
				break;
			}
		}
		
		if (bMatches)
		{
			const FString ModuleName = Module->GetName();
			UE_LOG(LogVFXAgent, Log, TEXT("  Removing module: %s"), *ModuleName);
			
			if (RemoveModuleByScript(Emitter, Module))
			{
				Result.ModulesRemoved++;
				Result.RemovedModuleNames.Add(ModuleName);
			}
			else
			{
				Result.FailedToRemove.Add(ModuleName);
				UE_LOG(LogVFXAgent, Warning, TEXT("  Failed to remove module: %s"), *ModuleName);
			}
		}
	}
	
	UE_LOG(LogVFXAgent, Log, TEXT("StripModulesByPattern: Removed %d modules"), Result.ModulesRemoved);
	
	return Result;
}

FModuleStripResult FVFXModuleStripper::StripModulesByPath(UNiagaraEmitter* Emitter, const TArray<FString>& ScriptPaths)
{
	FModuleStripResult Result;
	if (!Emitter)
	{
		Result.bSuccess = false;
		Result.ErrorMessage = TEXT("Null emitter");
		return Result;
	}
	if (ScriptPaths.Num() == 0)
	{
		return Result;
	}

	TArray<UNiagaraScript*> AllModules = GetAllModules(Emitter);
	for (UNiagaraScript* Module : AllModules)
	{
		if (!Module) continue;
		const FString ModulePath = Module->GetPathName();
		for (const FString& Path : ScriptPaths)
		{
			if (ModulePath.Equals(Path, ESearchCase::IgnoreCase))
			{
				UE_LOG(LogVFXAgent, Log, TEXT("  Removing module by path: %s"), *ModulePath);
				if (RemoveModuleByScript(Emitter, Module))
				{
					Result.ModulesRemoved++;
					Result.RemovedModuleNames.Add(Module->GetName());
				}
				else
				{
					Result.FailedToRemove.Add(Module->GetName());
				}
				break;
			}
		}
	}

	return Result;
}

FModuleStripResult FVFXModuleStripper::StripModulesByClassName(UNiagaraEmitter* Emitter, const TArray<FString>& ClassNames)
{
	FModuleStripResult Result;
	if (!Emitter)
	{
		Result.bSuccess = false;
		Result.ErrorMessage = TEXT("Null emitter");
		return Result;
	}
	if (ClassNames.Num() == 0)
	{
		return Result;
	}

	TArray<UNiagaraScript*> AllModules = GetAllModules(Emitter);
	for (UNiagaraScript* Module : AllModules)
	{
		if (!Module) continue;
		for (const FString& ClassName : ClassNames)
		{
			if (ModuleMatchesClass(Module, ClassName))
			{
				UE_LOG(LogVFXAgent, Log, TEXT("  Removing module by class: %s"), *ClassName);
				if (RemoveModuleByScript(Emitter, Module))
				{
					Result.ModulesRemoved++;
					Result.RemovedModuleNames.Add(Module->GetName());
				}
				else
				{
					Result.FailedToRemove.Add(Module->GetName());
				}
				break;
			}
		}
	}

	return Result;
}

FModuleStripResult FVFXModuleStripper::StripAllVelocityModules(UNiagaraEmitter* Emitter)
{
	TArray<FString> Patterns;
	Patterns.Add(TEXT("Add Velocity"));
	Patterns.Add(TEXT("Initial Velocity"));
	Patterns.Add(TEXT("Velocity"));
	Patterns.Add(TEXT("Cone"));
	return StripModulesByPattern(Emitter, Patterns);
}

FModuleStripResult FVFXModuleStripper::StripGravityModules(UNiagaraEmitter* Emitter)
{
	TArray<FString> Patterns;
	Patterns.Add(TEXT("Gravity"));
	return StripModulesByPattern(Emitter, Patterns);
}

FModuleStripResult FVFXModuleStripper::StripNoiseModules(UNiagaraEmitter* Emitter)
{
	TArray<FString> Patterns;
	Patterns.Add(TEXT("Noise"));
	Patterns.Add(TEXT("Curl"));
	Patterns.Add(TEXT("Turbulence"));
	return StripModulesByPattern(Emitter, Patterns);
}

FModuleStripResult FVFXModuleStripper::StripConeVelocityModules(UNiagaraEmitter* Emitter)
{
	TArray<FString> Patterns;
	Patterns.Add(TEXT("Add Velocity In Cone"));
	Patterns.Add(TEXT("Cone Velocity"));
	return StripModulesByPattern(Emitter, Patterns);
}

bool FVFXModuleStripper::ModuleMatchesPattern(UNiagaraScript* Module, const FString& Pattern)
{
	if (!Module || Pattern.IsEmpty())
		return false;
	
	const FString ModuleName = Module->GetName();
	const FString ModulePath = Module->GetPathName();
	
	// Case-insensitive substring match
	if (ModuleName.Contains(Pattern, ESearchCase::IgnoreCase))
		return true;
	
	if (ModulePath.Contains(Pattern, ESearchCase::IgnoreCase))
		return true;
	
	return false;
}

bool FVFXModuleStripper::ModuleMatchesClass(UNiagaraScript* Module, const FString& ClassName)
{
	if (!Module || ClassName.IsEmpty())
		return false;

	const FString ModuleClass = Module->GetClass()->GetName();
	const FString ModuleClassPath = Module->GetClass()->GetPathName();
	if (ModuleClass.Equals(ClassName, ESearchCase::IgnoreCase))
		return true;
	if (ModuleClassPath.Contains(ClassName, ESearchCase::IgnoreCase))
		return true;

	return false;
}

bool FVFXModuleStripper::RemoveModuleByScript(UNiagaraEmitter* Emitter, UNiagaraScript* ScriptToRemove)
{
	if (!Emitter || !ScriptToRemove)
		return false;
	
	// Try to remove from all possible stacks
	const FName StackNames[] = {
		TEXT("SpawnScriptProps"),
		TEXT("UpdateScriptProps"),
		TEXT("EmitterSpawnScriptProps"),
		TEXT("EmitterUpdateScriptProps"),
		TEXT("EventHandlerScriptProps")
	};
	
	bool bRemovedFromAnyStack = false;
	
	for (const FName& StackName : StackNames)
	{
		if (RemoveFromStack(Emitter, StackName, ScriptToRemove))
		{
			bRemovedFromAnyStack = true;
		}
	}
	
	return bRemovedFromAnyStack;
}

TArray<UNiagaraScript*> FVFXModuleStripper::GetAllModules(UNiagaraEmitter* Emitter)
{
	TArray<UNiagaraScript*> Modules;
	
	if (!Emitter)
		return Modules;
	
	const FName StackNames[] = {
		TEXT("SpawnScriptProps"),
		TEXT("UpdateScriptProps"),
		TEXT("EmitterSpawnScriptProps"),
		TEXT("EmitterUpdateScriptProps"),
		TEXT("EventHandlerScriptProps")
	};
	
	for (const FName& StackName : StackNames)
	{
		GetModulesFromStack(Emitter, StackName, Modules);
	}
	
	return Modules;
}

bool FVFXModuleStripper::RemoveFromStack(UNiagaraEmitter* Emitter, const FName& StackArrayName, UNiagaraScript* ScriptToRemove)
{
	if (!Emitter || !ScriptToRemove)
		return false;
	
	FArrayProperty* ArrayProp = FindFProperty<FArrayProperty>(UNiagaraEmitter::StaticClass(), StackArrayName);
	if (!ArrayProp)
		return false;
	
	FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(Emitter));
	FStructProperty* StructProp = CastField<FStructProperty>(ArrayProp->Inner);
	if (!StructProp)
		return false;
	
	UStruct* StructType = StructProp->Struct;
	
	// Find and remove matching entries
	bool bRemoved = false;
	for (int32 i = Helper.Num() - 1; i >= 0; --i)
	{
		void* ElemPtr = Helper.GetRawPtr(i);
		
		// Try to get script from various possible field names
		UNiagaraScript* Script = nullptr;
		const FName FieldNames[] = { TEXT("Script"), TEXT("ScriptObject"), TEXT("GeneratorScript"), TEXT("EventScript") };
		for (const FName& FieldName : FieldNames)
		{
			FProperty* Prop = StructType->FindPropertyByName(FieldName);
			if (FObjectPropertyBase* ObjProp = CastField<FObjectPropertyBase>(Prop))
			{
				if (UObject* Obj = ObjProp->GetObjectPropertyValue_InContainer(ElemPtr))
				{
					Script = Cast<UNiagaraScript>(Obj);
					if (Script)
						break;
				}
			}
		}
		
		if (Script == ScriptToRemove)
		{
			Helper.RemoveValues(i, 1);
			bRemoved = true;
		}
	}
	
	return bRemoved;
}

void FVFXModuleStripper::GetModulesFromStack(UNiagaraEmitter* Emitter, const FName& StackArrayName, TArray<UNiagaraScript*>& OutModules)
{
	if (!Emitter)
		return;
	
	FArrayProperty* ArrayProp = FindFProperty<FArrayProperty>(UNiagaraEmitter::StaticClass(), StackArrayName);
	if (!ArrayProp)
		return;
	
	FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(Emitter));
	FStructProperty* StructProp = CastField<FStructProperty>(ArrayProp->Inner);
	if (!StructProp)
		return;
	
	UStruct* StructType = StructProp->Struct;
	
	for (int32 i = 0; i < Helper.Num(); ++i)
	{
		void* ElemPtr = Helper.GetRawPtr(i);
		
		// Try to get script from various possible field names
		const FName FieldNames[] = { TEXT("Script"), TEXT("ScriptObject"), TEXT("GeneratorScript"), TEXT("EventScript") };
		for (const FName& FieldName : FieldNames)
		{
			FProperty* Prop = StructType->FindPropertyByName(FieldName);
			if (FObjectPropertyBase* ObjProp = CastField<FObjectPropertyBase>(Prop))
			{
				if (UObject* Obj = ObjProp->GetObjectPropertyValue_InContainer(ElemPtr))
				{
					if (UNiagaraScript* Script = Cast<UNiagaraScript>(Obj))
					{
						OutModules.AddUnique(Script);
						break;
					}
				}
			}
		}
	}
}
