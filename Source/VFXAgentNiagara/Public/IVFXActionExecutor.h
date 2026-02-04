#pragma once

#include "CoreMinimal.h"
#include "VFXDirectorTypes.h"

class UNiagaraSystem;

struct FVFXActionContext
{
	UNiagaraSystem* CurrentSystem = nullptr;
	TMap<FString, UNiagaraSystem*> SystemsByName;
	TMap<FString, FString> EmitterAliases;
	TMap<FString, FString> EmitterRoles;
	TMap<FString, FString> EmitterArchetypes;
	TArray<FString> StyleKeywords;
	FVFXExecutionReport* Report = nullptr;
	FString DefaultOutputPath;
};

class VFXAGENTNIAGARA_API IVFXActionExecutor
{
public:
	virtual ~IVFXActionExecutor() = default;
	virtual bool ExecuteAction(const FVFXAction& Action, FVFXActionContext& Context) = 0;
};
