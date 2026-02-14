#pragma once

#include "CoreMinimal.h"
#include "VFXRecipe.h"
#include "EffectSpecV2.h"
#include "VFXTemplateSelector.h"
#include "VFXMotionModuleLibrary.h"

class UNiagaraSystem;
class UNiagaraEmitter;
class UMaterialInterface;

/**
 * NiagaraSpec Builder - Orchestrates the new constraint-aware VFX generation pipeline
 * 
 * Pipeline:
 * 1. SelectStrategy (TemplateSelector)
 * 2. CreateEmitter (from template or scratch)
 * 3. StripForbiddenModules (ModuleStripper)
 * 4. InsertRequiredModules (MotionModuleLibrary)
 * 5. ValidateRenderers (RendererValidationFixer)
 * 6. ScoreQuality (QualityScorer)
 */

struct FNiagaraBuildContext
{
	FVFXIntent Intent;
	FVFXEffectSpec Spec;
	FTemplateSelectionResult SelectedStrategy;
	TArray<FString> BuildLog; // Detailed log of actions taken
	bool bSuccess = false;
	FString ErrorMessage;
};

struct FNiagaraBuildContextV2
{
	FEffectSpecV2 Spec;
	TArray<FString> BuildLog;
	bool bSuccess = false;
	FString ErrorMessage;
};

class VFXAGENTNIAGARA_API FVFXNiagaraSpecBuilder
{
public:
	/**
	 * Build a Niagara system from spec using the new constraint-aware pipeline
	 * @param Spec - VFX effect specification
	 * @param OutContext - Build context with logs and diagnostics
	 * @return Generated Niagara system or nullptr on failure
	 */
	static UNiagaraSystem* BuildFromSpec(const FVFXEffectSpec& Spec, FNiagaraBuildContext& OutContext);

	/**
	 * Build a Niagara system from V2 Spec (LLM Native)
	 */
	static UNiagaraSystem* BuildFromSpecV2(const FEffectSpecV2& Spec, FNiagaraBuildContextV2& OutContext);
	
	/**
	 * Build a single emitter with constraint enforcement
	 */
	static UNiagaraEmitter* BuildEmitter(
		const FVFXEmitterSpec& EmitterSpec,
		const FVFXIntent& Intent,
		FNiagaraBuildContext& OutContext
	);
	
	/**
	 * Apply motion behavior to an emitter
	 */
	static bool ApplyMotionBehavior(
		UNiagaraEmitter* Emitter,
		const FMotionBehaviorConfig& MotionConfig,
		const FVFXIntent& Intent,
		FNiagaraBuildContext& OutContext
	);
	
	/**
	 * Enforce constraints by stripping forbidden modules
	 */
	static bool EnforceConstraints(
		UNiagaraEmitter* Emitter,
		const FTemplateSelectionResult& SelectionResult,
		FNiagaraBuildContext& OutContext
	);
	
	/**
	 * Validate and fix renderers
	 */
	static bool ValidateAndFixRenderers(
		UNiagaraEmitter* Emitter,
		UMaterialInterface* DefaultMaterial,
		FNiagaraBuildContext& OutContext
	);

private:
	static void LogBuildAction(FNiagaraBuildContext& Context, const FString& Action);
	static void LogBuildActionV2(FNiagaraBuildContextV2& Context, const FString& Action);

	static UNiagaraEmitter* CreateFromTemplate(const FString& TemplatePath, const FString& EmitterName);
	static UNiagaraEmitter* CreateFromScratch(const FString& EmitterName);

	static UNiagaraEmitter* BuildEmitterV2(
		const FLayerSpecV2& Layer,
		FNiagaraBuildContextV2& Context);

	static void ConfigureEmitterMotionV2(
		UNiagaraEmitter* Emitter,
		const FLayerSpecV2& Layer,
		FNiagaraBuildContextV2& Context);
};
