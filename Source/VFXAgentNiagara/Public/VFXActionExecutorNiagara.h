#pragma once

#include "CoreMinimal.h"
#include "IVFXActionExecutor.h"
#include "VFXDirectorTypes.h"

class VFXAGENTNIAGARA_API FVFXNiagaraActionExecutor : public IVFXActionExecutor
{
public:
	virtual bool ExecuteAction(const FVFXAction& Action, FVFXActionContext& Context) override;
	bool ExecuteActionList(const TArray<FVFXAction>& Actions, FVFXActionContext& Context);
};
