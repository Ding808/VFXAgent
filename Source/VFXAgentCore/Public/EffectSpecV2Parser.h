#pragma once

#include "CoreMinimal.h"
#include "EffectSpecV2.h"

/**
 * Parser for EffectSpec v2 JSON format.
 * Handles both strict LLM output and relaxed user-edited JSON.
 */
class VFXAGENTCORE_API FEffectSpecV2Parser
{
public:
	/** Parse JSON string into EffectSpecV2. Returns false on failure. */
	static bool ParseFromJson(const FString& Json, FEffectSpecV2& OutSpec, FString& OutError);

	/** Serialize EffectSpecV2 to JSON string (for logging / round-trip). */
	static FString ToJson(const FEffectSpecV2& Spec);
};
