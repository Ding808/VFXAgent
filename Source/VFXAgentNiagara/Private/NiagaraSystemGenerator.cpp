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
#include "UObject/UObjectGlobals.h"

static FString NormalizeSystemObjectPath(const FString& InPath)
{
	FString Path = InPath;
	Path.TrimStartAndEndInline();
	if (Path.IsEmpty())
	{
		return FString();
	}
	// If the path already looks like an object path (/Game/X/Y.Asset), keep it.
	if (Path.Contains(TEXT(".")))
	{
		return Path;
	}
	// Otherwise, append .<AssetName> where AssetName is the last segment.
	int32 LastSlash = INDEX_NONE;
	Path.FindLastChar(TCHAR('/'), LastSlash);
	const FString AssetName = (LastSlash != INDEX_NONE) ? Path.Mid(LastSlash + 1) : Path;
	if (AssetName.IsEmpty())
	{
		return Path;
	}
	return FString::Printf(TEXT("%s.%s"), *Path, *AssetName);
}

#define LOCTEXT_NAMESPACE "UNiagaraSystemGenerator"

UNiagaraSystem* UNiagaraSystemGenerator::GenerateNiagaraSystem(
	const FString& SystemName,
	const FString& OutputPath,
	const FVFXRecipe& Recipe,
	const FString& TemplateSystemPath)
{
	UE_LOG(LogVFXAgent, Log, TEXT("Generating Niagara System: %s at %s"), *SystemName, *OutputPath);

	// Load optional template system (used to clone initialized emitters so the result isn't empty).
	TemplateSystem = nullptr;
	{
		const FString ObjPath = NormalizeSystemObjectPath(TemplateSystemPath);
		if (!ObjPath.IsEmpty())
		{
			TemplateSystem = LoadObject<UNiagaraSystem>(nullptr, *ObjPath);
			if (!TemplateSystem)
			{
				UE_LOG(LogVFXAgent, Warning, TEXT("Template system not found: %s (normalized: %s)"), *TemplateSystemPath, *ObjPath);
			}
		}
	}

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

static UNiagaraEmitter* FindFirstEmitterSubobject(UNiagaraSystem* System)
{
	if (!System)
	{
		return nullptr;
	}

	UNiagaraEmitter* Found = nullptr;
	ForEachObjectWithOuter(System, [&Found](UObject* Obj)
	{
		if (Found)
		{
			return;
		}
		if (UNiagaraEmitter* E = Cast<UNiagaraEmitter>(Obj))
		{
			Found = E;
		}
	}, true);
	return Found;
}

// Helper to apply recipe parameters to an emitter's scripts (Rapid Iteration Parameters)
static void ApplyEmitterParameters(UNiagaraEmitter* Emitter, const FVFXEmitterRecipe& Recipe)
{
	if (!Emitter)
	{
		return;
	}

	TArray<UNiagaraScript*> Scripts;
	ForEachObjectWithOuter(Emitter, [&Scripts](UObject* Obj)
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
		if (!Script) continue;

		FNiagaraParameterStore& Store = Script->RapidIterationParameters;

		TrySetFloat(Store, TEXT("SpawnRate"), FMath::Max(0.0f, Recipe.SpawnRate));
		
		if (Recipe.BurstCount > 0)
		{
			TrySetInt(Store, TEXT("Burst"), Recipe.BurstCount);
		}
   
		TrySetFloat(Store, TEXT("Lifetime"), FMath::Max(0.01f, Recipe.Lifetime));
		TrySetColor(Store, TEXT("Color"), Recipe.Color);

		Script->MarkPackageDirty();
	}
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
	// Try to clone from a template emitter (preferred), otherwise fall back to factory-created emitters.
	UNiagaraEmitter* TemplateEmitter = nullptr;
	if (TemplateSystem)
	{
		TemplateEmitter = FindFirstEmitterSubobject(TemplateSystem);
	}
	if (!TemplateEmitter)
	{
		// As a fallback, if the system already contains an emitter, use it as a template.
		TemplateEmitter = FindFirstEmitterSubobject(System);
	}

	// Fallback to loading a default engine emitter if possible
	if (!TemplateEmitter)
	{
		// Try a few standard locations
		const TCHAR* FallbackPaths[] = {
			TEXT("/Niagara/Emitters/Omnidirectional/Fountain.Fountain"),
			TEXT("/Niagara/Emitters/Fountain.Fountain"),
			TEXT("/Engine/Plugins/FX/Niagara/Content/Emitters/Omnidirectional/Fountain.Fountain")
		};

		for (const TCHAR* Path : FallbackPaths)
		{
			TemplateEmitter = LoadObject<UNiagaraEmitter>(nullptr, Path);
			if (TemplateEmitter)
			{
				UE_LOG(LogVFXAgent, Log, TEXT("Loaded fallback template emitter from: %s"), Path);
				break;
			}
		}
	}

	if (!TemplateEmitter && TemplateSystem)
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("Template system loaded but contained no UNiagaraEmitter subobjects: %s"), *TemplateSystem->GetPathName());
	}


	// Clear existing emitters.
	{
		TArray<FNiagaraEmitterHandle> HandlesCopy = System->GetEmitterHandles();
		for (const FNiagaraEmitterHandle& Handle : HandlesCopy)
		{
			System->RemoveEmitterHandle(Handle);
		}
	}


	for (int32 Index = 0; Index < Recipe.Emitters.Num(); ++Index)
	{
		const FVFXEmitterRecipe& EmitterRecipe = Recipe.Emitters[Index];
		UNiagaraEmitter* TargetTemplate = nullptr;

		// 1. Try to load specific template requested by LLM
		if (!EmitterRecipe.TemplateName.IsEmpty())
		{
			// Map friendly names to potential paths
			TArray<FString> CandidatePaths;
			
			auto AddCandidate = [&](const FString& InPath) { CandidatePaths.Add(InPath); };

			if (EmitterRecipe.TemplateName.Equals(TEXT("Fountain"), ESearchCase::IgnoreCase))
			{
				AddCandidate(TEXT("/Niagara/Emitters/Omnidirectional/Fountain.Fountain"));
				AddCandidate(TEXT("/Engine/Plugins/FX/Niagara/Content/Emitters/Omnidirectional/Fountain.Fountain"));
			}
			else if (EmitterRecipe.TemplateName.Equals(TEXT("DirectionalBurst"), ESearchCase::IgnoreCase))
			{
				AddCandidate(TEXT("/Niagara/Emitters/DirectionalBurst.DirectionalBurst"));
				AddCandidate(TEXT("/Engine/Plugins/FX/Niagara/Content/Emitters/DirectionalBurst.DirectionalBurst"));
			}
			else if (EmitterRecipe.TemplateName.Equals(TEXT("OmnidirectionalBurst"), ESearchCase::IgnoreCase))
			{
				AddCandidate(TEXT("/Niagara/Emitters/Omnidirectional/OmnidirectionalBurst.OmnidirectionalBurst"));
				AddCandidate(TEXT("/Niagara/Emitters/OmnidirectionalBurst.OmnidirectionalBurst"));
				AddCandidate(TEXT("/Engine/Plugins/FX/Niagara/Content/Emitters/Omnidirectional/OmnidirectionalBurst.OmnidirectionalBurst"));
			}
			else if (EmitterRecipe.TemplateName.Equals(TEXT("HangingParticulates"), ESearchCase::IgnoreCase))
			{
				AddCandidate(TEXT("/Niagara/Emitters/HangingParticulates.HangingParticulates"));
				AddCandidate(TEXT("/Engine/Plugins/FX/Niagara/Content/Emitters/HangingParticulates.HangingParticulates"));
			}
			else if (EmitterRecipe.TemplateName.Equals(TEXT("UpwardMeshBurst"), ESearchCase::IgnoreCase))
			{
				AddCandidate(TEXT("/Niagara/Emitters/UpwardMeshBurst.UpwardMeshBurst"));
				AddCandidate(TEXT("/Engine/Plugins/FX/Niagara/Content/Emitters/UpwardMeshBurst.UpwardMeshBurst"));
			}
			else if (EmitterRecipe.TemplateName.Equals(TEXT("Beam"), ESearchCase::IgnoreCase) || EmitterRecipe.RendererType.Equals(TEXT("Ribbon"), ESearchCase::IgnoreCase))
			{
				AddCandidate(TEXT("/Niagara/Emitters/Beams/Beam.Beam"));
				AddCandidate(TEXT("/Niagara/Emitters/Beam.Beam"));
				AddCandidate(TEXT("/Niagara/Emitters/Beams/DynamicBeam.DynamicBeam"));
				AddCandidate(TEXT("/Engine/Plugins/FX/Niagara/Content/Emitters/Beams/Beam.Beam"));
			}
			else
			{
				// User provided a direct path or something unknown
				AddCandidate(EmitterRecipe.TemplateName);
			}

			// Try to load
			for (const FString& Path : CandidatePaths)
			{
				TargetTemplate = LoadObject<UNiagaraEmitter>(nullptr, *Path);
				if (TargetTemplate)
				{
					UE_LOG(LogVFXAgent, Log, TEXT("Index %d: Loaded template '%s' from %s"), Index, *EmitterRecipe.TemplateName, *Path);
					break;
				}
				else
				{
					UE_LOG(LogVFXAgent, Verbose, TEXT("Index %d: Failed to load template candidate: %s"), Index, *Path);
				}
			}
			
			if (!TargetTemplate)
			{
				UE_LOG(LogVFXAgent, Warning, TEXT("Index %d: Could not find any valid template for '%s'"), Index, *EmitterRecipe.TemplateName);
			}
		}

		// 2. Fallback to default TemplateEmitter (Fountain) if specific one failed
		if (!TargetTemplate)
		{
			TargetTemplate = TemplateEmitter;
			UE_LOG(LogVFXAgent, Log, TEXT("Index %d: Falling back to global template (Fountain)"), Index);
		}

		UNiagaraEmitter* EmitterAsset = nullptr;
		if (TargetTemplate)
		{
			const FString BaseEmitterObjectName = FString::Printf(TEXT("%s_%s_Emitter"), *System->GetName(), *EmitterRecipe.RendererType);
			const FName UniqueObjectName = MakeUniqueObjectName(System, UNiagaraEmitter::StaticClass(), FName(*BaseEmitterObjectName));
			// Use DuplicateObject to create a deep copy of the template as a new object inside the System package
			EmitterAsset = DuplicateObject<UNiagaraEmitter>(TargetTemplate, System, UniqueObjectName);
		}
		
		if (!EmitterAsset)
		{
			// Last resort
			EmitterAsset = CreateBasicEmitter(EmitterRecipe, System);
			UE_LOG(LogVFXAgent, Warning, TEXT("Index %d: Created Basic Emitter (Empty fallback)"), Index);
		}

		if (!EmitterAsset)
		{
			UE_LOG(LogVFXAgent, Warning, TEXT("Failed to create emitter %d (Template: %s)"), Index, *EmitterRecipe.TemplateName);
			continue;
		}

		// Apply recipe parameters (Spawn, Lifetime, etc.)
		ApplyEmitterParameters(EmitterAsset, EmitterRecipe);

		FString LayerName = EmitterRecipe.Name;
		LayerName.TrimStartAndEndInline();
		if (LayerName.IsEmpty())
		{
			LayerName = EmitterRecipe.RendererType;
		}
		// Sanitize for object/name safety.
		for (int32 i = 0; i < LayerName.Len(); ++i)
		{
			TCHAR& C = LayerName[i];
			if (!(FChar::IsAlnum(C) || C == TCHAR('_')))
			{
				C = TCHAR('_');
			}
		}
		const FString EmitterNameStr = FString::Printf(TEXT("%s_%s_%02d"), *System->GetName(), *LayerName, Index);
		// IMPORTANT: Ensure the emitter is Public/Standalone so it survives and acts as a proper subobject? 
		// Actually, DuplicateObject with Outer=System usually makes it part of the package.
		EmitterAsset->SetFlags(RF_Transactional | RF_Public);

		const FGuid VersionGuid = EmitterAsset->GetExposedVersion().VersionGuid;
		System->AddEmitterHandle(*EmitterAsset, FName(*EmitterNameStr), VersionGuid);
	}

	// Force a full recompile and resource refresh to ensure emitters show up
	System->RequestCompile(false);

	// HACK: Sometimes emitters don't appear in the editor graph until the system is post-loaded or inspected.
	// Force update the graph representation if possible.
	// In some versions of UE5, we might need to notify the asset registry or something similar, 
	// but MarkPackageDirty + RequestCompile is standard.
	// Ensuring the handles are properly "Enabled" might be needed.
	for (int32 i = 0; i < System->GetNumEmitters(); ++i)
	{
		// Just ensuring we touch them
		System->GetEmitterHandle(i).SetIsEnabled(true, *System, true);
	}
	
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

	// Create an embedded emitter (subobject of the system) so users get ONE Niagara System asset,
	// instead of a clutter of separate NiagaraEmitter assets.
	const FString BaseEmitterObjectName = FString::Printf(TEXT("%s_%s_Emitter"), *ParentSystem->GetName(), *EmitterRecipe.RendererType);
	const FName UniqueObjectName = MakeUniqueObjectName(ParentSystem, UNiagaraEmitter::StaticClass(), FName(*BaseEmitterObjectName));
	UObject* CreatedObj = Factory->FactoryCreateNew(
		UNiagaraEmitter::StaticClass(),
		ParentSystem,
		UniqueObjectName,
		RF_Transactional,
		nullptr,
		GWarn);
	UNiagaraEmitter* NewEmitter = Cast<UNiagaraEmitter>(CreatedObj);
	if (!NewEmitter)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to create embedded Niagara Emitter"));
		return nullptr;
	}

	// Mark the parent system package dirty since the emitter lives inside it.
	ParentSystem->MarkPackageDirty();
	if (UPackage* Pkg = ParentSystem->GetOutermost())
	{
		Pkg->MarkPackageDirty();
	}

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