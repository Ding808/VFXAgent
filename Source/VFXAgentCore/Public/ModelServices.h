#pragma once

#include "CoreMinimal.h"
#include "EffectSpecV1.h"

struct FModelServiceResult
{
	bool bSuccess = false;
	FString OutputPath;
	FString Summary;
	FString Error;
};

class ILLMService
{
public:
	virtual ~ILLMService() = default;
	virtual bool GenerateEffectSpecJson(const FString& Prompt, const TArray<FString>& ReferenceImages, FString& OutJson, FString& OutError) = 0;
};

class IImageGenService
{
public:
	virtual ~IImageGenService() = default;
	virtual FModelServiceResult GenerateTexture(const FTextureRequestV1& Request) = 0;
};

class IImageTo3DService
{
public:
	virtual ~IImageTo3DService() = default;
	virtual FModelServiceResult GenerateModel(const FModelRequestV1& Request, const FString& SourceImage) = 0;
};

class VFXAGENTCORE_API FModelRouter
{
public:
	void RegisterLLM(const FString& Name, TSharedPtr<ILLMService> Service);
	void RegisterImageGen(const FString& Name, TSharedPtr<IImageGenService> Service);
	void RegisterImageTo3D(const FString& Name, TSharedPtr<IImageTo3DService> Service);

	TSharedPtr<ILLMService> PickLLM(const FString& QualityHint) const;
	TSharedPtr<IImageGenService> PickImageGen(const FString& QualityHint) const;
	TSharedPtr<IImageTo3DService> PickImageTo3D(const FString& QualityHint) const;

private:
	TMap<FString, TSharedPtr<ILLMService>> LLMs;
	TMap<FString, TSharedPtr<IImageGenService>> ImageGens;
	TMap<FString, TSharedPtr<IImageTo3DService>> ImageTo3Ds;
};
