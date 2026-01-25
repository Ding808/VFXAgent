#pragma once

#include "CoreMinimal.h"
#include "IAssetGenService.h"
#include "BasicAssetGenService.generated.h"

UCLASS()
class VFXAGENTNIAGARA_API UBasicAssetGenService : public UObject, public IAssetGenService
{
	GENERATED_BODY()

public:
	virtual UMaterialInstanceConstant* GenerateMaterial(
		const FString& MaterialName,
		const FString& OutputPath) override;

	virtual UTexture2D* GenerateTexture(
		const FString& TextureName,
		const FString& OutputPath) override;

	virtual UStaticMesh* GenerateStaticMesh(
		const FString& MeshName,
		const FString& OutputPath) override;
};