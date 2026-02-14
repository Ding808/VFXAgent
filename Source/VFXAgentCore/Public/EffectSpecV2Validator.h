#pragma once

#include "CoreMinimal.h"
#include "EffectSpecV2.h"

/**
 * Validator for EffectSpec v2 — checks structural integrity, archetype constraints,
 * Niagara feature requirements, and camera readability.
 */
class VFXAGENTCORE_API FEffectSpecV2Validator
{
public:
	/** Full validation pass. Returns true if all checks pass. */
	static bool Validate(const FEffectSpecV2& Spec, TArray<FString>& OutErrors, TArray<FString>& OutWarnings);

	/** Quick check: minimum layer count per archetype. */
	static bool HasMinimumLayers(const FEffectSpecV2& Spec, FString& OutError);

	/** Check that the Niagara hard constraints are met (forces/events/collision/light/ribbon). */
	static bool ValidateNiagaraFeatures(const FEffectSpecV2& Spec, TArray<FString>& OutErrors);

	/** Format errors/warnings to a human-readable string. */
	static FString FormatReport(const TArray<FString>& Errors, const TArray<FString>& Warnings);
};
