#pragma once

#include "CoreMinimal.h"
#include "EffectSpecV1.generated.h"

USTRUCT()
struct FMaterialHLSLInput
{
	GENERATED_BODY()

	UPROPERTY() FString Name;
	UPROPERTY() FString Type;
	UPROPERTY() float Default = 0.0f;
	UPROPERTY() float Min = 0.0f;
	UPROPERTY() float Max = 1.0f;
};

USTRUCT()
struct FMaterialHLSLTextureInput
{
	GENERATED_BODY()

	UPROPERTY() FString Name;
	UPROPERTY() FString Usage;
};

USTRUCT()
struct FMaterialHLSLOutputs
{
	GENERATED_BODY()

	UPROPERTY() bool emissive = true;
	UPROPERTY() bool opacity = true;
	UPROPERTY() bool distortion = false;
};

USTRUCT()
struct FMaterialHLSLCustom
{
	GENERATED_BODY()

	UPROPERTY() bool Enabled = false;
	UPROPERTY() FString Code;
	UPROPERTY() TArray<FMaterialHLSLInput> Inputs;
	UPROPERTY() TArray<FMaterialHLSLTextureInput> TextureInputs;
	UPROPERTY() FMaterialHLSLOutputs Outputs;
	UPROPERTY() FString Contract;
};

USTRUCT()
struct FMaterialSpecV1
{
	GENERATED_BODY()

	UPROPERTY() FString Shading; // unlit|lit
	UPROPERTY() FString Blend;   // additive|translucent|masked|opaque
	UPROPERTY() TMap<FString, bool> Features;
	UPROPERTY() TMap<FString, float> ScalarParams;
	UPROPERTY() TMap<FString, FLinearColor> VectorParams;
	UPROPERTY() TMap<FString, FString> TextureSlots;
	UPROPERTY() FMaterialHLSLCustom HLSLCustom;
};

USTRUCT()
struct FLayerSpawnSpecV1
{
	GENERATED_BODY()
	UPROPERTY() FString Mode; // rate|burst
	UPROPERTY() float Rate = 0.0f;
	UPROPERTY() int32 BurstCount = 0;
	UPROPERTY() float Duration = 0.0f;
};

USTRUCT()
struct FLayerInitSpecV1
{
	GENERATED_BODY()
	UPROPERTY() float Lifetime = 2.0f;
	UPROPERTY() FVector2f SizeRange = FVector2f(10.0f, 30.0f);
	UPROPERTY() FVector Velocity = FVector(0, 0, 0);
	UPROPERTY() FString DirectionMode;
};

USTRUCT()
struct FLayerUpdateSpecV1
{
	GENERATED_BODY()
	UPROPERTY() float Drag = 0.0f;
	UPROPERTY() float CurlNoiseStrength = 0.0f;
	UPROPERTY() FString ColorOverLife;
	UPROPERTY() FString AlphaOverLife;
};

USTRUCT()
struct FTextureRequestV1
{
	GENERATED_BODY()
	UPROPERTY() FString Name;
	UPROPERTY() FString Usage;
	UPROPERTY() int32 Width = 512;
	UPROPERTY() int32 Height = 512;
};

USTRUCT()
struct FModelRequestV1
{
	GENERATED_BODY()
	UPROPERTY() FString Name;
	UPROPERTY() FString Format; // glb|fbx|obj
};

USTRUCT()
struct FMotionSpecV1
{
	GENERATED_BODY()
	UPROPERTY() FString Semantic;
};

USTRUCT()
struct FQualityBudgetV1
{
	GENERATED_BODY()
	UPROPERTY() FString PerfCostHint; // low|mid|high
	UPROPERTY() int32 MaxParticlesHint = 1000;
};

USTRUCT()
struct FLayerSpecV1
{
	GENERATED_BODY()

	UPROPERTY() FString Id;
	UPROPERTY() FString Name;
	UPROPERTY() FString Role;
	UPROPERTY() FString RendererType; // sprite|ribbon|mesh
	UPROPERTY() FLayerSpawnSpecV1 Spawn;
	UPROPERTY() FLayerInitSpecV1 Init;
	UPROPERTY() FLayerUpdateSpecV1 Update;
	UPROPERTY() FMaterialSpecV1 Material;
	UPROPERTY() TArray<FTextureRequestV1> TexturesNeeded;
	UPROPERTY() FModelRequestV1 ModelNeeded;
	UPROPERTY() FMotionSpecV1 Motion;
	UPROPERTY() FQualityBudgetV1 QualityBudget;
};

USTRUCT()
struct FEffectStyleV1
{
	GENERATED_BODY()
	UPROPERTY() FString Palette;
	UPROPERTY() float RealismToAnime = 0.5f;
	UPROPERTY() float Brightness = 1.0f;
	UPROPERTY() float Contrast = 1.0f;
	UPROPERTY() FString NoiseStyle;
};

USTRUCT()
struct FExternalAssetsV1
{
	GENERATED_BODY()
	UPROPERTY() FString ReferenceImage;
	UPROPERTY() TArray<FString> ElementImages;
};

USTRUCT()
struct FEffectSpecV1
{
	GENERATED_BODY()

	static constexpr int32 Version = 1;

	UPROPERTY() FString EffectName;
	UPROPERTY() FEffectStyleV1 GlobalStyle;
	UPROPERTY() TArray<FLayerSpecV1> Layers;
	UPROPERTY() FExternalAssetsV1 ExternalAssets;
};
