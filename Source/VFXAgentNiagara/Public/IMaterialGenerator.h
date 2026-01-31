#pragma once

#include "CoreMinimal.h"
#include "VFXRecipe.h"

/**
 * Interface for generating and managing materials for VFX effects
 */
class IMaterialGenerator
{
public:
	virtual ~IMaterialGenerator() = default;

	/**
	 * Generate a material instance based on recipe
	 * @param MaterialRecipe Recipe describing the desired material properties
	 * @param OutputPath Path where the material asset should be created
	 * @return Created material instance, or nullptr on failure
	 */
	virtual class UMaterialInstanceConstant* GenerateMaterial(
		const FVFXMaterialRecipe& MaterialRecipe,
		const FString& OutputPath) = 0;

	/**
	 * Update an existing material instance based on new recipe
	 * @param Material The material instance to update
	 * @param MaterialRecipe New recipe to apply
	 * @return True if successful
	 */
	virtual bool UpdateMaterial(
		class UMaterialInstanceConstant* Material,
		const FVFXMaterialRecipe& MaterialRecipe) = 0;

	/**
	 * Create a procedural texture based on description
	 * @param TextureRecipe Recipe describing the desired texture
	 * @param OutputPath Path where the texture asset should be created
	 * @return Created texture, or nullptr on failure
	 */
	virtual class UTexture2D* GenerateProceduralTexture(
		const FVFXTextureRecipe& TextureRecipe,
		const FString& OutputPath) = 0;
};
