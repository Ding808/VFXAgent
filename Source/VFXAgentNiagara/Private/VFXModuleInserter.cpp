// DEPRECATED: VFXModuleInserter.cpp
// Stubbed as part of the VFXAgent Python-first architecture refactor.
// C++ no longer inserts Niagara graph modules directly.
#include "VFXModuleInserter.h"
#include "VFXAgentLog.h"

FModuleInsertResult FVFXModuleInserter::InsertModules(UNiagaraEmitter* Emitter, const TArray<FMotionModuleDescriptor>& Modules, const FString& DebugTag)
{
UE_LOG(LogVFXAgent, Warning, TEXT("FVFXModuleInserter::InsertModules is deprecated. Use Python script execution instead."));
FModuleInsertResult Result;
Result.bSuccess = false;
Result.ErrorMessage = TEXT("Deprecated: C++ module insertion removed. Use Python executor.");
return Result;
}

bool FVFXModuleInserter::InsertModuleByPath(UNiagaraEmitter* Emitter, const FMotionModuleDescriptor& Module, FString& OutError)
{
OutError = TEXT("Deprecated: C++ module insertion removed. Use Python executor.");
return false;
}
