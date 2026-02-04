#pragma once

#include "CoreMinimal.h"
#include "IMaterialGenerator.h"
#include "Materials/MaterialInstanceConstant.h"
#include "MaterialGenerator.generated.h"

/**
 * Concrete implementation of material generation for VFX effects
 */
UCLASS()
class VFXAGENTNIAGARA_API UMaterialGenerator : public UObject, public IMaterialGenerator
{
	GENERATED_BODY()

public:
	virtual UMaterialInstanceConstant* GenerateMaterial(
		const FVFXMaterialRecipe& MaterialRecipe,
		const FString& OutputPath) override;

	virtual bool UpdateMaterial(
		UMaterialInstanceConstant* Material,
		const FVFXMaterialRecipe& MaterialRecipe) override;

	virtual UTexture2D* GenerateProceduralTexture(
		const FVFXTextureRecipe& TextureRecipe,
		const FString& OutputPath) override;

	static FORCEINLINE UMaterialGenerator* CreateInstance()
	{
		return NewObject<UMaterialGenerator>();
	}
	
	/**
	 * Find or create a suitable parent material for the effect (static for external use)
	 */
	static UMaterial* GetParentMaterial(const FVFXMaterialRecipe& MaterialRecipe);

private:
	/**
	 * Build a procedural parent material when no textures are available
	 */
	UMaterial* BuildProceduralParentMaterial(const FVFXMaterialRecipe& Recipe, const FString& OutputPath);

	/**
	 * Whether the recipe should use a procedural noise-based parent material
	 */
	bool ShouldUseProceduralParent(const FVFXMaterialRecipe& Recipe) const;

	/**
	 * Apply color and opacity parameters to material instance
	 */
	void ApplyColorParameters(UMaterialInstanceConstant* Material, const FVFXMaterialRecipe& Recipe);

	/**
	 * Apply texture parameters to material instance
	 */
	void ApplyTextureParameters(UMaterialInstanceConstant* Material, const FVFXMaterialRecipe& Recipe);

	/**
	 * Generate a simple gradient texture procedurally
	 */
	UTexture2D* GenerateGradientTexture(const FVFXTextureRecipe& Recipe, const FString& OutputPath);

	/**
	 * Generate a noise texture procedurally
	 */
	UTexture2D* GenerateNoiseTexture(const FVFXTextureRecipe& Recipe, const FString& OutputPath);
};
