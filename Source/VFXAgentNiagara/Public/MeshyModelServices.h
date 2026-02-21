#pragma once

#include "CoreMinimal.h"
#include "ModelServices.h"

class VFXAGENTNIAGARA_API FMeshyImageGenService : public IImageGenService
{
public:
	virtual FModelServiceResult GenerateTexture(const FTextureRequestV1& Request) override;
};

class VFXAGENTNIAGARA_API FMeshyImageTo3DService : public IImageTo3DService
{
public:
	virtual FModelServiceResult GenerateModel(const FModelRequestV1& Request, const FString& SourceImage) override;
};
