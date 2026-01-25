#include "VFXAgentCoreModule.h"
#include "VFXAgentLog.h"

#define LOCTEXT_NAMESPACE "FVFXAgentCoreModule"

void FVFXAgentCoreModule::StartupModule()
{
	UE_LOG(LogVFXAgent, Log, TEXT("VFXAgentCore Module Started"));
}

void FVFXAgentCoreModule::ShutdownModule()
{
	UE_LOG(LogVFXAgent, Log, TEXT("VFXAgentCore Module Shutdown"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FVFXAgentCoreModule, VFXAgentCore)