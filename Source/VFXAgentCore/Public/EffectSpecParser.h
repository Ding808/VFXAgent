#pragma once

#include "CoreMinimal.h"
#include "EffectSpecV1.h"

class VFXAGENTCORE_API FEffectSpecParser
{
public:
	static bool ParseFromJsonString(const FString& Json, FEffectSpecV1& OutSpec, FString& OutError);
};
