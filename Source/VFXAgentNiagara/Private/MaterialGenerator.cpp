#include "MaterialGenerator.h"
#include "VFXAgentLog.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialExpressionConstant.h"
#include "Materials/MaterialExpressionVectorParameter.h"
#include "Materials/MaterialExpressionScalarParameter.h"
#include "Materials/MaterialExpressionTextureSampleParameter2D.h"
#include "Materials/MaterialExpressionMultiply.h"
#include "Materials/MaterialExpressionAdd.h"
#include "Materials/MaterialExpressionNoise.h"
#include "Materials/MaterialExpressionFresnel.h"
#include "Materials/MaterialExpressionLinearInterpolate.h"
#include "Materials/MaterialExpressionComponentMask.h"
#include "Materials/MaterialExpressionClamp.h"
#include "Materials/MaterialExpression.h"
#include "UObject/UnrealType.h"
#if __has_include("Materials/MaterialEditorOnlyData.h")
#include "Materials/MaterialEditorOnlyData.h"
#define VFXAGENT_HAS_MATERIAL_EDITOR_ONLY_DATA 1
#else
#define VFXAGENT_HAS_MATERIAL_EDITOR_ONLY_DATA 0
#endif
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

	// Get parent material (procedural if needed)
	UMaterial* ParentMaterial = nullptr;
	if (ShouldUseProceduralParent(MaterialRecipe))
	{
		ParentMaterial = BuildProceduralParentMaterial(MaterialRecipe, OutputPath);
		if (ParentMaterial)
		{
			UE_LOG(LogVFXAgent, Log, TEXT("Using procedural parent material: %s"), *ParentMaterial->GetPathName());
		}
	}

	if (!ParentMaterial)
	{
		ParentMaterial = GetParentMaterial(MaterialRecipe);
	}
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
			UE_LOG(LogVFXAgent, Log, TEXT("Using custom base material: %s"), *MaterialRecipe.BaseMaterialPath);
			return Material;
		}
		else
		{
			UE_LOG(LogVFXAgent, Warning, TEXT("Failed to load specified base material: %s"), *MaterialRecipe.BaseMaterialPath);
		}
	}

	// Robust fallback chain for particle materials
	// Try multiple known working paths in UE5
	TArray<FString> CandidatePaths;
	
	if (MaterialRecipe.bIsAdditive)
	{
		// Additive/Translucent particle materials
		CandidatePaths.Add(TEXT("/Niagara/DefaultAssets/DefaultSpriteMaterial.DefaultSpriteMaterial"));
		CandidatePaths.Add(TEXT("/Engine/EngineMaterials/DefaultMaterial.DefaultMaterial"));
		CandidatePaths.Add(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
	}
	else
	{
		// Opaque materials
		CandidatePaths.Add(TEXT("/Engine/EngineMaterials/DefaultMaterial.DefaultMaterial"));
		CandidatePaths.Add(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));
		CandidatePaths.Add(TEXT("/Niagara/DefaultAssets/DefaultSpriteMaterial.DefaultSpriteMaterial"));
	}
	
	// Try each candidate
	for (const FString& Path : CandidatePaths)
	{
		UMaterial* Material = LoadObject<UMaterial>(nullptr, *Path);
		if (Material)
		{
			UE_LOG(LogVFXAgent, Log, TEXT("Using fallback base material: %s"), *Path);
			return Material;
		}
	}
	
	// Final emergency fallback - default material
	UE_LOG(LogVFXAgent, Error, TEXT("Could not find any suitable base material! VFX may not render correctly."));
	return LoadObject<UMaterial>(nullptr, TEXT("/Engine/EngineMaterials/DefaultMaterial.DefaultMaterial"));
}

bool UMaterialGenerator::ShouldUseProceduralParent(const FVFXMaterialRecipe& Recipe) const
{
	const bool bHasAnyTexture =
		!Recipe.BaseColorTexture.IsEmpty() ||
		!Recipe.EmissiveTexture.IsEmpty() ||
		!Recipe.OpacityTexture.IsEmpty() ||
		!Recipe.NormalTexture.IsEmpty() ||
		Recipe.GeneratedTextures.Num() > 0;

	return !bHasAnyTexture;
}

UMaterial* UMaterialGenerator::BuildProceduralParentMaterial(const FVFXMaterialRecipe& Recipe, const FString& OutputPath)
{
#if WITH_EDITOR
	const FString BaseName = Recipe.Name + TEXT("_Base");
	FString PackageName = OutputPath / BaseName;
	UPackage* Package = FindPackage(nullptr, *PackageName);
	if (!Package)
	{
		Package = CreatePackage(*PackageName);
	}
	if (!Package)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to create material package: %s"), *PackageName);
		return nullptr;
	}
	if (!Package->IsFullyLoaded())
	{
		Package->FullyLoad();
	}

	UMaterial* Material = FindObject<UMaterial>(Package, *BaseName);
	if (!Material)
	{
		Material = NewObject<UMaterial>(Package, *BaseName, RF_Public | RF_Standalone);
	}
	if (!Material)
	{
		return nullptr;
	}

	Material->BlendMode = Recipe.bIsAdditive ? BLEND_Additive : BLEND_Translucent;
#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5)
	Material->SetShadingModel(MSM_Unlit);
#else
	Material->ShadingModels = FMaterialShadingModelField(MSM_Unlit);
#endif
	Material->TwoSided = true;
	Material->bUseMaterialAttributes = false;

	// Expressions
	auto CreateExpressionByPath = [Material](const TCHAR* ClassPath, const TCHAR* ClassNameForLog) -> UMaterialExpression*
	{
		UClass* ExpressionClass = FindObject<UClass>(nullptr, ClassPath);
		if (!ExpressionClass)
		{
			ExpressionClass = StaticLoadClass(UMaterialExpression::StaticClass(), nullptr, ClassPath);
		}
		if (!ExpressionClass)
		{
			UE_LOG(LogVFXAgent, Warning, TEXT("Failed to load material expression class: %s"), ClassNameForLog);
			return nullptr;
		}
		return NewObject<UMaterialExpression>(Material, ExpressionClass);
	};

	UMaterialExpression* ParticleColor = CreateExpressionByPath(
		TEXT("/Script/Engine.MaterialExpressionParticleColor"),
		TEXT("MaterialExpressionParticleColor"));
	UMaterialExpressionNoise* Noise = NewObject<UMaterialExpressionNoise>(Material);
	Noise->Scale = 5.0f;

	UMaterialExpressionScalarParameter* OpacityParam = NewObject<UMaterialExpressionScalarParameter>(Material);
	OpacityParam->ParameterName = TEXT("Opacity");
	OpacityParam->DefaultValue = Recipe.Opacity;

	UMaterialExpressionScalarParameter* EmissiveStrength = NewObject<UMaterialExpressionScalarParameter>(Material);
	EmissiveStrength->ParameterName = TEXT("EmissiveStrength");
	EmissiveStrength->DefaultValue = FMath::Max(Recipe.EmissiveStrength, 50.0f); // Boost default emissive

	UMaterialExpressionScalarParameter* SoftParticleStrength = NewObject<UMaterialExpressionScalarParameter>(Material);
	SoftParticleStrength->ParameterName = TEXT("SoftParticleStrength");
	SoftParticleStrength->DefaultValue = 0.8f; // Increase soft particle effect

	UMaterialExpressionScalarParameter* SoftParticleDistance = NewObject<UMaterialExpressionScalarParameter>(Material);
	SoftParticleDistance->ParameterName = TEXT("SoftParticleDistance");
	SoftParticleDistance->DefaultValue = 50.0f; // Increase soft particle distance

	UMaterialExpressionScalarParameter* FresnelIntensity = NewObject<UMaterialExpressionScalarParameter>(Material);
	FresnelIntensity->ParameterName = TEXT("FresnelIntensity");
	FresnelIntensity->DefaultValue = 0.0f;

	UMaterialExpressionScalarParameter* DissolveStrength = NewObject<UMaterialExpressionScalarParameter>(Material);
	DissolveStrength->ParameterName = TEXT("DissolveStrength");
	DissolveStrength->DefaultValue = 0.0f;

	UMaterialExpressionComponentMask* ParticleAlpha = NewObject<UMaterialExpressionComponentMask>(Material);
	ParticleAlpha->R = false;
	ParticleAlpha->G = false;
	ParticleAlpha->B = false;
	ParticleAlpha->A = true;
	ParticleAlpha->Input.Expression = ParticleColor;

	UMaterialExpressionMultiply* BaseOpacityMul = NewObject<UMaterialExpressionMultiply>(Material);
	BaseOpacityMul->A.Expression = ParticleAlpha;
	BaseOpacityMul->B.Expression = OpacityParam;

	UMaterialExpressionMultiply* NoiseOpacityMul = NewObject<UMaterialExpressionMultiply>(Material);
	NoiseOpacityMul->A.Expression = BaseOpacityMul;
	NoiseOpacityMul->B.Expression = Noise;

	UMaterialExpressionLinearInterpolate* DissolveLerp = NewObject<UMaterialExpressionLinearInterpolate>(Material);
	DissolveLerp->A.Expression = BaseOpacityMul;
	DissolveLerp->B.Expression = NoiseOpacityMul;
	DissolveLerp->Alpha.Expression = DissolveStrength;

	UMaterialExpression* DepthFade = CreateExpressionByPath(
		TEXT("/Script/Engine.MaterialExpressionDepthFade"),
		TEXT("MaterialExpressionDepthFade"));
	if (DepthFade)
	{
		FStructProperty* FadeDistanceProp = FindFProperty<FStructProperty>(
			DepthFade->GetClass(),
			TEXT("FadeDistance"));
		if (FadeDistanceProp && FadeDistanceProp->Struct && FadeDistanceProp->Struct->GetFName() == TEXT("ExpressionInput"))
		{
			FExpressionInput* FadeDistanceInput = FadeDistanceProp->ContainerPtrToValuePtr<FExpressionInput>(DepthFade);
			if (FadeDistanceInput)
			{
				FadeDistanceInput->Expression = SoftParticleDistance;
			}
		}
	}

	UMaterialExpressionLinearInterpolate* SoftParticleLerp = NewObject<UMaterialExpressionLinearInterpolate>(Material);
	SoftParticleLerp->A.Expression = DissolveLerp;
	SoftParticleLerp->B.Expression = DepthFade;
	SoftParticleLerp->Alpha.Expression = SoftParticleStrength;

	UMaterialExpressionMultiply* EmissiveMul = NewObject<UMaterialExpressionMultiply>(Material);
	EmissiveMul->A.Expression = ParticleColor;
	EmissiveMul->B.Expression = EmissiveStrength;

	UMaterialExpressionMultiply* EmissiveNoiseMul = NewObject<UMaterialExpressionMultiply>(Material);
	EmissiveNoiseMul->A.Expression = EmissiveMul;
	EmissiveNoiseMul->B.Expression = Noise;

	UMaterialExpressionFresnel* Fresnel = NewObject<UMaterialExpressionFresnel>(Material);
	UMaterialExpressionMultiply* FresnelMul = NewObject<UMaterialExpressionMultiply>(Material);
	FresnelMul->A.Expression = Fresnel;
	FresnelMul->B.Expression = FresnelIntensity;

	UMaterialExpressionAdd* EmissiveAdd = NewObject<UMaterialExpressionAdd>(Material);
	EmissiveAdd->A.Expression = EmissiveNoiseMul;
	EmissiveAdd->B.Expression = FresnelMul;

#if WITH_EDITORONLY_DATA && VFXAGENT_HAS_MATERIAL_EDITOR_ONLY_DATA
	if (UMaterialEditorOnlyData* EditorOnly = Material->GetEditorOnlyData())
	{
		EditorOnly->ExpressionCollection.Expressions =
		{
			ParticleColor,
			Noise,
			OpacityParam,
			EmissiveStrength,
			SoftParticleStrength,
			SoftParticleDistance,
			FresnelIntensity,
			DissolveStrength,
			ParticleAlpha,
			BaseOpacityMul,
			NoiseOpacityMul,
			DissolveLerp,
			DepthFade,
			SoftParticleLerp,
			EmissiveMul,
			EmissiveNoiseMul,
			Fresnel,
			FresnelMul,
			EmissiveAdd
		};

		EditorOnly->EmissiveColor.Expression = EmissiveAdd;
		EditorOnly->Opacity.Expression = SoftParticleLerp;
	}
	else
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("Material editor-only data unavailable; procedural graph not assigned."));
	}
#else
	UE_LOG(LogVFXAgent, Warning, TEXT("Material editor-only data header not found; procedural graph not assigned."));
#endif
	Material->PostEditChange();
	Material->MarkPackageDirty();
	Package->SetDirtyFlag(true);

	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
	SaveArgs.Error = GError;
	SaveArgs.bForceByteSwapping = false;
	SaveArgs.bWarnOfLongFilename = true;

	FString PackageFilename = FPackageName::LongPackageNameToFilename(
		PackageName,
		FPackageName::GetAssetPackageExtension());

	if (UPackage::SavePackage(Package, Material, *PackageFilename, SaveArgs))
	{
		FAssetRegistryModule::AssetCreated(Material);
		UE_LOG(LogVFXAgent, Log, TEXT("Procedural parent material saved: %s"), *PackageFilename);
	}
	else
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("Failed to save procedural parent material: %s"), *PackageFilename);
	}

	return Material;
#else
	UE_LOG(LogVFXAgent, Warning, TEXT("Procedural material generation requires editor support; skipping."));
	return nullptr;
#endif
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
	Material->SetScalarParameterValueEditorOnly(FName("EmissiveStrength"), FMath::Max(Recipe.EmissiveStrength, 50.0f)); // Boost default emissive

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
