#include "VFXNiagaraSpecBuilder.h"
#include "VFXAgentLog.h"
#include "VFXTemplateSelector.h"
#include "VFXMotionModuleLibrary.h"
#include "VFXModuleInserter.h"
#include "VFXModuleStripper.h"
#include "VFXRendererValidationFixer.h"
#include "VFXQualityScorer.h"
#include "MaterialGenerator.h"
#include "PipelineLog.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "NiagaraScript.h"
#include "NiagaraSpriteRendererProperties.h"
#include "NiagaraRibbonRendererProperties.h"
#include "NiagaraMeshRendererProperties.h"
#include "NiagaraLightRendererProperties.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Factories/Factory.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/Paths.h"

static FString GetSafeName(const FString& InName, const FString& Fallback)
{
	FString Safe = InName;
	Safe = Safe.Replace(TEXT(" "), TEXT("_"));
	Safe = FPaths::MakeValidFileName(Safe, TEXT('_'));
	Safe.TrimStartAndEndInline();

	if (Safe.IsEmpty())
	{
		return Fallback;
	}

	while (Safe.Contains(TEXT("__")))
	{
		Safe = Safe.Replace(TEXT("__"), TEXT("_"));
	}

	return Safe;
}

void FVFXNiagaraSpecBuilder::LogBuildAction(FNiagaraBuildContext& Context, const FString& Action)
{
	Context.BuildLog.Add(Action);
	UE_LOG(LogVFXAgent, Log, TEXT("[BUILD] %s"), *Action);
}

UNiagaraSystem* FVFXNiagaraSpecBuilder::BuildFromSpec(const FVFXEffectSpec& Spec, FNiagaraBuildContext& OutContext)
{
	OutContext.Spec = Spec;
	OutContext.bSuccess = false;
	
	// Extract intent if available
	if (!Spec.bHasIntent)
	{
		OutContext.ErrorMessage = TEXT("Spec must have Intent set");
		UE_LOG(LogVFXAgent, Error, TEXT("%s"), *OutContext.ErrorMessage);
		return nullptr;
	}
	
	OutContext.Intent = Spec.Intent;
	
	LogBuildAction(OutContext, FString::Printf(
		TEXT("Building VFX: Archetype=%s, Motion=%s, Emitters=%d"),
		*UEnum::GetValueAsString(OutContext.Intent.Archetype),
		*UEnum::GetValueAsString(OutContext.Intent.Motion.PrimaryModel),
		Spec.Emitters.Num()
	));
	
	// Create system asset
	const FString SystemPath = Spec.OutputPath.IsEmpty() ? TEXT("/Game/GeneratedVFX") : Spec.OutputPath;
	const FString SystemName = GetSafeName(Spec.Name.IsEmpty() ? TEXT("GeneratedSystem") : Spec.Name, TEXT("GeneratedSystem"));
	
	UNiagaraSystem* System = NewObject<UNiagaraSystem>(
		GetTransientPackage(),
		*SystemName,
		RF_Public | RF_Standalone | RF_Transactional
	);
	
	if (!System)
	{
		OutContext.ErrorMessage = TEXT("Failed to create Niagara system");
		return nullptr;
	}
	
	LogBuildAction(OutContext, FString::Printf(TEXT("Created system: %s"), *SystemName));
	
	// Build each emitter
	for (const FVFXEmitterSpec& EmitterSpec : Spec.Emitters)
	{
		UNiagaraEmitter* Emitter = BuildEmitter(EmitterSpec, OutContext.Intent, OutContext);
		if (Emitter)
		{
			// Add emitter to system (implementation depends on UE version)
			LogBuildAction(OutContext, FString::Printf(TEXT("Successfully built emitter: %s"), *EmitterSpec.Name));
		}
		else
		{
			LogBuildAction(OutContext, FString::Printf(TEXT("Failed to build emitter: %s"), *EmitterSpec.Name));
		}
	}
	
	OutContext.bSuccess = true;
	return System;
}

UNiagaraEmitter* FVFXNiagaraSpecBuilder::BuildEmitter(
	const FVFXEmitterSpec& EmitterSpec,
	const FVFXIntent& Intent,
	FNiagaraBuildContext& OutContext)
{
	// STEP 1: Select strategy
	FTemplateSelectionResult SelectionResult = FVFXTemplateSelector::SelectStrategy(Intent, EmitterSpec);
	OutContext.SelectedStrategy = SelectionResult;
	
	LogBuildAction(OutContext, FString::Printf(
		TEXT("Strategy: %s - %s"),
		StrategyToString(SelectionResult.Strategy),
		*SelectionResult.StrategyReason
	));
	
	// STEP 2: Create emitter (from template or scratch)
	UNiagaraEmitter* Emitter = nullptr;
	
	const FString SafeEmitterName = GetSafeName(EmitterSpec.Name, TEXT("Emitter"));

	if (SelectionResult.Strategy == EConstructionStrategy::BuildFromScratch)
	{
		Emitter = CreateFromScratch(SafeEmitterName);
		LogBuildAction(OutContext, TEXT("Built emitter from scratch (no template)"));
	}
	else
	{
		// Use template
		Emitter = CreateFromTemplate(SelectionResult.TemplatePath, SafeEmitterName);
		if (Emitter)
		{
			LogBuildAction(OutContext, FString::Printf(TEXT("Created from template: %s"), *SelectionResult.TemplatePath));
		}
		else
		{
			LogBuildAction(OutContext, TEXT("Template load failed, building from scratch"));
			Emitter = CreateFromScratch(SafeEmitterName);
		}
	}
	
	if (!Emitter)
	{
		OutContext.ErrorMessage = TEXT("Failed to create emitter");
		return nullptr;
	}
	
	// STEP 3: Enforce constraints (strip forbidden modules)
	if (!EnforceConstraints(Emitter, SelectionResult, OutContext))
	{
		LogBuildAction(OutContext, TEXT("Warning: Constraint enforcement had issues"));
	}
	
	// STEP 4: Apply motion behavior (insert required modules)
	EMotionArchetype MotionArchetype = FVFXMotionModuleLibrary::DetermineMotionArchetype(Intent);
	FMotionBehaviorConfig MotionConfig = FVFXMotionModuleLibrary::GetMotionConfigByArchetype(MotionArchetype);
	
	if (!ApplyMotionBehavior(Emitter, MotionConfig, Intent, OutContext))
	{
		LogBuildAction(OutContext, TEXT("Warning: Motion behavior application had issues"));
	}
	
	// STEP 5: Validate renderers
	// Try to load/create a default material
	UMaterialInterface* DefaultMaterial = nullptr;
	// Note: FVFXEmitterSpec doesn't have MaterialIndex, using first material if available
	if (OutContext.Spec.Materials.Num() > 0)
	{
		// Try to load a basic particle material
		DefaultMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Engine/EngineMaterials/DefaultMaterial"));
	}
	
	if (!ValidateAndFixRenderers(Emitter, DefaultMaterial, OutContext))
	{
		LogBuildAction(OutContext, TEXT("Warning: Renderer validation had issues"));
	}
	
	return Emitter;
}

bool FVFXNiagaraSpecBuilder::EnforceConstraints(
	UNiagaraEmitter* Emitter,
	const FTemplateSelectionResult& SelectionResult,
	FNiagaraBuildContext& OutContext)
{
	if (!Emitter)
		return false;
	
	bool bSuccess = true;
	
	// Strip forbidden modules
	if (SelectionResult.ModulesToStrip.Num() > 0)
	{
		LogBuildAction(OutContext, FString::Printf(TEXT("Stripping %d forbidden module patterns"), SelectionResult.ModulesToStrip.Num()));
		
		FModuleStripResult StripResult = FVFXModuleStripper::StripModulesByPattern(Emitter, SelectionResult.ModulesToStrip);
		
		LogBuildAction(OutContext, FString::Printf(
			TEXT("  Removed %d modules: %s"),
			StripResult.ModulesRemoved,
			*FString::Join(StripResult.RemovedModuleNames, TEXT(", "))
		));
		
		if (StripResult.FailedToRemove.Num() > 0)
		{
			LogBuildAction(OutContext, FString::Printf(
				TEXT("  WARNING: Failed to remove %d modules"),
				StripResult.FailedToRemove.Num()
			));
			bSuccess = false;
		}
	}
	
	// Additional constraint enforcement
	if (SelectionResult.bMustStripGravity)
	{
		FModuleStripResult GravityStrip = FVFXModuleStripper::StripGravityModules(Emitter);
		if (GravityStrip.ModulesRemoved > 0)
		{
			LogBuildAction(OutContext, FString::Printf(TEXT("  Removed %d gravity modules"), GravityStrip.ModulesRemoved));
		}
	}
	
	if (SelectionResult.bMustStripAllVelocity)
	{
		FModuleStripResult VelocityStrip = FVFXModuleStripper::StripAllVelocityModules(Emitter);
		if (VelocityStrip.ModulesRemoved > 0)
		{
			LogBuildAction(OutContext, FString::Printf(TEXT("  Removed %d velocity modules"), VelocityStrip.ModulesRemoved));
		}
	}
	
	if (SelectionResult.bMustStripNoise)
	{
		FModuleStripResult NoiseStrip = FVFXModuleStripper::StripNoiseModules(Emitter);
		if (NoiseStrip.ModulesRemoved > 0)
		{
			LogBuildAction(OutContext, FString::Printf(TEXT("  Removed %d noise modules"), NoiseStrip.ModulesRemoved));
		}
	}
	
	return bSuccess;
}

bool FVFXNiagaraSpecBuilder::ApplyMotionBehavior(
	UNiagaraEmitter* Emitter,
	const FMotionBehaviorConfig& MotionConfig,
	const FVFXIntent& Intent,
	FNiagaraBuildContext& OutContext)
{
	if (!Emitter)
		return false;
	
	if (MotionConfig.RequiredModules.Num() == 0)
	{
		LogBuildAction(OutContext, TEXT("No required motion modules for this archetype"));
		return true;
	}
	
	LogBuildAction(OutContext, FString::Printf(
		TEXT("Applying motion behavior: %s"),
		*MotionConfig.Description
	));
	
	// Note: Actually inserting modules requires reflection into Niagara's module system
	// For now, log what should be inserted
	for (const FMotionModuleDescriptor& ModuleDesc : MotionConfig.RequiredModules)
	{
		LogBuildAction(OutContext, FString::Printf(
			TEXT("  Should insert: %s (Phase=%d, Priority=%d, Required=%s)"),
			*ModuleDesc.DisplayName,
			(int32)ModuleDesc.Phase,
			ModuleDesc.Priority,
			ModuleDesc.bRequired ? TEXT("YES") : TEXT("NO")
		));
		
		// TODO: Actually load and insert the module
		// This requires:
		// 1. Load module script: UNiagaraScript* Module = LoadObject<UNiagaraScript>(nullptr, *ModuleDesc.ModulePath);
		// 2. Insert into appropriate stack with proper ordering
		// 3. Set default parameters from ModuleDesc.DefaultParams
	}
	
	return true;
}

bool FVFXNiagaraSpecBuilder::ValidateAndFixRenderers(
	UNiagaraEmitter* Emitter,
	UMaterialInterface* DefaultMaterial,
	FNiagaraBuildContext& OutContext)
{
	if (!Emitter)
		return false;
	
	FRendererValidationReport Report = FVFXRendererValidationFixer::ValidateAndFixRenderers(Emitter, DefaultMaterial);
	
	LogBuildAction(OutContext, FString::Printf(
		TEXT("Renderer validation: %s"),
		*Report.Summary
	));
	
	if (Report.InvalidRenderersRemoved > 0)
	{
		LogBuildAction(OutContext, FString::Printf(
			TEXT("  Removed %d invalid renderers: %s"),
			Report.InvalidRenderersRemoved,
			*FString::Join(Report.RemovedRendererTypes, TEXT(", "))
		));
	}
	
	if (Report.RenderersFixed > 0)
	{
		LogBuildAction(OutContext, FString::Printf(
			TEXT("  Fixed %d renderers: %s"),
			Report.RenderersFixed,
			*FString::Join(Report.FixedRendererTypes, TEXT(", "))
		));
	}
	
	if (!Report.bHasValidRenderer)
	{
		LogBuildAction(OutContext, TEXT("  ERROR: No valid renderer after validation!"));
		return false;
	}
	
	return true;
}

UNiagaraEmitter* FVFXNiagaraSpecBuilder::CreateFromTemplate(const FString& TemplatePath, const FString& EmitterName)
{
	if (TemplatePath.IsEmpty())
		return nullptr;

	bool bDisallowTemplates = true;
	{
		const TCHAR* Section = TEXT("/Script/VFXAgentEditor.VFXAgentSettings");
		const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
		for (const FString& File : ConfigFiles)
		{
			if (GConfig && GConfig->GetBool(Section, TEXT("bDisallowTemplates"), bDisallowTemplates, File))
			{
				break;
			}
		}
	}
	if (bDisallowTemplates)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Template usage blocked"));
		FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::Niagara, TEXT("Template usage blocked"));
		return nullptr;
	}
	
	// Try to load template emitter
	UNiagaraEmitter* Template = LoadObject<UNiagaraEmitter>(nullptr, *TemplatePath);
	if (!Template)
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("Failed to load template: %s"), *TemplatePath);
		return nullptr;
	}
	
	// Duplicate the template
	UNiagaraEmitter* NewEmitter = DuplicateObject<UNiagaraEmitter>(Template, GetTransientPackage(), *EmitterName);
	if (NewEmitter)
	{
		NewEmitter->SetFlags(RF_Public | RF_Standalone | RF_Transactional);
	}
	
	return NewEmitter;
}

UNiagaraEmitter* FVFXNiagaraSpecBuilder::CreateFromScratch(const FString& EmitterName)
{
	// Create minimal emitter
	UNiagaraEmitter* Emitter = NewObject<UNiagaraEmitter>(
		GetTransientPackage(),
		*EmitterName,
		RF_Public | RF_Standalone | RF_Transactional
	);
	
	if (!Emitter)
		return nullptr;
	
return Emitter;
}

// ============================================================================
// V2 BUILDER IMPLEMENTATION
// ============================================================================

void FVFXNiagaraSpecBuilder::LogBuildActionV2(FNiagaraBuildContextV2& Context, const FString& Action)
{
	Context.BuildLog.Add(Action);
	UE_LOG(LogVFXAgent, Log, TEXT("[BUILD V2] %s"), *Action);
}

UNiagaraSystem* FVFXNiagaraSpecBuilder::BuildFromSpecV2(const FEffectSpecV2& Spec, FNiagaraBuildContextV2& OutContext)
{
	OutContext.Spec = Spec;
	OutContext.bSuccess = false;

	FString SystemName = GetSafeName(Spec.EffectName, TEXT("VFXGen_V2"));
	if (SystemName.IsEmpty()) SystemName = TEXT("VFXGen_V2");
    
	UNiagaraSystem* System = NewObject<UNiagaraSystem>(
		GetTransientPackage(), 
		*SystemName, 
		RF_Public | RF_Standalone | RF_Transactional
	);

	if (!System)
	{
		OutContext.ErrorMessage = TEXT("Failed to create Niagara system");
		return nullptr;
	}

	LogBuildActionV2(OutContext, FString::Printf(TEXT("Created system: %s"), *SystemName));

	for (const FLayerSpecV2& Layer : Spec.Layers)
	{
		UNiagaraEmitter* Emitter = BuildEmitterV2(Layer, OutContext);
		if (Emitter)
		{
			FGuid EmitterVersion = Emitter->GetExposedVersion().VersionGuid;
			if (!EmitterVersion.IsValid())
			{
				EmitterVersion = FGuid::NewGuid(); // Fallback if no version exists
			}

			const FString SafeLayerName = GetSafeName(Layer.Name, TEXT("Layer"));
			FNiagaraEmitterHandle Handle = System->AddEmitterHandle(*Emitter, FName(*SafeLayerName), EmitterVersion);
			Handle.SetIsEnabled(true, *System, true);
			LogBuildActionV2(OutContext, FString::Printf(TEXT("Added Emitter: %s"), *SafeLayerName));
		}
	}

	OutContext.bSuccess = true;
	return System;
}

UNiagaraEmitter* FVFXNiagaraSpecBuilder::BuildEmitterV2(const FLayerSpecV2& Layer, FNiagaraBuildContextV2& Context)
{
	const FString SafeLayerName = GetSafeName(Layer.Name, TEXT("Layer"));
	UNiagaraEmitter* Emitter = CreateFromScratch(SafeLayerName);
	if (!Emitter) return nullptr;

	ConfigureEmitterMotionV2(Emitter, Layer, Context);

	// ========================================================================
	// MATERIAL GENERATION
	// ========================================================================
	
	// 1. Prepare Material Recipe
	FVFXMaterialRecipe MatRecipe;
	MatRecipe.Name = GetSafeName(FString::Printf(TEXT("M_%s_%s"), *SafeLayerName, *FGuid::NewGuid().ToString().Left(4)), TEXT("M_VFX_Mat"));
	
	// Map Shading Model
	MatRecipe.bIsUnlit = (Layer.Material.Shading.ToLower() == TEXT("unlit"));
	
	// Map Blend Mode
	const FString Blend = Layer.Material.Blend.ToLower();
	if (Blend == TEXT("additive")) MatRecipe.bIsAdditive = true;
	else if (Blend == TEXT("translucent")) MatRecipe.bIsAdditive = false; // Simplified mapping
	else if (Blend == TEXT("masked")) MatRecipe.bIsAdditive = false; // Need fuller support in Recipe
	
	MatRecipe.BaseColor = Layer.Material.BaseColor;
	MatRecipe.EmissiveColor = Layer.Material.EmissiveColor;
	MatRecipe.EmissiveStrength = Layer.Material.EmissiveIntensity;
	MatRecipe.Opacity = Layer.Material.Opacity;

	// 2. Generate Material Asset
	const FString MatRootPath = TEXT("/Game/VFXAgent/Generated/Materials");
	UMaterialGenerator* MatGen = UMaterialGenerator::CreateInstance();
	UMaterialInstanceConstant* NewMaterial = MatGen->GenerateMaterial(MatRecipe, MatRootPath);
	
	if (NewMaterial)
	{
		LogBuildActionV2(Context, FString::Printf(TEXT("Generated Material: %s"), *NewMaterial->GetName()));
	}
	else
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("Failed to generate material for layer %s"), *Layer.Name);
	}

	// 3. Create & Assign Renderer
	UNiagaraRendererProperties* RendererProps = nullptr;
	const FString RendererType = Layer.RendererType.ToLower();
	
	FGuid VersionGuid = Emitter->GetExposedVersion().VersionGuid;
	if (!VersionGuid.IsValid())
	{
		VersionGuid = FGuid::NewGuid(); // Fallback if no version exists
	}

	if (RendererType.Contains(TEXT("sprite")))
	{
		UNiagaraSpriteRendererProperties* SpriteRen = NewObject<UNiagaraSpriteRendererProperties>(Emitter, "SpriteRenderer");
		if (NewMaterial) SpriteRen->Material = NewMaterial;
		
		// Set Alignment based on motion
		if (Layer.Motion.Verb == EMotionVerbV2::Stream || Layer.Motion.Verb == EMotionVerbV2::Rise)
		{
			SpriteRen->Alignment = ENiagaraSpriteAlignment::VelocityAligned;
		}
		else
		{
			SpriteRen->Alignment = ENiagaraSpriteAlignment::Unaligned;
		}
		
		RendererProps = SpriteRen;
	}
	else if (RendererType.Contains(TEXT("ribbon")))
	{
		UNiagaraRibbonRendererProperties* RibbonRen = NewObject<UNiagaraRibbonRendererProperties>(Emitter, "RibbonRenderer");
		if (NewMaterial) RibbonRen->Material = NewMaterial;
		RendererProps = RibbonRen;
	}
	else if (RendererType.Contains(TEXT("mesh")))
	{
		UNiagaraMeshRendererProperties* MeshRen = NewObject<UNiagaraMeshRendererProperties>(Emitter, "MeshRenderer");
		if (NewMaterial) 
		{
			FNiagaraMeshMaterialOverride Override;
			Override.ExplicitMat = NewMaterial;
			MeshRen->OverrideMaterials.Add(Override);
		}
		RendererProps = MeshRen;
	}
	else if (RendererType.Contains(TEXT("light")))
	{
		UNiagaraLightRendererProperties* LightRen = NewObject<UNiagaraLightRendererProperties>(Emitter, "LightRenderer");
		RendererProps = LightRen;
	}

	if (RendererProps)
	{
		Emitter->AddRenderer(RendererProps, VersionGuid);
		LogBuildActionV2(Context, FString::Printf(TEXT("Added Renderer: %s"), *RendererProps->GetName()));
	}
	else
	{
		// Default to sprite if unknown
		UNiagaraSpriteRendererProperties* DefaultRen = NewObject<UNiagaraSpriteRendererProperties>(Emitter, "DefaultSpriteRenderer");
		if (NewMaterial) DefaultRen->Material = NewMaterial;
		Emitter->AddRenderer(DefaultRen, VersionGuid);
		LogBuildActionV2(Context, TEXT("Added Default Renderer (Sprite)"));
	}

	return Emitter;
}

void FVFXNiagaraSpecBuilder::ConfigureEmitterMotionV2(UNiagaraEmitter* Emitter, const FLayerSpecV2& Layer, FNiagaraBuildContextV2& Context)
{
	TArray<FMotionModuleDescriptor> Modules;

	// 1. Initialize
	FMotionModuleDescriptor InitModule;
	InitModule.DisplayName = TEXT("Initialize Particle");
	InitModule.ModulePath = TEXT("/Niagara/Modules/Initialize/InitializeParticle.InitializeParticle"); 
	InitModule.Phase = EModulePhase::PreSim;
	InitModule.Priority = 0;
	InitModule.DefaultParams.Add(TEXT("Lifetime"), Layer.Timing.TotalLifetime);
	InitModule.DefaultParams.Add(TEXT("SpriteSize"), 50.0f);
	InitModule.bRequired = true;
	Modules.Add(InitModule);

	// 2. Spawn Logic
	FMotionModuleDescriptor SpawnModule;
	SpawnModule.Phase = EModulePhase::PreSim;
	SpawnModule.Priority = 2; // After Init
	SpawnModule.bRequired = true;

	bool bUseBurst = (Layer.Timing.TotalLifetime < 2.0f && !Layer.Timing.bLoop);
	if (Layer.Motion.Verb == EMotionVerbV2::Explode || Layer.Motion.Verb == EMotionVerbV2::Snap)
	{
		bUseBurst = true;
	}
    
	if (bUseBurst)
	{
		SpawnModule.DisplayName = TEXT("Spawn Burst Instant");
		SpawnModule.ModulePath = TEXT("/Niagara/Modules/Emitter/SpawnBurstInstant.SpawnBurstInstant");
		SpawnModule.DefaultParamsInt.Add(TEXT("SpawnCount"), Layer.MaxParticles);
	}
	else
	{
		SpawnModule.DisplayName = TEXT("Spawn Rate");
		SpawnModule.ModulePath = TEXT("/Niagara/Modules/Emitter/SpawnRate.SpawnRate");
		SpawnModule.DefaultParams.Add(TEXT("SpawnRate"), (float)Layer.MaxParticles / FMath::Max(0.1f, Layer.Timing.TotalLifetime));
	}
	Modules.Add(SpawnModule);

	// 3. Motion & Velocity
	if (Layer.Motion.Verb == EMotionVerbV2::Explode)
	{
		FMotionModuleDescriptor VelModule;
		VelModule.DisplayName = TEXT("Add Velocity In Cone");
		VelModule.ModulePath = TEXT("/Niagara/Modules/Velocity/AddVelocityInCone.AddVelocityInCone");
		VelModule.Phase = EModulePhase::Forces;
		VelModule.DefaultParams.Add(TEXT("VelocityStrength"), Layer.Motion.Speed);
		Modules.Add(VelModule);
	}
	else if (Layer.Motion.Verb == EMotionVerbV2::Rise || Layer.Motion.Verb == EMotionVerbV2::Fall)
	{
		FMotionModuleDescriptor VelModule;
		VelModule.DisplayName = TEXT("Add Velocity");
		VelModule.ModulePath = TEXT("/Niagara/Modules/Velocity/AddVelocity.AddVelocity");
		VelModule.Phase = EModulePhase::Forces;
		VelModule.DefaultParamsVector.Add(TEXT("Velocity"), Layer.Init.Velocity);
		Modules.Add(VelModule);
	}
	else if (Layer.Motion.Verb == EMotionVerbV2::Orbit || Layer.Motion.Verb == EMotionVerbV2::Spiral)
	{
		FMotionModuleDescriptor VortexModule;
		VortexModule.DisplayName = TEXT("Vortex Force");
		VortexModule.ModulePath = TEXT("/Niagara/Modules/Forces/VortexForce.VortexForce");
		VortexModule.Phase = EModulePhase::Forces;
		VortexModule.DefaultParams.Add(TEXT("VortexStrength"), Layer.Motion.Speed);
		Modules.Add(VortexModule);
	}

	// 4. Drag
	if (Layer.Motion.DragCoefficient > 0.0f)
	{
		FMotionModuleDescriptor DragModule;
		DragModule.DisplayName = TEXT("Drag");
		DragModule.ModulePath = TEXT("/Niagara/Modules/Solve/Drag.Drag");
		DragModule.Phase = EModulePhase::Damping;
		DragModule.DefaultParams.Add(TEXT("Drag"), Layer.Motion.DragCoefficient);
		Modules.Add(DragModule); 
	}
	
	// 5. Solver
	FMotionModuleDescriptor SolverModule;
	SolverModule.DisplayName = TEXT("Solve Forces and Velocity");
	SolverModule.ModulePath = TEXT("/Niagara/Modules/Solve/SolveForcesAndVelocity.SolveForcesAndVelocity");
	SolverModule.Phase = EModulePhase::Integrate;
	SolverModule.bRequired = true;
	Modules.Add(SolverModule);

	FVFXModuleInserter::InsertModules(Emitter, Modules, TEXT("V2_Builder"));
}
