#pragma once

#include "CoreMinimal.h"
#include "ModelServices.h"

class VFXAGENTNIAGARA_API FLocalImageGenService : public IImageGenService
{
public:
	virtual FModelServiceResult GenerateTexture(const FTextureRequestV1& Request) override;
};

class VFXAGENTNIAGARA_API FLocalImageTo3DService : public IImageTo3DService
{
public:
	virtual FModelServiceResult GenerateModel(const FModelRequestV1& Request, const FString& SourceImage) override;
};

class VFXAGENTNIAGARA_API FExternalImageGenService : public IImageGenService
{
public:
	virtual FModelServiceResult GenerateTexture(const FTextureRequestV1& Request) override;
};

class VFXAGENTNIAGARA_API FExternalImageTo3DService : public IImageTo3DService
{
public:
	virtual FModelServiceResult GenerateModel(const FModelRequestV1& Request, const FString& SourceImage) override;
};
