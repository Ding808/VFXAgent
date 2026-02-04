#pragma once

#include "CoreMinimal.h"
#include "VFXRecipe.h"

class VFXAGENTNIAGARA_API FVFXModuleLibrary
{
public:
	static void ApplyDefaults(FVFXLayerRecipe& Layer, TArray<FString>& OutWarnings);
};
