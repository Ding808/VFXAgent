#include "NiagaraSystemGenerator.h"
#include "VFXAgentLog.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "NiagaraEmitterHandle.h"
#include "NiagaraScript.h"
#include "NiagaraParameterStore.h"
#include "NiagaraTypes.h"
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

	// Apply recipe (emitters + basic settings)
	if (!UpdateNiagaraSystem(NewSystem, Recipe))
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("Failed to apply recipe to Niagara System"));
	}

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

	UE_LOG(LogVFXAgent, Log, TEXT("Updating Niagara System from recipe (emitters=%d)"), Recipe.Emitters.Num());

	// Update basic properties
	// TODO: Update system properties through proper Niagara API
	// System->SetLooping(Recipe.bLoop);
	// System->SetDurationSeconds(Recipe.Duration);
	// System->SetWarmupTime(Recipe.WarmupTime);

	if (Recipe.Emitters.Num() <= 0)
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("UpdateNiagaraSystem: Recipe has no emitters"));
		return false;
	}

#if WITH_EDITOR
	// Clear existing emitters.
	{
		// RemoveEmitterHandle takes a handle reference in UE 5.5.
		TArray<FNiagaraEmitterHandle> HandlesCopy = System->GetEmitterHandles();
		for (const FNiagaraEmitterHandle& Handle : HandlesCopy)
		{
			System->RemoveEmitterHandle(Handle);
		}
	}

	for (int32 Index = 0; Index < Recipe.Emitters.Num(); ++Index)
	{
		const FVFXEmitterRecipe& EmitterRecipe = Recipe.Emitters[Index];
		UNiagaraEmitter* EmitterAsset = CreateBasicEmitter(EmitterRecipe, System);
		if (!EmitterAsset)
		{
			UE_LOG(LogVFXAgent, Warning, TEXT("Failed to create emitter %d"), Index);
			continue;
		}

		const FString EmitterNameStr = FString::Printf(TEXT("%s_%s_%02d"), *System->GetName(), *EmitterRecipe.RendererType, Index);
		const FGuid VersionGuid = EmitterAsset->GetExposedVersion().VersionGuid;
		System->AddEmitterHandle(*EmitterAsset, FName(*EmitterNameStr), VersionGuid);
	}

	System->RequestCompile(false);
	System->MarkPackageDirty();
	return true;
#else
	UE_LOG(LogVFXAgent, Error, TEXT("UpdateNiagaraSystem requires editor"));
	return false;
#endif
}

UNiagaraEmitter* UNiagaraSystemGenerator::CreateBasicEmitter(
	const FVFXEmitterRecipe& EmitterRecipe,
	UNiagaraSystem* ParentSystem)
{
	if (!ParentSystem)
	{
		return nullptr;
	}

#if WITH_EDITOR
	FModuleManager::LoadModuleChecked<IModuleInterface>(TEXT("NiagaraEditor"));
	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));

	const FString SystemPackageName = ParentSystem->GetOutermost() ? ParentSystem->GetOutermost()->GetName() : FString();
	const FString FolderPath = SystemPackageName.IsEmpty() ? TEXT("/Game/VFXAgent/Generated") : FPackageName::GetLongPackagePath(SystemPackageName);
	const FString BaseEmitterName = FString::Printf(TEXT("%s_%s_Emitter"), *ParentSystem->GetName(), *EmitterRecipe.RendererType);
	const FString DesiredPath = FolderPath / BaseEmitterName;

	FString UniquePackageName;
	FString UniqueAssetName;
	AssetToolsModule.Get().CreateUniqueAssetName(DesiredPath, TEXT(""), UniquePackageName, UniqueAssetName);
	const FString UniquePackagePath = FPackageName::GetLongPackagePath(UniquePackageName);

	UClass* FactoryClass = StaticLoadClass(UFactory::StaticClass(), nullptr, TEXT("/Script/NiagaraEditor.NiagaraEmitterFactoryNew"));
	if (!FactoryClass)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to load NiagaraEmitterFactoryNew class"));
		return nullptr;
	}

	UFactory* Factory = NewObject<UFactory>(GetTransientPackage(), FactoryClass);
	if (!Factory)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to instantiate NiagaraEmitterFactoryNew"));
		return nullptr;
	}

	UObject* CreatedAsset = AssetToolsModule.Get().CreateAsset(UniqueAssetName, UniquePackagePath, UNiagaraEmitter::StaticClass(), Factory);
	UNiagaraEmitter* NewEmitter = Cast<UNiagaraEmitter>(CreatedAsset);
	if (!NewEmitter)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to create Niagara Emitter asset"));
		return nullptr;
	}

	NewEmitter->MarkPackageDirty();

	// Best-effort: push recipe values into scripts' rapid-iteration parameters.
	// This avoids needing pre-made template assets, and works as long as the emitter has the default SpawnRate/Initialize modules.
	{
		TArray<UNiagaraScript*> Scripts;
		ForEachObjectWithOuter(NewEmitter, [&Scripts](UObject* Obj)
		{
			if (UNiagaraScript* Script = Cast<UNiagaraScript>(Obj))
			{
				Scripts.AddUnique(Script);
			}
		}, true);

		auto TrySetFloat = [](FNiagaraParameterStore& Store, const FString& NameContains, float Value) -> bool
		{
			for (const FNiagaraVariableWithOffset& ParamWithOffset : Store.ReadParameterVariables())
			{
				if (ParamWithOffset.GetType() != FNiagaraTypeDefinition::GetFloatDef())
				{
					continue;
				}
				const FString VarName = ParamWithOffset.GetName().ToString();
				if (!VarName.Contains(NameContains, ESearchCase::IgnoreCase))
				{
					continue;
				}

				FNiagaraVariable Param(ParamWithOffset.GetType(), ParamWithOffset.GetName());
				return Store.SetParameterData(reinterpret_cast<const uint8*>(&Value), Param, false);
			}
			return false;
		};

		auto TrySetInt = [](FNiagaraParameterStore& Store, const FString& NameContains, int32 Value) -> bool
		{
			for (const FNiagaraVariableWithOffset& ParamWithOffset : Store.ReadParameterVariables())
			{
				if (ParamWithOffset.GetType() != FNiagaraTypeDefinition::GetIntDef())
				{
					continue;
				}
				const FString VarName = ParamWithOffset.GetName().ToString();
				if (!VarName.Contains(NameContains, ESearchCase::IgnoreCase))
				{
					continue;
				}

				FNiagaraVariable Param(ParamWithOffset.GetType(), ParamWithOffset.GetName());
				return Store.SetParameterData(reinterpret_cast<const uint8*>(&Value), Param, false);
			}
			return false;
		};

		auto TrySetColor = [](FNiagaraParameterStore& Store, const FString& NameContains, const FLinearColor& Value) -> bool
		{
			for (const FNiagaraVariableWithOffset& ParamWithOffset : Store.ReadParameterVariables())
			{
				const FString VarName = ParamWithOffset.GetName().ToString();
				if (!VarName.Contains(NameContains, ESearchCase::IgnoreCase))
				{
					continue;
				}

				// Niagara commonly uses ColorDef or Vec4Def for colors.
				if (ParamWithOffset.GetType() == FNiagaraTypeDefinition::GetColorDef())
				{
					FNiagaraVariable Param(ParamWithOffset.GetType(), ParamWithOffset.GetName());
					return Store.SetParameterData(reinterpret_cast<const uint8*>(&Value), Param, false);
				}
				if (ParamWithOffset.GetType() == FNiagaraTypeDefinition::GetVec4Def())
				{
					const FVector4f V(Value.R, Value.G, Value.B, Value.A);
					FNiagaraVariable Param(ParamWithOffset.GetType(), ParamWithOffset.GetName());
					return Store.SetParameterData(reinterpret_cast<const uint8*>(&V), Param, false);
				}
			}
			return false;
		};

		for (UNiagaraScript* Script : Scripts)
		{
			if (!Script)
			{
				continue;
			}

			FNiagaraParameterStore& Store = Script->RapidIterationParameters;

			// Spawn rate tends to be in EmitterUpdate scripts.
			TrySetFloat(Store, TEXT("SpawnRate"), FMath::Max(0.0f, EmitterRecipe.SpawnRate));
			// Burst count often appears as an int param.
			if (EmitterRecipe.BurstCount > 0)
			{
				TrySetInt(Store, TEXT("Burst"), EmitterRecipe.BurstCount);
			}
			// Lifetime and Color typically appear in Initialize Particle.
			TrySetFloat(Store, TEXT("Lifetime"), FMath::Max(0.01f, EmitterRecipe.Lifetime));
			TrySetColor(Store, TEXT("Color"), EmitterRecipe.Color);

			Script->MarkPackageDirty();
		}

		if (Scripts.Num() == 0)
		{
			UE_LOG(LogVFXAgent, Warning, TEXT("CreateBasicEmitter: No UNiagaraScript subobjects found; cannot apply SpawnRate/Lifetime/Color overrides"));
		}
	}

	if (UPackage* Pkg = NewEmitter->GetOutermost())
	{
		Pkg->MarkPackageDirty();

		const FString SavedPackagePath = Pkg->GetName();
		FString PackageFilename = FPackageName::LongPackageNameToFilename(SavedPackagePath, FPackageName::GetAssetPackageExtension());
		const FString PackageDir = FPaths::GetPath(PackageFilename);
		if (!PackageDir.IsEmpty())
		{
			IFileManager::Get().MakeDirectory(*PackageDir, true);
		}

		FSavePackageArgs SaveArgs;
		SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
		SaveArgs.bForceByteSwapping = false;
		SaveArgs.bWarnOfLongFilename = true;

		const bool bSaved = UPackage::SavePackage(Pkg, NewEmitter, *PackageFilename, SaveArgs);
		if (!bSaved)
		{
			UE_LOG(LogVFXAgent, Warning, TEXT("Failed to save emitter package: %s"), *PackageFilename);
		}
	}

	return NewEmitter;
#else
	return nullptr;
#endif
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