#pragma once

#include "CoreMinimal.h"
#include "EffectSpecV1.h"

struct FEffectSpecValidationError
{
	FString Path;
	FString Message;
};

class VFXAGENTCORE_API FEffectSpecValidator
{
public:
	static bool Validate(const FEffectSpecV1& Spec, TArray<FEffectSpecValidationError>& OutErrors);
	static FString FormatErrors(const TArray<FEffectSpecValidationError>& Errors);
};
