#pragma once

#include "CoreMinimal.h"

// Forward declarations for asset generation
class IAssetGenService
{
public:
	virtual ~IAssetGenService() = default;

	// Generate material asset
	virtual class UMaterialInstanceConstant* GenerateMaterial(
		const FString& MaterialName,
		const FString& OutputPath) = 0;

	// Generate texture asset (placeholder)
	virtual class UTexture2D* GenerateTexture(
		const FString& TextureName,
		const FString& OutputPath) = 0;

	// Generate static mesh (placeholder)
	virtual class UStaticMesh* GenerateStaticMesh(
		const FString& MeshName,
		const FString& OutputPath) = 0;
};