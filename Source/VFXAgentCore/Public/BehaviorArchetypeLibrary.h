#pragma once

#include "CoreMinimal.h"
#include "EffectSpecV2.h"

/**
 * Behavior Archetype Library — Canonical VFX families with pre-defined constraints,
 * layer templates, material presets, and Niagara feature requirements.
 *
 * Each archetype provides:
 *   - Minimum layer layout (roles + renderer types)
 *   - Default timing envelopes
 *   - Motion verb assignments per role
 *   - Material feature presets
 *   - Niagara hard-constraint requirements
 *   - Forbidden patterns (what the LLM must NOT do)
 */

// ---------------------------------------------------------------------------
// Archetype layer preset
// ---------------------------------------------------------------------------
struct FArchetypeLayerPreset
{
	ELayerRoleV2 Role;
	FString DefaultName;
	FString RendererType;                 // sprite | ribbon | mesh | light
	FTimingEnvelopeV2 Timing;
	EMotionVerbV2 MotionVerb;
	float MotionSpeed;
	FString BlendMode;                    // additive | translucent | masked
	bool bFresnel;
	bool bDepthFade;
	bool bErodeMask;
	bool bUVDistortion;
	int32 MaxParticles;
};

// ---------------------------------------------------------------------------
// Full archetype definition
// ---------------------------------------------------------------------------
struct FBehaviorArchetypeDefinition
{
	EVFXBehaviorArchetype Archetype;
	FString DisplayName;
	FString Description;

	// Layer templates
	TArray<FArchetypeLayerPreset> LayerPresets;

	// Niagara feature requirements
	FNiagaraFeatureRequirementsV2 Requirements;

	// Forbidden module patterns (things the LLM and builder must avoid)
	TArray<FString> ForbiddenPatterns;

	// Style defaults
	FEffectStyleV2 DefaultStyle;

	// Camera readability
	FCameraReadabilityV2 CameraReadability;
};

// ---------------------------------------------------------------------------
// Static library
// ---------------------------------------------------------------------------
class VFXAGENTCORE_API FBehaviorArchetypeLibrary
{
public:
	/** Get the full definition for an archetype */
	static const FBehaviorArchetypeDefinition& GetDefinition(EVFXBehaviorArchetype Archetype);

	/** Get all registered definitions */
	static const TArray<FBehaviorArchetypeDefinition>& GetAllDefinitions();

	/** Populate a V2 spec's layers, events, requirements, and style from an archetype */
	static void ApplyArchetypeDefaults(FEffectSpecV2& OutSpec);

	/** Validate a spec against its archetype constraints; returns list of violations */
	static TArray<FString> ValidateAgainstArchetype(const FEffectSpecV2& Spec);

	/** Infer the best archetype from a user prompt */
	static EVFXBehaviorArchetype InferFromPrompt(const FString& Prompt);

private:
	static void InitializeLibrary();
	static TArray<FBehaviorArchetypeDefinition> Definitions;
	static bool bInitialized;
};
