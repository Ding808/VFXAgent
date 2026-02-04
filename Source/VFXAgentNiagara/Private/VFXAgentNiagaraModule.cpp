#include "VFXAgentNiagaraModule.h"
#include "VFXAgentLog.h"
#include "VFXTemplateRegistry.h"

#define LOCTEXT_NAMESPACE "FVFXAgentNiagaraModule"

void FVFXAgentNiagaraModule::StartupModule()
{
	UE_LOG(LogVFXAgent, Log, TEXT("VFXAgentNiagara Module Started"));
	FVFXTemplateRegistry::Get().Initialize(TEXT("/Game/VFX/Archetypes"));
}

void FVFXAgentNiagaraModule::ShutdownModule()
{
	UE_LOG(LogVFXAgent, Log, TEXT("VFXAgentNiagara Module Shutdown"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FVFXAgentNiagaraModule, VFXAgentNiagara)