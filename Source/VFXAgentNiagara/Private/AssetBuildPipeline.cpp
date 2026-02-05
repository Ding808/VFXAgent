#include "AssetBuildPipeline.h"
#include "EffectSpecParser.h"
#include "EffectSpecValidator.h"
#include "NiagaraSpecExecutor.h"
#include "VFXAgentLog.h"
#include "PipelineLog.h"
#include "MaterialCustomBuilder.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "NiagaraRendererProperties.h"
#include "NiagaraSpriteRendererProperties.h"
#include "NiagaraRibbonRendererProperties.h"
#include "NiagaraMeshRendererProperties.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "Misc/Crc.h"
#include "Misc/ConfigCacheIni.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "Modules/ModuleManager.h"
#include "UObject/UnrealType.h"
#include "AssetImportTask.h"
#include "Engine/Texture2D.h"
#include "Engine/StaticMesh.h"
#include "LocalModelServices.h"

static FString NormalizeOutputPath(const FString& Path)
{
	FString Result = Path.TrimStartAndEnd();
	if (!Result.StartsWith(TEXT("/Game")))
	{
		Result = FString::Printf(TEXT("/Game/%s"), *Result);
	}
	return Result;
}

static FString GetSettingString(const TCHAR* Key, const FString& DefaultValue)
{
	FString Value = DefaultValue;
	const TCHAR* Section = TEXT("/Script/VFXAgentEditor.VFXAgentSettings");
	const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
	for (const FString& File : ConfigFiles)
	{
		if (GConfig && GConfig->GetString(Section, Key, Value, File) && !Value.IsEmpty())
		{
			return Value;
		}
	}
	return DefaultValue;
}

static bool GetSettingBool(const TCHAR* Key, bool bDefault)
{
	bool bValue = bDefault;
	const TCHAR* Section = TEXT("/Script/VFXAgentEditor.VFXAgentSettings");
	const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
	for (const FString& File : ConfigFiles)
	{
		if (GConfig && GConfig->GetBool(Section, Key, bValue, File))
		{
			return bValue;
		}
	}
	return bDefault;
}

static FString ReadSpecHash(const FString& Folder);
static void WriteSpecHash(const FString& Folder, const FString& Hash);

static FString CreateVersionedFolder(const FString& Root, const FString& EffectName)
{
	FString Base = FPaths::Combine(Root, EffectName);
	Base = Base.Replace(TEXT("\\"), TEXT("/"));
	Base = NormalizeOutputPath(Base);

	for (int32 i = 1; i <= 999; ++i)
	{
		const FString Version = FString::Printf(TEXT("v%03d"), i);
		const FString Candidate = FPaths::Combine(Base, Version).Replace(TEXT("\\"), TEXT("/"));
		const FString PackageName = Candidate / EffectName;
		if (!FPackageName::DoesPackageExist(PackageName))
		{
			return Candidate;
		}
	}
	return Base;
}

static FString FindFolderByHash(const FString& Root, const FString& EffectName, const FString& Hash)
{
	FString Base = FPaths::Combine(Root, EffectName);
	Base = Base.Replace(TEXT("\\"), TEXT("/"));
	Base = NormalizeOutputPath(Base);

	for (int32 i = 1; i <= 999; ++i)
	{
		const FString Version = FString::Printf(TEXT("v%03d"), i);
		const FString Candidate = FPaths::Combine(Base, Version).Replace(TEXT("\\"), TEXT("/"));
		const FString PackageName = Candidate / EffectName;
		if (FPackageName::DoesPackageExist(PackageName))
		{
			const FString ExistingHash = ReadSpecHash(Candidate);
			if (!ExistingHash.IsEmpty() && ExistingHash == Hash)
			{
				return Candidate;
			}
		}
	}

	return FString();
}

static FString ReadSpecHash(const FString& Folder)
{
	const FString Path = FPaths::Combine(FPackageName::LongPackageNameToFilename(Folder), TEXT("spec_hash.txt"));
	FString Content;
	if (FFileHelper::LoadFileToString(Content, *Path))
	{
		return Content.TrimStartAndEnd();
	}
	return FString();
}

static void WriteSpecHash(const FString& Folder, const FString& Hash)
{
	const FString DiskFolder = FPackageName::LongPackageNameToFilename(Folder);
	IFileManager::Get().MakeDirectory(*DiskFolder, true);
	const FString Path = FPaths::Combine(DiskFolder, TEXT("spec_hash.txt"));
	FFileHelper::SaveStringToFile(Hash, *Path);
}

static EVFXRendererType ToRendererType(const FString& Type)
{
	const FString Lower = Type.ToLower();
	if (Lower == TEXT("ribbon")) return EVFXRendererType::Ribbon;
	if (Lower == TEXT("mesh")) return EVFXRendererType::Mesh;
	return EVFXRendererType::Sprite;
}

static bool SetStructMaterialProperty(void* StructPtr, UStruct* Struct, UMaterialInterface* Material)
{
	if (!StructPtr || !Struct || !Material)
	{
		return false;
	}

	for (TFieldIterator<FObjectPropertyBase> It(Struct); It; ++It)
	{
		FObjectPropertyBase* Prop = *It;
		if (!Prop)
		{
			continue;
		}
		if (Prop->PropertyClass->IsChildOf(UMaterialInterface::StaticClass()) && Prop->GetName().Contains(TEXT("Material")))
		{
			Prop->SetObjectPropertyValue_InContainer(StructPtr, Material);
			return true;
		}
	}

	return false;
}

static bool SetMeshRendererMaterial(UNiagaraMeshRendererProperties* Mesh, UMaterialInterface* Material)
{
	if (!Mesh || !Material)
	{
		return false;
	}

	const FName PossibleNames[] = { TEXT("OverrideMaterials"), TEXT("Materials") };
	for (const FName& Name : PossibleNames)
	{
		FArrayProperty* ArrayProp = FindFProperty<FArrayProperty>(Mesh->GetClass(), Name);
		if (!ArrayProp)
		{
			continue;
		}
		FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(Mesh));
		if (Helper.Num() == 0)
		{
			Helper.AddValue();
		}
		void* ElemPtr = Helper.GetRawPtr(0);
		if (FStructProperty* StructProp = CastField<FStructProperty>(ArrayProp->Inner))
		{
			if (SetStructMaterialProperty(ElemPtr, StructProp->Struct, Material))
			{
				return true;
			}
		}
		else if (FObjectPropertyBase* ObjProp = CastField<FObjectPropertyBase>(ArrayProp->Inner))
		{
			ObjProp->SetObjectPropertyValue(ElemPtr, Material);
			return true;
		}
	}

	return false;
}

static void AssignMaterialToEmitter(UNiagaraEmitter* Emitter, UMaterialInterface* Material)
{
	if (!Emitter || !Material) return;
	const FName PossibleNames[] = { TEXT("RendererProperties"), TEXT("Renderers") };
	for (const FName& Name : PossibleNames)
	{
		FArrayProperty* ArrayProp = FindFProperty<FArrayProperty>(Emitter->GetClass(), Name);
		if (!ArrayProp) continue;
		FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(Emitter));
		FObjectPropertyBase* InnerObjProp = CastField<FObjectPropertyBase>(ArrayProp->Inner);
		if (!InnerObjProp) break;
		for (int32 i = 0; i < Helper.Num(); ++i)
		{
			void* ElemPtr = Helper.GetRawPtr(i);
			UObject* Obj = InnerObjProp->GetObjectPropertyValue(ElemPtr);
			if (UNiagaraSpriteRendererProperties* Sprite = Cast<UNiagaraSpriteRendererProperties>(Obj))
			{
				Sprite->Material = Material;
			}
			else if (UNiagaraRibbonRendererProperties* Ribbon = Cast<UNiagaraRibbonRendererProperties>(Obj))
			{
				Ribbon->Material = Material;
			}
			else if (UNiagaraMeshRendererProperties* Mesh = Cast<UNiagaraMeshRendererProperties>(Obj))
			{
				SetMeshRendererMaterial(Mesh, Material);
			}
		}
		break;
	}
	Emitter->Modify();
	Emitter->PostEditChange();
}

static UObject* ImportAssetFromFile(const FString& SourceFile, const FString& DestPath)
{
#if WITH_EDITOR
	if (!FPaths::FileExists(SourceFile))
	{
		return nullptr;
	}

	UAssetImportTask* Task = NewObject<UAssetImportTask>();
	Task->Filename = SourceFile;
	Task->DestinationPath = DestPath;
	Task->bAutomated = true;
	Task->bReplaceExisting = true;
	Task->bSave = true;

	TArray<UAssetImportTask*> Tasks;
	Tasks.Add(Task);

	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
	AssetToolsModule.Get().ImportAssetTasks(Tasks);

	if (Task->ImportedObjectPaths.Num() > 0)
	{
		const FString ObjectPath = Task->ImportedObjectPaths[0];
		return LoadObject<UObject>(nullptr, *ObjectPath);
	}
#endif
	return nullptr;
}

static void BindMeshToEmitter(UNiagaraEmitter* Emitter, UStaticMesh* Mesh)
{
	if (!Emitter || !Mesh) return;
	const FName PossibleNames[] = { TEXT("RendererProperties"), TEXT("Renderers") };
	for (const FName& Name : PossibleNames)
	{
		FArrayProperty* ArrayProp = FindFProperty<FArrayProperty>(Emitter->GetClass(), Name);
		if (!ArrayProp) continue;
		FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(Emitter));
		FObjectPropertyBase* InnerObjProp = CastField<FObjectPropertyBase>(ArrayProp->Inner);
		if (!InnerObjProp) break;
		for (int32 i = 0; i < Helper.Num(); ++i)
		{
			void* ElemPtr = Helper.GetRawPtr(i);
			UObject* Obj = InnerObjProp->GetObjectPropertyValue(ElemPtr);
			if (UNiagaraMeshRendererProperties* MeshProp = Cast<UNiagaraMeshRendererProperties>(Obj))
			{
				if (MeshProp->Meshes.Num() == 0)
				{
					MeshProp->Meshes.AddDefaulted();
				}
				MeshProp->Meshes[0].Mesh = Mesh;
				MeshProp->Modify();
				return;
			}
		}
		break;
	}
}

bool FAssetBuildPipeline::BuildFromJsonSpec(const FString& JsonSpec, const FString& OutputRootPath, FAssetBuildResult& OutResult)
{
	OutResult = FAssetBuildResult();

	FEffectSpecV1 Spec;
	FString ParseError;
	if (!FEffectSpecParser::ParseFromJsonString(JsonSpec, Spec, ParseError))
	{
		OutResult.Errors.Add(ParseError);
		FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::Validate, TEXT("Spec JSON parse failed"));
		return false;
	}

	TArray<FEffectSpecValidationError> Errors;
	if (!FEffectSpecValidator::Validate(Spec, Errors))
	{
		OutResult.Errors.Add(FEffectSpecValidator::FormatErrors(Errors));
		FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::Validate, TEXT("Spec validation failed"));
		return false;
	}

	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Orchestrator, TEXT("Building assets from EffectSpec"));
	const FString SpecHash = FString::Printf(TEXT("%u"), FCrc::StrCrc32(*JsonSpec));
	if (GetSettingBool(TEXT("bDryRun"), false))
	{
		FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Orchestrator, TEXT("Dry-run enabled: no assets will be created"));
		OutResult.bSuccess = true;
		OutResult.SystemPath = TEXT("<dry-run>");
		return true;
	}

	FString OutputPath = FindFolderByHash(OutputRootPath, Spec.EffectName, SpecHash);
	if (OutputPath.IsEmpty())
	{
		OutputPath = CreateVersionedFolder(OutputRootPath, Spec.EffectName);
		WriteSpecHash(OutputPath, SpecHash);
	}
	else
	{
		FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Validate, TEXT("Spec hash matched; reusing output folder"));
	}
	UNiagaraSystem* System = FNiagaraSpecExecutor::CreateNiagaraSystemAsset(OutputPath, Spec.EffectName);
	if (!System)
	{
		OutResult.Errors.Add(TEXT("Failed to create Niagara system"));
		return false;
	}

	FModelRouter Router;
	Router.RegisterImageGen(TEXT("Local"), MakeShared<FLocalImageGenService>());
	Router.RegisterImageTo3D(TEXT("Local"), MakeShared<FLocalImageTo3DService>());
	Router.RegisterImageGen(TEXT("External"), MakeShared<FExternalImageGenService>());
	Router.RegisterImageTo3D(TEXT("External"), MakeShared<FExternalImageTo3DService>());
	const FString PreferredImageGen = GetSettingString(TEXT("PreferredImageGenProvider"), TEXT("Local"));
	const FString PreferredImageTo3D = GetSettingString(TEXT("PreferredImageTo3DProvider"), TEXT("Local"));
	TSharedPtr<IImageGenService> ImageGen = Router.PickImageGen(PreferredImageGen);
	TSharedPtr<IImageTo3DService> ImageTo3D = Router.PickImageTo3D(PreferredImageTo3D);
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Orchestrator,
		FString::Printf(TEXT("ImageGen Provider: %s"), *PreferredImageGen), PreferredImageGen);
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Orchestrator,
		FString::Printf(TEXT("ImageTo3D Provider: %s"), *PreferredImageTo3D), PreferredImageTo3D);
	if (!ImageGen.IsValid())
	{
		ImageGen = Router.PickImageGen(TEXT("Local"));
		FPipelineLog::Get().Push(EPipelineLogLevel::Warning, EPipelineStage::ImageGen, TEXT("Falling back to Local ImageGen"));
	}
	if (!ImageTo3D.IsValid())
	{
		ImageTo3D = Router.PickImageTo3D(TEXT("Local"));
		FPipelineLog::Get().Push(EPipelineLogLevel::Warning, EPipelineStage::ImageTo3D, TEXT("Falling back to Local ImageTo3D"));
	}

	for (int32 LayerIndex = 0; LayerIndex < Spec.Layers.Num(); ++LayerIndex)
	{
		const FLayerSpecV1& Layer = Spec.Layers[LayerIndex];
		FPipelineLogEntry Entry;
		Entry.Timestamp = FDateTime::UtcNow();
		Entry.Level = EPipelineLogLevel::Info;
		Entry.Stage = EPipelineStage::Niagara;
		Entry.Message = FString::Printf(TEXT("Building layer %d/%d (%s)"), LayerIndex + 1, Spec.Layers.Num(), *Layer.Name);
		Entry.CurrentStep = LayerIndex + 1;
		Entry.TotalSteps = Spec.Layers.Num();
		Entry.Percent = (float)(LayerIndex + 1) / (float)Spec.Layers.Num();
		FPipelineLog::Get().Push(Entry);

		FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara,
			FString::Printf(TEXT("Building layer '%s'"), *Layer.Name));

		TMap<FString, FString> ImportedTextures;

		// Import textures (if available on disk)
		for (const FTextureRequestV1& TexReq : Layer.TexturesNeeded)
		{
			const FString TexDir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("VFXAgent"), TEXT("GeneratedTextures"), Spec.EffectName, Layer.Name);
			IFileManager::Get().MakeDirectory(*TexDir, true);
			const FString TexFile = FPaths::Combine(TexDir, TexReq.Name + TEXT(".png"));
			if (!FPaths::FileExists(TexFile) && ImageGen.IsValid())
			{
				FTextureRequestV1 Req = TexReq;
				FModelServiceResult GenResult = ImageGen->GenerateTexture(Req);
				if (!GenResult.bSuccess)
				{
					FPipelineLog::Get().Push(EPipelineLogLevel::Warning, EPipelineStage::ImageGen, TEXT("Texture generation failed"));
				}
				else if (!GenResult.OutputPath.IsEmpty() && GenResult.OutputPath != TexFile)
				{
					IFileManager::Get().Copy(*TexFile, *GenResult.OutputPath);
				}
			}
			UObject* Imported = ImportAssetFromFile(TexFile, FPaths::Combine(OutputPath, TEXT("Textures")));
			if (Imported)
			{
				FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Import, FString::Printf(TEXT("Imported texture: %s"), *TexReq.Name));
				ImportedTextures.Add(TexReq.Name, Imported->GetPathName());
			}
			else
			{
				FPipelineLog::Get().Push(EPipelineLogLevel::Warning, EPipelineStage::Import, FString::Printf(TEXT("Texture missing: %s"), *TexReq.Name));
			}
		}

		FVFXEmitterSpec EmitterSpec;
		EmitterSpec.Name = Layer.Name;
		EmitterSpec.RendererType = ToRendererType(Layer.RendererType);
		EmitterSpec.Spawn.Rate = Layer.Spawn.Rate;
		EmitterSpec.Spawn.Burst = Layer.Spawn.BurstCount;
		EmitterSpec.Lifetime = Layer.Init.Lifetime;
		EmitterSpec.Size = (Layer.Init.SizeRange.X + Layer.Init.SizeRange.Y) * 0.5f;
		EmitterSpec.Velocity = Layer.Init.Velocity;
		EmitterSpec.Drag = Layer.Update.Drag;
		EmitterSpec.CurlNoiseStrength = Layer.Update.CurlNoiseStrength;

		const FString RoleLower = Layer.Role.ToLower();
		if (EmitterSpec.RendererType == EVFXRendererType::Ribbon || RoleLower.Contains(TEXT("trail")))
		{
			EmitterSpec.Alignment = TEXT("velocity");
			EmitterSpec.FacingMode = TEXT("camera");
			EmitterSpec.MotionStretch = 1.0f;
			EmitterSpec.bUseSizeOverLife = true;
			EmitterSpec.SizeEnd = FMath::Max(EmitterSpec.Size * 0.5f, 1.0f);
		}

		const FString Motion = Layer.Motion.Semantic.ToLower();
		if (Motion.Contains(TEXT("vortex")) || Motion.Contains(TEXT("orbit")))
		{
			EmitterSpec.VortexStrength = 25.0f;
			EmitterSpec.VortexAxis = FVector(0, 0, 1);
			FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara, TEXT("Applied vortex motion"));
		}
		if (Motion.Contains(TEXT("radial")))
		{
			EmitterSpec.Velocity = FVector(300, 0, 0);
			FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara, TEXT("Applied radial motion"));
		}
		if (Motion.Contains(TEXT("vertical")))
		{
			EmitterSpec.Velocity = FVector(0, 0, 400);
			FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara, TEXT("Applied vertical motion"));
		}
		if (Motion.Contains(TEXT("turbulent")))
		{
			EmitterSpec.CurlNoiseStrength = FMath::Max(EmitterSpec.CurlNoiseStrength, 20.0f);
			FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara, TEXT("Applied turbulence"));
		}

		if (!FNiagaraSpecExecutor::AddBasicEmitterToSystem(System, EmitterSpec.Name))
		{
			OutResult.Warnings.Add(FString::Printf(TEXT("Failed to add emitter: %s"), *EmitterSpec.Name));
			continue;
		}

		FNiagaraSpecExecutor::ConfigureEmitter(System, EmitterSpec.Name, EmitterSpec);

		UNiagaraEmitter* EmitterInstance = nullptr;
		for (FNiagaraEmitterHandle& H : System->GetEmitterHandles())
		{
			if (H.GetName() == FName(*EmitterSpec.Name))
			{
				EmitterInstance = H.GetInstance().Emitter;
				break;
			}
		}

		FMaterialSpecV1 MatSpec = Layer.Material;
		for (TPair<FString, FString>& Slot : MatSpec.TextureSlots)
		{
			if (ImportedTextures.Contains(Slot.Key))
			{
				Slot.Value = ImportedTextures[Slot.Key];
			}
			else if (ImportedTextures.Contains(Slot.Value))
			{
				Slot.Value = ImportedTextures[Slot.Value];
			}
		}

		UMaterialInterface* Mat = FMaterialCustomBuilder::BuildMaterialFromSpec(MatSpec, OutputPath, Layer.Name + TEXT("_Mat"), Spec.EffectName, Layer.Name);
		AssignMaterialToEmitter(EmitterInstance, Mat);

		// Import model if required and bind to mesh renderer
		if (Layer.RendererType.ToLower() == TEXT("mesh") && !Layer.ModelNeeded.Name.IsEmpty())
		{
			const FString Ext = Layer.ModelNeeded.Format.IsEmpty() ? TEXT("obj") : Layer.ModelNeeded.Format;
			const FString MeshDir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("VFXAgent"), TEXT("GeneratedMeshes"), Spec.EffectName, Layer.Name);
			IFileManager::Get().MakeDirectory(*MeshDir, true);
			const FString MeshFile = FPaths::Combine(MeshDir, Layer.ModelNeeded.Name + TEXT(".") + Ext);
			if (!FPaths::FileExists(MeshFile) && ImageTo3D.IsValid())
			{
				FModelRequestV1 Req = Layer.ModelNeeded;
				FModelServiceResult GenResult = ImageTo3D->GenerateModel(Req, FString());
				if (!GenResult.bSuccess)
				{
					FPipelineLog::Get().Push(EPipelineLogLevel::Warning, EPipelineStage::ImageTo3D, TEXT("Model generation failed"));
				}
				else if (!GenResult.OutputPath.IsEmpty() && GenResult.OutputPath != MeshFile)
				{
					IFileManager::Get().Copy(*MeshFile, *GenResult.OutputPath);
				}
			}
			UObject* ImportedMesh = ImportAssetFromFile(MeshFile, FPaths::Combine(OutputPath, TEXT("Meshes")));
			if (UStaticMesh* StaticMesh = Cast<UStaticMesh>(ImportedMesh))
			{
				BindMeshToEmitter(EmitterInstance, StaticMesh);
				FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Import, FString::Printf(TEXT("Imported mesh: %s"), *Layer.ModelNeeded.Name));
			}
			else
			{
				FPipelineLog::Get().Push(EPipelineLogLevel::Warning, EPipelineStage::Import, FString::Printf(TEXT("Mesh missing: %s"), *Layer.ModelNeeded.Name));
			}
		}
	}

	FVFXRepairReport Report;
	if (!FNiagaraSpecExecutor::SaveCompileAndSelfCheck(System, Report))
	{
		OutResult.Warnings.Append(Report.Errors);
	}

	OutResult.bSuccess = true;
	OutResult.SystemPath = System->GetPathName();
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara, TEXT("Build pipeline completed"));
	return true;
}
