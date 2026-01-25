#include "VFXAgentNiagaraModule.h"
#include "VFXAgentLog.h"

// Define log category for this module
DEFINE_LOG_CATEGORY(LogVFXAgent);

#define LOCTEXT_NAMESPACE "FVFXAgentNiagaraModule"

void FVFXAgentNiagaraModule::StartupModule()
{
	UE_LOG(LogVFXAgent, Log, TEXT("VFXAgentNiagara Module Started"));
}

void FVFXAgentNiagaraModule::ShutdownModule()
{
	UE_LOG(LogVFXAgent, Log, TEXT("VFXAgentNiagara Module Shutdown"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FVFXAgentNiagaraModule, VFXAgentNiagara)