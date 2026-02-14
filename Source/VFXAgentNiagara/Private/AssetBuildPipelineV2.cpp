#include "AssetBuildPipelineV2.h"
#include "NiagaraSpecExecutor.h"
#include "MaterialCustomBuilder.h"
#include "VFXAgentLog.h"
#include "PipelineLog.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "NiagaraRendererProperties.h"
#include "NiagaraSpriteRendererProperties.h"
#include "NiagaraRibbonRendererProperties.h"
#include "NiagaraLightRendererProperties.h"
#include "NiagaraMeshRendererProperties.h"
#include "VFXRendererValidationFixer.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Misc/Crc.h"
#include "Misc/ConfigCacheIni.h"
#include "HAL/FileManager.h"
#include "AssetRegistry/AssetRegistryModule.h"

// ============================================================================
// Helpers
// ============================================================================

static FString NormalizeOutputPathV2(const FString& Path)
{
	FString Result = Path.TrimStartAndEnd();
	if (!Result.StartsWith(TEXT("/Game")))
	{
		Result = FString::Printf(TEXT("/Game/%s"), *Result);
	}
	return Result;
}

static bool GetV2SettingBool(const TCHAR* Key, bool bDefault)
{
	bool bValue = bDefault;
	const TCHAR* Section = TEXT("/Script/VFXAgentEditor.VFXAgentSettings");
	const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
	for (const FString& File : ConfigFiles)
	{
		if (GConfig && GConfig->GetBool(Section, Key, bValue, File))
		{
			return bValue;
		}
	}
	return bDefault;
}

static EVFXRendererType ToRendererTypeV2(const FString& Type)
{
	const FString Lower = Type.ToLower();
	if (Lower == TEXT("ribbon")) return EVFXRendererType::Ribbon;
	if (Lower == TEXT("mesh"))   return EVFXRendererType::Mesh;
	if (Lower == TEXT("light"))  return EVFXRendererType::Light;
	return EVFXRendererType::Sprite;
}

static FString CreateVersionedFolderV2(const FString& Root, const FString& EffectName)
{
	FString Base = FPaths::Combine(Root, EffectName);
	Base = Base.Replace(TEXT("\\"), TEXT("/"));
	Base = NormalizeOutputPathV2(Base);

	for (int32 i = 1; i <= 999; ++i)
	{
		const FString Version = FString::Printf(TEXT("v%03d"), i);
		const FString Candidate = FPaths::Combine(Base, Version).Replace(TEXT("\\"), TEXT("/"));
		const FString PackageName = Candidate / EffectName;
		if (!FPackageName::DoesPackageExist(PackageName))
		{
			return Candidate;
		}
	}
	return Base;
}

static FString ReadSpecHashV2(const FString& Folder)
{
	const FString Path = FPaths::Combine(FPackageName::LongPackageNameToFilename(Folder), TEXT("spec_hash.txt"));
	FString Content;
	if (FFileHelper::LoadFileToString(Content, *Path))
	{
		return Content.TrimStartAndEnd();
	}
	return FString();
}

static void WriteSpecHashV2(const FString& Folder, const FString& Hash)
{
	const FString DiskFolder = FPackageName::LongPackageNameToFilename(Folder);
	IFileManager::Get().MakeDirectory(*DiskFolder, true);
	const FString Path = FPaths::Combine(DiskFolder, TEXT("spec_hash.txt"));
	FFileHelper::SaveStringToFile(Hash, *Path);
}

static FString FindFolderByHashV2(const FString& Root, const FString& EffectName, const FString& Hash)
{
	FString Base = FPaths::Combine(Root, EffectName);
	Base = Base.Replace(TEXT("\\"), TEXT("/"));
	Base = NormalizeOutputPathV2(Base);

	for (int32 i = 1; i <= 999; ++i)
	{
		const FString Version = FString::Printf(TEXT("v%03d"), i);
		const FString Candidate = FPaths::Combine(Base, Version).Replace(TEXT("\\"), TEXT("/"));
		const FString PackageName = Candidate / EffectName;
		if (FPackageName::DoesPackageExist(PackageName))
		{
			const FString ExistingHash = ReadSpecHashV2(Candidate);
			if (!ExistingHash.IsEmpty() && ExistingHash == Hash)
			{
				return Candidate;
			}
		}
	}
	return FString();
}

// ============================================================================
// ResolveOutputFolder
// ============================================================================

FString FAssetBuildPipelineV2::ResolveOutputFolder(const FString& OutputRootPath, const FString& EffectName, const FString& SpecHash)
{
	FString OutputPath = FindFolderByHashV2(OutputRootPath, EffectName, SpecHash);
	if (OutputPath.IsEmpty())
	{
		OutputPath = CreateVersionedFolderV2(OutputRootPath, EffectName);
		WriteSpecHashV2(OutputPath, SpecHash);
	}
	else
	{
		FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Validate, TEXT("V2 spec hash matched; reusing output folder"));
	}
	return OutputPath;
}

// ============================================================================
// ApplySpawnConfig
// ============================================================================

void FAssetBuildPipelineV2::ApplySpawnConfig(UNiagaraSystem* System, const FString& EmitterName, const FLayerSpawnV2& Spawn)
{
	if (!System) return;

	if (Spawn.Mode.ToLower() == TEXT("burst"))
	{
		if (Spawn.BurstCount > 0)
		{
			FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Spawn Burst Instantaneous.Spawn Count"), (float)Spawn.BurstCount);
			FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("SpawnBurst_Instant.SpawnBurst"), (float)Spawn.BurstCount);
		}
	}
	else // rate
	{
		if (Spawn.Rate > 0.0f)
		{
			FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("SpawnRate.SpawnRate"), Spawn.Rate);
			FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Spawn Rate"), Spawn.Rate);
		}
	}
}

// ============================================================================
// ApplyTimingEnvelope
// ============================================================================

void FAssetBuildPipelineV2::ApplyTimingEnvelope(UNiagaraSystem* System, const FString& EmitterName, const FTimingEnvelopeV2& Timing)
{
	if (!System) return;

	// Set particle lifetime
	FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("InitializeParticle.Lifetime"), Timing.TotalLifetime);
	FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Lifetime"), Timing.TotalLifetime);

	// Emitter-level delay — configure via Spawn Burst time offset
	if (Timing.DelaySeconds > 0.01f)
	{
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Spawn Burst Instantaneous.Spawn Time"), Timing.DelaySeconds);
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("SpawnBurst_Instant.SpawnTime"), Timing.DelaySeconds);
	}

	// Attack → alpha ramp up. We use alpha over life to approximate the envelope.
	// Attack < 0.05 means sharp (alpha starts at full).
	// Longer attack means slow fade-in.
	if (Timing.AttackSeconds > 0.05f)
	{
		// Set alpha start to 0 and end to 1 during attack phase
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Alpha"), 0.0f);
	}

	// Decay → alpha fade-out
	if (Timing.DecaySeconds > 0.0f)
	{
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Alpha End"), 0.0f);
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Scale Color.End Alpha"), 0.0f);
	}
}

// ============================================================================
// ApplyMotionVerb
// ============================================================================

void FAssetBuildPipelineV2::ApplyMotionVerb(UNiagaraSystem* System, const FString& EmitterName, const FMotionDescV2& Motion, const FLayerUpdateV2& Update)
{
	if (!System) return;

	// Apply velocity based on motion verb + axis + speed
	FVector Velocity = FVector::ZeroVector;
	switch (Motion.Verb)
	{
	case EMotionVerbV2::Explode:
		// Radial burst — distribute via velocity magnitude
		Velocity = FVector(Motion.Speed, Motion.Speed, Motion.Speed);
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Velocity Strength"), Motion.Speed);
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("AddVelocity.Randomness"), FMath::Max(Motion.SpeedVariation, 0.3f));
		break;

	case EMotionVerbV2::Implode:
		Velocity = -Motion.Axis * Motion.Speed;
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Velocity Strength"), Motion.Speed);
		break;

	case EMotionVerbV2::Rise:
		Velocity = FVector(0, 0, Motion.Speed);
		break;

	case EMotionVerbV2::Fall:
		Velocity = FVector(0, 0, -Motion.Speed);
		FNiagaraSpecExecutor::SetVariableVec3(System, EmitterName, TEXT("Gravity.Acceleration"), FVector(0, 0, -980));
		break;

	case EMotionVerbV2::Orbit:
		Velocity = Motion.Axis * Motion.Speed * 0.5f;
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Vortex Force.Strength"), Motion.Speed * 0.1f);
		FNiagaraSpecExecutor::SetVariableVec3(System, EmitterName, TEXT("Vortex Force.Axis"), Motion.Axis);
		break;

	case EMotionVerbV2::Spiral:
		Velocity = Motion.Axis * Motion.Speed;
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Vortex Force.Strength"), Motion.Speed * 0.15f);
		FNiagaraSpecExecutor::SetVariableVec3(System, EmitterName, TEXT("Vortex Force.Axis"), Motion.Axis);
		break;

	case EMotionVerbV2::Drift:
		Velocity = Motion.Axis * Motion.Speed * 0.3f;
		break;

	case EMotionVerbV2::Snap:
		Velocity = Motion.Axis * Motion.Speed * 3.0f; // Instant speed burst
		break;

	case EMotionVerbV2::Pulse:
		Velocity = Motion.Axis * Motion.Speed;
		// Pulse uses size-over-life for expand/contract
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Scale Sprite Size.End Size"), 0.1f);
		break;

	case EMotionVerbV2::Stream:
		Velocity = Motion.Axis * Motion.Speed;
		break;

	case EMotionVerbV2::Flutter:
		Velocity = Motion.Axis * Motion.Speed * 0.2f;
		// Flutter uses high curl noise
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Curl Noise Force.Strength"), FMath::Max(Motion.CurlNoiseIntensity, 15.0f));
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Curl Noise Force.Frequency"), FMath::Max(Motion.CurlNoiseFrequency, 3.0f));
		break;

	case EMotionVerbV2::Static:
	default:
		break;
	}

	FNiagaraSpecExecutor::SetVariableVec3(System, EmitterName, TEXT("AddVelocity.Velocity"), Velocity);
	FNiagaraSpecExecutor::SetVariableVec3(System, EmitterName, TEXT("Velocity"), Velocity);

	// Apply velocity variation
	if (Motion.SpeedVariation > 0.001f)
	{
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Velocity Variation"), Motion.SpeedVariation);
	}

	// Apply drag from motion desc and/or update spec
	float Drag = FMath::Max(Motion.DragCoefficient, Update.Drag);
	if (Drag > 0.001f)
	{
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Drag.Drag"), Drag);
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Drag"), Drag);
	}

	// Apply curl noise
	float CurlStrength = FMath::Max(Motion.CurlNoiseIntensity, Update.CurlNoiseStrength);
	if (CurlStrength > 0.0f)
	{
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Curl Noise Force.Strength"), CurlStrength);
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("CurlNoiseForce.Strength"), CurlStrength);
		if (Motion.CurlNoiseFrequency > 0.0f)
		{
			FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Curl Noise Force.Frequency"), Motion.CurlNoiseFrequency);
		}
	}
}

// ============================================================================
// BuildV2Material
// ============================================================================

UMaterialInterface* FAssetBuildPipelineV2::BuildV2Material(
	const FMaterialSpecV2& MatSpec,
	const FString& OutputPath,
	const FString& MaterialName,
	const FString& EffectName,
	const FString& LayerName)
{
	// Translate FMaterialSpecV2 → FMaterialSpecV1 for the existing material builder
	FMaterialSpecV1 V1Spec;
	V1Spec.Shading = MatSpec.Shading;
	V1Spec.Blend = MatSpec.Blend;
	V1Spec.TextureSlots = MatSpec.TextureSlots;

	// Map V2 features → V1 features
	const FMaterialFeatureSetV2& F = MatSpec.Features;
	V1Spec.Features.Add(TEXT("fresnel"), F.bFresnel);
	V1Spec.Features.Add(TEXT("depth_fade"), F.bDepthFade);
	V1Spec.Features.Add(TEXT("uv_distortion"), F.bUVDistortion);
	V1Spec.Features.Add(TEXT("noise_mask"), F.bNoiseMask);
	V1Spec.Features.Add(TEXT("erode_mask"), F.bErodeMask);
	V1Spec.Features.Add(TEXT("pan_uv"), F.bPanUV);

	// Map scalar params
	V1Spec.ScalarParams.Add(TEXT("EmissiveIntensity"), MatSpec.EmissiveIntensity);
	V1Spec.ScalarParams.Add(TEXT("Opacity"), MatSpec.Opacity);
	if (F.bFresnel) V1Spec.ScalarParams.Add(TEXT("FresnelExponent"), F.FresnelExponent);
	if (F.bDepthFade) V1Spec.ScalarParams.Add(TEXT("DepthFadeDistance"), F.DepthFadeDistance);
	if (F.bUVDistortion) V1Spec.ScalarParams.Add(TEXT("DistortionStrength"), F.DistortionStrength);
	if (F.bNoiseMask)
	{
		V1Spec.ScalarParams.Add(TEXT("NoiseTiling"), F.NoiseTiling);
		V1Spec.ScalarParams.Add(TEXT("NoiseContrast"), F.NoiseContrast);
	}
	if (F.bErodeMask) V1Spec.ScalarParams.Add(TEXT("ErodeThreshold"), F.ErodeThreshold);

	// Map vector params
	V1Spec.VectorParams.Add(TEXT("BaseColor"), MatSpec.BaseColor);
	V1Spec.VectorParams.Add(TEXT("EmissiveColor"), MatSpec.EmissiveColor);

	// HLSL custom if specified
	if (MatSpec.bCustomHLSL && !MatSpec.HLSLCode.IsEmpty())
	{
		V1Spec.HLSLCustom.Enabled = true;
		V1Spec.HLSLCustom.Code = MatSpec.HLSLCode;
		V1Spec.HLSLCustom.Contract = MatSpec.HLSLContract;
		V1Spec.HLSLCustom.Outputs.emissive = true;
		V1Spec.HLSLCustom.Outputs.opacity = true;
	}

	return FMaterialCustomBuilder::BuildMaterialFromSpec(V1Spec, OutputPath, MaterialName, EffectName, LayerName);
}

// ============================================================================
// ApplyEventBindings
// ============================================================================

void FAssetBuildPipelineV2::ApplyEventBindings(UNiagaraSystem* System, const FEffectSpecV2& Spec, FAssetBuildResult& OutResult)
{
	if (!System) return;

	for (const FEventBindingV2& Event : Spec.Events)
	{
		// Find source and target layer names from IDs
		FString SourceName, TargetName;
		for (const FLayerSpecV2& L : Spec.Layers)
		{
			if (L.Id == Event.SourceLayerId) SourceName = L.Name;
			if (L.Id == Event.TargetLayerId) TargetName = L.Name;
		}

		if (SourceName.IsEmpty() || TargetName.IsEmpty())
		{			OutResult.Warnings.Add(FString::Printf(TEXT("Event binding references unknown layer: %s → %s"),
				*Event.SourceLayerId, *Event.TargetLayerId));
			continue;
		}

		FVFXEventRecipe EventRecipe;
		switch (Event.Type)
		{
		case EEventTypeV2::OnDeath:
			EventRecipe.Type = EVFXEventType::OnEmitterDeath;
			break;
		case EEventTypeV2::OnCollision:
			EventRecipe.Type = EVFXEventType::OnEmitterCollision;
			break;
		case EEventTypeV2::OnSpawn:
			EventRecipe.Type = EVFXEventType::OnEmitterStart;
			break;
		case EEventTypeV2::OnLifetimeExpire:
			EventRecipe.Type = EVFXEventType::OnEmitterDeath;
			break;
		case EEventTypeV2::Timed:
			EventRecipe.Type = EVFXEventType::OnEmitterBurst;
			break;
		}
		EventRecipe.SourceLayer = SourceName;
		EventRecipe.TargetLayer = TargetName;
		EventRecipe.BurstOverride = Event.SpawnCount;
		EventRecipe.Delay = Event.Delay;

		if (Event.Type == EEventTypeV2::OnCollision)
		{
			if (!FNiagaraSpecExecutor::ConfigureCollisionEventHandler(System, SourceName, TargetName, EventRecipe))
			{
				OutResult.Warnings.Add(FString::Printf(TEXT("Failed to wire collision event: %s → %s"), *SourceName, *TargetName));
			}
			else
			{				FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara,
					FString::Printf(TEXT("Wired collision event: %s → %s"), *SourceName, *TargetName));
			}
		}
		else
		{
			// For on_death, on_spawn, timed — configure via event handler source on the target emitter
			const TCHAR* TypeStr =
				Event.Type == EEventTypeV2::OnDeath ? TEXT("on_death") :
				Event.Type == EEventTypeV2::OnSpawn ? TEXT("on_spawn") :
				Event.Type == EEventTypeV2::Timed ? TEXT("timed") : TEXT("other");
			FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara,
				FString::Printf(TEXT("Event binding registered: %s [%s] → %s (spawn %d)"),
					*SourceName, TypeStr, *TargetName, Event.SpawnCount));

			// Set spawn count on target emitter's event-driven spawn
			FNiagaraSpecExecutor::SetVariableFloat(System, TargetName,
				TEXT("Spawn Burst Instantaneous.Spawn Count"), (float)Event.SpawnCount);
		}
	}
}

// ============================================================================
// BuildFromV2Spec — main entry point
// ============================================================================

bool FAssetBuildPipelineV2::BuildFromV2Spec(const FEffectSpecV2& Spec, const FString& OutputRootPath, FAssetBuildResult& OutResult)
{
	OutResult = FAssetBuildResult();

	if (Spec.Layers.Num() == 0)
	{
		OutResult.Errors.Add(TEXT("V2 spec has no layers"));
		return false;
	}

	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Orchestrator,
		FString::Printf(TEXT("V2 Build: '%s', %d layers, %d events"), *Spec.EffectName, Spec.Layers.Num(), Spec.Events.Num()));

	// Dry-run check
	if (GetV2SettingBool(TEXT("bDryRun"), false))
	{
		FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Orchestrator, TEXT("Dry-run enabled: no assets will be created"));
		OutResult.bSuccess = true;
		OutResult.SystemPath = TEXT("<dry-run>");
		return true;
	}

	// Compute spec hash for deduplication
	const FString SpecJson = FString::Printf(TEXT("%s_%d_%d"), *Spec.EffectName, Spec.Layers.Num(), Spec.Events.Num());
	const FString SpecHash = FString::Printf(TEXT("%u"), FCrc::StrCrc32(*SpecJson));
	const FString OutputPath = ResolveOutputFolder(OutputRootPath, Spec.EffectName, SpecHash);

	// Create the Niagara system asset
	UNiagaraSystem* System = FNiagaraSpecExecutor::CreateNiagaraSystemAsset(OutputPath, Spec.EffectName);
	if (!System)
	{
		OutResult.Errors.Add(TEXT("Failed to create Niagara system asset"));
		return false;
	}

	// Process each layer
	for (int32 LayerIndex = 0; LayerIndex < Spec.Layers.Num(); ++LayerIndex)
	{
		const FLayerSpecV2& Layer = Spec.Layers[LayerIndex];

		FPipelineLogEntry Entry;
		Entry.Timestamp = FDateTime::UtcNow();
		Entry.Level = EPipelineLogLevel::Info;
		Entry.Stage = EPipelineStage::Niagara;
		Entry.Message = FString::Printf(TEXT("V2 Building layer %d/%d: '%s' [%s]"),
			LayerIndex + 1, Spec.Layers.Num(), *Layer.Name, *Layer.RendererType);
		Entry.CurrentStep = LayerIndex + 1;
		Entry.TotalSteps = Spec.Layers.Num();
		Entry.Percent = (float)(LayerIndex + 1) / (float)Spec.Layers.Num();
		FPipelineLog::Get().Push(Entry);

		// Add emitter to system
		if (!FNiagaraSpecExecutor::AddBasicEmitterToSystem(System, Layer.Name))
		{
			OutResult.Warnings.Add(FString::Printf(TEXT("Failed to add emitter: %s"), *Layer.Name));
			continue;
		}

		// Build the base emitter spec for ConfigureEmitter
		FVFXEmitterSpec EmitterSpec;
		EmitterSpec.Name = Layer.Name;
		EmitterSpec.RendererType = ToRendererTypeV2(Layer.RendererType);
		EmitterSpec.SortOrder = Layer.SortOrder;

		// Spawn
		EmitterSpec.Spawn.Rate = Layer.Spawn.Rate;
		EmitterSpec.Spawn.Burst = Layer.Spawn.BurstCount;

		// Init
		EmitterSpec.Lifetime = Layer.Init.Lifetime > 0.01f ? Layer.Init.Lifetime : Layer.Timing.TotalLifetime;
		EmitterSpec.LifetimeVariation = Layer.Init.LifetimeVariation;
		EmitterSpec.Size = (Layer.Init.SizeRange.X + Layer.Init.SizeRange.Y) * 0.5f;
		EmitterSpec.SizeVariation = (Layer.Init.SizeRange.Y - Layer.Init.SizeRange.X) / FMath::Max(EmitterSpec.Size, 1.0f);
		EmitterSpec.Velocity = Layer.Init.Velocity;

		// Update
		EmitterSpec.Drag = FMath::Max(Layer.Update.Drag, Layer.Motion.DragCoefficient);
		EmitterSpec.CurlNoiseStrength = FMath::Max(Layer.Update.CurlNoiseStrength, Layer.Motion.CurlNoiseIntensity);

		// Color from material spec
		EmitterSpec.Color = Layer.Material.BaseColor;
		EmitterSpec.bUseColorGradient = true;
		EmitterSpec.ColorEnd = Layer.Material.EmissiveColor;

		// Alpha from material opacity + timing decay
		EmitterSpec.Alpha = Layer.Material.Opacity;
		EmitterSpec.bUseAlphaOverLife = (Layer.Timing.DecaySeconds > 0.0f);
		EmitterSpec.AlphaEnd = 0.0f;

		// Ribbon/trail specific setup
		if (EmitterSpec.RendererType == EVFXRendererType::Ribbon ||
			Layer.RendererType.ToLower() == TEXT("ribbon"))
		{
			EmitterSpec.Alignment = TEXT("velocity");
			EmitterSpec.FacingMode = TEXT("camera");
			EmitterSpec.MotionStretch = 1.0f;
			EmitterSpec.bUseSizeOverLife = true;
			EmitterSpec.SizeEnd = FMath::Max(EmitterSpec.Size * 0.5f, 1.0f);
		}

		// Light renderer setup
		if (EmitterSpec.RendererType == EVFXRendererType::Light)
		{
			EmitterSpec.Size = FMath::Max(EmitterSpec.Size, 100.0f);
			EmitterSpec.bUseSizeOverLife = true;
			EmitterSpec.SizeEnd = 0.0f;
		}

		// Configure the emitter via the existing spec executor
		FNiagaraSpecExecutor::ConfigureEmitter(System, Layer.Name, EmitterSpec);

		// Apply V2-specific parameters on top
		ApplyTimingEnvelope(System, Layer.Name, Layer.Timing);
		ApplySpawnConfig(System, Layer.Name, Layer.Spawn);
		ApplyMotionVerb(System, Layer.Name, Layer.Motion, Layer.Update);

		// Build and assign material
		const FString MatName = Layer.Name + TEXT("_Mat");
		UMaterialInterface* Mat = BuildV2Material(Layer.Material, OutputPath, MatName, Spec.EffectName, Layer.Name);
		if (Mat)
		{
			// Find the emitter instance and assign material via the renderer validation fixer
			// (UNiagaraEmitter doesn't expose GetRenderers() publicly in UE 5.5)
			for (FNiagaraEmitterHandle& H : System->GetEmitterHandles())
			{
				FString HandleName = H.GetName().ToString();
				if (HandleName == Layer.Name || HandleName.StartsWith(Layer.Name))
				{
					UNiagaraEmitter* EmitterInstance = H.GetInstance().Emitter;
					if (EmitterInstance)
					{
						// Use the validation fixer's public API to count and set materials
						const int32 RendererCount = FVFXRendererValidationFixer::CountValidRenderers(EmitterInstance);
						if (RendererCount > 0)
						{
							// Validate & fix assigns the material to all existing renderers
							FRendererValidationReport Report = FVFXRendererValidationFixer::ValidateAndFixRenderers(EmitterInstance, Mat);
							UE_LOG(LogVFXAgent, Log, TEXT("V2 Material assignment for '%s': %d renderers, %d fixed"),
								*Layer.Name, Report.TotalRenderers, Report.RenderersFixed);
						}
						else
						{
							// No renderers yet — ensure at least a sprite renderer exists with our material
							FVFXRendererValidationFixer::EnsureValidSpriteRenderer(EmitterInstance, Mat);
						}
						EmitterInstance->Modify();
					}
					break;
				}
			}
			FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Material,
				FString::Printf(TEXT("Material assigned to '%s'"), *Layer.Name));
		}
		else
		{
			OutResult.Warnings.Add(FString::Printf(TEXT("Material build failed for layer '%s'; using default"), *Layer.Name));
		}
	}

	// Wire event bindings between emitters
	if (Spec.Events.Num() > 0)
	{
		ApplyEventBindings(System, Spec, OutResult);
	}

	// Save, compile, and self-check
	FVFXRepairReport Report;
	if (!FNiagaraSpecExecutor::SaveCompileAndSelfCheck(System, Report))
	{
		OutResult.Warnings.Append(Report.Errors);
	}

	OutResult.bSuccess = true;
	OutResult.SystemPath = System->GetPathName();
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara,
		FString::Printf(TEXT("V2 Build pipeline completed: %s (%d layers)"), *OutResult.SystemPath, Spec.Layers.Num()));
	return true;
}
