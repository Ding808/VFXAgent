#include "NiagaraSystemGenerator.h"
#include "VFXAgentLog.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "NiagaraScriptSourceBase.h"
#include "NiagaraScript.h"
#include "Particles/ParticleSystemComponent.h"
#include "Misc/Paths.h"
#include "Misc/PackageName.h"
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

	// Sanitize system name for package creation
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

	UE_LOG(LogVFXAgent, Log, TEXT("PackagePath computed: %s"), *PackagePath);
	UPackage* Package = CreatePackage(*PackagePath);
	if (!Package)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to create package: %s"), *PackagePath);
		return nullptr;
	}

	// Create the Niagara System object
	UNiagaraSystem* NewSystem = NewObject<UNiagaraSystem>(Package, FName(*SafeSystemName), RF_Public | RF_Standalone);
	UE_LOG(LogVFXAgent, Log, TEXT("NewSystem pointer after NewObject: %p (Name: %s)"), NewSystem, *SafeSystemName);
	if (!NewSystem)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to create UNiagaraSystem object"));
		return nullptr;
	}

	// Initialize system scripts - use built-in GetSystemSpawnScript/GetSystemUpdateScript
	UNiagaraScript* SystemSpawnScript = NewSystem->GetSystemSpawnScript();
	UNiagaraScript* SystemUpdateScript = NewSystem->GetSystemUpdateScript();

	if (!SystemSpawnScript || !SystemUpdateScript)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to get system scripts from Niagara system"));
		return nullptr;
	}

	// Create and assign script source
	UNiagaraScriptSourceBase* SpawnScriptSource = NewObject<UNiagaraScriptSourceBase>(
		SystemSpawnScript, NAME_None, RF_Transactional);
	
	if (SpawnScriptSource)
	{
		SystemSpawnScript->SetLatestSource(SpawnScriptSource);
		SystemUpdateScript->SetLatestSource(SpawnScriptSource);
		UE_LOG(LogVFXAgent, Log, TEXT("Created and assigned script source to spawn and update scripts"));
	}
	else
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("Failed to create script source - system may still function"));
	}

	// Set basic properties
	// TODO: Set Looping, Duration, WarmupTime through Niagara system properties

	UE_LOG(LogVFXAgent, Log, TEXT("Created base Niagara System: %s"), *SystemName);

	// TODO: Add emitters from recipe
	// For now, just mark the system as needing saving
	if (NewSystem)
	{
		NewSystem->MarkPackageDirty();
	}
	else
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("NewSystem invalid; skipping MarkPackageDirty"));
	}

	// Mark package dirty to ensure it gets saved
	Package->MarkPackageDirty();
	UE_LOG(LogVFXAgent, Log, TEXT("Registered Niagara System asset: %s"), *PackagePath);

	// Do NOT register with AssetRegistry immediately - let the system initialization complete first
	// The asset registry will pick it up when the package is saved

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