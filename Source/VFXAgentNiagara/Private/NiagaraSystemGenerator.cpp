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
	FString PackagePath = OutputPath / SystemName;
	UPackage* Package = CreatePackage(*PackagePath);
	if (!Package)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to create package: %s"), *PackagePath);
		return nullptr;
	}

	// Create the Niagara System object
	UNiagaraSystem* NewSystem = NewObject<UNiagaraSystem>(Package, FName(*SystemName), RF_Public | RF_Standalone);
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

	// Save the package
	FString PackageFilename = FPackageName::LongPackageNameToFilename(PackagePath, FPackageName::GetAssetPackageExtension());
	
	// Mark package as dirty to force save
	Package->MarkPackageDirty();
	
	// Use the simple SavePackage call with filename
	if (UPackage::SavePackage(Package, NewSystem, RF_Public | RF_Standalone, *PackageFilename, GError, nullptr, true))
	{
		UE_LOG(LogVFXAgent, Log, TEXT("Successfully saved Niagara System to: %s"), *PackageFilename);
		return NewSystem;
	}
	else
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to save Niagara System"));
		return nullptr;
	}
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