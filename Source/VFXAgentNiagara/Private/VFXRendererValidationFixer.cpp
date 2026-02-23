// DEPRECATED: VFXRendererValidationFixer.cpp
// Stubbed as part of the VFXAgent Python-first architecture refactor.
// C++ no longer validates or fixes Niagara renderer configurations directly.
#include "VFXRendererValidationFixer.h"
#include "VFXAgentLog.h"

FRendererValidationReport FVFXRendererValidationFixer::ValidateAndFixRenderers(UNiagaraEmitter* Emitter, UMaterialInterface* DefaultMaterial)
{
UE_LOG(LogVFXAgent, Warning, TEXT("FVFXRendererValidationFixer is deprecated. Use Python script execution instead."));
return FRendererValidationReport();
}

int32 FVFXRendererValidationFixer::RemoveRenderersWithNullMaterial(UNiagaraEmitter* Emitter) { return 0; }
bool  FVFXRendererValidationFixer::IsRendererValid(UNiagaraRendererProperties* Renderer)    { return false; }

UMaterialInterface* FVFXRendererValidationFixer::GetRendererMaterial(UNiagaraRendererProperties* Renderer)
{
return nullptr;
}

bool FVFXRendererValidationFixer::SetRendererMaterial(UNiagaraRendererProperties* Renderer, UMaterialInterface* Material)
{
return false;
}

int32 FVFXRendererValidationFixer::CountValidRenderers(UNiagaraEmitter* Emitter)    { return 0; }
bool  FVFXRendererValidationFixer::EnsureValidSpriteRenderer(UNiagaraEmitter* Emitter, UMaterialInterface* DefaultMaterial) { return false; }
