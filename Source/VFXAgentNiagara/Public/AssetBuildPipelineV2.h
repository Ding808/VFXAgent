#pragma once

#include "CoreMinimal.h"
#include "EffectSpecV2.h"
#include "AssetBuildPipeline.h" // Reuse FAssetBuildResult

/**
 * V2 Asset Build Pipeline — converts FEffectSpecV2 into a Niagara system.
 *
 * Key differences from V1:
 *   - Timing envelopes → emitter delay / lifetime / looping
 *   - Motion verbs → velocity / force module configuration
 *   - Material feature skeleton → material graph composition
 *   - Event bindings → Niagara event handlers between emitters
 *   - Archetype-aware defaults applied when layer data is sparse
 */
class VFXAGENTNIAGARA_API FAssetBuildPipelineV2
{
public:
	/**
	 * Build a full Niagara system from an EffectSpec v2.
	 * @param Spec           Parsed & validated V2 spec
	 * @param OutputRootPath Virtual path root (e.g. /Game/VFXAgent/Generated)
	 * @param OutResult      Build result with system path, errors, warnings
	 * @return true on success
	 */
	static bool BuildFromV2Spec(const FEffectSpecV2& Spec, const FString& OutputRootPath, FAssetBuildResult& OutResult);

private:
	// ---- Per-Layer Configuration ----

	/** Configure spawn mode (burst vs. rate). */
	static void ApplySpawnConfig(class UNiagaraSystem* System, const FString& EmitterName, const FLayerSpawnV2& Spawn);

	/** Configure timing envelope (delay, lifetime, looping). */
	static void ApplyTimingEnvelope(class UNiagaraSystem* System, const FString& EmitterName, const FTimingEnvelopeV2& Timing);

	/** Map a motion verb to velocity + force module parameters. */
	static void ApplyMotionVerb(class UNiagaraSystem* System, const FString& EmitterName, const FMotionDescV2& Motion, const FLayerUpdateV2& Update);

	/** Build and assign a material from the V2 material spec. */
	static class UMaterialInterface* BuildV2Material(const FMaterialSpecV2& MatSpec, const FString& OutputPath, const FString& MaterialName, const FString& EffectName, const FString& LayerName);

	// ---- System-Level Features ----

	/** Wire event bindings between emitters. */
	static void ApplyEventBindings(class UNiagaraSystem* System, const FEffectSpecV2& Spec, FAssetBuildResult& OutResult);

	/** Create versioned output folder and write spec hash. */
	static FString ResolveOutputFolder(const FString& OutputRootPath, const FString& EffectName, const FString& SpecHash);
};
