#include "VFXRendererValidationFixer.h"
#include "VFXAgentLog.h"
#include "NiagaraEmitter.h"
#include "NiagaraRendererProperties.h"
#include "NiagaraSpriteRendererProperties.h"
#include "NiagaraRibbonRendererProperties.h"
#include "NiagaraLightRendererProperties.h"
#include "NiagaraMeshRendererProperties.h"
#include "Materials/MaterialInterface.h"
#include "UObject/UnrealType.h"
#include "Runtime/Launch/Resources/Version.h"

static bool ResolveRendererArrayProperty(UNiagaraEmitter* Emitter, void*& OutContainer, FArrayProperty*& OutArrayProp)
{
	OutContainer = Emitter;
	OutArrayProp = nullptr;

	if (!Emitter)
	{
		return false;
	}

	OutArrayProp = FindFProperty<FArrayProperty>(Emitter->GetClass(), TEXT("RendererProperties"));
	if (OutArrayProp)
	{
		return true;
	}

#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5
	if (FVersionedNiagaraEmitterData* EmitterData = Emitter->GetLatestEmitterData())
	{
		OutContainer = EmitterData;
		OutArrayProp = FindFProperty<FArrayProperty>(FVersionedNiagaraEmitterData::StaticStruct(), TEXT("RendererProperties"));
		if (OutArrayProp)
		{
			return true;
		}
	}
#endif

	OutContainer = nullptr;
	return false;
}

static UMaterialInterface* GetMaterialFromStruct(void* StructPtr, UStruct* Struct)
{
	if (!StructPtr || !Struct)
	{
		return nullptr;
	}

	for (TFieldIterator<FObjectPropertyBase> It(Struct); It; ++It)
	{
		FObjectPropertyBase* Prop = *It;
		if (!Prop)
		{
			continue;
		}
		if (Prop->PropertyClass->IsChildOf(UMaterialInterface::StaticClass()) && Prop->GetName().Contains(TEXT("Material")))
		{
			return Cast<UMaterialInterface>(Prop->GetObjectPropertyValue_InContainer(StructPtr));
		}
	}

	return nullptr;
}

static bool SetMaterialOnStruct(void* StructPtr, UStruct* Struct, UMaterialInterface* Material)
{
	if (!StructPtr || !Struct || !Material)
	{
		return false;
	}

	for (TFieldIterator<FObjectPropertyBase> It(Struct); It; ++It)
	{
		FObjectPropertyBase* Prop = *It;
		if (!Prop)
		{
			continue;
		}
		if (Prop->PropertyClass->IsChildOf(UMaterialInterface::StaticClass()) && Prop->GetName().Contains(TEXT("Material")))
		{
			Prop->SetObjectPropertyValue_InContainer(StructPtr, Material);
			return true;
		}
	}

	return false;
}

FRendererValidationReport FVFXRendererValidationFixer::ValidateAndFixRenderers(UNiagaraEmitter* Emitter, UMaterialInterface* DefaultMaterial)
{
	FRendererValidationReport Report;
	
	if (!Emitter)
	{
		Report.Warnings.Add(TEXT("Null emitter"));
		return Report;
	}
	
	TArray<UNiagaraRendererProperties*> Renderers = GetRenderers(Emitter);
	Report.TotalRenderers = Renderers.Num();
	
	UE_LOG(LogVFXAgent, Log, TEXT("Renderer Validation: Found %d renderers"), Report.TotalRenderers);
	
	// Pass 1: Remove invalid renderers
	TArray<UNiagaraRendererProperties*> ToRemove;
	for (UNiagaraRendererProperties* Renderer : Renderers)
	{
		if (!Renderer)
		{
			continue;
		}
		
		if (!IsRendererValid(Renderer))
		{
			UE_LOG(LogVFXAgent, Warning, TEXT("  Found invalid renderer: %s (material is null)"), *Renderer->GetClass()->GetName());
			ToRemove.Add(Renderer);
			Report.InvalidRenderersRemoved++;
			Report.RemovedRendererTypes.Add(Renderer->GetClass()->GetName());
		}
	}
	
	// Remove invalid renderers
	for (UNiagaraRendererProperties* Renderer : ToRemove)
	{
		RemoveRenderer(Emitter, Renderer);
	}
	
	// Refresh renderer list after removal
	Renderers = GetRenderers(Emitter);
	
	// Pass 2: Fix renderers that can be fixed
	for (UNiagaraRendererProperties* Renderer : Renderers)
	{
		if (!Renderer) continue;
		
		UMaterialInterface* CurrentMaterial = GetRendererMaterial(Renderer);
		if (!CurrentMaterial && DefaultMaterial)
		{
			UE_LOG(LogVFXAgent, Log, TEXT("  Assigning default material to renderer: %s"), *Renderer->GetClass()->GetName());
			SetRendererMaterial(Renderer, DefaultMaterial);
			Report.RenderersFixed++;
			Report.FixedRendererTypes.Add(Renderer->GetClass()->GetName());
		}
	}
	
	// Final validation
	Report.bHasValidRenderer = (CountValidRenderers(Emitter) > 0);
	
	if (!Report.bHasValidRenderer && DefaultMaterial)
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("  No valid renderers found, creating sprite renderer"));
		if (EnsureValidSpriteRenderer(Emitter, DefaultMaterial))
		{
			Report.bHasValidRenderer = true;
			Report.RenderersFixed++;
			Report.FixedRendererTypes.Add(TEXT("Created SpriteRenderer"));
		}
	}
	
	// Generate summary
	Report.Summary = FString::Printf(
		TEXT("Renderers: %d total, %d removed (invalid), %d fixed. Valid: %s"),
		Report.TotalRenderers,
		Report.InvalidRenderersRemoved,
		Report.RenderersFixed,
		Report.bHasValidRenderer ? TEXT("YES") : TEXT("NO")
	);
	
	UE_LOG(LogVFXAgent, Log, TEXT("Renderer Validation Complete: %s"), *Report.Summary);
	
	return Report;
}

int32 FVFXRendererValidationFixer::RemoveRenderersWithNullMaterial(UNiagaraEmitter* Emitter)
{
	if (!Emitter)
		return 0;
	
	TArray<UNiagaraRendererProperties*> Renderers = GetRenderers(Emitter);
	int32 RemovedCount = 0;
	
	for (UNiagaraRendererProperties* Renderer : Renderers)
	{
		if (!Renderer) continue;
		
		UMaterialInterface* Material = GetRendererMaterial(Renderer);
		if (!Material)
		{
			RemoveRenderer(Emitter, Renderer);
			RemovedCount++;
		}
	}
	
	return RemovedCount;
}

bool FVFXRendererValidationFixer::IsRendererValid(UNiagaraRendererProperties* Renderer)
{
	if (!Renderer)
		return false;
	
	// Check if it has a valid material
	UMaterialInterface* Material = GetRendererMaterial(Renderer);
	if (!Material)
		return false;
	
	// Additional validation for sprite renderers
	if (UNiagaraSpriteRendererProperties* SpriteRenderer = Cast<UNiagaraSpriteRendererProperties>(Renderer))
	{
		// Sprite is valid if it has material
		return true;
	}
	
	// Additional validation for ribbon renderers
	if (UNiagaraRibbonRendererProperties* RibbonRenderer = Cast<UNiagaraRibbonRendererProperties>(Renderer))
	{
		// Ribbon is valid if it has material
		return true;
	}

	// Mesh renderers are valid if they have any material assigned
	if (UNiagaraMeshRendererProperties* MeshRenderer = Cast<UNiagaraMeshRendererProperties>(Renderer))
	{
		UMaterialInterface* MeshMat = GetRendererMaterial(Renderer);
		return (MeshMat != nullptr);
	}
	
	// Light renderers don't need materials
	if (Cast<UNiagaraLightRendererProperties>(Renderer))
	{
		return true;
	}
	
	// Unknown renderer type - assume valid if it has material
	return (Material != nullptr);
}

UMaterialInterface* FVFXRendererValidationFixer::GetRendererMaterial(UNiagaraRendererProperties* Renderer)
{
	if (!Renderer)
		return nullptr;
	
	// Try sprite renderer
	if (UNiagaraSpriteRendererProperties* SpriteRenderer = Cast<UNiagaraSpriteRendererProperties>(Renderer))
	{
		return SpriteRenderer->Material;
	}
	
	// Try ribbon renderer
	if (UNiagaraRibbonRendererProperties* RibbonRenderer = Cast<UNiagaraRibbonRendererProperties>(Renderer))
	{
		return RibbonRenderer->Material;
	}
	
	// Try to find Material property via reflection
	FObjectPropertyBase* MaterialProp = FindFProperty<FObjectPropertyBase>(Renderer->GetClass(), TEXT("Material"));
	if (MaterialProp)
	{
		return Cast<UMaterialInterface>(MaterialProp->GetObjectPropertyValue_InContainer(Renderer));
	}

	// Try Materials array (mesh renderer)
	FArrayProperty* MaterialsProp = FindFProperty<FArrayProperty>(Renderer->GetClass(), TEXT("Materials"));
	if (MaterialsProp)
	{
		FScriptArrayHelper Helper(MaterialsProp, MaterialsProp->ContainerPtrToValuePtr<void>(Renderer));
		if (Helper.Num() > 0)
		{
			void* ElemPtr = Helper.GetRawPtr(0);
			if (FStructProperty* StructProp = CastField<FStructProperty>(MaterialsProp->Inner))
			{
				if (UMaterialInterface* Mat = GetMaterialFromStruct(ElemPtr, StructProp->Struct))
				{
					return Mat;
				}
			}
			else if (FObjectPropertyBase* ObjProp = CastField<FObjectPropertyBase>(MaterialsProp->Inner))
			{
				UObject* Obj = ObjProp->GetObjectPropertyValue(ElemPtr);
				return Cast<UMaterialInterface>(Obj);
			}
		}
	}
	
	return nullptr;
}

bool FVFXRendererValidationFixer::SetRendererMaterial(UNiagaraRendererProperties* Renderer, UMaterialInterface* Material)
{
	if (!Renderer)
		return false;
	
	// Try sprite renderer
	if (UNiagaraSpriteRendererProperties* SpriteRenderer = Cast<UNiagaraSpriteRendererProperties>(Renderer))
	{
		SpriteRenderer->Material = Material;
		return true;
	}
	
	// Try ribbon renderer
	if (UNiagaraRibbonRendererProperties* RibbonRenderer = Cast<UNiagaraRibbonRendererProperties>(Renderer))
	{
		RibbonRenderer->Material = Material;
		return true;
	}
	
	// Try to set via reflection
	FObjectPropertyBase* MaterialProp = FindFProperty<FObjectPropertyBase>(Renderer->GetClass(), TEXT("Material"));
	if (MaterialProp)
	{
		MaterialProp->SetObjectPropertyValue_InContainer(Renderer, Material);
		return true;
	}

	// Try Materials array (mesh renderer)
	FArrayProperty* MaterialsProp = FindFProperty<FArrayProperty>(Renderer->GetClass(), TEXT("Materials"));
	if (MaterialsProp)
	{
		FScriptArrayHelper Helper(MaterialsProp, MaterialsProp->ContainerPtrToValuePtr<void>(Renderer));
		if (Helper.Num() == 0)
		{
			Helper.AddValue();
		}
		void* ElemPtr = Helper.GetRawPtr(0);
		if (FStructProperty* StructProp = CastField<FStructProperty>(MaterialsProp->Inner))
		{
			if (SetMaterialOnStruct(ElemPtr, StructProp->Struct, Material))
			{
				return true;
			}
		}
		else if (FObjectPropertyBase* ObjProp = CastField<FObjectPropertyBase>(MaterialsProp->Inner))
		{
			ObjProp->SetObjectPropertyValue(ElemPtr, Material);
			return true;
		}
	}
	
	return false;
}

int32 FVFXRendererValidationFixer::CountValidRenderers(UNiagaraEmitter* Emitter)
{
	if (!Emitter)
		return 0;
	
	TArray<UNiagaraRendererProperties*> Renderers = GetRenderers(Emitter);
	int32 ValidCount = 0;
	
	for (UNiagaraRendererProperties* Renderer : Renderers)
	{
		if (IsRendererValid(Renderer))
		{
			ValidCount++;
		}
	}
	
	return ValidCount;
}

bool FVFXRendererValidationFixer::EnsureValidSpriteRenderer(UNiagaraEmitter* Emitter, UMaterialInterface* DefaultMaterial)
{
	if (!Emitter || !DefaultMaterial)
		return false;
	
	// Check if we already have a valid sprite renderer
	TArray<UNiagaraRendererProperties*> Renderers = GetRenderers(Emitter);
	for (UNiagaraRendererProperties* Renderer : Renderers)
	{
		if (UNiagaraSpriteRendererProperties* SpriteRenderer = Cast<UNiagaraSpriteRendererProperties>(Renderer))
		{
			if (IsRendererValid(SpriteRenderer))
			{
				return true; // Already have one
			}
		}
	}
	
	// Create new sprite renderer
	UNiagaraRendererProperties* NewRenderer = AddSpriteRenderer(Emitter, DefaultMaterial);
	return (NewRenderer != nullptr);
}

TArray<UNiagaraRendererProperties*> FVFXRendererValidationFixer::GetRenderers(UNiagaraEmitter* Emitter)
{
	TArray<UNiagaraRendererProperties*> Renderers;
	
	if (!Emitter)
		return Renderers;

	void* TargetContainer = nullptr;
	FArrayProperty* ArrayProp = nullptr;
	if (!ResolveRendererArrayProperty(Emitter, TargetContainer, ArrayProp) || !TargetContainer || !ArrayProp)
		return Renderers;

	FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(TargetContainer));
	
	for (int32 i = 0; i < Helper.Num(); ++i)
	{
		if (FObjectPropertyBase* ObjProp = CastField<FObjectPropertyBase>(ArrayProp->Inner))
		{
			UObject* Obj = ObjProp->GetObjectPropertyValue(Helper.GetRawPtr(i));
			if (UNiagaraRendererProperties* Renderer = Cast<UNiagaraRendererProperties>(Obj))
			{
				Renderers.Add(Renderer);
			}
		}
	}
	
	return Renderers;
}

void FVFXRendererValidationFixer::RemoveRenderer(UNiagaraEmitter* Emitter, UNiagaraRendererProperties* RendererToRemove)
{
	if (!Emitter || !RendererToRemove)
		return;

	void* TargetContainer = nullptr;
	FArrayProperty* ArrayProp = nullptr;
	if (!ResolveRendererArrayProperty(Emitter, TargetContainer, ArrayProp) || !TargetContainer || !ArrayProp)
		return;

	FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(TargetContainer));
	
	for (int32 i = Helper.Num() - 1; i >= 0; --i)
	{
		if (FObjectPropertyBase* ObjProp = CastField<FObjectPropertyBase>(ArrayProp->Inner))
		{
			UObject* Obj = ObjProp->GetObjectPropertyValue(Helper.GetRawPtr(i));
			if (Obj == RendererToRemove)
			{
				UE_LOG(LogVFXAgent, Log, TEXT("    Removing renderer at index %d"), i);
				Helper.RemoveValues(i, 1);
			}
		}
	}
}

UNiagaraRendererProperties* FVFXRendererValidationFixer::AddSpriteRenderer(UNiagaraEmitter* Emitter, UMaterialInterface* Material)
{
	if (!Emitter)
		return nullptr;
	
	UNiagaraSpriteRendererProperties* SpriteRenderer = NewObject<UNiagaraSpriteRendererProperties>(
		Emitter,
		UNiagaraSpriteRendererProperties::StaticClass(),
		NAME_None,
		RF_Transactional
	);
	
	if (!SpriteRenderer)
		return nullptr;
	
	SpriteRenderer->Material = Material;
	
	// Add to RendererProperties array
	void* TargetContainer = nullptr;
	FArrayProperty* ArrayProp = nullptr;
	if (ResolveRendererArrayProperty(Emitter, TargetContainer, ArrayProp) && TargetContainer && ArrayProp)
	{
		FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(TargetContainer));
		const int32 NewIndex = Helper.AddValue();
		
		if (FObjectPropertyBase* ObjProp = CastField<FObjectPropertyBase>(ArrayProp->Inner))
		{
			ObjProp->SetObjectPropertyValue(Helper.GetRawPtr(NewIndex), SpriteRenderer);
		}
	}
	
	return SpriteRenderer;
}
