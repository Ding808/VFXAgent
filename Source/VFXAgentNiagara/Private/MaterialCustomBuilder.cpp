#include "MaterialCustomBuilder.h"
#include "VFXAgentLog.h"
#include "PipelineLog.h"
#include "Materials/Material.h"
#include "Materials/MaterialExpressionCustom.h"
#include "Materials/MaterialExpressionTextureSampleParameter2D.h"
#include "Materials/MaterialExpressionScalarParameter.h"
#include "Materials/MaterialExpressionVectorParameter.h"
#include "Materials/MaterialExpressionTime.h"
#include "Materials/MaterialExpressionTextureCoordinate.h"
#include "Engine/Texture.h"
#if __has_include("Materials/MaterialEditorOnlyData.h")
#include "Materials/MaterialEditorOnlyData.h"
#define VFXAGENT_HAS_MATERIAL_EDITOR_ONLY_DATA 1
#else
#define VFXAGENT_HAS_MATERIAL_EDITOR_ONLY_DATA 0
#endif
#include "UObject/SavePackage.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "PackageTools.h"

static FString BuildPackagePath(const FString& OutputPath, const FString& Name)
{
	FString PackageName = OutputPath / Name;
	if (!PackageName.StartsWith(TEXT("/Game")))
	{
		PackageName = FString::Printf(TEXT("/Game/%s"), *PackageName);
	}
	return PackageName;
}

UMaterialInterface* FMaterialCustomBuilder::BuildMaterialFromSpec(const FMaterialSpecV1& Spec, const FString& OutputPath, const FString& MaterialName, const FString& EffectName, const FString& LayerName)
{
	if (!Spec.HLSLCustom.Enabled || Spec.HLSLCustom.Code.IsEmpty())
	{
		FPipelineLog::Get().Push(EPipelineLogLevel::Warning, EPipelineStage::Material, TEXT("HLSL disabled; using fallback material"));
		return BuildFallbackMaterial(OutputPath, MaterialName);
	}

	SaveHlslToDisk(EffectName, LayerName, Spec.HLSLCustom.Code);
	UMaterial* Material = CreateCustomMasterMaterial(Spec, OutputPath, MaterialName, EffectName, LayerName);
	if (!Material)
	{
		FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::Material, TEXT("HLSL material build failed; using fallback"));
		return BuildFallbackMaterial(OutputPath, MaterialName);
	}

	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Material, TEXT("HLSL material build succeeded"));
	return Material;
}

UMaterial* FMaterialCustomBuilder::CreateCustomMasterMaterial(const FMaterialSpecV1& Spec, const FString& OutputPath, const FString& MaterialName, const FString& EffectName, const FString& LayerName)
{
#if WITH_EDITOR
	const FString PackageName = BuildPackagePath(OutputPath, MaterialName);
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

	UMaterial* Material = FindObject<UMaterial>(Package, *MaterialName);
	if (!Material)
	{
		Material = NewObject<UMaterial>(Package, *MaterialName, RF_Public | RF_Standalone);
	}
	if (!Material)
	{
		return nullptr;
	}

	const FString Blend = Spec.Blend.ToLower();
	if (Blend == TEXT("additive")) Material->BlendMode = BLEND_Additive;
	else if (Blend == TEXT("masked")) Material->BlendMode = BLEND_Masked;
	else if (Blend == TEXT("opaque")) Material->BlendMode = BLEND_Opaque;
	else Material->BlendMode = BLEND_Translucent;

#if ENGINE_MAJOR_VERSION > 5 || (ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5)
	Material->SetShadingModel(Spec.Shading.ToLower() == TEXT("lit") ? MSM_DefaultLit : MSM_Unlit);
#else
	Material->ShadingModels = FMaterialShadingModelField(Spec.Shading.ToLower() == TEXT("lit") ? MSM_DefaultLit : MSM_Unlit);
#endif
	Material->TwoSided = true;
	Material->bUseMaterialAttributes = false;

#if VFXAGENT_HAS_MATERIAL_EDITOR_ONLY_DATA
	UMaterialEditorOnlyData* EditorData = Material->GetEditorOnlyData();
	EditorData->Expressions.Empty();
	EditorData->EditorComments.Empty();

	UMaterialExpressionCustom* Custom = NewObject<UMaterialExpressionCustom>(Material);
	Custom->Code = Spec.HLSLCustom.Code;
	Custom->OutputType = CMOT_Float4;

	UMaterialExpressionTextureCoordinate* TexCoord = NewObject<UMaterialExpressionTextureCoordinate>(Material);
	UMaterialExpressionTime* Time = NewObject<UMaterialExpressionTime>(Material);

	EditorData->Expressions.Add(Custom);
	EditorData->Expressions.Add(TexCoord);
	EditorData->Expressions.Add(Time);

	Custom->Inputs.Empty();
	FCustomInput UvInput;
	UvInput.InputName = TEXT("uv");
	Custom->Inputs.Add(UvInput);
	FCustomInput TimeInput;
	TimeInput.InputName = TEXT("t");
	Custom->Inputs.Add(TimeInput);
	Custom->Inputs[0].Input.Expression = TexCoord;
	Custom->Inputs[1].Input.Expression = Time;

	// Add scalar/vector inputs
	for (const FMaterialHLSLInput& Input : Spec.HLSLCustom.Inputs)
	{
		FCustomInput CI;
		CI.InputName = *Input.Name;
		if (Input.Type.Contains(TEXT("float3")) || Input.Type.Contains(TEXT("float4")))
		{
			UMaterialExpressionVectorParameter* Vec = NewObject<UMaterialExpressionVectorParameter>(Material);
			Vec->ParameterName = *Input.Name;
			Vec->DefaultValue = FLinearColor(Input.Default, Input.Default, Input.Default, 1.0f);
			EditorData->Expressions.Add(Vec);
			CI.Input.Expression = Vec;
		}
		else
		{
			UMaterialExpressionScalarParameter* Scalar = NewObject<UMaterialExpressionScalarParameter>(Material);
			Scalar->ParameterName = *Input.Name;
			Scalar->DefaultValue = Input.Default;
			EditorData->Expressions.Add(Scalar);
			CI.Input.Expression = Scalar;
		}
		Custom->Inputs.Add(CI);
	}

	// Add texture inputs
	for (const FMaterialHLSLTextureInput& TexInput : Spec.HLSLCustom.TextureInputs)
	{
		UMaterialExpressionTextureSampleParameter2D* Tex = NewObject<UMaterialExpressionTextureSampleParameter2D>(Material);
		Tex->ParameterName = *TexInput.Name;
		Tex->Coordinates.Expression = TexCoord;
		EditorData->Expressions.Add(Tex);
		FCustomInput CI;
		CI.InputName = *TexInput.Name;
		CI.Input.Expression = Tex;
		Custom->Inputs.Add(CI);
	}

	if (Spec.HLSLCustom.Outputs.emissive)
	{
		Material->EmissiveColor.Expression = Custom;
	}
	if (Spec.HLSLCustom.Outputs.opacity)
	{
		Material->Opacity.Expression = Custom;
		Material->OpacityMask.Expression = Custom;
	}

	// Apply scalar/vector parameters from spec
	for (UMaterialExpression* Expr : EditorData->Expressions)
	{
		if (UMaterialExpressionScalarParameter* Scalar = Cast<UMaterialExpressionScalarParameter>(Expr))
		{
			if (const float* Found = Spec.ScalarParams.Find(Scalar->ParameterName.ToString()))
			{
				Scalar->DefaultValue = *Found;
			}
		}
		else if (UMaterialExpressionVectorParameter* Vector = Cast<UMaterialExpressionVectorParameter>(Expr))
		{
			if (const FLinearColor* Found = Spec.VectorParams.Find(Vector->ParameterName.ToString()))
			{
				Vector->DefaultValue = *Found;
			}
		}
		else if (UMaterialExpressionTextureSampleParameter2D* Tex = Cast<UMaterialExpressionTextureSampleParameter2D>(Expr))
		{
			if (const FString* Path = Spec.TextureSlots.Find(Tex->ParameterName.ToString()))
			{
				if (UTexture* Texture = LoadObject<UTexture>(nullptr, **Path))
				{
					Tex->Texture = Texture;
				}
			}
		}
	}

	Material->PostEditChange();
	Material->MarkPackageDirty();
	Package->SetDirtyFlag(true);

	if (Material->bCompilationErrors)
	{
		const FString Errors = FString::Join(Material->CompileErrors, TEXT("\n"));
		FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::Material, Errors);
		return nullptr;
	}

	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
	SaveArgs.Error = GError;
	const FString PackageFilename = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());
	if (UPackage::SavePackage(Package, Material, *PackageFilename, SaveArgs))
	{
		FAssetRegistryModule::AssetCreated(Material);
		FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Material, TEXT("HLSL custom material built"));
		return Material;
	}
#endif
	return nullptr;
#else
	return nullptr;
#endif
}

void FMaterialCustomBuilder::SaveHlslToDisk(const FString& EffectName, const FString& LayerName, const FString& Code)
{
	const FString BaseDir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("VFXAgent"), TEXT("Logs"), EffectName);
	IFileManager::Get().MakeDirectory(*BaseDir, true);
	const FString FilePath = FPaths::Combine(BaseDir, FString::Printf(TEXT("%s_custom.hlsl"), *LayerName));
	FFileHelper::SaveStringToFile(Code, *FilePath);
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Material, FString::Printf(TEXT("HLSL saved: %s"), *FilePath));
}

UMaterialInterface* FMaterialCustomBuilder::BuildFallbackMaterial(const FString& OutputPath, const FString& MaterialName)
{
	UMaterial* DefaultMat = LoadObject<UMaterial>(nullptr, TEXT("/Niagara/DefaultAssets/DefaultSpriteMaterial.DefaultSpriteMaterial"));
	if (DefaultMat)
	{
		return DefaultMat;
	}
	return LoadObject<UMaterial>(nullptr, TEXT("/Engine/EngineMaterials/DefaultMaterial.DefaultMaterial"));
}
