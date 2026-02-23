#include "VFXPythonExecutor.h"
#include "VFXAgentLog.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

// UE5 Python scripting bridge
#include "IPythonScriptPlugin.h"

// ---------------------------------------------------------------------------
// ExecutePythonScript
// ---------------------------------------------------------------------------
bool FVFXPythonExecutor::ExecutePythonScript(const FString& PythonCode)
{
	if (PythonCode.IsEmpty())
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("VFXPythonExecutor: Received empty Python script — nothing to execute."));
		return false;
	}

	IPythonScriptPlugin* PythonPlugin = IPythonScriptPlugin::Get();
	if (!PythonPlugin)
	{
		UE_LOG(LogVFXAgent, Error,
			TEXT("VFXPythonExecutor: IPythonScriptPlugin is unavailable. "
			     "Please enable 'Python Editor Script Plugin' in Edit → Plugins, then restart the editor."));
		return false;
	}

	if (!PythonPlugin->IsPythonAvailable())
	{
		UE_LOG(LogVFXAgent, Error,
			TEXT("VFXPythonExecutor: Python runtime is not available in this build configuration. "
			     "Ensure the plugin is enabled and the editor has been restarted."));
		return false;
	}

	UE_LOG(LogVFXAgent, Log,
		TEXT("VFXPythonExecutor: Executing LLM-generated Python script (%d chars)..."),
		PythonCode.Len());

	const bool bSuccess = PythonPlugin->ExecPythonCommand(*PythonCode);

	if (bSuccess)
	{
		UE_LOG(LogVFXAgent, Log,
			TEXT("VFXPythonExecutor: Python script executed successfully — VFX asset generation complete."));
	}
	else
	{
		UE_LOG(LogVFXAgent, Error,
			TEXT("VFXPythonExecutor: Python script execution FAILED. "
			     "Check the Output Log for Python tracebacks. "
			     "Common causes: invalid asset paths, missing unreal module imports, syntax errors in LLM output."));
	}

	return bSuccess;
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
