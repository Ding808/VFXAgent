#pragma once

#include "CoreMinimal.h"
#include "VFXDirectorTypes.h"
#include "Dom/JsonValue.h"

class VFXAGENTCORE_API FVFXDirectorJson
{
public:
	static bool ParseDirectorJson(const FString& JsonText, FVFXDirectorPlan& OutPlan, FString& OutError);
	static bool ParseActionValue(const TSharedPtr<FJsonValue>& JsonValue, const FString& ParamName, FVFXActionValue& OutValue, FString& OutError);
	static FString ExecutionReportToJson(const FVFXExecutionReport& Report);
};
