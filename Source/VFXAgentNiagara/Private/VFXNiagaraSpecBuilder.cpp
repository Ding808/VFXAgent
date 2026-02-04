#include "VFXNiagaraSpecBuilder.h"
#include "VFXAgentLog.h"
#include "VFXTemplateSelector.h"
#include "VFXMotionModuleLibrary.h"
#include "VFXModuleStripper.h"
#include "VFXRendererValidationFixer.h"
#include "VFXQualityScorer.h"
#include "MaterialGenerator.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "NiagaraScript.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Factories/Factory.h"

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
	const FString SystemName = Spec.Name.IsEmpty() ? TEXT("GeneratedSystem") : Spec.Name;
	
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
	
	if (SelectionResult.Strategy == EConstructionStrategy::BuildFromScratch)
	{
		Emitter = CreateFromScratch(EmitterSpec.Name);
		LogBuildAction(OutContext, TEXT("Built emitter from scratch (no template)"));
	}
	else
	{
		// Use template
		Emitter = CreateFromTemplate(SelectionResult.TemplatePath, EmitterSpec.Name);
		if (Emitter)
		{
			LogBuildAction(OutContext, FString::Printf(TEXT("Created from template: %s"), *SelectionResult.TemplatePath));
		}
		else
		{
			LogBuildAction(OutContext, TEXT("Template load failed, building from scratch"));
			Emitter = CreateFromScratch(EmitterSpec.Name);
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
	
	// Initialize with minimal required scripts
	// (This would require setting up spawn/update scripts, etc.)
	// For now, return the created emitter
	
	return Emitter;
}
