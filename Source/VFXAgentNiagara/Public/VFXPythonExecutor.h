#pragma once

#include "CoreMinimal.h"

/**
 * VFXPythonExecutor
 *
 * Core executor for the new Python-first VFX generation architecture.
 *
 * Workflow:
 *   1. The UI panel receives a user prompt (SVFXAgentPanel).
 *   2. The prompt is sent to the LLM (UHttpLLMProvider).
 *   3. The LLM returns a raw UE5 Python script string.
 *   4. This executor receives the script and runs it silently via
 *      IPythonScriptPlugin, which invokes the engine's embedded Python
 *      interpreter — no nodes, no JSON, no C++ Niagara assembly.
 *
 * Requirements:
 *   - The "Python Editor Script Plugin" must be enabled in the UE project's
 *     plugin list (Edit → Plugins → Python Editor Script Plugin).
 *   - PythonScriptPlugin must be listed in PrivateDependencyModuleNames
 *     of VFXAgentNiagara.Build.cs (already done).
 */
class VFXAGENTNIAGARA_API FVFXPythonExecutor
{
public:
	/**
	 * Execute a Python script string returned by the LLM.
	 *
	 * @param PythonCode  Raw Python source code (no markdown, no code fences).
	 * @return            True if the script ran without a Python-level exception.
	 */
	static bool ExecutePythonScript(const FString& PythonCode);

	/**
	 * Execute a Python script and capture the Python error output.
	 *
	 * @param PythonCode  Raw Python source code.
	 * @param OutError    Populated with the Python traceback on failure.
	 * @return            True on success.
	 */
	static bool ExecutePythonScript(const FString& PythonCode, FString& OutError);

	/**
	 * Execute a Python script file on disk.
	 * Convenience wrapper that reads the file then calls ExecutePythonScript.
	 *
	 * @param FilePath  Absolute path to a .py file.
	 */
	static bool ExecutePythonFile(const FString& FilePath);

	/**
	 * Strip common LLM output artefacts from a Python code string:
	 *   - ```python ... ``` / ``` ... ``` Markdown fences
	 *   - Leading/trailing whitespace
	 *
	 * Call this before passing LLM output to ExecutePythonScript.
	 */
	static FString SanitizeLLMPythonOutput(const FString& RawLLMOutput);

	/**
	 * Returns true only when Python runtime is available and a global callable
	 * with the provided name exists in the current Python state.
	 */
	static bool CanInvokeCallbackFunction(const FString& CallbackName, FString& OutReason);

	/**
	 * Append a runtime error message to a small in-memory buffer.
	 */
	static void AppendRuntimeError(const FString& ErrorMessage);

	/**
	 * Returns buffered runtime errors as a prompt-ready text block and clears them.
	 */
	static FString ConsumeRuntimeErrorsForPrompt(int32 MaxEntries = 8);
};
