#pragma once

#include "CoreMinimal.h"
#include "EffectSpecV1.h"

struct VFXAGENTNIAGARA_API FAssetBuildResult
{
	bool bSuccess = false;
	FString SystemPath;
	TArray<FString> Errors;
	TArray<FString> Warnings;
};

class VFXAGENTNIAGARA_API FAssetBuildPipeline
{
public:
	static bool BuildFromJsonSpec(const FString& JsonSpec, const FString& OutputRootPath, FAssetBuildResult& OutResult);
};
