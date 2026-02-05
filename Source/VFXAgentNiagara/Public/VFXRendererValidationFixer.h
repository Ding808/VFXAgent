#pragma once

#include "CoreMinimal.h"

class UNiagaraEmitter;
class UNiagaraRendererProperties;
class UNiagaraMeshRendererProperties;
class UMaterialInterface;

/**
 * Renderer Validation Fixer - Removes invalid renderers and ensures materials are properly assigned
 * 
 * Common issues fixed:
 *  - Renderers with null/None materials
 *  - Duplicate renderers
 *  - Invalid renderer configurations
 */

struct FRendererValidationReport
{
	int32 TotalRenderers = 0;
	int32 InvalidRenderersRemoved = 0;
	int32 RenderersFixed = 0;
	TArray<FString> RemovedRendererTypes;
	TArray<FString> FixedRendererTypes;
	TArray<FString> Warnings;
	bool bHasValidRenderer = false;
	FString Summary;
};

class VFXAGENTNIAGARA_API FVFXRendererValidationFixer
{
public:
	/**
	 * Validate and fix all renderers in an emitter
	 * - Removes renderers with null materials
	 * - Removes duplicate renderers
	 * - Assigns default material if needed
	 * @param Emitter - The emitter to validate
	 * @param DefaultMaterial - Optional default material to assign if none exists
	 * @return Validation report with details
	 */
	static FRendererValidationReport ValidateAndFixRenderers(UNiagaraEmitter* Emitter, UMaterialInterface* DefaultMaterial = nullptr);
	
	/**
	 * Remove renderers with invalid materials
	 */
	static int32 RemoveRenderersWithNullMaterial(UNiagaraEmitter* Emitter);
	
	/**
	 * Check if a renderer is valid
	 */
	static bool IsRendererValid(UNiagaraRendererProperties* Renderer);
	
	/**
	 * Get material from renderer (works with Sprite, Ribbon, etc.)
	 */
	static UMaterialInterface* GetRendererMaterial(UNiagaraRendererProperties* Renderer);
	
	/**
	 * Set material on renderer (works with Sprite, Ribbon, etc.)
	 */
	static bool SetRendererMaterial(UNiagaraRendererProperties* Renderer, UMaterialInterface* Material);
	
	/**
	 * Count valid renderers in emitter
	 */
	static int32 CountValidRenderers(UNiagaraEmitter* Emitter);
	
	/**
	 * Ensure at least one valid sprite renderer exists, create if needed
	 */
	static bool EnsureValidSpriteRenderer(UNiagaraEmitter* Emitter, UMaterialInterface* DefaultMaterial);

private:
	static TArray<UNiagaraRendererProperties*> GetRenderers(UNiagaraEmitter* Emitter);
	static void RemoveRenderer(UNiagaraEmitter* Emitter, UNiagaraRendererProperties* Renderer);
	static UNiagaraRendererProperties* AddSpriteRenderer(UNiagaraEmitter* Emitter, UMaterialInterface* Material);
};
