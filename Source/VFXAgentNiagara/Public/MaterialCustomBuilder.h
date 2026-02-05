#pragma once

#include "CoreMinimal.h"
#include "EffectSpecV1.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceConstant.h"

class VFXAGENTNIAGARA_API FMaterialCustomBuilder
{
public:
	static UMaterialInterface* BuildMaterialFromSpec(const FMaterialSpecV1& Spec, const FString& OutputPath, const FString& MaterialName, const FString& EffectName, const FString& LayerName);

private:
	static UMaterial* CreateCustomMasterMaterial(const FMaterialSpecV1& Spec, const FString& OutputPath, const FString& MaterialName, const FString& EffectName, const FString& LayerName);
	static void SaveHlslToDisk(const FString& EffectName, const FString& LayerName, const FString& Code);
	static UMaterialInterface* BuildFallbackMaterial(const FString& OutputPath, const FString& MaterialName);
};
