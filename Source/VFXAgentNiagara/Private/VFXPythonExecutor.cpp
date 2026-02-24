#include "VFXPythonExecutor.h"
#include "VFXAgentLog.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/ConfigCacheIni.h"
#include "UObject/UnrealType.h"
#include "Misc/ScopeLock.h"

// UE5 Python scripting bridge
#include "IPythonScriptPlugin.h"
#include "PythonScriptTypes.h"

namespace
{
	FCriticalSection GRuntimeErrorBufferMutex;
	TArray<FString> GRuntimeErrorBuffer;
	constexpr int32 GMaxBufferedRuntimeErrors = 32;
}

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
		TEXT("if 'safe_get_path_name' not in globals():\n")
		TEXT("    def safe_get_path_name(obj):\n")
		TEXT("        if obj is None:\n")
		TEXT("            return ''\n")
		TEXT("        try:\n")
		TEXT("            return str(obj.get_path_name())\n")
		TEXT("        except Exception:\n")
		TEXT("            return ''\n")
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
		TEXT("if 'on_mesh_ready_schema_example' not in globals():\n")
		TEXT("    def on_mesh_ready_schema_example(payload):\n")
		TEXT("        try:\n")
		TEXT("            run_id = str(payload.get('run_id', ''))\n")
		TEXT("            task_id = str(payload.get('task_id', ''))\n")
		TEXT("            status = str(payload.get('status', ''))\n")
		TEXT("            asset_path = str(payload.get('asset_path', ''))\n")
		TEXT("            error = str(payload.get('error', ''))\n")
		TEXT("            elapsed = payload.get('elapsed', 0.0)\n")
		TEXT("            unreal.log(f'[VFXAgent] mesh callback run_id={run_id} task_id={task_id} status={status} asset={asset_path} elapsed={elapsed}')\n")
		TEXT("            if error:\n")
		TEXT("                _msg = f'[VFXAgent] mesh callback error: {error}'\n")
		TEXT("                unreal.log_warning(_msg)\n")
		TEXT("                if hasattr(unreal, 'VFXAgentPythonBridge'):\n")
		TEXT("                    unreal.VFXAgentPythonBridge.push_python_error_to_buffer(_msg)\n")
		TEXT("        except Exception as _cb_parse_err:\n")
		TEXT("            _msg = f'[VFXAgent] mesh callback payload parse failed: {_cb_parse_err}'\n")
		TEXT("            unreal.log_error(_msg)\n")
		TEXT("            try:\n")
		TEXT("                if hasattr(unreal, 'VFXAgentPythonBridge'):\n")
		TEXT("                    unreal.VFXAgentPythonBridge.push_python_error_to_buffer(_msg)\n")
		TEXT("            except Exception:\n")
		TEXT("                pass\n")
		TEXT("if 'vfx_agent' not in globals():\n")
		TEXT("    class _VFXAgentBridge:\n")
		TEXT("        @staticmethod\n")
		TEXT("        def generate_mesh(prompt):\n")
		TEXT("            try:\n")
		TEXT("                if hasattr(unreal, 'VFXAgentPythonBridge'):\n")
		TEXT("                    return unreal.VFXAgentPythonBridge.generate_mesh_async(prompt, 'glb', '')\n")
		TEXT("            except Exception as _bridge_err:\n")
		TEXT("                unreal.log_warning(f'VFXAgent bridge generate_mesh failed: {_bridge_err}')\n")
		TEXT("            unreal.log_warning('VFXAgentPythonBridge unavailable. Returning empty mesh id.')\n")
		TEXT("            return ''\n")
		TEXT("        @staticmethod\n")
		TEXT("        def generate_mesh_with_callback(prompt, callback_name='on_mesh_ready_schema_example', fmt='glb'):\n")
		TEXT("            try:\n")
		TEXT("                if hasattr(unreal, 'VFXAgentPythonBridge'):\n")
		TEXT("                    return unreal.VFXAgentPythonBridge.generate_mesh_async(prompt, fmt, callback_name)\n")
		TEXT("            except Exception as _bridge_cb_err:\n")
		TEXT("                unreal.log_warning(f'VFXAgent bridge generate_mesh_with_callback failed: {_bridge_cb_err}')\n")
		TEXT("            unreal.log_warning('VFXAgentPythonBridge unavailable. Returning empty mesh id.')\n")
		TEXT("            return ''\n")
		TEXT("        @staticmethod\n")
		TEXT("        def get_mesh_task_status(task_id):\n")
		TEXT("            try:\n")
		TEXT("                if hasattr(unreal, 'VFXAgentPythonBridge'):\n")
		TEXT("                    return unreal.VFXAgentPythonBridge.get_mesh_task_status(task_id)\n")
		TEXT("            except Exception as _status_err:\n")
		TEXT("                unreal.log_warning(f'VFXAgent bridge get_mesh_task_status failed: {_status_err}')\n")
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
	bool bSuccess = PythonPlugin->ExecPythonCommandEx(Cmd);

	if (bSuccess)
	{
		FString PythonErrorOutput;
		for (const FPythonLogOutputEntry& Entry : Cmd.LogOutput)
		{
			if (Entry.Type == EPythonLogOutputType::Error)
			{
				PythonErrorOutput += Entry.Output + TEXT("\n");
			}
		}

		PythonErrorOutput.TrimEndInline();
		if (!PythonErrorOutput.IsEmpty())
		{
			bSuccess = false;
			OutError = PythonErrorOutput;
		}
	}

	if (bSuccess)
	{
		UE_LOG(LogVFXAgent, Log, TEXT("VFXPythonExecutor: Python script executed successfully."));
	}
	else
	{
		// CommandResult contains the Python traceback / exception string on failure
		if (OutError.IsEmpty() && !Cmd.CommandResult.IsEmpty())
		{
			OutError = Cmd.CommandResult;
		}
		else if (OutError.IsEmpty())
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
		AppendRuntimeError(FString::Printf(TEXT("Python execution failed: %s"), *OutError));
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

bool FVFXPythonExecutor::CanInvokeCallbackFunction(const FString& CallbackName, FString& OutReason)
{
	OutReason.Empty();

	const FString TrimmedName = CallbackName.TrimStartAndEnd();
	if (TrimmedName.IsEmpty())
	{
		OutReason = TEXT("callback name is empty");
		return false;
	}

	IPythonScriptPlugin* PythonPlugin = IPythonScriptPlugin::Get();
	if (!PythonPlugin)
	{
		OutReason = TEXT("python plugin unavailable");
		return false;
	}

	if (!PythonPlugin->IsPythonAvailable())
	{
		OutReason = TEXT("python runtime unavailable");
		return false;
	}

	FPythonCommandEx Cmd;
	Cmd.Command = FString::Printf(
		TEXT("_cb = globals().get('%s', None)\n")
		TEXT("if not callable(_cb):\n")
		TEXT("    raise RuntimeError('callback_not_callable')\n"),
		*EscapeForPythonSingleQuoted(TrimmedName));
	Cmd.ExecutionMode = EPythonCommandExecutionMode::ExecuteFile;
	Cmd.FileExecutionScope = EPythonFileExecutionScope::Public;

	const bool bOk = PythonPlugin->ExecPythonCommandEx(Cmd);
	if (!bOk)
	{
		OutReason = Cmd.CommandResult.IsEmpty() ? TEXT("callback is not callable in current Python state") : Cmd.CommandResult;
		return false;
	}

	return true;
}

void FVFXPythonExecutor::AppendRuntimeError(const FString& ErrorMessage)
{
	const FString Trimmed = ErrorMessage.TrimStartAndEnd();
	if (Trimmed.IsEmpty())
	{
		return;
	}

	FScopeLock Lock(&GRuntimeErrorBufferMutex);
	GRuntimeErrorBuffer.Add(FString::Printf(TEXT("[%s] %s"), *FDateTime::UtcNow().ToString(TEXT("%Y-%m-%d %H:%M:%S")), *Trimmed));
	while (GRuntimeErrorBuffer.Num() > GMaxBufferedRuntimeErrors)
	{
		GRuntimeErrorBuffer.RemoveAt(0);
	}
}

FString FVFXPythonExecutor::ConsumeRuntimeErrorsForPrompt(int32 MaxEntries)
{
	FScopeLock Lock(&GRuntimeErrorBufferMutex);
	if (GRuntimeErrorBuffer.Num() == 0)
	{
		return FString();
	}

	const int32 SafeMaxEntries = FMath::Max(1, MaxEntries);
	const int32 StartIndex = FMath::Max(0, GRuntimeErrorBuffer.Num() - SafeMaxEntries);

	FString Out;
	for (int32 Index = StartIndex; Index < GRuntimeErrorBuffer.Num(); ++Index)
	{
		Out += TEXT("- ") + GRuntimeErrorBuffer[Index] + TEXT("\n");
	}

	GRuntimeErrorBuffer.Empty();
	return Out;
}
