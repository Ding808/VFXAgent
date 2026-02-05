#include "ModelServices.h"

void FModelRouter::RegisterLLM(const FString& Name, TSharedPtr<ILLMService> Service)
{
	LLMs.Add(Name, Service);
}

void FModelRouter::RegisterImageGen(const FString& Name, TSharedPtr<IImageGenService> Service)
{
	ImageGens.Add(Name, Service);
}

void FModelRouter::RegisterImageTo3D(const FString& Name, TSharedPtr<IImageTo3DService> Service)
{
	ImageTo3Ds.Add(Name, Service);
}

TSharedPtr<ILLMService> FModelRouter::PickLLM(const FString& QualityHint) const
{
	if (const TSharedPtr<ILLMService>* Found = LLMs.Find(QualityHint))
	{
		return *Found;
	}
	for (const TPair<FString, TSharedPtr<ILLMService>>& KV : LLMs)
	{
		if (KV.Value.IsValid())
		{
			return KV.Value;
		}
	}
	return nullptr;
}

TSharedPtr<IImageGenService> FModelRouter::PickImageGen(const FString& QualityHint) const
{
	if (const TSharedPtr<IImageGenService>* Found = ImageGens.Find(QualityHint))
	{
		return *Found;
	}
	for (const TPair<FString, TSharedPtr<IImageGenService>>& KV : ImageGens)
	{
		if (KV.Value.IsValid())
		{
			return KV.Value;
		}
	}
	return nullptr;
}

TSharedPtr<IImageTo3DService> FModelRouter::PickImageTo3D(const FString& QualityHint) const
{
	if (const TSharedPtr<IImageTo3DService>* Found = ImageTo3Ds.Find(QualityHint))
	{
		return *Found;
	}
	for (const TPair<FString, TSharedPtr<IImageTo3DService>>& KV : ImageTo3Ds)
	{
		if (KV.Value.IsValid())
		{
			return KV.Value;
		}
	}
	return nullptr;
}
