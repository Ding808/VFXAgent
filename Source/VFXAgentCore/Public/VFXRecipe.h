#pragma once

#include "CoreMinimal.h"
#include "VFXRecipe.generated.h"

USTRUCT(BlueprintType)
struct FVFXEmitterRecipe
{
	GENERATED_BODY()

	// Optional human-readable layer name/purpose (e.g. "CoreBurst", "Sparks", "Smoke", "Shockwave").
	// Used for naming within the generated Niagara System.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	float SpawnRate = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	int32 BurstCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FString RendererType = "Sprite"; // Sprite, Mesh, Ribbon

	// New: Specify a preferred Niagara template to base this emitter on.
	// Examples: "Fountain", "DirectionalBurst", "HangingParticulates", "OmnidirectionalBurst", "UpwardMeshBurst", "Beam"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FString TemplateName = "Fountain";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FLinearColor Color = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	float Lifetime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	float Size = 10.0f;

	// Initial velocity direction and magnitude for particles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FVector Velocity = FVector(0, 0, 100);
};

USTRUCT(BlueprintType)
struct FVFXTextureRecipe
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	FString Name = "GeneratedTexture";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	FString Type = "Gradient"; // Gradient, Noise, Perlin, Voronoi, Custom

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	FLinearColor PrimaryColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	FLinearColor SecondaryColor = FLinearColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	int32 Resolution = 256; // Texture resolution (256, 512, 1024, etc.)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	float NoiseScale = 1.0f; // For noise-based textures

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	int32 Octaves = 4; // For fractal noise

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	FString Description;
};

USTRUCT(BlueprintType)
struct FVFXMaterialRecipe
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FString Name = "GeneratedMaterial";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FString Description = "Basic additive material";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	bool bIsAdditive = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	bool bIsUnlit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FString BaseMaterialPath = "/Engine/EngineMaterials/ParticleSpriteMaterial";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FLinearColor BaseColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FLinearColor EmissiveColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	float EmissiveStrength = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	float Opacity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	float Roughness = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	float Metallic = 0.0f;

	// Textures to use (can reference generated textures)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FString BaseColorTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FString EmissiveTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FString OpacityTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FString NormalTexture;

	// Auto-generate textures based on these recipes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	TArray<FVFXTextureRecipe> GeneratedTextures;
};

// --- New Schema for Niagara Spec ---

UENUM(BlueprintType)
enum class EVFXRendererType : uint8
{
	Sprite UMETA(DisplayName = "Sprite"),
	Ribbon UMETA(DisplayName = "Ribbon"),
	Light UMETA(DisplayName = "Light")
};

USTRUCT(BlueprintType)
struct FVFXPerSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float Rate = 0.0f; // If > 0, use SpawnRate

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	int32 Burst = 0; // If > 0, use Burst
};

USTRUCT(BlueprintType)
struct FVFXEmitterSpec
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FString Name;

	// Path to a Niagara System or Emitter asset to use as template
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FString TemplatePath;

	// Or a known ID like "Fountain", "Beam" if we support mapping
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FString TemplateId; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	EVFXRendererType RendererType = EVFXRendererType::Sprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FVFXPerSpawnInfo Spawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FLinearColor Color = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	float Lifetime = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	float Size = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FString Notes;
};

USTRUCT(BlueprintType)
struct FVFXEffectSpec
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	FString SystemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	FString TargetPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	TArray<FVFXEmitterSpec> Emitters;
};

USTRUCT(BlueprintType)
struct FVFXRepairReport
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Report")
	FString SystemPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Report")
	bool bCompileSuccess = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Report")
	TArray<FString> Errors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Report")
	TArray<FString> Warnings;
};

USTRUCT(BlueprintType)
struct FVFXRecipe
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "System")
	bool bLoop = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "System")
	float Duration = 0.0f; // 0 for infinite

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "System")
	float WarmupTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "System")
	FVector Bounds = FVector(100.0f, 100.0f, 100.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitters")
	TArray<FVFXEmitterRecipe> Emitters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	TMap<FString, FString> Parameters; // User parameters like color, intensity

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	TArray<FVFXMaterialRecipe> Materials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dependencies")
	TArray<FString> Dependencies; // Texture/Model paths

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Version")
	int32 Version = 1;
};