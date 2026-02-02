#include "MaterialGenerator.h"
#include "VFXAgentLog.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialExpressionConstant.h"
#include "Materials/MaterialExpressionVectorParameter.h"
#include "Materials/MaterialExpressionScalarParameter.h"
#include "Materials/MaterialExpressionTextureSampleParameter2D.h"
#include "Engine/Texture2D.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "UObject/SavePackage.h"
#include "Factories/MaterialInstanceConstantFactoryNew.h"
#include "Factories/Texture2DFactoryNew.h"
#include "PackageTools.h"

UMaterialInstanceConstant* UMaterialGenerator::GenerateMaterial(
	const FVFXMaterialRecipe& MaterialRecipe,
	const FString& OutputPath)
{
	UE_LOG(LogVFXAgent, Log, TEXT("Generating material: %s at %s"), *MaterialRecipe.Name, *OutputPath);

	// Get parent material
	UMaterial* ParentMaterial = GetParentMaterial(MaterialRecipe);
	if (!ParentMaterial)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to find parent material"));
		return nullptr;
	}

	// Create package for material instance
	FString PackageName = OutputPath / MaterialRecipe.Name;
	UPackage* Package = FindPackage(nullptr, *PackageName);
	if (!Package)
	{
		Package = CreatePackage(*PackageName);
	}
	if (!Package)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to create package: %s"), *PackageName);
		return nullptr;
	}
	if (!Package->IsFullyLoaded())
	{
		Package->FullyLoad();
	}

	// Create material instance
	UMaterialInstanceConstant* MaterialInstance = FindObject<UMaterialInstanceConstant>(Package, *MaterialRecipe.Name);
	const bool bCreatedNew = (MaterialInstance == nullptr);
	if (!MaterialInstance)
	{
		MaterialInstance = NewObject<UMaterialInstanceConstant>(
			Package,
			*MaterialRecipe.Name,
			RF_Public | RF_Standalone);
	}
	else
	{
		MaterialInstance->SetFlags(RF_Public | RF_Standalone);
	}

	if (!MaterialInstance)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to create material instance"));
		return nullptr;
	}

	// Set parent material
	MaterialInstance->SetParentEditorOnly(ParentMaterial);

	// Apply parameters
	ApplyColorParameters(MaterialInstance, MaterialRecipe);
	ApplyTextureParameters(MaterialInstance, MaterialRecipe);

	// Initialize static parameters
	MaterialInstance->InitStaticPermutation();
	MaterialInstance->PostEditChange();
	MaterialInstance->MarkPackageDirty();
	Package->SetDirtyFlag(true);

	// Save package
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
	SaveArgs.Error = GError;
	SaveArgs.bForceByteSwapping = false;
	SaveArgs.bWarnOfLongFilename = true;

	FString PackageFilename = FPackageName::LongPackageNameToFilename(
		PackageName,
		FPackageName::GetAssetPackageExtension());

	if (UPackage::SavePackage(Package, MaterialInstance, *PackageFilename, SaveArgs))
	{
		UE_LOG(LogVFXAgent, Log, TEXT("Material saved successfully: %s"), *PackageFilename);
		
		// Register asset
		if (bCreatedNew)
		{
			FAssetRegistryModule::AssetCreated(MaterialInstance);
		}
		
		return MaterialInstance;
	}

	UE_LOG(LogVFXAgent, Error, TEXT("Failed to save material package"));
	return nullptr;
}

bool UMaterialGenerator::UpdateMaterial(
	UMaterialInstanceConstant* Material,
	const FVFXMaterialRecipe& MaterialRecipe)
{
	if (!Material)
	{
		return false;
	}

	UE_LOG(LogVFXAgent, Log, TEXT("Updating material: %s"), *Material->GetName());

	ApplyColorParameters(Material, MaterialRecipe);
	ApplyTextureParameters(Material, MaterialRecipe);

	Material->PostEditChange();
	return true;
}

UTexture2D* UMaterialGenerator::GenerateProceduralTexture(
	const FVFXTextureRecipe& TextureRecipe,
	const FString& OutputPath)
{
	UE_LOG(LogVFXAgent, Log, TEXT("Generating procedural texture: %s"), *TextureRecipe.Name);

	if (TextureRecipe.Type == "Gradient")
	{
		return GenerateGradientTexture(TextureRecipe, OutputPath);
	}
	else if (TextureRecipe.Type == "Noise" || TextureRecipe.Type == "Perlin")
	{
		return GenerateNoiseTexture(TextureRecipe, OutputPath);
	}

	UE_LOG(LogVFXAgent, Warning, TEXT("Unsupported texture type: %s"), *TextureRecipe.Type);
	return nullptr;
}

UMaterial* UMaterialGenerator::GetParentMaterial(const FVFXMaterialRecipe& MaterialRecipe)
{
	// Try to load specified base material
	if (!MaterialRecipe.BaseMaterialPath.IsEmpty())
	{
		UMaterial* Material = LoadObject<UMaterial>(nullptr, *MaterialRecipe.BaseMaterialPath);
		if (Material)
		{
			return Material;
		}
	}

	// Fallback to default particle materials based on properties
	FString DefaultPath;
	if (MaterialRecipe.bIsAdditive)
	{
		DefaultPath = TEXT("/Engine/EngineMaterials/ParticleSpriteMaterial");
	}
	else
	{
		DefaultPath = TEXT("/Engine/EngineMaterials/DefaultMaterial");
	}

	return LoadObject<UMaterial>(nullptr, *DefaultPath);
}

void UMaterialGenerator::ApplyColorParameters(
	UMaterialInstanceConstant* Material,
	const FVFXMaterialRecipe& Recipe)
{
	if (!Material)
	{
		return;
	}

	// Set base color
	Material->SetVectorParameterValueEditorOnly(FName("BaseColor"), Recipe.BaseColor);
	Material->SetVectorParameterValueEditorOnly(FName("Color"), Recipe.BaseColor);
	Material->SetVectorParameterValueEditorOnly(FName("Tint"), Recipe.BaseColor);

	// Set emissive color
	Material->SetVectorParameterValueEditorOnly(FName("EmissiveColor"), Recipe.EmissiveColor);
	Material->SetScalarParameterValueEditorOnly(FName("EmissiveStrength"), Recipe.EmissiveStrength);

	// Set opacity
	Material->SetScalarParameterValueEditorOnly(FName("Opacity"), Recipe.Opacity);
	Material->SetScalarParameterValueEditorOnly(FName("Alpha"), Recipe.Opacity);

	// Set material properties
	Material->SetScalarParameterValueEditorOnly(FName("Roughness"), Recipe.Roughness);
	Material->SetScalarParameterValueEditorOnly(FName("Metallic"), Recipe.Metallic);

	UE_LOG(LogVFXAgent, Log, TEXT("Applied color parameters to material"));
}

void UMaterialGenerator::ApplyTextureParameters(
	UMaterialInstanceConstant* Material,
	const FVFXMaterialRecipe& Recipe)
{
	if (!Material)
	{
		return;
	}

	// Apply base color texture
	if (!Recipe.BaseColorTexture.IsEmpty())
	{
		UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, *Recipe.BaseColorTexture);
		if (Texture)
		{
			Material->SetTextureParameterValueEditorOnly(FName("BaseColorTexture"), Texture);
			Material->SetTextureParameterValueEditorOnly(FName("Texture"), Texture);
		}
	}

	// Apply emissive texture
	if (!Recipe.EmissiveTexture.IsEmpty())
	{
		UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, *Recipe.EmissiveTexture);
		if (Texture)
		{
			Material->SetTextureParameterValueEditorOnly(FName("EmissiveTexture"), Texture);
		}
	}

	// Apply opacity texture
	if (!Recipe.OpacityTexture.IsEmpty())
	{
		UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, *Recipe.OpacityTexture);
		if (Texture)
		{
			Material->SetTextureParameterValueEditorOnly(FName("OpacityTexture"), Texture);
			Material->SetTextureParameterValueEditorOnly(FName("OpacityMask"), Texture);
		}
	}

	// Apply normal texture
	if (!Recipe.NormalTexture.IsEmpty())
	{
		UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, *Recipe.NormalTexture);
		if (Texture)
		{
			Material->SetTextureParameterValueEditorOnly(FName("NormalTexture"), Texture);
			Material->SetTextureParameterValueEditorOnly(FName("Normal"), Texture);
		}
	}

	UE_LOG(LogVFXAgent, Log, TEXT("Applied texture parameters to material"));
}

UTexture2D* UMaterialGenerator::GenerateGradientTexture(
	const FVFXTextureRecipe& Recipe,
	const FString& OutputPath)
{
	const int32 Size = Recipe.Resolution;
	
	// Create package
	FString PackageName = OutputPath / Recipe.Name;
	UPackage* Package = FindPackage(nullptr, *PackageName);
	if (!Package)
	{
		Package = CreatePackage(*PackageName);
	}
	if (!Package)
	{
		return nullptr;
	}
	if (!Package->IsFullyLoaded())
	{
		Package->FullyLoad();
	}

	// Create texture
	UTexture2D* Texture = FindObject<UTexture2D>(Package, *Recipe.Name);
	const bool bCreatedNew = (Texture == nullptr);
	if (!Texture)
	{
		Texture = NewObject<UTexture2D>(
			Package,
			*Recipe.Name,
			RF_Public | RF_Standalone);
	}
	else
	{
		Texture->SetFlags(RF_Public | RF_Standalone);
	}

	if (!Texture)
	{
		return nullptr;
	}

	// Setup texture properties
	Texture->Source.Init(Size, Size, 1, 1, TSF_BGRA8);
	Texture->SRGB = true;
	Texture->CompressionSettings = TC_Default;

	// Lock mip data
	uint8* MipData = Texture->Source.LockMip(0);

	// Generate gradient (vertical gradient from primary to secondary color)
	for (int32 Y = 0; Y < Size; Y++)
	{
		float T = (float)Y / (float)(Size - 1);
		FLinearColor Color = FMath::Lerp(Recipe.PrimaryColor, Recipe.SecondaryColor, T);
		FColor Color32 = Color.ToFColor(true);

		for (int32 X = 0; X < Size; X++)
		{
			int32 Index = (Y * Size + X) * 4;
			MipData[Index + 0] = Color32.B;
			MipData[Index + 1] = Color32.G;
			MipData[Index + 2] = Color32.R;
			MipData[Index + 3] = Color32.A;
		}
	}

	// Unlock and update
	Texture->Source.UnlockMip(0);
	Texture->UpdateResource();
	Texture->PostEditChange();
	Texture->MarkPackageDirty();
	Package->SetDirtyFlag(true);

	// Save package
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
	FString PackageFilename = FPackageName::LongPackageNameToFilename(
		PackageName,
		FPackageName::GetAssetPackageExtension());

	if (UPackage::SavePackage(Package, Texture, *PackageFilename, SaveArgs))
	{
		if (bCreatedNew)
		{
			FAssetRegistryModule::AssetCreated(Texture);
		}
		UE_LOG(LogVFXAgent, Log, TEXT("Gradient texture created: %s"), *PackageFilename);
		return Texture;
	}

	return nullptr;
}

UTexture2D* UMaterialGenerator::GenerateNoiseTexture(
	const FVFXTextureRecipe& Recipe,
	const FString& OutputPath)
{
	const int32 Size = Recipe.Resolution;
	
	FString PackageName = OutputPath / Recipe.Name;
	UPackage* Package = FindPackage(nullptr, *PackageName);
	if (!Package)
	{
		Package = CreatePackage(*PackageName);
	}
	if (!Package)
	{
		return nullptr;
	}
	if (!Package->IsFullyLoaded())
	{
		Package->FullyLoad();
	}

	UTexture2D* Texture = FindObject<UTexture2D>(Package, *Recipe.Name);
	const bool bCreatedNew = (Texture == nullptr);
	if (!Texture)
	{
		Texture = NewObject<UTexture2D>(
			Package,
			*Recipe.Name,
			RF_Public | RF_Standalone);
	}
	else
	{
		Texture->SetFlags(RF_Public | RF_Standalone);
	}

	if (!Texture)
	{
		return nullptr;
	}

	Texture->Source.Init(Size, Size, 1, 1, TSF_BGRA8);
	Texture->SRGB = false; // Noise textures typically don't use sRGB
	Texture->CompressionSettings = TC_Grayscale;

	uint8* MipData = Texture->Source.LockMip(0);

	// Simple Perlin-like noise using random values
	// In a real implementation, you'd use proper Perlin/Simplex noise
	for (int32 Y = 0; Y < Size; Y++)
	{
		for (int32 X = 0; X < Size; X++)
		{
			// Simple fractal noise
			float NoiseValue = 0.0f;
			float Amplitude = 1.0f;
			float Frequency = Recipe.NoiseScale;

			for (int32 Octave = 0; Octave < Recipe.Octaves; Octave++)
			{
				float SampleX = X * Frequency / Size;
				float SampleY = Y * Frequency / Size;
				
				// Simple hash-based noise (replace with proper Perlin in production)
				float HashF = (SampleX * 12.9898f + SampleY * 78.233f) * 43758.5453f;
				float Random = FMath::Frac(FMath::Sin(HashF) * 43758.5453f);
				
				NoiseValue += Random * Amplitude;
				Amplitude *= 0.5f;
				Frequency *= 2.0f;
			}

			NoiseValue /= 2.0f; // Normalize
			uint8 GrayValue = (uint8)(FMath::Clamp(NoiseValue, 0.0f, 1.0f) * 255);

			int32 Index = (Y * Size + X) * 4;
			MipData[Index + 0] = GrayValue;
			MipData[Index + 1] = GrayValue;
			MipData[Index + 2] = GrayValue;
			MipData[Index + 3] = 255;
		}
	}

	Texture->Source.UnlockMip(0);
	Texture->UpdateResource();
	Texture->PostEditChange();
	Texture->MarkPackageDirty();
	Package->SetDirtyFlag(true);

	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
	FString PackageFilename = FPackageName::LongPackageNameToFilename(
		PackageName,
		FPackageName::GetAssetPackageExtension());

	if (UPackage::SavePackage(Package, Texture, *PackageFilename, SaveArgs))
	{
		if (bCreatedNew)
		{
			FAssetRegistryModule::AssetCreated(Texture);
		}
		UE_LOG(LogVFXAgent, Log, TEXT("Noise texture created: %s"), *PackageFilename);
		return Texture;
	}

	return nullptr;
}
