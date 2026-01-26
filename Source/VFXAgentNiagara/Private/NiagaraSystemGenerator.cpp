#include "NiagaraSystemGenerator.h"
#include "VFXAgentLog.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "Misc/Paths.h"
#include "Misc/PackageName.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "Factories/Factory.h"
#include "Modules/ModuleManager.h"
#include "UObject/SavePackage.h"
#include "HAL/FileManager.h"
#include "Runtime/Launch/Resources/Version.h"

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

	UNiagaraSystem* NewSystem = nullptr;
#if WITH_EDITOR
	// Create the Niagara system via AssetTools + Niagara's factory to ensure the asset is fully initialized.
	// Avoid referencing UNiagaraSystemFactoryNew directly (it may not be exported for linking in some setups).
	FModuleManager::LoadModuleChecked<IModuleInterface>(TEXT("NiagaraEditor"));
	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));

	FString UniquePackageName;
	FString UniqueAssetName;
	AssetToolsModule.Get().CreateUniqueAssetName(PackagePath, TEXT(""), UniquePackageName, UniqueAssetName);
	const FString UniquePackagePath = FPackageName::GetLongPackagePath(UniquePackageName);

	UClass* FactoryClass = StaticLoadClass(UFactory::StaticClass(), nullptr, TEXT("/Script/NiagaraEditor.NiagaraSystemFactoryNew"));
	if (!FactoryClass)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to load NiagaraSystemFactoryNew class. Is the NiagaraEditor module available?"));
		return nullptr;
	}

	UFactory* Factory = NewObject<UFactory>(GetTransientPackage(), FactoryClass);
	if (!Factory)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to instantiate NiagaraSystemFactoryNew"));
		return nullptr;
	}

	UE_LOG(LogVFXAgent, Log, TEXT("Creating Niagara System asset via AssetTools: %s"), *UniqueAssetName);
	UObject* CreatedAsset = AssetToolsModule.Get().CreateAsset(UniqueAssetName, UniquePackagePath, UNiagaraSystem::StaticClass(), Factory);
	NewSystem = Cast<UNiagaraSystem>(CreatedAsset);
	if (!NewSystem)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to create Niagara System asset via AssetTools"));
		return nullptr;
	}
#else
	UE_LOG(LogVFXAgent, Error, TEXT("Niagara System generation requires editor"));
	return nullptr;
#endif

	UE_LOG(LogVFXAgent, Log, TEXT("Successfully created UNiagaraSystem asset at %p"), NewSystem);

	// Set basic properties
	// TODO: Set Looping, Duration, WarmupTime through Niagara system properties
	// The Niagara API may require different approaches in UE5.5+

	// TODO: Set bounds
	// NewSystem->SetSystemBounds(FBox(FVector::ZeroVector, Recipe.Bounds));

	// Mark the system and package as needing save
	UPackage* OutermostPackage = NewSystem->GetOutermost();
	NewSystem->MarkPackageDirty();
	if (OutermostPackage)
	{
		OutermostPackage->MarkPackageDirty();
	}

	UE_LOG(LogVFXAgent, Log, TEXT("Created base Niagara System: %s"), *SafeSystemName);

	// TODO: Add emitters from recipe
	// For now, the system is created with default properties

	// Save the package
	if (!OutermostPackage)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to resolve package for Niagara System"));
		return nullptr;
	}

	const FString SavedPackagePath = OutermostPackage->GetName();
	FString PackageFilename = FPackageName::LongPackageNameToFilename(SavedPackagePath, FPackageName::GetAssetPackageExtension());
	UE_LOG(LogVFXAgent, Log, TEXT("Saving package to: %s"), *PackageFilename);

	// Ensure the output directory exists
	const FString PackageDir = FPaths::GetPath(PackageFilename);
	if (!PackageDir.IsEmpty())
	{
		IFileManager::Get().MakeDirectory(*PackageDir, true);
	}

	// Use the correct SavePackage API for UE5.x
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
	SaveArgs.bForceByteSwapping = false;
	SaveArgs.bWarnOfLongFilename = true;

	const bool bSaved = UPackage::SavePackage(OutermostPackage, NewSystem, *PackageFilename, SaveArgs);

	if (bSaved)
	{
		UE_LOG(LogVFXAgent, Log, TEXT("Successfully saved Niagara System to: %s"), *PackageFilename);
		OutermostPackage->SetDirtyFlag(false);
		return NewSystem;
	}

	UE_LOG(LogVFXAgent, Error, TEXT("Failed to save Niagara System to: %s"), *PackageFilename);
	return nullptr;
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