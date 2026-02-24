#pragma once

#include "CoreMinimal.h"
#include "ModelServices.h"

struct VFXAGENTNIAGARA_API FMeshyAsyncTaskSnapshot
{
	FString RunId;
	FString TaskId;
	FString Status;
	double ElapsedSeconds = 0.0;
	bool bCompleted = false;
	bool bSucceeded = false;
	FModelServiceResult Result;
	FString Error;
};

DECLARE_DELEGATE_OneParam(FOnMeshyTaskFinished, const FMeshyAsyncTaskSnapshot&)

class VFXAGENTNIAGARA_API FMeshyImageGenService : public IImageGenService
{
public:
	virtual FModelServiceResult GenerateTexture(const FTextureRequestV1& Request) override;
};

class VFXAGENTNIAGARA_API FMeshyImageTo3DService : public IImageTo3DService
{
public:
	virtual FModelServiceResult GenerateModel(const FModelRequestV1& Request, const FString& SourceImage) override;

	static bool StartGenerateModelAsync(
		const FModelRequestV1& Request,
		const FString& SourceImage,
		const FOnMeshyTaskFinished& OnFinished,
		FString& OutTaskId,
		FString& OutError,
		const FString& InRunId = TEXT(""));

	static bool QueryTask(const FString& TaskId, FMeshyAsyncTaskSnapshot& OutSnapshot);
};
