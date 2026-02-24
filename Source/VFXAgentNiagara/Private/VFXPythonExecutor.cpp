#include "VFXPythonExecutor.h"
#include "VFXAgentLog.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

// UE5 Python scripting bridge
#include "IPythonScriptPlugin.h"
#include "PythonScriptTypes.h"

// ---------------------------------------------------------------------------
// ExecutePythonScript (with error capture)
// ---------------------------------------------------------------------------
bool FVFXPythonExecutor::ExecutePythonScript(const FString& PythonCode, FString& OutError)
{
	OutError.Empty();

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

	const FString BootstrapGlobals =
		TEXT("if 'target_path' not in globals():\n")
		TEXT("    target_path = '/Game/VFXAgent/Generated'\n")
		TEXT("if 'system_name' not in globals():\n")
		TEXT("    system_name = 'NS_VFXAgent_Auto'\n")
		TEXT("if 'system_object_path' not in globals():\n")
		TEXT("    system_object_path = f'{target_path}/{system_name}.{system_name}'\n\n");

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
