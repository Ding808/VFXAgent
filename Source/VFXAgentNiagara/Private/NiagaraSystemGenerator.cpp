#include "NiagaraSystemGenerator.h"
#include "NiagaraSpecExecutor.h"
#include "VFXRecipeCompiler.h"
#include "VFXPythonExecutor.h"
#include "HttpLLMProvider.h"
#include "VFXAgentPromptDefaults.h"
#include "VFXAgentLog.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "NiagaraRendererProperties.h"
#include "NiagaraSpriteRendererProperties.h"
#include "NiagaraRibbonRendererProperties.h"
#include "Materials/MaterialInterface.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceConstant.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Modules/ModuleManager.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/Paths.h"
#include "Misc/PackageName.h"
#include "UObject/UnrealType.h"
#include "ScopedTransaction.h"
#include "HttpModule.h"
#include "HttpManager.h"
#include "JsonObjectConverter.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "Runtime/Launch/Resources/Version.h"

#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5
#include "NiagaraEmitter.h"
#endif

static FString SanitizeGeneratedName(const FString& SourceString, const FString& Fallback)
{
    FString Sanitized = SourceString;
    Sanitized = Sanitized.Replace(TEXT(" "), TEXT("_"));

    FString Clean;
    Clean.Reserve(Sanitized.Len());
    for (const TCHAR Ch : Sanitized)
    {
        if (FChar::IsAlnum(Ch) || Ch == TEXT('_'))
        {
            Clean.AppendChar(Ch);
        }
        else
        {
            Clean.AppendChar(TEXT('_'));
        }
    }

    while (Clean.Contains(TEXT("__")))
    {
        Clean = Clean.Replace(TEXT("__"), TEXT("_"));
    }

    Clean.TrimStartAndEndInline();
    if (Clean.IsEmpty())
    {
        return Fallback;
    }
    return Clean;
}

static FString NormalizeOutputAssetPath(const FString& InputPath)
{
    FString Output = InputPath;
    Output.TrimStartAndEndInline();

    if (Output.IsEmpty())
    {
        Output = TEXT("/Game/VFXAgent/Generated");
    }

    if (!Output.StartsWith(TEXT("/Game")))
    {
        Output = FString::Printf(TEXT("/Game/%s"), *Output);
    }

    while (Output.EndsWith(TEXT("/")))
    {
        Output.LeftChopInline(1, EAllowShrinking::No);
    }

    return Output;
}

static FString BuildSystemObjectPath(const FString& OutputPath, const FString& SystemName)
{
    const FString PackagePath = OutputPath / SystemName;
    return FString::Printf(TEXT("%s.%s"), *PackagePath, *SystemName);
}

static bool DoesNiagaraSystemAssetExist(const FString& OutputPath, const FString& SystemName)
{
    const FString ObjPath = BuildSystemObjectPath(OutputPath, SystemName);
    return LoadObject<UNiagaraSystem>(nullptr, *ObjPath) != nullptr;
}

static FString ResolveUniqueSystemName(const FString& OutputPath, const FString& RequestedName)
{
    if (!DoesNiagaraSystemAssetExist(OutputPath, RequestedName))
    {
        return RequestedName;
    }

    for (int32 Index = 1; Index <= 999; ++Index)
    {
        const FString Candidate = FString::Printf(TEXT("%s_%03d"), *RequestedName, Index);
        if (!DoesNiagaraSystemAssetExist(OutputPath, Candidate))
        {
            UE_LOG(LogVFXAgent, Warning,
                TEXT("Target Niagara system already exists. Auto-resolved name: %s -> %s"),
                *RequestedName, *Candidate);
            return Candidate;
        }
    }

    return FString::Printf(TEXT("%s_%lld"), *RequestedName, static_cast<long long>(FDateTime::UtcNow().ToUnixTimestamp()));
}

static FString EscapeForPythonString(const FString& Input)
{
    FString Out = Input;
    Out = Out.Replace(TEXT("\\"), TEXT("\\\\"));
    Out = Out.Replace(TEXT("'"), TEXT("\\'"));
    return Out;
}

static bool TryGetVFXAgentSettingString(const TCHAR* Key, FString& OutValue)
{
    const TCHAR* Section = TEXT("/Script/VFXAgentEditor.VFXAgentSettings");
    const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
    for (const FString& File : ConfigFiles)
    {
        if (GConfig && GConfig->GetString(Section, Key, OutValue, File))
        {
            return true;
        }
    }

    FString VFXAgentIni;
    if (FConfigCacheIni::LoadGlobalIniFile(VFXAgentIni, TEXT("VFXAgent"), nullptr, true, true))
    {
        if (GConfig && GConfig->GetString(Section, Key, OutValue, VFXAgentIni))
        {
            return true;
        }
    }

    const FString DefaultVFXAgentIni = FPaths::Combine(FPaths::ProjectConfigDir(), TEXT("DefaultVFXAgent.ini"));
    if (GConfig && GConfig->GetString(Section, Key, OutValue, DefaultVFXAgentIni))
    {
        return true;
    }

    return false;
}

static bool TryGetVFXAgentSettingFloat(const TCHAR* Key, float& OutValue)
{
    const TCHAR* Section = TEXT("/Script/VFXAgentEditor.VFXAgentSettings");
    const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
    for (const FString& File : ConfigFiles)
    {
        if (GConfig && GConfig->GetFloat(Section, Key, OutValue, File))
        {
            return true;
        }
    }

    FString VFXAgentIni;
    if (FConfigCacheIni::LoadGlobalIniFile(VFXAgentIni, TEXT("VFXAgent"), nullptr, true, true))
    {
        if (GConfig && GConfig->GetFloat(Section, Key, OutValue, VFXAgentIni))
        {
            return true;
        }
    }

    const FString DefaultVFXAgentIni = FPaths::Combine(FPaths::ProjectConfigDir(), TEXT("DefaultVFXAgent.ini"));
    if (GConfig && GConfig->GetFloat(Section, Key, OutValue, DefaultVFXAgentIni))
    {
        return true;
    }

    return false;
}

static bool TryGetVFXAgentSettingBool(const TCHAR* Key, bool& OutValue)
{
    const TCHAR* Section = TEXT("/Script/VFXAgentEditor.VFXAgentSettings");
    const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
    for (const FString& File : ConfigFiles)
    {
        if (GConfig && GConfig->GetBool(Section, Key, OutValue, File))
        {
            return true;
        }
    }
    return false;
}

static void ForceScanAssetPaths(const FString& OutputPath)
{
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    TArray<FString> PathsToScan;
    PathsToScan.Add(TEXT("/Niagara"));
    PathsToScan.Add(TEXT("/Engine"));
    if (!OutputPath.IsEmpty())
    {
        PathsToScan.Add(OutputPath);
    }

    AssetRegistryModule.Get().SearchAllAssets(true);
    AssetRegistryModule.Get().ScanPathsSynchronous(PathsToScan, true, false);
}

static EVFXAgentLLMBackend ParseBackend(const FString& BackendString)
{
    const FString Lower = BackendString.ToLower();
    if (Lower.Contains(TEXT("ollama")))
    {
        return EVFXAgentLLMBackend::OllamaGenerate;
    }
    if (Lower.Contains(TEXT("responses")))
    {
        return EVFXAgentLLMBackend::OpenAIResponses;
    }
    return EVFXAgentLLMBackend::OpenAIChatCompletions;
}

static bool RequestPythonScriptBlocking(UHttpLLMProvider* Provider, const FString& Prompt, float TimeoutSeconds, FString& OutScript, FString& OutError)
{
    if (!Provider)
    {
        OutError = TEXT("LLM provider is null.");
        return false;
    }

    bool bDone = false;
    bool bSuccess = false;
    FString Script;
    FString Error;

    Provider->RequestPythonScriptAsync(Prompt,
        [&bDone, &bSuccess, &Script, &Error](bool bInSuccess, const FString& InScript, const FString& InError)
        {
            bSuccess = bInSuccess;
            Script = InScript;
            Error = InError;
            bDone = true;
        });

    const double StartTime = FPlatformTime::Seconds();
    const double EffectiveTimeout = FMath::Max(5.0, static_cast<double>(TimeoutSeconds));
    while (!bDone)
    {
        if ((FPlatformTime::Seconds() - StartTime) > EffectiveTimeout)
        {
            OutError = FString::Printf(TEXT("RequestPythonScriptAsync timed out after %.1f seconds."), TimeoutSeconds);
            return false;
        }

        if (IsInGameThread())
        {
            FHttpModule::Get().GetHttpManager().Tick(0.01f);
        }
        FPlatformProcess::Sleep(0.01f);
    }

    OutScript = Script;
    OutError = Error;
    return bSuccess;
}

static FString BuildPythonGenerationPrompt(
    const FString& UserSystemName,
    const FString& OutputPath,
    const FString& TemplateSystemPath,
    const FVFXRecipe& Recipe,
    const FVFXEffectSpec& CompiledSpec)
{
    FString RecipeJson;
    FJsonObjectConverter::UStructToJsonObjectString(Recipe, RecipeJson);

    FString SpecJson;
    FJsonObjectConverter::UStructToJsonObjectString(CompiledSpec, SpecJson);

    return FString::Printf(
        TEXT("Generate a UE5.5 Niagara Python script for this VFX.\\n")
        TEXT("IMPORTANT: The runtime will inject Python globals target_path, system_name, system_object_path.\\n")
        TEXT("You MUST use these globals when creating/saving the Niagara system asset.\\n")
        TEXT("Prefer bridge commands over raw low-level operations:\\n")
        TEXT("- unreal.VFXAgentPythonBridge.prepare_editor_context(path)\\n")
        TEXT("- unreal.VFXAgentPythonBridge.create_system(target_path, system_name)\\n")
        TEXT("- unreal.VFXAgentPythonBridge.create_emitter(system_object_path, template_name, emitter_name)\\n")
        TEXT("- unreal.VFXAgentPythonBridge.bind_emitter_material(system_object_path, emitter_name, material_path)\\n")
        TEXT("- unreal.VFXAgentPythonBridge.save_compile_simple(system_object_path)\\n")
        TEXT("- unreal.VFXAgentPythonBridge.generate_mesh_async(prompt, format, callback_name) for non-blocking mesh jobs\\n")
        TEXT("  callback_name must resolve to: def callback(payload), where payload has run_id/task_id/status/asset_path/error/elapsed\\n")
        TEXT("  minimal example: def on_mesh_ready(payload): unreal.log(str(payload.get('status', '')))\\n")
        TEXT("  task_id = unreal.VFXAgentPythonBridge.generate_mesh_async('%s', 'glb', 'on_mesh_ready')\\n")
        TEXT("- unreal.VFXAgentPythonBridge.get_mesh_task_status(task_id) for polling status\\n")
        TEXT("You MUST create/assign materials INSIDE this Python script (do not rely on C++ post-fix material assignment).\\n")
        TEXT("When NiagaraEditorSubsystem is available, add emitters and bind materials in script in one flow.\\n")
        TEXT("Do not hard-code a different output folder or system name.\\n\\n")
        TEXT("Target system name: %s\\n")
        TEXT("Target output folder: %s\\n")
        TEXT("Optional template path: %s\\n\\n")
        TEXT("Recipe JSON:\\n%s\\n\\n")
        TEXT("Compiled Spec JSON:\\n%s\\n"),
        VFXAgentPromptDefaults::MeshAsyncExamplePrompt,
        *UserSystemName,
        *OutputPath,
        *TemplateSystemPath,
        *RecipeJson,
        *SpecJson);
}

static FString BuildPythonRepairPayloadJson(
    const FString& SystemName,
    const FString& OutputPath,
    const FString& SystemObjectPath,
    const FString& PreviousScript,
    const FString& Traceback)
{
    TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetStringField(TEXT("system_name"), SystemName);
    Root->SetStringField(TEXT("output_path"), OutputPath);
    Root->SetStringField(TEXT("system_object_path"), SystemObjectPath);
    Root->SetStringField(TEXT("python_traceback"), Traceback);
    Root->SetStringField(TEXT("previous_script"), PreviousScript);

    FString JsonText;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonText);
    FJsonSerializer::Serialize(Root.ToSharedRef(), Writer);
    return JsonText;
}

static FString BuildPythonRepairPrompt(
    const FString& UserSystemName,
    const FString& OutputPath,
    const FString& SystemObjectPath,
    const FString& PreviousScript,
    const FString& Traceback)
{
    const FString Payload = BuildPythonRepairPayloadJson(UserSystemName, OutputPath, SystemObjectPath, PreviousScript, Traceback);
    return FString::Printf(
        TEXT("Repair the Unreal Engine 5.5 Python script based on this execution failure report.\\n")
        TEXT("Return ONLY raw Python code (no markdown).\\n")
        TEXT("Use runtime globals: target_path, system_name, system_object_path.\\n")
        TEXT("Do not call duplicate_asset/create_asset blindly if assets already exist; load existing assets when possible.\\n")
        TEXT("Failure report JSON:\\n%s\\n"),
        *Payload);
}

static UNiagaraSystem* TryLoadGeneratedSystem(const FString& SystemObjectPath, const FString& OutputPath, const FString& SystemName)
{
    if (UNiagaraSystem* Loaded = LoadObject<UNiagaraSystem>(nullptr, *SystemObjectPath))
    {
        return Loaded;
    }

    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    FARFilter Filter;
    Filter.PackagePaths.Add(*OutputPath);
    Filter.ClassPaths.Add(UNiagaraSystem::StaticClass()->GetClassPathName());
    Filter.bRecursivePaths = false;

    TArray<FAssetData> Assets;
    AssetRegistryModule.Get().GetAssets(Filter, Assets);
    for (const FAssetData& Asset : Assets)
    {
        if (Asset.AssetName.ToString().Equals(SystemName, ESearchCase::CaseSensitive))
        {
            return Cast<UNiagaraSystem>(Asset.GetAsset());
        }
    }

    return nullptr;
}

static bool TryAttachExistingEmitterAsset(UNiagaraSystem* System, const FString& OutputPath)
{
    UE_LOG(LogVFXAgent, Warning, TEXT("TryAttachExistingEmitterAsset is disabled for safety in this environment (path=%s)."), *OutputPath);
    return false;
}

static FString StripEditorOpenCalls(const FString& InScript)
{
    FString OutScript = InScript;
    OutScript.ReplaceInline(
        TEXT("unreal.get_editor_subsystem(unreal.AssetEditorSubsystem).open_editor_for_assets([system])"),
        TEXT("pass"),
        ESearchCase::CaseSensitive);
    return OutScript;
}

static FString BuildTemplateFallbackPythonScript(const FString& OutputPath, const FString& SystemName)
{
    const FString EscapedOutputPath = EscapeForPythonString(OutputPath);
    const FString EscapedSystemName = EscapeForPythonString(SystemName);

    return FString::Printf(
        TEXT("import unreal\n")
        TEXT("target_path = '%s'\n")
        TEXT("system_name = '%s'\n")
        TEXT("system_path = f'{target_path}/{system_name}'\n")
        TEXT("def get_emitter_count(sys_obj):\n")
        TEXT("    if sys_obj is None:\n")
        TEXT("        return -1\n")
        TEXT("    try:\n")
        TEXT("        return len(list(sys_obj.get_editor_property('emitter_handles') or []))\n")
        TEXT("    except Exception:\n")
        TEXT("        pass\n")
        TEXT("    try:\n")
        TEXT("        if hasattr(sys_obj, 'get_emitter_handles'):\n")
        TEXT("            return len(list(sys_obj.get_emitter_handles() or []))\n")
        TEXT("    except Exception:\n")
        TEXT("        pass\n")
        TEXT("    return -1\n")
        TEXT("\n")
        TEXT("def class_name_of(asset_data):\n")
        TEXT("    try:\n")
        TEXT("        return str(asset_data.asset_class_path.asset_name)\n")
        TEXT("    except Exception:\n")
        TEXT("        return str(getattr(asset_data, 'asset_class', ''))\n")
        TEXT("\n")
        TEXT("def pick_if_non_empty(path):\n")
        TEXT("    try:\n")
        TEXT("        if not unreal.EditorAssetLibrary.does_asset_exist(path):\n")
        TEXT("            return None\n")
        TEXT("        loaded = unreal.EditorAssetLibrary.load_asset(path)\n")
        TEXT("        if loaded is None:\n")
        TEXT("            return None\n")
        TEXT("        if get_emitter_count(loaded) > 0:\n")
        TEXT("            return path\n")
        TEXT("    except Exception:\n")
        TEXT("        pass\n")
        TEXT("    return None\n")
        TEXT("\n")
        TEXT("template_path = None\n")
        TEXT("candidate_paths = [\n")
        TEXT("    '/Niagara/DefaultAssets/Templates/Systems/NS_Fountain.NS_Fountain',\n")
        TEXT("    '/Niagara/DefaultAssets/Templates/System/NS_Fountain.NS_Fountain',\n")
        TEXT("    '/Niagara/DefaultAssets/Templates/Systems/NS_Template.NS_Template',\n")
        TEXT("    '/Niagara/DefaultAssets/Templates/System/NS_Template.NS_Template',\n")
        TEXT("    '/Niagara/DefaultAssets/Templates/Systems/NS_Minimal.NS_Minimal',\n")
        TEXT("    '/Niagara/DefaultAssets/Templates/System/NS_Minimal.NS_Minimal',\n")
        TEXT("]\n")
        TEXT("for p in candidate_paths:\n")
        TEXT("    chosen = pick_if_non_empty(p)\n")
        TEXT("    if chosen:\n")
        TEXT("        template_path = chosen\n")
        TEXT("        break\n")
        TEXT("\n")
        TEXT("if template_path is None:\n")
        TEXT("    try:\n")
        TEXT("        ar = unreal.AssetRegistryHelpers.get_asset_registry()\n")
        TEXT("        try:\n")
        TEXT("            ar.search_all_assets(True)\n")
        TEXT("        except Exception:\n")
        TEXT("            pass\n")
        TEXT("        try:\n")
        TEXT("            ar.scan_paths_synchronous(['/Niagara', '/Engine'], True, False)\n")
        TEXT("        except Exception:\n")
        TEXT("            pass\n")
        TEXT("\n")
        TEXT("        for base in ['/Niagara/DefaultAssets/Templates/Systems', '/Niagara/DefaultAssets/Templates/System', '/Niagara/DefaultAssets/Templates', '/Niagara']:\n")
        TEXT("            try:\n")
        TEXT("                assets = ar.get_assets_by_path(base, recursive=True)\n")
        TEXT("            except Exception:\n")
        TEXT("                assets = []\n")
        TEXT("            for a in assets:\n")
        TEXT("                obj_path = str(getattr(a, 'object_path', ''))\n")
        TEXT("                if not obj_path:\n")
        TEXT("                    continue\n")
        TEXT("                if 'NiagaraSystem' not in class_name_of(a):\n")
        TEXT("                    continue\n")
        TEXT("                asset_name = str(getattr(a, 'asset_name', '')).lower()\n")
        TEXT("                if ('template' in asset_name) or ('fountain' in asset_name) or asset_name.startswith('ns_') or ('system' in asset_name):\n")
        TEXT("                    chosen = pick_if_non_empty(obj_path)\n")
        TEXT("                    if chosen:\n")
        TEXT("                        template_path = chosen\n")
        TEXT("                        break\n")
        TEXT("            if template_path is not None:\n")
        TEXT("                break\n")
        TEXT("\n")
        TEXT("        if template_path is None:\n")
        TEXT("            try:\n")
        TEXT("                assets = ar.get_assets_by_path('/Niagara', recursive=True)\n")
        TEXT("            except Exception:\n")
        TEXT("                assets = []\n")
        TEXT("            for a in assets:\n")
        TEXT("                obj_path = str(getattr(a, 'object_path', ''))\n")
        TEXT("                if not obj_path:\n")
        TEXT("                    continue\n")
        TEXT("                if 'NiagaraSystem' not in class_name_of(a):\n")
        TEXT("                    continue\n")
        TEXT("                chosen = pick_if_non_empty(obj_path)\n")
        TEXT("                if chosen:\n")
        TEXT("                    template_path = chosen\n")
        TEXT("                    break\n")
        TEXT("    except Exception:\n")
        TEXT("        pass\n")

        TEXT("if template_path is None:\n")
        TEXT("    raise RuntimeError('No Niagara system template found for fallback.')\n")
        TEXT("if unreal.EditorAssetLibrary.does_asset_exist(system_path):\n")
        TEXT("    unreal.EditorAssetLibrary.delete_asset(system_path)\n")
        TEXT("if not unreal.EditorAssetLibrary.duplicate_asset(template_path, system_path):\n")
        TEXT("    raise RuntimeError(f'Duplicate fallback template failed: {template_path} -> {system_path}')\n")
        TEXT("if not unreal.EditorAssetLibrary.save_asset(system_path):\n")
        TEXT("    raise RuntimeError(f'Save fallback system failed: {system_path}')\n")
        TEXT("loaded = unreal.EditorAssetLibrary.load_asset(system_path)\n")
        TEXT("if loaded is None:\n")
        TEXT("    raise RuntimeError(f'Load fallback system failed: {system_path}')\n")
        TEXT("count = -1\n")
        TEXT("try:\n")
        TEXT("    count = len(list(loaded.get_editor_property('emitter_handles') or []))\n")
        TEXT("except Exception:\n")
        TEXT("    pass\n")
        TEXT("print(f'SUCCESS: {system_path} emitters={count} template={template_path}')\n"),
        *EscapedOutputPath,
        *EscapedSystemName);
}

static bool TryReplaceWithTemplateSystemFallback(const FString& OutputPath, const FString& SystemName, FString& OutError)
{
    const FString Script = BuildTemplateFallbackPythonScript(OutputPath, SystemName);
    return FVFXPythonExecutor::ExecutePythonScript(Script, OutError);
}

// NOTE: Removed automatic repair/retry logic that appended "_Fixed" to the system name.
// Generation now performs a single Create + Save/Compile + SelfCheck pass.

UNiagaraSystem* UNiagaraSystemGenerator::GenerateNiagaraSystem(
    const FString& SystemName,
    const FString& OutputPath,
    const FVFXRecipe& Recipe,
    const FString& TemplateSystemPath)
{
    const FString BaseSystemName = SanitizeGeneratedName(SystemName, TEXT("GeneratedSystem"));
    const FString SafeOutputPath = NormalizeOutputAssetPath(OutputPath);
    const FString SafeSystemName = ResolveUniqueSystemName(SafeOutputPath, BaseSystemName);
    const FString SystemObjectPath = BuildSystemObjectPath(SafeOutputPath, SafeSystemName);
    UE_LOG(LogVFXAgent, Log, TEXT("Starting Recipe-Driven Niagara Generation for: %s (sanitized=%s)"), *SystemName, *SafeSystemName);

    TArray<FString> Warnings;
    FVFXEffectSpec Spec = FRecipeCompiler::Compile(SafeSystemName, OutputPath, Recipe, TemplateSystemPath, Warnings);

    if (Warnings.Num() > 0)
    {
        for (const FString& W : Warnings)
        {
            UE_LOG(LogVFXAgent, Warning, TEXT("Recipe Warning: %s"), *W);
        }
    }

    UE_LOG(LogVFXAgent, Log, TEXT("Generating System (single attempt)"));
    
    FScopedTransaction Transaction(FText::FromString("Generating Niagara System"));
    
    FVFXRepairReport Report;
    FString Endpoint;
    FString Model;
    FString ApiKey;
    FString BackendString;
    float TimeoutSeconds = 120.0f;
    bool bPythonLifecycleOnly = true;

    TryGetVFXAgentSettingString(TEXT("LLMEndpoint"), Endpoint);
    TryGetVFXAgentSettingString(TEXT("LLMModel"), Model);
    TryGetVFXAgentSettingString(TEXT("LLMApiKey"), ApiKey);
    TryGetVFXAgentSettingString(TEXT("LLMBackend"), BackendString);
    TryGetVFXAgentSettingFloat(TEXT("LLMTimeoutSeconds"), TimeoutSeconds);
    TryGetVFXAgentSettingBool(TEXT("PythonLifecycleOnly"), bPythonLifecycleOnly);

    UHttpLLMProvider* Provider = NewObject<UHttpLLMProvider>(GetTransientPackage());
    if (!Provider)
    {
        UE_LOG(LogVFXAgent, Error, TEXT("Failed to create UHttpLLMProvider."));
        return nullptr;
    }

    Provider->AddToRoot();
    struct FProviderRootGuard
    {
        UHttpLLMProvider* Provider = nullptr;
        ~FProviderRootGuard()
        {
            if (Provider)
            {
                Provider->RemoveFromRoot();
            }
        }
    } ProviderGuard{ Provider };

    Provider->Configure(ParseBackend(BackendString), Endpoint, Model, ApiKey, TimeoutSeconds);

    const FString PythonPrompt = BuildPythonGenerationPrompt(SafeSystemName, SafeOutputPath, TemplateSystemPath, Recipe, Spec);

    FString RawPythonScript;
    FString PythonRequestError;
    const bool bGotScript = RequestPythonScriptBlocking(Provider, PythonPrompt, TimeoutSeconds, RawPythonScript, PythonRequestError);

    if (!bGotScript)
    {
        UE_LOG(LogVFXAgent, Error, TEXT("Failed to request Python script from LLM: %s"), *PythonRequestError);
        return nullptr;
    }

    const FString CleanPythonScript = FVFXPythonExecutor::SanitizeLLMPythonOutput(RawPythonScript);
    if (CleanPythonScript.IsEmpty())
    {
        UE_LOG(LogVFXAgent, Error, TEXT("LLM returned empty Python script for system: %s"), *SafeSystemName);
        return nullptr;
    }

    FString CurrentScript = FString::Printf(
        TEXT("target_path = '%s'\nsystem_name = '%s'\nsystem_object_path = '%s'\n\n%s"),
        *EscapeForPythonString(SafeOutputPath),
        *EscapeForPythonString(SafeSystemName),
        *EscapeForPythonString(SystemObjectPath),
        *StripEditorOpenCalls(CleanPythonScript));

    int32 MaxRepairAttempts = 2;
    if (int32 ConfigRepairAttempts = 0;
        GConfig && GConfig->GetInt(TEXT("/Script/VFXAgentEditor.VFXAgentSettings"), TEXT("PythonAutoRepairAttempts"), ConfigRepairAttempts, GEditorIni))
    {
        MaxRepairAttempts = FMath::Clamp(ConfigRepairAttempts, 0, 5);
    }

    FString PythonExecError;
    bool bExecOk = false;
    ForceScanAssetPaths(SafeOutputPath);
    for (int32 Attempt = 0; Attempt <= MaxRepairAttempts; ++Attempt)
    {
        PythonExecError.Reset();
        bExecOk = FVFXPythonExecutor::ExecutePythonScript(CurrentScript, PythonExecError);
        if (bExecOk)
        {
            break;
        }

        UE_LOG(LogVFXAgent, Warning,
            TEXT("Python execution failed (attempt %d/%d) for '%s'. Traceback: %s"),
            Attempt + 1,
            MaxRepairAttempts + 1,
            *SafeSystemName,
            *PythonExecError);

        if (Attempt >= MaxRepairAttempts)
        {
            break;
        }

        const FString RepairPrompt = BuildPythonRepairPrompt(
            SafeSystemName,
            SafeOutputPath,
            SystemObjectPath,
            CurrentScript,
            PythonExecError);

        FString RepairedRawScript;
        FString RepairRequestError;
        if (!RequestPythonScriptBlocking(Provider, RepairPrompt, TimeoutSeconds, RepairedRawScript, RepairRequestError))
        {
            UE_LOG(LogVFXAgent, Error,
                TEXT("Failed to request repaired Python script (attempt %d): %s"),
                Attempt + 1,
                *RepairRequestError);
            break;
        }

        const FString RepairedClean = FVFXPythonExecutor::SanitizeLLMPythonOutput(RepairedRawScript);
        if (RepairedClean.IsEmpty())
        {
            UE_LOG(LogVFXAgent, Error, TEXT("Repair attempt %d returned empty Python script."), Attempt + 1);
            break;
        }

        CurrentScript = FString::Printf(
            TEXT("target_path = '%s'\nsystem_name = '%s'\nsystem_object_path = '%s'\n\n%s"),
            *EscapeForPythonString(SafeOutputPath),
            *EscapeForPythonString(SafeSystemName),
            *EscapeForPythonString(SystemObjectPath),
            *StripEditorOpenCalls(RepairedClean));
    }

    if (!bExecOk)
    {
        UE_LOG(LogVFXAgent, Error, TEXT("Python execution failed for generated system '%s': %s"), *SafeSystemName, *PythonExecError);
        return nullptr;
    }

    UNiagaraSystem* ResultSystem = TryLoadGeneratedSystem(SystemObjectPath, SafeOutputPath, SafeSystemName);
    if (!ResultSystem)
    {
        UE_LOG(LogVFXAgent, Error, TEXT("Python script executed but Niagara system could not be loaded: %s"), *SystemObjectPath);
        return nullptr;
    }

    if (bPythonLifecycleOnly)
    {
        UE_LOG(LogVFXAgent, Log, TEXT("PythonLifecycleOnly=true. Returning reloaded system without C++ post-processing: %s"), *SystemObjectPath);
        return ResultSystem;
    }

    if (ResultSystem->GetEmitterHandles().Num() == 0)
    {
        UE_LOG(LogVFXAgent, Warning, TEXT("Python generated an empty Niagara system. Applying C++ fallback emitters."));

        const TArray<FVFXEmitterSpec>& EmitterSpecs = Spec.Emitters;
        if (EmitterSpecs.Num() > 0)
        {
            int32 AddedCount = 0;
            for (int32 SpecIndex = 0; SpecIndex < EmitterSpecs.Num(); ++SpecIndex)
            {
                const FVFXEmitterSpec& EmitterSpec = EmitterSpecs[SpecIndex];
                FString EmitterName = EmitterSpec.Name;
                if (EmitterName.IsEmpty())
                {
                    EmitterName = FString::Printf(TEXT("Emitter_%d"), SpecIndex);
                }

                if (FNiagaraSpecExecutor::AddBasicEmitterToSystem(ResultSystem, EmitterName))
                {
                    FNiagaraSpecExecutor::ConfigureEmitter(ResultSystem, EmitterName, EmitterSpec);
                    ++AddedCount;
                }
            }

            if (AddedCount == 0)
            {
                if (!TryAttachExistingEmitterAsset(ResultSystem, SafeOutputPath))
                {
                    UE_LOG(LogVFXAgent, Error, TEXT("Fallback failed to add any emitters."));
                    return nullptr;
                }
            }
        }
        else
        {
            if (!FNiagaraSpecExecutor::AddBasicEmitterToSystem(ResultSystem, TEXT("FallbackEmitter")))
            {
                if (!TryAttachExistingEmitterAsset(ResultSystem, SafeOutputPath))
                {
                    UE_LOG(LogVFXAgent, Warning, TEXT("C++ fallback failed to add default emitter; will try template replacement fallback."));
                }
            }
        }
    }

    if (ResultSystem->GetEmitterHandles().Num() == 0)
    {
        FString FallbackError;
        UE_LOG(LogVFXAgent, Warning, TEXT("Niagara system is still empty after C++ fallback. Replacing with template system fallback."));
        if (!TryReplaceWithTemplateSystemFallback(SafeOutputPath, SafeSystemName, FallbackError))
        {
            UE_LOG(LogVFXAgent, Error, TEXT("Template replacement fallback failed: %s"), *FallbackError);
            return nullptr;
        }

        ResultSystem = TryLoadGeneratedSystem(SystemObjectPath, SafeOutputPath, SafeSystemName);
        if (!ResultSystem)
        {
            UE_LOG(LogVFXAgent, Error, TEXT("Template replacement fallback executed but system could not be reloaded: %s"), *SystemObjectPath);
            return nullptr;
        }

        if (ResultSystem->GetEmitterHandles().Num() == 0)
        {
            UE_LOG(LogVFXAgent, Error, TEXT("Template replacement fallback completed but generated system is still empty: %s"), *SystemObjectPath);
            return nullptr;
        }
    }
    
    // Ensure the system is marked as standalone to prevent GC during generation
    ResultSystem->SetFlags(RF_Public | RF_Standalone);
    
    ResultSystem->Modify();

    // Keep C++ material assignment only as a fallback safety net for scripts that did not bind materials.
    const bool bUseCppMaterialFallback = false;
    if (bUseCppMaterialFallback)
    {
        AssignMaterialsFromLibrary(Recipe, ResultSystem);
    }

    // Apply collision event handlers (module-stack level) after system creation
    if (Recipe.Events.Num() > 0)
    {
        for (const FVFXEventRecipe& Event : Recipe.Events)
        {
            if (Event.Type == EVFXEventType::OnEmitterCollision)
            {
                FNiagaraSpecExecutor::ConfigureCollisionEventHandler(ResultSystem, Event.SourceLayer, Event.TargetLayer, Event);
            }
        }
    }

    if (FNiagaraSpecExecutor::SaveCompileAndSelfCheck(ResultSystem, Report))
    {
        UE_LOG(LogVFXAgent, Log, TEXT("Generation Success! Asset: %s"), *Report.SystemPath);
        return ResultSystem;
    }

    UE_LOG(LogVFXAgent, Warning, TEXT("SelfCheck Failed for system '%s' but automatic repair/retry is disabled."), *Spec.Name);
    for (const FString& E : Report.Errors)
    {
        UE_LOG(LogVFXAgent, Warning, TEXT("Error: %s"), *E);
    }

    // Return the generated system even if self-check failed; caller can decide further action.
    return ResultSystem;
}

bool UNiagaraSystemGenerator::UpdateNiagaraSystem(UNiagaraSystem* System, const FVFXRecipe& Recipe)
{
    // Simplified update using Executor's Configure
    if (!System) return false;

    TArray<FString> Warnings;
    FVFXEffectSpec Spec = FRecipeCompiler::Compile(System->GetName(), System->GetPathName(), Recipe, FString(), Warnings);
    if (Spec.Emitters.Num() == 0) return false;

    for (const FVFXEmitterSpec& EmitterSpec : Spec.Emitters)
    {
        FNiagaraSpecExecutor::ConfigureEmitter(System, EmitterSpec.Name, EmitterSpec);
    }

    if (Recipe.Events.Num() > 0)
    {
        for (const FVFXEventRecipe& Event : Recipe.Events)
        {
            if (Event.Type == EVFXEventType::OnEmitterCollision)
            {
                FNiagaraSpecExecutor::ConfigureCollisionEventHandler(System, Event.SourceLayer, Event.TargetLayer, Event);
            }
        }
    }
    return true;
}

static TArray<FString> GetMaterialLibraryPaths()
{
    TArray<FString> Paths;
    const TCHAR* Section = TEXT("/Script/VFXAgentEditor.VFXAgentSettings");
    const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
    for (const FString& File : ConfigFiles)
    {
        if (GConfig && GConfig->GetArray(Section, TEXT("MaterialLibraryPaths"), Paths, File) && Paths.Num() > 0)
        {
            break;
        }
    }
    if (Paths.Num() == 0)
    {
        Paths.Add(TEXT("/Game/VFXAgent/Materials"));
    }
    return Paths;
}

static void CollectMaterialAssets(const TArray<FString>& RootPaths, TArray<FAssetData>& OutAssets)
{
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    FARFilter Filter;
    for (const FString& Root : RootPaths)
    {
        Filter.PackagePaths.Add(*Root);
    }
    Filter.ClassPaths.Add(UMaterialInterface::StaticClass()->GetClassPathName());
    Filter.ClassPaths.Add(UMaterial::StaticClass()->GetClassPathName());
    Filter.ClassPaths.Add(UMaterialInstanceConstant::StaticClass()->GetClassPathName());
    Filter.bRecursivePaths = true;
    AssetRegistryModule.Get().GetAssets(Filter, OutAssets);
}

static void AppendKeywordsFromText(const FString& Text, TSet<FString>& Out)
{
    FString Token;
    for (int32 i = 0; i < Text.Len(); ++i)
    {
        const TCHAR C = Text[i];
        if (FChar::IsAlnum(C))
        {
            Token.AppendChar(FChar::ToLower(C));
        }
        else if (!Token.IsEmpty())
        {
            if (Token.Len() > 2)
            {
                Out.Add(Token);
            }
            Token.Reset();
        }
    }
    if (Token.Len() > 2)
    {
        Out.Add(Token);
    }

    const FString Lower = Text.ToLower();
    if (Lower.Contains(TEXT("烟")) || Lower.Contains(TEXT("雾"))) Out.Add(TEXT("smoke"));
    if (Lower.Contains(TEXT("火")) || Lower.Contains(TEXT("焰"))) Out.Add(TEXT("fire"));
    if (Lower.Contains(TEXT("电")) || Lower.Contains(TEXT("雷"))) Out.Add(TEXT("electric"));
    if (Lower.Contains(TEXT("光")) || Lower.Contains(TEXT("辉"))) Out.Add(TEXT("glow"));
    if (Lower.Contains(TEXT("尘"))) Out.Add(TEXT("dust"));
    if (Lower.Contains(TEXT("爆"))) Out.Add(TEXT("burst"));
    if (Lower.Contains(TEXT("尾")) || Lower.Contains(TEXT("拖"))) Out.Add(TEXT("trail"));
}

static TArray<FString> BuildKeywords(const FString& Text)
{
    TSet<FString> Keywords;
    AppendKeywordsFromText(Text, Keywords);

    if (Keywords.Contains(TEXT("smoke"))) { Keywords.Add(TEXT("fog")); Keywords.Add(TEXT("mist")); }
    if (Keywords.Contains(TEXT("spark"))) { Keywords.Add(TEXT("sparks")); Keywords.Add(TEXT("ember")); }
    if (Keywords.Contains(TEXT("electric"))) { Keywords.Add(TEXT("lightning")); }
    if (Keywords.Contains(TEXT("fire"))) { Keywords.Add(TEXT("flame")); }
    if (Keywords.Contains(TEXT("trail"))) { Keywords.Add(TEXT("ribbon")); }
    if (Keywords.Contains(TEXT("glow"))) { Keywords.Add(TEXT("flare")); }

    TArray<FString> Result = Keywords.Array();
    return Result;
}

static int32 ScoreMaterialName(const FString& MaterialNameLower, const TArray<FString>& Keywords)
{
    int32 Score = 0;
    for (const FString& Key : Keywords)
    {
        if (MaterialNameLower == Key)
        {
            Score += 20;
        }
        else if (MaterialNameLower.Contains(Key))
        {
            Score += 10;
        }
    }
    return Score;
}

static FString NormalizeEmitterNameForMatch(const FString& Name)
{
    FString Result = Name;
    while (Result.Len() > 0 && FChar::IsDigit(Result[Result.Len() - 1]))
    {
        Result.LeftChopInline(1);
    }
    return Result.ToLower();
}

void UNiagaraSystemGenerator::AssignMaterialsFromLibrary(
    const FVFXRecipe& Recipe,
    UNiagaraSystem* System)
{
    if (!System)
    {
        UE_LOG(LogVFXAgent, Error, TEXT("Cannot assign materials for null system"));
        return;
    }

    const TArray<FString> LibraryPaths = GetMaterialLibraryPaths();
    TArray<FAssetData> MaterialAssets;
    CollectMaterialAssets(LibraryPaths, MaterialAssets);

    if (MaterialAssets.Num() == 0)
    {
        UE_LOG(LogVFXAgent, Warning, TEXT("No materials found in library paths. Using default Niagara material."));
    }

    TArray<TArray<FString>> MaterialKeywords;
    MaterialKeywords.Reserve(Recipe.Materials.Num());
    for (const FVFXMaterialRecipe& Mat : Recipe.Materials)
    {
        MaterialKeywords.Add(BuildKeywords(Mat.Name + TEXT(" ") + Mat.Description));
    }

    TMap<FString, TArray<FString>> EmitterKeywords;
    for (const FVFXLayerRecipe& Layer : Recipe.Layers)
    {
        EmitterKeywords.Add(Layer.Name.ToLower(), BuildKeywords(Layer.Name + TEXT(" ") + Layer.Role));
    }
    for (const FVFXEmitterRecipe& Emitter : Recipe.Emitters)
    {
        EmitterKeywords.Add(Emitter.Name.ToLower(), BuildKeywords(Emitter.Name + TEXT(" ") + Emitter.RendererType));
    }

    auto ApplyMaterialToEmitter = [&](UNiagaraEmitter* Emitter, UMaterialInterface* Material)
    {
        if (!Emitter || !Material) return;
        
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
            if (!Prop) continue;
            if (UNiagaraSpriteRendererProperties* Sprite = Cast<UNiagaraSpriteRendererProperties>(Prop))
            {
                Sprite->Material = Material;
            }
            else if (UNiagaraRibbonRendererProperties* Ribbon = Cast<UNiagaraRibbonRendererProperties>(Prop))
            {
                Ribbon->Material = Material;
            }
        }
        
#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5
        if (FVersionedNiagaraEmitterData* EmitterData = Emitter->GetLatestEmitterData())
        {
            // EmitterData->Modify(); // FVersionedNiagaraEmitterData is a struct, not a UObject
        }
#endif
        Emitter->Modify();
        Emitter->PostEditChange();
    };

    auto PickMaterialByKeywords = [&](const TArray<FString>& Keywords) -> UMaterialInterface*
    {
        int32 BestScore = 0;
        FAssetData BestAsset;
        for (const FAssetData& Asset : MaterialAssets)
        {
            const FString AssetNameLower = Asset.AssetName.ToString().ToLower();
            const int32 Score = ScoreMaterialName(AssetNameLower, Keywords);
            if (Score > BestScore)
            {
                BestScore = Score;
                BestAsset = Asset;
            }
        }
        if (BestScore == 0)
        {
            return nullptr;
        }
        return LoadObject<UMaterialInterface>(nullptr, *BestAsset.GetObjectPathString());
    };

    UMaterialInterface* DefaultMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Niagara/DefaultAssets/DefaultSpriteMaterial.DefaultSpriteMaterial"));

    const TArray<FNiagaraEmitterHandle>& Handles = System->GetEmitterHandles();
    for (const FNiagaraEmitterHandle& Handle : Handles)
    {
        UNiagaraEmitter* Emitter = Handle.GetInstance().Emitter;
        if (!Emitter) continue;

        const FString HandleName = Handle.GetName().ToString();
        const FString Normalized = NormalizeEmitterNameForMatch(HandleName);

        int32 MatIndex = -1;
        for (const FVFXEmitterRecipe& EmitterRecipe : Recipe.Emitters)
        {
            if (NormalizeEmitterNameForMatch(EmitterRecipe.Name) == Normalized)
            {
                MatIndex = EmitterRecipe.MaterialIndex;
                break;
            }
        }
        for (const FVFXLayerRecipe& Layer : Recipe.Layers)
        {
            if (NormalizeEmitterNameForMatch(Layer.Name) == Normalized)
            {
                MatIndex = (MatIndex >= 0) ? MatIndex : Layer.MaterialIndex;
                break;
            }
        }

        TArray<FString> Keywords;
        if (MatIndex >= 0 && MaterialKeywords.IsValidIndex(MatIndex))
        {
            Keywords = MaterialKeywords[MatIndex];
        }
        else if (EmitterKeywords.Contains(Normalized))
        {
            Keywords = EmitterKeywords[Normalized];
        }
        else
        {
            Keywords = BuildKeywords(HandleName);
        }

        UMaterialInterface* ChosenMaterial = PickMaterialByKeywords(Keywords);
        if (!ChosenMaterial && MaterialAssets.Num() > 0)
        {
            ChosenMaterial = LoadObject<UMaterialInterface>(nullptr, *MaterialAssets[0].GetObjectPathString());
        }
        if (!ChosenMaterial)
        {
            ChosenMaterial = DefaultMaterial;
        }

        if (ChosenMaterial)
        {
            ApplyMaterialToEmitter(Emitter, ChosenMaterial);
        }
    }
}
