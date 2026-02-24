#include "VFXAgentPythonBridge.h"
#include "MeshyModelServices.h"
#include "NiagaraSpecExecutor.h"
#include "VFXAgentLog.h"
#include "Misc/ConfigCacheIni.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Modules/ModuleManager.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "NiagaraRendererProperties.h"
#include "NiagaraSpriteRendererProperties.h"
#include "NiagaraRibbonRendererProperties.h"
#include "NiagaraMeshRendererProperties.h"
#include "Materials/MaterialInterface.h"
#include "Runtime/Launch/Resources/Version.h"
#include "AssetToolsModule.h"
#include "AssetImportTask.h"
#include "Engine/StaticMesh.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "IPythonScriptPlugin.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"

namespace
{
	FString GActiveSystemObjectPath;
	FString GPreferredMeshEmitterName;
	bool GLastMeshBindUsedPreferred = false;
	FString GCurrentRunId;

	FString BuildRunId()
	{
		const FString Timestamp = FDateTime::UtcNow().ToString(TEXT("%Y%m%d_%H%M%S"));
		const FString ShortGuid = FGuid::NewGuid().ToString(EGuidFormats::Digits).Left(8);
		return FString::Printf(TEXT("run_%s_%s"), *Timestamp, *ShortGuid);
	}

	FString EscapeForPythonSingleQuoted(const FString& Input)
	{
		FString Out = Input;
		Out = Out.Replace(TEXT("\\"), TEXT("\\\\"));
		Out = Out.Replace(TEXT("'"), TEXT("\\'"));
		Out = Out.Replace(TEXT("\r\n"), TEXT("\\n"));
		Out = Out.Replace(TEXT("\n"), TEXT("\\n"));
		Out = Out.Replace(TEXT("\r"), TEXT("\\n"));
		return Out;
	}

	void InvokePythonMeshCallback(
		const FString& CallbackName,
		const FString& TaskId,
		const FString& AssetPath,
		bool bSuccess,
		const FString& Error)
	{
		if (CallbackName.TrimStartAndEnd().IsEmpty())
		{
			return;
		}

		IPythonScriptPlugin* PythonPlugin = IPythonScriptPlugin::Get();
		if (!PythonPlugin || !PythonPlugin->IsPythonAvailable())
		{
			UE_LOG(LogVFXAgent, Warning, TEXT("VFXAgentPythonBridge::InvokePythonMeshCallback skipped (python unavailable)."));
			return;
		}

		const FString Script = FString::Printf(
			TEXT("import unreal\n")
			TEXT("try:\n")
			TEXT("    %s('%s', '%s', %s, '%s')\n")
			TEXT("except Exception as _cb_err:\n")
			TEXT("    unreal.log_error(f'VFXAgent async callback failed: {_cb_err}')\n"),
			*CallbackName,
			*EscapeForPythonSingleQuoted(TaskId),
			*EscapeForPythonSingleQuoted(AssetPath),
			bSuccess ? TEXT("True") : TEXT("False"),
			*EscapeForPythonSingleQuoted(Error));

		PythonPlugin->ExecPythonCommand(*Script);
	}

	UObject* ImportAssetFromFileForBridge(const FString& SourceFile, const FString& DestPath)
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
			return LoadObject<UObject>(nullptr, *Task->ImportedObjectPaths[0]);
		}
#endif
		return nullptr;
	}

	bool TryBindStaticMeshToEmitter(UNiagaraSystem* System, UStaticMesh* Mesh, const FString& PreferredEmitterName)
	{
		if (!System || !Mesh)
		{
			return false;
		}

		for (const FNiagaraEmitterHandle& Handle : System->GetEmitterHandles())
		{
			if (!PreferredEmitterName.IsEmpty() && !Handle.GetName().ToString().Equals(PreferredEmitterName, ESearchCase::IgnoreCase))
			{
				continue;
			}

			UNiagaraEmitter* Emitter = Handle.GetInstance().Emitter;
			if (!Emitter)
			{
				continue;
			}

			TArray<UNiagaraRendererProperties*> Renderers;
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5
			if (FVersionedNiagaraEmitterData* EmitterData = Emitter->GetLatestEmitterData())
			{
				Renderers = EmitterData->GetRenderers();
			}
#else
			Renderers = Emitter->GetRenderers();
#endif

			for (UNiagaraRendererProperties* Renderer : Renderers)
			{
				UNiagaraMeshRendererProperties* MeshRenderer = Cast<UNiagaraMeshRendererProperties>(Renderer);
				if (!MeshRenderer)
				{
					continue;
				}

				if (MeshRenderer->Meshes.Num() == 0)
				{
					MeshRenderer->Meshes.AddDefaulted();
				}

				MeshRenderer->Meshes[0].Mesh = Mesh;
				MeshRenderer->Modify();
				Emitter->Modify();
				Emitter->PostEditChange();
				return true;
			}
		}

		return false;
	}

	bool TryBindStaticMeshToExistingRenderer(UNiagaraSystem* System, UStaticMesh* Mesh)
	{
		GLastMeshBindUsedPreferred = false;

		if (!GPreferredMeshEmitterName.IsEmpty())
		{
			if (TryBindStaticMeshToEmitter(System, Mesh, GPreferredMeshEmitterName))
			{
				GLastMeshBindUsedPreferred = true;
				UE_LOG(LogVFXAgent, Log,
					TEXT("VFXAgentPythonBridge::Mesh binding prioritized latest emitter '%s'"),
					*GPreferredMeshEmitterName);
				return true;
			}
		}

		return TryBindStaticMeshToEmitter(System, Mesh, FString());
	}

	FString MakeUniqueEmitterName(UNiagaraSystem* System, const FString& BaseName)
	{
		if (!System)
		{
			return BaseName;
		}

		TSet<FString> ExistingNames;
		for (const FNiagaraEmitterHandle& Handle : System->GetEmitterHandles())
		{
			ExistingNames.Add(Handle.GetName().ToString());
		}

		if (!ExistingNames.Contains(BaseName))
		{
			return BaseName;
		}

		for (int32 Index = 1; Index <= 999; ++Index)
		{
			const FString Candidate = FString::Printf(TEXT("%s_%03d"), *BaseName, Index);
			if (!ExistingNames.Contains(Candidate))
			{
				return Candidate;
			}
		}

		return BaseName + TEXT("_Auto");
	}

	bool BindStaticMeshToSystem(UNiagaraSystem* System, UStaticMesh* Mesh)
	{
		if (TryBindStaticMeshToExistingRenderer(System, Mesh))
		{
			return true;
		}

		if (!System)
		{
			return false;
		}

		const FString EmitterName = MakeUniqueEmitterName(System, TEXT("AutoMeshEmitter"));
		const FString MeshTemplatePath = TEXT("/Niagara/DefaultAssets/Templates/Emitters/UpwardMeshBurst.UpwardMeshBurst");
		const bool bCreated = FNiagaraSpecExecutor::AddEmitterFromTemplate(System, MeshTemplatePath, EmitterName)
			|| FNiagaraSpecExecutor::AddBasicEmitterToSystem(System, EmitterName);

		if (!bCreated)
		{
			UE_LOG(LogVFXAgent, Warning,
				TEXT("VFXAgentPythonBridge::BindStaticMeshToSystem fallback failed to create emitter for mesh binding."));
			return false;
		}

		if (TryBindStaticMeshToExistingRenderer(System, Mesh))
		{
			GPreferredMeshEmitterName = EmitterName;
			UE_LOG(LogVFXAgent, Log,
				TEXT("VFXAgentPythonBridge::BindStaticMeshToSystem created fallback emitter '%s' and bound mesh."),
				*EmitterName);
			return true;
		}

		UE_LOG(LogVFXAgent, Warning,
			TEXT("VFXAgentPythonBridge::BindStaticMeshToSystem created fallback emitter '%s' but no mesh renderer was found."),
			*EmitterName);
		return false;
	}
}

static FString NormalizeObjectPath(const FString& InPath)
{
	FString Path = InPath;
	Path.TrimStartAndEndInline();
	if (Path.IsEmpty())
	{
		return Path;
	}
	if (!Path.Contains(TEXT(".")))
	{
		const FString Name = FPaths::GetCleanFilename(Path);
		if (!Name.IsEmpty())
		{
			Path = FString::Printf(TEXT("%s.%s"), *Path, *Name);
		}
	}
	return Path;
}

static UNiagaraSystem* LoadSystemByPath(const FString& SystemObjectPath)
{
	const FString Normalized = NormalizeObjectPath(SystemObjectPath);
	if (Normalized.IsEmpty())
	{
		return nullptr;
	}
	return LoadObject<UNiagaraSystem>(nullptr, *Normalized);
}

static FString ResolveEmitterTemplatePath(const FString& TemplateName)
{
	FString Name = TemplateName;
	Name.TrimStartAndEndInline();
	if (Name.IsEmpty())
	{
		return TEXT("/Niagara/DefaultAssets/Templates/Emitters/Fountain.Fountain");
	}
	if (Name.Contains(TEXT("/")))
	{
		return NormalizeObjectPath(Name);
	}

	if (Name.Equals(TEXT("Fountain"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/Fountain.Fountain");
	if (Name.Equals(TEXT("Minimal"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/Minimal.Minimal");
	if (Name.Equals(TEXT("DirectionalBurst"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/DirectionalBurst.DirectionalBurst");
	if (Name.Equals(TEXT("SimpleSpriteBurst"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/SimpleSpriteBurst.SimpleSpriteBurst");

	return FString::Printf(TEXT("/Niagara/DefaultAssets/Templates/Emitters/%s.%s"), *Name, *Name);
}

static FString ReadConfigValue(const TCHAR* Section, const TCHAR* Key)
{
	FString Value;
	const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
	for (const FString& File : ConfigFiles)
	{
		if (GConfig && GConfig->GetString(Section, Key, Value, File))
		{
			Value.TrimStartAndEndInline();
			if (!Value.IsEmpty())
			{
				return Value;
			}
		}
	}
	return FString();
}

bool UVFXAgentPythonBridge::PrepareEditorContext(const FString& RootPath)
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	AssetRegistryModule.Get().SearchAllAssets(true);

	TArray<FString> Paths;
	Paths.Add(TEXT("/Niagara"));
	Paths.Add(TEXT("/Engine"));
	if (!RootPath.IsEmpty())
	{
		Paths.Add(RootPath);
	}

	AssetRegistryModule.Get().ScanPathsSynchronous(Paths, true, false);
	UE_LOG(LogVFXAgent, Log, TEXT("VFXAgentPythonBridge::PrepareEditorContext scanned %d paths."), Paths.Num());
	return true;
}

FString UVFXAgentPythonBridge::CreateSystem(const FString& TargetPath, const FString& SystemName)
{
	PrepareEditorContext(TargetPath);
	UNiagaraSystem* System = FNiagaraSpecExecutor::CreateNiagaraSystemAsset(TargetPath, SystemName);
	if (!System)
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("VFXAgentPythonBridge::CreateSystem failed. TargetPath=%s SystemName=%s"), *TargetPath, *SystemName);
		return FString();
	}
	GActiveSystemObjectPath = System->GetPathName();
	GPreferredMeshEmitterName.Reset();
	GLastMeshBindUsedPreferred = false;
	GCurrentRunId = BuildRunId();
	return System->GetPathName();
}

bool UVFXAgentPythonBridge::SetActiveSystemContext(const FString& SystemObjectPath)
{
	const FString Normalized = NormalizeObjectPath(SystemObjectPath);
	UNiagaraSystem* System = LoadSystemByPath(Normalized);
	if (!System)
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("VFXAgentPythonBridge::SetActiveSystemContext failed. System not found: %s"), *SystemObjectPath);
		return false;
	}

	GActiveSystemObjectPath = Normalized;
	GPreferredMeshEmitterName.Reset();
	GLastMeshBindUsedPreferred = false;
	GCurrentRunId = BuildRunId();
	return true;
}

bool UVFXAgentPythonBridge::CreateEmitter(const FString& SystemObjectPath, const FString& TemplateName, const FString& EmitterName)
{
	UNiagaraSystem* System = LoadSystemByPath(SystemObjectPath);
	if (!System)
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("VFXAgentPythonBridge::CreateEmitter failed. System not found: %s"), *SystemObjectPath);
		return false;
	}

	const FString TemplatePath = ResolveEmitterTemplatePath(TemplateName);
	if (FNiagaraSpecExecutor::AddEmitterFromTemplate(System, TemplatePath, EmitterName))
	{
		GPreferredMeshEmitterName = EmitterName;
		GLastMeshBindUsedPreferred = false;
		return true;
	}

	UE_LOG(LogVFXAgent, Warning,
		TEXT("VFXAgentPythonBridge::CreateEmitter template add failed. Falling back to basic emitter. Template=%s"),
		*TemplatePath);
	const bool bAdded = FNiagaraSpecExecutor::AddBasicEmitterToSystem(System, EmitterName);
	if (bAdded)
	{
		GPreferredMeshEmitterName = EmitterName;
		GLastMeshBindUsedPreferred = false;
	}
	return bAdded;
}

bool UVFXAgentPythonBridge::BindEmitterMaterial(const FString& SystemObjectPath, const FString& EmitterName, const FString& MaterialObjectPath)
{
	UNiagaraSystem* System = LoadSystemByPath(SystemObjectPath);
	if (!System)
	{
		return false;
	}

	UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, *NormalizeObjectPath(MaterialObjectPath));
	if (!Material)
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("VFXAgentPythonBridge::BindEmitterMaterial material not found: %s"), *MaterialObjectPath);
		return false;
	}

	bool bApplied = false;
	for (const FNiagaraEmitterHandle& Handle : System->GetEmitterHandles())
	{
		if (!Handle.GetName().ToString().Equals(EmitterName, ESearchCase::IgnoreCase))
		{
			continue;
		}

		UNiagaraEmitter* Emitter = Handle.GetInstance().Emitter;
		if (!Emitter)
		{
			continue;
		}

		TArray<UNiagaraRendererProperties*> Renderers;
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5
		if (FVersionedNiagaraEmitterData* EmitterData = Emitter->GetLatestEmitterData())
		{
			Renderers = EmitterData->GetRenderers();
		}
#else
		Renderers = Emitter->GetRenderers();
#endif

		for (UNiagaraRendererProperties* Prop : Renderers)
		{
			if (UNiagaraSpriteRendererProperties* Sprite = Cast<UNiagaraSpriteRendererProperties>(Prop))
			{
				Sprite->Material = Material;
				bApplied = true;
			}
			else if (UNiagaraRibbonRendererProperties* Ribbon = Cast<UNiagaraRibbonRendererProperties>(Prop))
			{
				Ribbon->Material = Material;
				bApplied = true;
			}
		}

		Emitter->Modify();
		Emitter->PostEditChange();
	}

	return bApplied;
}

int32 UVFXAgentPythonBridge::GetEmitterCount(const FString& SystemObjectPath)
{
	if (UNiagaraSystem* System = LoadSystemByPath(SystemObjectPath))
	{
		return System->GetEmitterHandles().Num();
	}
	return -1;
}

bool UVFXAgentPythonBridge::SaveCompile(const FString& SystemObjectPath, FString& OutReport)
{
	OutReport.Empty();
	UNiagaraSystem* System = LoadSystemByPath(SystemObjectPath);
	if (!System)
	{
		OutReport = TEXT("System not found");
		return false;
	}

	FVFXRepairReport Report;
	const bool bOk = FNiagaraSpecExecutor::SaveCompileAndSelfCheck(System, Report);
	OutReport = FString::Printf(TEXT("path=%s errors=%d warnings=%d"), *Report.SystemPath, Report.Errors.Num(), Report.Warnings.Num());
	if (!bOk)
	{
		for (const FString& Err : Report.Errors)
		{
			OutReport += TEXT(" | ") + Err;
		}
	}
	return bOk;
}

bool UVFXAgentPythonBridge::SaveCompileSimple(const FString& SystemObjectPath)
{
	FString Report;
	return SaveCompile(SystemObjectPath, Report);
}

FString UVFXAgentPythonBridge::GenerateMesh(const FString& Prompt, const FString& Format)
{
	FModelRequestV1 Request;
	Request.Name = Prompt.IsEmpty() ? TEXT("GeneratedMesh") : Prompt;
	Request.Format = Format.IsEmpty() ? TEXT("glb") : Format;

	FMeshyImageTo3DService Service;
	const FModelServiceResult Result = Service.GenerateModel(Request, FString());
	if (!Result.bSuccess)
	{
		UE_LOG(LogVFXAgent, Warning,
			TEXT("VFXAgentPythonBridge::GenerateMesh failed. Prompt=%s Error=%s"),
			*Prompt,
			*Result.Error);
		return FString();
	}

	FString ReturnPath = Result.OutputPath;

	if (!Result.OutputPath.IsEmpty() && !GActiveSystemObjectPath.IsEmpty())
	{
		UNiagaraSystem* TargetSystem = LoadSystemByPath(GActiveSystemObjectPath);
		if (TargetSystem)
		{
			const FString MeshDestPath = TEXT("/Game/VFXAgent/Generated/Meshes");
			if (UObject* Imported = ImportAssetFromFileForBridge(Result.OutputPath, MeshDestPath))
			{
				if (UStaticMesh* StaticMesh = Cast<UStaticMesh>(Imported))
				{
					if (BindStaticMeshToSystem(TargetSystem, StaticMesh))
					{
						ReturnPath = StaticMesh->GetPathName();
						UE_LOG(LogVFXAgent, Log,
							TEXT("VFXAgentPythonBridge::GenerateMesh attached mesh '%s' to system '%s' preferred_emitter='%s' prioritized_bind=%s"),
							*ReturnPath,
							*GActiveSystemObjectPath,
							*GPreferredMeshEmitterName,
							GLastMeshBindUsedPreferred ? TEXT("true") : TEXT("false"));
					}
				}
			}
		}
	}

	if (!Result.OutputPath.IsEmpty())
	{
		return ReturnPath;
	}
	return Result.Summary;
}

FString UVFXAgentPythonBridge::GenerateMeshAsync(
	const FString& Prompt,
	const FString& Format,
	const FString& OnReadyPythonCallback)
{
	FModelRequestV1 Request;
	Request.Name = Prompt.IsEmpty() ? TEXT("GeneratedMesh") : Prompt;
	Request.Format = Format.IsEmpty() ? TEXT("glb") : Format;

	const FString SystemContextPath = GActiveSystemObjectPath;
	const FString CallbackName = OnReadyPythonCallback;
	if (GCurrentRunId.IsEmpty())
	{
		GCurrentRunId = BuildRunId();
	}
    const FString RunId = GCurrentRunId;

	FString TaskId;
	FString Error;
	const bool bStarted = FMeshyImageTo3DService::StartGenerateModelAsync(
		Request,
		FString(),
		FOnMeshyTaskFinished::CreateLambda(
			[SystemContextPath, CallbackName](const FMeshyAsyncTaskSnapshot& Snapshot)
			{
				FString FinalAssetPath = Snapshot.Result.OutputPath;

				if (Snapshot.bSucceeded && !Snapshot.Result.OutputPath.IsEmpty() && !SystemContextPath.IsEmpty())
				{
					UNiagaraSystem* TargetSystem = LoadSystemByPath(SystemContextPath);
					if (TargetSystem)
					{
						const FString MeshDestPath = TEXT("/Game/VFXAgent/Generated/Meshes");
						if (UObject* Imported = ImportAssetFromFileForBridge(Snapshot.Result.OutputPath, MeshDestPath))
						{
							if (UStaticMesh* StaticMesh = Cast<UStaticMesh>(Imported))
							{
								if (BindStaticMeshToSystem(TargetSystem, StaticMesh))
								{
									FinalAssetPath = StaticMesh->GetPathName();
								}
							}
						}
					}
				}

				InvokePythonMeshCallback(
					CallbackName,
					Snapshot.TaskId,
					FinalAssetPath,
					Snapshot.bSucceeded,
					Snapshot.Error);
			}),
		TaskId,
		Error,
		RunId);

	if (!bStarted)
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("VFXAgentPythonBridge::GenerateMeshAsync failed: %s"), *Error);
		return FString();
	}

	UE_LOG(LogVFXAgent, Log,
		TEXT("VFXAgentPythonBridge::GenerateMeshAsync started task_id=%s callback=%s"),
		*TaskId,
		*CallbackName);
	return TaskId;
}

FString UVFXAgentPythonBridge::GetMeshTaskStatus(const FString& TaskId)
{
	FMeshyAsyncTaskSnapshot Snapshot;
	if (!FMeshyImageTo3DService::QueryTask(TaskId, Snapshot))
	{
		return TEXT("{\"found\":false}");
	}

	TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
	Root->SetBoolField(TEXT("found"), true);
	Root->SetStringField(TEXT("run_id"), Snapshot.RunId);
	Root->SetStringField(TEXT("task_id"), Snapshot.TaskId);
	Root->SetStringField(TEXT("status"), Snapshot.Status);
	Root->SetBoolField(TEXT("completed"), Snapshot.bCompleted);
	Root->SetBoolField(TEXT("succeeded"), Snapshot.bSucceeded);
	Root->SetStringField(TEXT("output_path"), Snapshot.Result.OutputPath);
	Root->SetStringField(TEXT("error"), Snapshot.Error);

	FString Json;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Json);
	FJsonSerializer::Serialize(Root.ToSharedRef(), Writer);
	return Json;
}

FString UVFXAgentPythonBridge::GetMeshyEndpoint()
{
	const FString Endpoint = ReadConfigValue(TEXT("VFXAgent"), TEXT("MeshyEndpoint"));
	return Endpoint.IsEmpty() ? TEXT("https://api.meshy.ai/v1") : Endpoint;
}
