#include "NiagaraSystemGenerator.h"
#include "VFXAgentLog.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "NiagaraScriptSourceBase.h"
#include "Particles/ParticleSystemComponent.h"
#include "Misc/Paths.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "Factories/Factory.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "UNiagaraSystemGenerator"

UNiagaraSystem* UNiagaraSystemGenerator::GenerateNiagaraSystem(
	const FString& SystemName,
	const FString& OutputPath,
	const FVFXRecipe& Recipe)
{
	UE_LOG(LogVFXAgent, Log, TEXT("Generating Niagara System: %s at %s"), *SystemName, *OutputPath);

	if (Recipe.Emitters.Num() == 0)
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("Recipe has no emitters, cannot generate system"));
		return nullptr;
	}

	// Create package
	// Validate and sanitize inputs
	FString SafeOutputPath = OutputPath;
	if (!SafeOutputPath.StartsWith(TEXT("/Game")))
	{
		SafeOutputPath = FString::Printf(TEXT("/Game/%s"), *SafeOutputPath.TrimStartAndEnd());
	}

	FString SafeSystemName = SystemName;
	if (SafeSystemName.IsEmpty())
	{
		SafeSystemName = TEXT("VFX_GeneratedSystem");
	}
	// Replace invalid characters in name
	for (int32 i = 0; i < SafeSystemName.Len(); ++i)
	{
		TCHAR& C = SafeSystemName[i];
		if (!(FChar::IsAlnum(C) || C == TCHAR('_')))
		{
			C = TCHAR('_');
		}
	}

	FString PackagePath = SafeOutputPath / SafeSystemName;
	UE_LOG(LogVFXAgent, Log, TEXT("PackagePath computed: %s"), *PackagePath);
	UPackage* Package = CreatePackage(*PackagePath);
	if (!Package)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to create package: %s"), *PackagePath);
		return nullptr;
	}

	// Create the Niagara System object
	// Use the sanitized system name when creating the UObject to avoid invalid name characters
	UNiagaraSystem* NewSystem = NewObject<UNiagaraSystem>(Package, FName(*SafeSystemName), RF_Public | RF_Standalone);
	UE_LOG(LogVFXAgent, Log, TEXT("NewSystem pointer after NewObject: %p (Name: %s)"), NewSystem, *SafeSystemName);
	if (!NewSystem)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to create UNiagaraSystem object"));
		return nullptr;
	}

	// Set basic properties
	// TODO: Set Looping, Duration, WarmupTime through Niagara system properties
	// The Niagara API may require different approaches in UE5.5+

	// TODO: Set bounds
	// NewSystem->SetSystemBounds(FBox(FVector::ZeroVector, Recipe.Bounds));

	UE_LOG(LogVFXAgent, Log, TEXT("Created base Niagara System: %s"), *SystemName);

	// TODO: Add emitters from recipe
	// For now, just mark the system as needing saving
	NewSystem->MarkPackageDirty();

	// Register the new asset with the asset registry and mark package dirty.
	// Register the asset with the Asset Registry if available
	if (FModuleManager::Get().IsModuleLoaded("AssetRegistry"))
	{
		FAssetRegistryModule* AssetRegistryModulePtr = FModuleManager::GetModulePtr<FAssetRegistryModule>("AssetRegistry");
		if (AssetRegistryModulePtr)
		{
			AssetRegistryModulePtr->Get().AssetCreated(NewSystem);
		}
		else
		{
			UE_LOG(LogVFXAgent, Warning, TEXT("AssetRegistry module pointer null despite IsModuleLoaded reporting true"));
		}
	}
	else
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("AssetRegistry module not loaded; asset not registered"));
	}

	Package->MarkPackageDirty();
	UE_LOG(LogVFXAgent, Log, TEXT("Registered Niagara System asset: %s"), *PackagePath);

	return NewSystem;
}

bool UNiagaraSystemGenerator::UpdateNiagaraSystem(UNiagaraSystem* System, const FVFXRecipe& Recipe)
{
	if (!System)
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("UpdateNiagaraSystem: System is null"));
		return false;
	}

	UE_LOG(LogVFXAgent, Log, TEXT("Updating Niagara System"));

	// Update basic properties
	// TODO: Update system properties through proper Niagara API
	// System->SetLooping(Recipe.bLoop);
	// System->SetDurationSeconds(Recipe.Duration);
	// System->SetWarmupTime(Recipe.WarmupTime);

	// TODO: Update emitters and other properties
	System->MarkPackageDirty();

	return true;
}

UNiagaraEmitter* UNiagaraSystemGenerator::CreateBasicEmitter(
	const FVFXEmitterRecipe& EmitterRecipe,
	UNiagaraSystem* ParentSystem)
{
	// TODO: Implement emitter creation
	UE_LOG(LogVFXAgent, Log, TEXT("CreateBasicEmitter: Not yet implemented"));
	return nullptr;
}

bool UNiagaraSystemGenerator::BindMaterialToEmitter(
	class UNiagaraEmitter* Emitter,
	const FVFXMaterialRecipe& MaterialRecipe)
{
	// TODO: Implement material binding
	UE_LOG(LogVFXAgent, Log, TEXT("BindMaterialToEmitter: Not yet implemented"));
	return false;
}

UMaterialInstanceConstant* UNiagaraSystemGenerator::GetOrCreateBasicMaterial(
	const FString& Path,
	const FVFXMaterialRecipe& MaterialRecipe)
{
	// TODO: Implement material creation/retrieval
	UE_LOG(LogVFXAgent, Log, TEXT("GetOrCreateBasicMaterial: Not yet implemented"));
	return nullptr;
}

#undef LOCTEXT_NAMESPACE