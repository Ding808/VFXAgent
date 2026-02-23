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
	 * @return            True if the script was accepted and executed without
	 *                    a Python-level exception; false otherwise.
	 *
	 * Note: "accepted" means IPythonScriptPlugin::ExecPythonCommand returned
	 * true. It does NOT guarantee that the generated Niagara asset is
	 * semantically correct — check the Output Log for runtime errors.
	 */
	static bool ExecutePythonScript(const FString& PythonCode);

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
};
