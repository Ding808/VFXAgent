#include "VFXAgentNiagaraModule.h"
#include "VFXAgentLog.h"
#include "VFXTemplateRegistry.h"
#include "Interfaces/IPluginManager.h"
#include "Modules/ModuleManager.h"
#include "Misc/Paths.h"

static void LogModuleStartupDiagnostics(const TCHAR* ModuleName)
{
	const FString ModuleNameStr(ModuleName);
	FString ModuleFilename;
	if (FModuleManager::Get().QueryModule(ModuleNameStr, ModuleFilename))
	{
		UE_LOG(LogVFXAgent, Log, TEXT("[%s] QueryModule filename: %s"), ModuleName, *ModuleFilename);
	}
	else
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("[%s] QueryModule failed, module may not be registered yet"), ModuleName);
	}

	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("VFXAgent")))
	{
		const FString PluginDir = Plugin->GetBaseDir();
		const FString ExpectedDll = FPaths::Combine(PluginDir, TEXT("Binaries/Win64"), FString::Printf(TEXT("UnrealEditor-%s.dll"), ModuleName));
		UE_LOG(LogVFXAgent, Log, TEXT("[%s] PluginDir=%s"), ModuleName, *PluginDir);
		UE_LOG(LogVFXAgent, Log, TEXT("[%s] ExpectedDLL=%s Exists=%s"), ModuleName, *ExpectedDll, FPaths::FileExists(ExpectedDll) ? TEXT("true") : TEXT("false"));
	}
	else
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("[%s] Plugin 'VFXAgent' not found in IPluginManager"), ModuleName);
	}
}

#define LOCTEXT_NAMESPACE "FVFXAgentNiagaraModule"

void FVFXAgentNiagaraModule::StartupModule()
{
	UE_LOG(LogVFXAgent, Log, TEXT("VFXAgentNiagara Module Started"));
	LogModuleStartupDiagnostics(TEXT("VFXAgentNiagara"));
	FVFXTemplateRegistry::Get().Initialize(TEXT("/Game/VFX/Archetypes"));
}

void FVFXAgentNiagaraModule::ShutdownModule()
{
	UE_LOG(LogVFXAgent, Log, TEXT("VFXAgentNiagara Module Shutdown"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FVFXAgentNiagaraModule, VFXAgentNiagara)