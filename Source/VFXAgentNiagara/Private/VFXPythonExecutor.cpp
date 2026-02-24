#include "VFXPythonExecutor.h"
#include "VFXAgentLog.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/ConfigCacheIni.h"
#include "UObject/UnrealType.h"

// UE5 Python scripting bridge
#include "IPythonScriptPlugin.h"
#include "PythonScriptTypes.h"

static FString EscapeForPythonSingleQuoted(const FString& Input)
{
	FString Out = Input;
	Out = Out.Replace(TEXT("\\"), TEXT("\\\\"));
	Out = Out.Replace(TEXT("'"), TEXT("\\'"));
	Out = Out.Replace(TEXT("\r\n"), TEXT("\\n"));
	Out = Out.Replace(TEXT("\n"), TEXT("\\n"));
	Out = Out.Replace(TEXT("\r"), TEXT("\\n"));
	return Out;
}

static bool TryReadConfigString(const TCHAR* Section, const TCHAR* Key, FString& OutValue)
{
	const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
	for (const FString& File : ConfigFiles)
	{
		if (GConfig && GConfig->GetString(Section, Key, OutValue, File))
		{
			return true;
		}
	}
	return false;
}

static FString ReadVFXAgentSettingOrDefault(const TCHAR* Key, const FString& DefaultValue)
{
	FString Value;
	if (TryReadConfigString(TEXT("/Script/VFXAgentEditor.VFXAgentSettings"), Key, Value))
	{
		Value.TrimStartAndEndInline();
		return Value.IsEmpty() ? DefaultValue : Value;
	}
	return DefaultValue;
}

static FString ReadVFXAgentGlobalOrDefault(const TCHAR* Key, const FString& DefaultValue)
{
	FString Value;
	if (TryReadConfigString(TEXT("VFXAgent"), Key, Value))
	{
		Value.TrimStartAndEndInline();
		return Value.IsEmpty() ? DefaultValue : Value;
	}
	return DefaultValue;
}

static FString BuildExecutorBootstrapContext()
{
	const FString TargetPath = TEXT("/Game/VFXAgent/Generated");
	const FString SystemName = TEXT("NS_VFXAgent_Auto");
	const FString MaterialLibraryPath = ReadVFXAgentSettingOrDefault(TEXT("MaterialLibraryPaths"), TEXT("/Game/VFXAgent/Materials"));
	const FString LLMApiKey = ReadVFXAgentSettingOrDefault(TEXT("LLMApiKey"), FString());
	const FString MeshyApiKey = ReadVFXAgentGlobalOrDefault(TEXT("MeshyApiKey"), FString());
	const FString MeshyEndpoint = ReadVFXAgentGlobalOrDefault(TEXT("MeshyEndpoint"), TEXT("https://api.meshy.ai/v1"));

	return FString::Printf(
		TEXT("import unreal\n")
		TEXT("try:\n")
		TEXT("    if hasattr(unreal, 'VFXAgentPythonBridge'):\n")
		TEXT("        unreal.VFXAgentPythonBridge.prepare_editor_context('/Niagara')\n")
		TEXT("except Exception as _ctx_err:\n")
		TEXT("    unreal.log_warning(f'VFXAgent context preparation warning: {_ctx_err}')\n")
		TEXT("if 'target_path' not in globals():\n")
		TEXT("    target_path = '%s'\n")
		TEXT("if 'system_name' not in globals():\n")
		TEXT("    system_name = '%s'\n")
		TEXT("if 'system_object_path' not in globals():\n")
		TEXT("    system_object_path = f'{target_path}/{system_name}.{system_name}'\n")
		TEXT("try:\n")
		TEXT("    if hasattr(unreal, 'VFXAgentPythonBridge'):\n")
		TEXT("        unreal.VFXAgentPythonBridge.set_active_system_context(system_object_path)\n")
		TEXT("except Exception as _ctx_set_err:\n")
		TEXT("    unreal.log_warning(f'VFXAgent set_active_system_context warning: {_ctx_set_err}')\n")
		TEXT("if 'TARGET_PATH' not in globals():\n")
		TEXT("    TARGET_PATH = target_path\n")
		TEXT("if 'SYSTEM_NAME' not in globals():\n")
		TEXT("    SYSTEM_NAME = system_name\n")
		TEXT("if 'SYSTEM_OBJECT_PATH' not in globals():\n")
		TEXT("    SYSTEM_OBJECT_PATH = system_object_path\n")
		TEXT("if 'TARGET_SYSTEM' not in globals():\n")
		TEXT("    try:\n")
		TEXT("        TARGET_SYSTEM = unreal.load_asset(system_object_path)\n")
		TEXT("    except Exception:\n")
		TEXT("        TARGET_SYSTEM = None\n")
		TEXT("if 'material_library_path' not in globals():\n")
		TEXT("    material_library_path = '%s'\n")
		TEXT("if 'llm_api_key' not in globals():\n")
		TEXT("    llm_api_key = '%s'\n")
		TEXT("if 'LLM_API_KEY' not in globals():\n")
		TEXT("    LLM_API_KEY = llm_api_key\n")
		TEXT("if 'meshy_api_key' not in globals():\n")
		TEXT("    meshy_api_key = '%s'\n")
		TEXT("if 'MESHY_API_KEY' not in globals():\n")
		TEXT("    MESHY_API_KEY = meshy_api_key\n")
		TEXT("if 'meshy_endpoint' not in globals():\n")
		TEXT("    meshy_endpoint = '%s'\n")
		TEXT("if 'vfx_paths' not in globals():\n")
		TEXT("    vfx_paths = {'generated': target_path, 'materials': material_library_path}\n")
		TEXT("if 'vfx_agent' not in globals():\n")
		TEXT("    class _VFXAgentBridge:\n")
		TEXT("        @staticmethod\n")
		TEXT("        def generate_mesh(prompt):\n")
		TEXT("            try:\n")
		TEXT("                if hasattr(unreal, 'VFXAgentPythonBridge'):\n")
		TEXT("                    return unreal.VFXAgentPythonBridge.generate_mesh(prompt)\n")
		TEXT("            except Exception as _bridge_err:\n")
		TEXT("                unreal.log_warning(f'VFXAgent bridge generate_mesh failed: {_bridge_err}')\n")
		TEXT("            unreal.log_warning('VFXAgentPythonBridge unavailable. Returning empty mesh id.')\n")
		TEXT("            return ''\n")
		TEXT("    vfx_agent = _VFXAgentBridge()\n\n"),
		*EscapeForPythonSingleQuoted(TargetPath),
		*EscapeForPythonSingleQuoted(SystemName),
		*EscapeForPythonSingleQuoted(MaterialLibraryPath),
		*EscapeForPythonSingleQuoted(LLMApiKey),
		*EscapeForPythonSingleQuoted(MeshyApiKey),
		*EscapeForPythonSingleQuoted(MeshyEndpoint));
}

// ---------------------------------------------------------------------------
// ExecutePythonScript (with error capture)
// ---------------------------------------------------------------------------
bool FVFXPythonExecutor::ExecutePythonScript(const FString& PythonCode, FString& OutError)
{
	OutError.Empty();

	if (!IsInGameThread())
	{
		OutError = TEXT("Python execution must run on the editor/game thread.");
		UE_LOG(LogVFXAgent, Error, TEXT("VFXPythonExecutor: Called off game thread."));
		return false;
	}

	if (PythonCode.IsEmpty())
	{
		OutError = TEXT("Python script is empty.");
		UE_LOG(LogVFXAgent, Warning, TEXT("VFXPythonExecutor: Received empty Python script."));
		return false;
	}

	IPythonScriptPlugin* PythonPlugin = IPythonScriptPlugin::Get();
	if (!PythonPlugin)
	{
		OutError = TEXT("Python Editor Script Plugin is not loaded. Enable it in Edit \u2192 Plugins, then restart the editor.");
		UE_LOG(LogVFXAgent, Error, TEXT("VFXPythonExecutor: IPythonScriptPlugin unavailable."));
		return false;
	}

	if (!PythonPlugin->IsPythonAvailable())
	{
		OutError = TEXT("Python runtime is not available. Enable 'Python Editor Script Plugin' and restart the editor.");
		UE_LOG(LogVFXAgent, Error, TEXT("VFXPythonExecutor: Python runtime not available."));
		return false;
	}

	UE_LOG(LogVFXAgent, Log,
		TEXT("VFXPythonExecutor: Executing LLM-generated Python script (%d chars)..."),
		PythonCode.Len());

	const FString BootstrapGlobals = BuildExecutorBootstrapContext();

	const FString FinalPythonCode = BootstrapGlobals + PythonCode;

	// ExecuteFile mode runs a literal multi-statement Python script (same as exec())
	FPythonCommandEx Cmd;
	Cmd.Command = FinalPythonCode;
	Cmd.ExecutionMode = EPythonCommandExecutionMode::ExecuteFile;
	Cmd.FileExecutionScope = EPythonFileExecutionScope::Public;
	const bool bSuccess = PythonPlugin->ExecPythonCommandEx(Cmd);

	if (bSuccess)
	{
		UE_LOG(LogVFXAgent, Log, TEXT("VFXPythonExecutor: Python script executed successfully."));
	}
	else
	{
		// CommandResult contains the Python traceback / exception string on failure
		if (!Cmd.CommandResult.IsEmpty())
		{
			OutError = Cmd.CommandResult;
		}
		else
		{
			// Fall back to collecting error entries from LogOutput
			for (const FPythonLogOutputEntry& Entry : Cmd.LogOutput)
			{
				if (Entry.Type == EPythonLogOutputType::Error || Entry.Type == EPythonLogOutputType::Warning)
				{
					OutError += Entry.Output + TEXT("\n");
				}
			}
			OutError.TrimEndInline();
		}

		if (OutError.IsEmpty())
		{
			OutError = TEXT("Python execution failed (no traceback captured). Check Output Log for LogPython entries.");
		}

		UE_LOG(LogVFXAgent, Error,
			TEXT("VFXPythonExecutor: Python script FAILED.\n%s"), *OutError);
	}

	return bSuccess;
}

// ---------------------------------------------------------------------------
// ExecutePythonScript (simple bool overload — kept for backward compat)
// ---------------------------------------------------------------------------
bool FVFXPythonExecutor::ExecutePythonScript(const FString& PythonCode)
{
	FString DiscardedError;
	return ExecutePythonScript(PythonCode, DiscardedError);
}

// ---------------------------------------------------------------------------
// ExecutePythonFile
// ---------------------------------------------------------------------------
bool FVFXPythonExecutor::ExecutePythonFile(const FString& FilePath)
{
	if (!FPaths::FileExists(FilePath))
	{
		UE_LOG(LogVFXAgent, Error,
			TEXT("VFXPythonExecutor: Python file not found: %s"), *FilePath);
		return false;
	}

	FString PythonCode;
	if (!FFileHelper::LoadFileToString(PythonCode, *FilePath))
	{
		UE_LOG(LogVFXAgent, Error,
			TEXT("VFXPythonExecutor: Failed to read Python file: %s"), *FilePath);
		return false;
	}

	UE_LOG(LogVFXAgent, Log,
		TEXT("VFXPythonExecutor: Executing Python file: %s"), *FilePath);

	return ExecutePythonScript(PythonCode);
}

// ---------------------------------------------------------------------------
// SanitizeLLMPythonOutput
// ---------------------------------------------------------------------------
FString FVFXPythonExecutor::SanitizeLLMPythonOutput(const FString& RawLLMOutput)
{
	FString Code = RawLLMOutput;
	Code.TrimStartAndEndInline();

	// Strip ```python ... ``` fences
	static const FString FencePython = TEXT("```python");
	static const FString FenceGeneric = TEXT("```");

	if (Code.StartsWith(FencePython))
	{
		Code.RemoveFromStart(FencePython);
		Code.TrimStartInline();
	}
	else if (Code.StartsWith(FenceGeneric))
	{
		Code.RemoveFromStart(FenceGeneric);
		Code.TrimStartInline();
	}

	if (Code.EndsWith(FenceGeneric))
	{
		Code.RemoveFromEnd(FenceGeneric);
		Code.TrimEndInline();
	}

	return Code;
}
