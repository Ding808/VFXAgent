#pragma once

#include "CoreMinimal.h"
#include "VFXRecipe.h"
#include "VFXMotionModuleLibrary.h"

/**
 * Template Selector (Deprecated) - Templates are disallowed by default
 * Strategies:
 *   - BuildFromScratch: Module whitelist construction (no template)
 *   - TemplateMinimal: Use Minimal template then replace/strip modules
 *   - TemplateFountain: Use Fountain template with modifications
 *   - TemplateBurst: Use burst templates with modifications
 */

enum class EConstructionStrategy : uint8
{
	BuildFromScratch,     // No template, build from module whitelist
	TemplateMinimal,      // Start from Minimal template
	TemplateFountain,     // Use Fountain template (directional effects)
	TemplateBurst,        // Use burst templates (explosions)
	TemplateRibbon,       // Use ribbon for trails
	Custom                // User-specified template
};

struct FTemplateSelectionResult
{
	EConstructionStrategy Strategy;
	FString TemplatePath;          // Empty if BuildFromScratch
	FString StrategyReason;        // Why this strategy was chosen
	TArray<FString> ModulesToStrip; // Modules that must be removed
	TArray<FMotionModuleDescriptor> ModulesToAdd; // Modules to insert
	bool bMustStripAllVelocity;    // Remove all velocity modules
	bool bMustStripGravity;        // Remove gravity
	bool bMustStripNoise;          // Remove noise modules
};

// Helper to convert strategy enum to string
static inline const TCHAR* StrategyToString(EConstructionStrategy Strategy)
{
	switch (Strategy)
	{
		case EConstructionStrategy::BuildFromScratch: return TEXT("BuildFromScratch");
		case EConstructionStrategy::TemplateMinimal: return TEXT("TemplateMinimal");
		case EConstructionStrategy::TemplateFountain: return TEXT("TemplateFountain");
		case EConstructionStrategy::TemplateBurst: return TEXT("TemplateBurst");
		case EConstructionStrategy::TemplateRibbon: return TEXT("TemplateRibbon");
		case EConstructionStrategy::Custom: return TEXT("Custom");
		default: return TEXT("Unknown");
	}
}

class VFXAGENTNIAGARA_API FVFXTemplateSelector
{
public:
	/**
	 * Select the best construction strategy based on VFX intent
	 * @param Intent - The VFX intent describing desired behavior
	 * @param EmitterSpec - Specific emitter spec parameters
	 * @return Selection result with strategy and required modifications
	 */
	static FTemplateSelectionResult SelectStrategy(const FVFXIntent& Intent, const FVFXEmitterSpec& EmitterSpec);
	
	/**
	 * Determine if we should build from scratch (no template) based on constraints
	 */
	static bool ShouldBuildFromScratch(const FVFXIntent& Intent, const FMotionBehaviorConfig& MotionConfig);
	
	/**
	 * Get the appropriate template path for a given strategy
	 */
	static FString GetTemplatePathForStrategy(EConstructionStrategy Strategy, const FVFXIntent& Intent);
	
	/**
	 * Validate if a template is compatible with motion requirements
	 */
	static bool IsTemplateCompatible(const FString& TemplatePath, const FMotionBehaviorConfig& MotionConfig);

private:
	static EConstructionStrategy DetermineStrategyForArchetype(EVFXArchetype Archetype, EVFXMotionModel MotionModel);
	static FString GetReasonForStrategy(EConstructionStrategy Strategy, const FVFXIntent& Intent);
};
