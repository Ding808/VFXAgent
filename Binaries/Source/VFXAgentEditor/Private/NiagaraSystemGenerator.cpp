#include "NiagaraSystemGenerator.h"
#include "VFXAgentLog.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "Particles/ParticleSystemComponent.h"
#include "Misc/Paths.h"
#include "Misc/PackageName.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "Factories/Factory.h"
#include "Serialization/ObjectWriter.h"
#include "UObject/SavePackage.h"

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

	// Create package and validate
	FString SafeOutputPath = OutputPath.TrimStartAndEnd();
	if (SafeOutputPath.IsEmpty())
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Output path is empty - cannot compute package path"));
		return nullptr;
	}

	if (!SafeOutputPath.StartsWith(TEXT("/Game")))
	{
		SafeOutputPath = FString::Printf(TEXT("/Game/%s"), *SafeOutputPath);
	}

	// Sanitize system name
	FString SafeSystemName = SystemName;
	if (SafeSystemName.IsEmpty())
	{
		SafeSystemName = TEXT("VFX_GeneratedSystem");
	}
	for (int32 i = 0; i < SafeSystemName.Len(); ++i)
	{
		TCHAR& C = SafeSystemName[i];
		if (!(FChar::IsAlnum(C) || C == TCHAR('_')))
		{
			C = TCHAR('_');
		}
	}

	FString PackagePath = SafeOutputPath / SafeSystemName;
	if (!FPackageName::IsValidLongPackageName(PackagePath))
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Computed package path is not valid: %s"), *PackagePath);
		return nullptr;
	}

	UE_LOG(LogVFXAgent, Log, TEXT("Creating package at: %s"), *PackagePath);
	UPackage* Package = CreatePackage(*PackagePath);
	if (!Package)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to create package: %s"), *PackagePath);
		return nullptr;
	}

	UE_LOG(LogVFXAgent, Log, TEXT("Creating Niagara System object with name: %s"), *SafeSystemName);
	// Create the Niagara System object
	UNiagaraSystem* NewSystem = NewObject<UNiagaraSystem>(Package, FName(*SafeSystemName), RF_Public | RF_Standalone);
	if (!NewSystem)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to create UNiagaraSystem object"));
		return nullptr;
	}

	UE_LOG(LogVFXAgent, Log, TEXT("Successfully created UNiagaraSystem object at %p"), NewSystem);

	// Set basic properties
	// TODO: Set Looping, Duration, WarmupTime through Niagara system properties
	// The Niagara API may require different approaches in UE5.5+

	// TODO: Set bounds
	// NewSystem->SetSystemBounds(FBox(FVector::ZeroVector, Recipe.Bounds));

	// Mark the system and package as needing save
	NewSystem->MarkPackageDirty();
	Package->MarkPackageDirty();

	UE_LOG(LogVFXAgent, Log, TEXT("Created base Niagara System: %s"), *SafeSystemName);

	// TODO: Add emitters from recipe
	// For now, the system is created with default properties

	// Save the package
	FString PackageFilename = FPackageName::LongPackageNameToFilename(PackagePath, FPackageName::GetAssetPackageExtension());
	UE_LOG(LogVFXAgent, Log, TEXT("Saving package to: %s"), *PackageFilename);
	
	// Use the correct SavePackage API for UE5.x
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
	SaveArgs.bForceByteSwapping = false;
	SaveArgs.bWarnOfLongFilenames = true;
	SaveArgs.SaveFilter = SAVE_NoError;
	
	if (UPackage::SavePackage(Package, NewSystem, SaveArgs))
	{
		UE_LOG(LogVFXAgent, Log, TEXT("Successfully saved Niagara System to: %s"), *PackageFilename);
		// Force asset registry to recognize the new asset
		FAssetRegistryModule::AssetCreated(NewSystem);
		return NewSystem;
	}
	else
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to save Niagara System to: %s"), *PackageFilename);
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