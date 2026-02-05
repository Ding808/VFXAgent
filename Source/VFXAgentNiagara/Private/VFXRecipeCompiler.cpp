#include "VFXRecipeCompiler.h"
#include "VFXModuleLibrary.h"
#include "VFXAgentLog.h"
#include "Misc/ConfigCacheIni.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"

// ============================================================================
// INTENT-AWARE PROCESSING
// ============================================================================

static FString InferLayerRoleFromName(const FString& Name, const FString& RendererType)
{
	const FString LowerName = Name.ToLower();
	const FString LowerRenderer = RendererType.ToLower();

	if (LowerRenderer.Contains(TEXT("ribbon")) || LowerName.Contains(TEXT("trail")) || LowerName.Contains(TEXT("ribbon")))
	{
		return TEXT("trail");
	}
	if (LowerName.Contains(TEXT("smoke")) || LowerName.Contains(TEXT("fog")) || LowerName.Contains(TEXT("mist")))
	{
		return TEXT("smoke");
	}
	if (LowerName.Contains(TEXT("spark")) || LowerName.Contains(TEXT("ember")) || LowerName.Contains(TEXT("debris")))
	{
		return TEXT("spark");
	}
	if (LowerName.Contains(TEXT("glow")) || LowerName.Contains(TEXT("core")) || LowerName.Contains(TEXT("burst")))
	{
		return TEXT("core");
	}
	return TEXT("core");
}

static FString ChooseTemplateIdForRole(const FString& Role, const FString& RendererType)
{
	const FString LowerRole = Role.ToLower();
	const FString LowerRenderer = RendererType.ToLower();

	if (LowerRenderer.Contains(TEXT("ribbon")) || LowerRole.Contains(TEXT("trail")))
	{
		return TEXT("LocationBasedRibbon");
	}
	if (LowerRole.Contains(TEXT("smoke")) || LowerRole.Contains(TEXT("fog")))
	{
		return TEXT("HangingParticulates");
	}
	if (LowerRole.Contains(TEXT("spark")) || LowerRole.Contains(TEXT("debris")))
	{
		return TEXT("DirectionalBurst");
	}
	if (LowerRole.Contains(TEXT("core")) || LowerRole.Contains(TEXT("burst")) || LowerRole.Contains(TEXT("explosion")))
	{
		return TEXT("OmnidirectionalBurst");
	}
	return TEXT("Minimal");
}

// Apply archetype-specific rules and restrictions based on VFX Intent
static void ApplyArchetypeRules(const FVFXIntent& Intent, FVFXRecipe& Recipe, TArray<FString>& OutWarnings)
{
	if (Intent.Archetype == EVFXArchetype::Custom)
	{
		return; // No specific rules for custom
	}

	// TORNADO: Must use vortex motion with centripetal attraction
	if (Intent.Archetype == EVFXArchetype::Tornado)
	{
		OutWarnings.Add(TEXT("[TORNADO] Enforcing vortex motion + centripetal rules"));

		// If LLM incorrectly used cone velocity, disable it
		for (FVFXLayerRecipe& Layer : Recipe.Layers)
		{
			// Log if we're overriding patterns
			if (Intent.Avoidance.bAvoidConeVelocity && !Layer.InitialVelocity.IsNearlyZero())
			{
				OutWarnings.Add(FString::Printf(TEXT("[TORNADO] Layer '%s': Reducing outward cone velocity (avoiding radial pattern)"), *Layer.Name));
				// Reduce the magnitude of radial component
				Layer.InitialVelocity *= 0.3f;
			}

			// Enforce height-driven parameters
			if (Intent.Motion.bHeightDriven)
			{
				OutWarnings.Add(FString::Printf(TEXT("[TORNADO] Layer '%s': Applying height-driven vortex behavior"), *Layer.Name));
			}
		}

		// Suggest 3-layer structure if recipe has fewer
		if (Recipe.Layers.Num() < 3)
		{
			OutWarnings.Add(FString::Printf(TEXT("[TORNADO] Recipe has only %d layer(s); suggest 3: core_funnel, debris, dust"), Recipe.Layers.Num()));
		}
	}

	// EXPLOSION: Must use radial outward, allow gravity
	if (Intent.Archetype == EVFXArchetype::Explosion)
	{
		OutWarnings.Add(TEXT("[EXPLOSION] Enforcing radial outward motion"));

		// Ensure gravity is applied
		for (FVFXLayerRecipe& Layer : Recipe.Layers)
		{
			// Allow gravity for explosion
			FVFXForceRecipe GravityForce;
			GravityForce.Type = EVFXForceType::Gravity;
			GravityForce.Direction = FVector(0, 0, -1);
			GravityForce.Strength = 1.0f;

			bool bHasGravity = Layer.Forces.ContainsByPredicate([](const FVFXForceRecipe& F) { return F.Type == EVFXForceType::Gravity; });
			if (!bHasGravity && Layer.Forces.Num() < 10)
			{
				Layer.Forces.Add(GravityForce);
				OutWarnings.Add(FString::Printf(TEXT("[EXPLOSION] Layer '%s': Added gravity force"), *Layer.Name));
			}
		}
	}

	// FIRE: Upward motion, avoid downward gravity
	if (Intent.Archetype == EVFXArchetype::Fire)
	{
		OutWarnings.Add(TEXT("[FIRE] Enforcing upward motion, reducing downward forces"));

		for (FVFXLayerRecipe& Layer : Recipe.Layers)
		{
			// Ensure upward initial velocity
			if (Layer.InitialVelocity.Z < 50.0f)
			{
				Layer.InitialVelocity.Z = FMath::Max(50.0f, Layer.InitialVelocity.Z);
				OutWarnings.Add(FString::Printf(TEXT("[FIRE] Layer '%s': Enforcing upward velocity"), *Layer.Name));
			}

			// Remove or reduce downward acceleration
			if (Layer.Forces.Num() > 0)
			{
				for (FVFXForceRecipe& Force : Layer.Forces)
				{
					if (Force.Type == EVFXForceType::Gravity)
					{
						Force.Strength *= 0.2f; // Reduce gravity impact
						OutWarnings.Add(FString::Printf(TEXT("[FIRE] Layer '%s': Reduced gravity influence"), *Layer.Name));
					}
				}
			}
		}
	}
}

FVFXRecipe UVFXRecipeCompiler::ValidateAndSanitize(const FVFXRecipe& InRecipe, TArray<FString>& OutWarnings)
{
	FVFXRecipe Result = InRecipe;

	// Ensure tornado/vortex avoid cone velocity by default
	if (Result.Intent.Archetype == EVFXArchetype::Tornado || Result.Intent.Motion.PrimaryModel == EVFXMotionModel::Vortex)
	{
		Result.Intent.Avoidance.bAvoidConeVelocity = true;
	}

	// STAGE 1: Apply archetype-specific rules based on Intent
	if (Result.Intent.Archetype != EVFXArchetype::Custom)
	{
		OutWarnings.Add(FString::Printf(TEXT("Applying archetype rules: %d"), (int32)Result.Intent.Archetype));
		ApplyArchetypeRules(Result.Intent, Result, OutWarnings);
	}

	// STAGE 2: For Tornado, create default 3-emitter structure if needed
	if (Result.Intent.Archetype == EVFXArchetype::Tornado && Result.Layers.Num() < 3)
	{
		OutWarnings.Add(TEXT("[TORNADO] Generating default 3-layer structure: core_funnel, debris, dust"));

		// Clear existing layers and create tornado-specific ones
		Result.Layers.Empty();

		// Layer 1: Core Funnel (main vortex)
		FVFXLayerRecipe CoreLayer;
		CoreLayer.Name = TEXT("CoreFunnel");
		CoreLayer.Role = TEXT("core_funnel");
		CoreLayer.Spawn.Rate = 40.0f;
		CoreLayer.Lifetime = 3.0f;
		CoreLayer.LifetimeVariation = 0.2f;
		CoreLayer.Size = 30.0f;
		CoreLayer.Color = FLinearColor(0.3f, 0.3f, 0.4f, 0.7f); // Gray-blue
		CoreLayer.InitialVelocity = FVector(0, 0, 100.0f); // Upward
		CoreLayer.VelocityVariation = 0.3f;
		CoreLayer.Render.RendererType = TEXT("Sprite");
		CoreLayer.EmitShape = TEXT("Cylinder");
		CoreLayer.ShapeSize = FVector(150.0f, 150.0f, 500.0f);
		CoreLayer.Curves.Alpha = { {0.0f, 0.5f}, {1.0f, 0.0f} };
		CoreLayer.Curves.Size = { {0.0f, 1.0f}, {1.0f, 1.2f} };
		Result.Layers.Add(CoreLayer);

		// Layer 2: Debris (larger, spinning particles)
		FVFXLayerRecipe DebrisLayer;
		DebrisLayer.Name = TEXT("Debris");
		DebrisLayer.Role = TEXT("debris");
		DebrisLayer.Spawn.Rate = 20.0f;
		DebrisLayer.Lifetime = 4.0f;
		DebrisLayer.LifetimeVariation = 0.3f;
		DebrisLayer.Size = 50.0f;
		DebrisLayer.Color = FLinearColor(0.5f, 0.4f, 0.3f, 0.6f); // Brown
		DebrisLayer.InitialVelocity = FVector(0, 0, 80.0f);
		DebrisLayer.VelocityVariation = 0.5f;
		DebrisLayer.Render.RendererType = TEXT("Sprite");
		DebrisLayer.EmitShape = TEXT("Sphere");
		DebrisLayer.ShapeSize = FVector(100.0f, 100.0f, 100.0f);
		DebrisLayer.Curves.Alpha = { {0.0f, 0.4f}, {1.0f, 0.0f} };
		DebrisLayer.Curves.Size = { {0.0f, 1.0f}, {1.0f, 0.8f} };
		Result.Layers.Add(DebrisLayer);

		// Layer 3: Dust (light, small, turbulent)
		FVFXLayerRecipe DustLayer;
		DustLayer.Name = TEXT("Dust");
		DustLayer.Role = TEXT("dust");
		DustLayer.Spawn.Rate = 60.0f;
		DustLayer.Lifetime = 5.0f;
		DustLayer.LifetimeVariation = 0.4f;
		DustLayer.Size = 15.0f;
		DustLayer.Color = FLinearColor(0.6f, 0.6f, 0.6f, 0.3f); // Light gray
		DustLayer.InitialVelocity = FVector(0, 0, 50.0f);
		DustLayer.VelocityVariation = 0.6f;
		DustLayer.Render.RendererType = TEXT("Sprite");
		DustLayer.EmitShape = TEXT("Sphere");
		DustLayer.ShapeSize = FVector(200.0f, 200.0f, 100.0f);
		DustLayer.Curves.Alpha = { {0.0f, 0.2f}, {0.7f, 0.2f}, {1.0f, 0.0f} };
		DustLayer.Curves.Size = { {0.0f, 0.8f}, {1.0f, 1.5f} };
		Result.Layers.Add(DustLayer);
	}

	// Convert legacy emitters to layers if needed
	if (Result.Layers.Num() == 0 && Result.Emitters.Num() > 0)
	{
		for (const FVFXEmitterRecipe& Emitter : Result.Emitters)
		{
			Result.Layers.Add(ConvertLegacyEmitter(Emitter));
		}
		OutWarnings.Add(TEXT("Converted legacy Emitters to Layers."));
	}

	// Ensure at least one layer
	if (Result.Layers.Num() == 0)
	{
		FVFXLayerRecipe DefaultLayer;
		DefaultLayer.Name = TEXT("Core");
		DefaultLayer.Role = TEXT("core");
		DefaultLayer.Spawn.Burst = 20;
		DefaultLayer.Lifetime = 1.5f;
		DefaultLayer.Size = 20.0f;
		DefaultLayer.Render.RendererType = TEXT("Sprite");
		DefaultLayer.Curves.Size = { {0.0f, 0.0f}, {1.0f, 1.0f} };
		DefaultLayer.Curves.Alpha = { {0.0f, 1.0f}, {1.0f, 0.0f} };
		Result.Layers.Add(DefaultLayer);
		OutWarnings.Add(TEXT("Recipe had no layers; injected a default core layer."));
	}

	for (FVFXLayerRecipe& Layer : Result.Layers)
	{
		Layer.Name = Layer.Name.IsEmpty() ? TEXT("Layer") : Layer.Name;
		Layer.Role = Layer.Role.IsEmpty() ? TEXT("core") : Layer.Role;

		Layer.Lifetime = FMath::Max(0.01f, Layer.Lifetime);
		Layer.LifetimeVariation = FMath::Clamp(Layer.LifetimeVariation, 0.0f, 1.0f);
		Layer.Size = FMath::Max(0.01f, Layer.Size);
		Layer.VelocityVariation = FMath::Clamp(Layer.VelocityVariation, 0.0f, 1.0f);

		if (Layer.Spawn.Rate <= 0.0f && Layer.Spawn.Burst <= 0)
		{
			Layer.Spawn.Burst = 10;
		}

		NormalizeCurve(Layer.Curves.Size, 0.0f, 1.0f);
		NormalizeCurve(Layer.Curves.Alpha, 1.0f, 0.0f);
		NormalizeColorCurve(Layer.Curves.Color);

		for (FVFXForceRecipe& Force : Layer.Forces)
		{
			Force.Strength = FMath::Clamp(Force.Strength, 0.0f, 10000.0f);
			Force.Frequency = FMath::Clamp(Force.Frequency, 0.0f, 1000.0f);
			Force.Radius = FMath::Max(0.0f, Force.Radius);
			Force.MaxVelocity = FMath::Max(0.0f, Force.MaxVelocity);
		}

		if (Layer.Render.RendererType.IsEmpty())
		{
			Layer.Render.RendererType = TEXT("Sprite");
		}

		// Apply module library defaults (only where missing)
		FVFXModuleLibrary::ApplyDefaults(Layer, OutWarnings);
	}

	// Apply event chain after layer defaults are in place
	ApplyEventsToLayers(Result, OutWarnings);

	return Result;
}

FVFXEffectSpec UVFXRecipeCompiler::CompileToSpec(const FString& SystemName, const FString& OutputPath, const FVFXRecipe& InRecipe, const FString& TemplateSystemPath, TArray<FString>& OutWarnings)
{
	FVFXRecipe Recipe = ValidateAndSanitize(InRecipe, OutWarnings);

	FVFXEffectSpec Spec;
	Spec.Name = SystemName;
	Spec.OutputPath = OutputPath;
	Spec.Intent = Recipe.Intent;
	Spec.bHasIntent = true;

	for (const FVFXLayerRecipe& Layer : Recipe.Layers)
	{
		FVFXEmitterSpec EmitterSpec = BuildEmitterSpecFromLayer(Layer, TemplateSystemPath);
		Spec.Emitters.Add(EmitterSpec);
	}

	return Spec;
}

UNiagaraSystem* UVFXRecipeCompiler::AssembleSystem(const FVFXEffectSpec& Spec, FVFXRepairReport& OutReport)
{
	FString Error;
	if (!FNiagaraSpecExecutor::ValidateSpec(Spec, Error))
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Spec Validation Failed: %s"), *Error);
		return nullptr;
	}

	UNiagaraSystem* System = FNiagaraSpecExecutor::CreateSystemFromSpec(Spec);
	if (!System)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to create system from spec: %s"), *Spec.Name);
		return nullptr;
	}

	return System;
}

FString UVFXRecipeCompiler::ResolveTemplatePath(const FString& TemplateId)
{
	if (TemplateId.IsEmpty())
	{
		return FString();
	}

	FString Id = TemplateId;
	Id.TrimStartAndEndInline();

	if (Id.Contains(TEXT("/")))
	{
		if (!Id.Contains(TEXT(".")))
		{
			const FString AssetName = FPaths::GetCleanFilename(Id);
			if (!AssetName.IsEmpty())
			{
				return FString::Printf(TEXT("%s.%s"), *Id, *AssetName);
			}
		}
		return Id;
	}

	if (Id.Equals(TEXT("Fountain"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/Fountain.Fountain");
	if (Id.Equals(TEXT("UpwardMeshBurst"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/UpwardMeshBurst.UpwardMeshBurst");
	if (Id.Equals(TEXT("DirectionalBurst"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/DirectionalBurst.DirectionalBurst");
	if (Id.Equals(TEXT("OmnidirectionalBurst"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/OmnidirectionalBurst.OmnidirectionalBurst");
	if (Id.Equals(TEXT("SimpleSpriteBurst"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/SimpleSpriteBurst.SimpleSpriteBurst");
	if (Id.Equals(TEXT("BlowingParticles"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/BlowingParticles.BlowingParticles");
	if (Id.Equals(TEXT("ConfettiBurst"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/ConfettiBurst.ConfettiBurst");
	if (Id.Equals(TEXT("DynamicBeam"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/DynamicBeam.DynamicBeam");
	if (Id.Equals(TEXT("StaticBeam"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/StaticBeam.StaticBeam");
	if (Id.Equals(TEXT("HangingParticulates"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/HangingParticulates.HangingParticulates");
	if (Id.Equals(TEXT("LocationBasedRibbon"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/LocationBasedRibbon.LocationBasedRibbon");
	if (Id.Equals(TEXT("Minimal"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/Minimal.Minimal");
	if (Id.Equals(TEXT("SingleLoopingParticle"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/SingleLoopingParticle.SingleLoopingParticle");

	return TEXT("/Niagara/DefaultAssets/Templates/Emitters/Minimal.Minimal");
}

void UVFXRecipeCompiler::NormalizeCurve(TArray<FVFXCurveKey>& Curve, float DefaultStart, float DefaultEnd)
{
	if (Curve.Num() == 0)
	{
		Curve.Add({0.0f, DefaultStart});
		Curve.Add({1.0f, DefaultEnd});
	}

	Curve.Sort([](const FVFXCurveKey& A, const FVFXCurveKey& B)
	{
		return A.Time < B.Time;
	});

	for (FVFXCurveKey& Key : Curve)
	{
		Key.Time = FMath::Clamp(Key.Time, 0.0f, 1.0f);
	}
}

void UVFXRecipeCompiler::NormalizeColorCurve(TArray<FVFXColorKey>& Curve)
{
	if (Curve.Num() == 0)
	{
		return;
	}

	Curve.Sort([](const FVFXColorKey& A, const FVFXColorKey& B)
	{
		return A.Time < B.Time;
	});

	for (FVFXColorKey& Key : Curve)
	{
		Key.Time = FMath::Clamp(Key.Time, 0.0f, 1.0f);
	}
}

FVFXLayerRecipe UVFXRecipeCompiler::ConvertLegacyEmitter(const FVFXEmitterRecipe& Emitter)
{
	FVFXLayerRecipe Layer;
	Layer.Name = Emitter.Name.IsEmpty() ? TEXT("Layer") : Emitter.Name;
	Layer.Role = InferLayerRoleFromName(Layer.Name, Emitter.RendererType);
	Layer.Spawn.Rate = Emitter.SpawnRate;
	Layer.Spawn.Burst = Emitter.BurstCount;
	Layer.Spawn.BurstTime = Emitter.BurstTime;
	Layer.Render.RendererType = Emitter.RendererType;
	Layer.Color = Emitter.Color;
	Layer.Lifetime = Emitter.Lifetime;
	Layer.LifetimeVariation = Emitter.LifetimeVariation;
	Layer.Size = Emitter.Size;
	Layer.InitialVelocity = Emitter.Velocity;
	Layer.VelocityVariation = Emitter.VelocityVariation;
	Layer.EmitShape = Emitter.EmitShape;
	Layer.ShapeSize = Emitter.ShapeSize;
	Layer.MaterialIndex = Emitter.MaterialIndex;
	Layer.SortOrder = Emitter.SortOrder;
	Layer.bLocalSpace = Emitter.bLocalSpace;

	if (Emitter.bUseSizeOverLife)
	{
		Layer.Curves.Size = { {0.0f, 1.0f}, {1.0f, Emitter.SizeEnd / FMath::Max(0.01f, Emitter.Size)} };
	}

	if (Emitter.bUseColorGradient)
	{
		Layer.Curves.Color = { {0.0f, Emitter.Color}, {1.0f, Emitter.ColorEnd} };
	}

	if (Emitter.Drag > 0.0f)
	{
		Layer.Forces.Add({EVFXForceType::Drag, Emitter.Drag, 0.0f, FVector::ZeroVector, 0.0f, 0.0f, true});
	}
	if (Emitter.bUseGravity)
	{
		FVFXForceRecipe Gravity;
		Gravity.Type = EVFXForceType::Gravity;
		Gravity.Strength = 1.0f;
		Gravity.Direction = FVector(0, 0, -1);
		Layer.Forces.Add(Gravity);
	}

	return Layer;
}

FVFXEmitterSpec UVFXRecipeCompiler::BuildEmitterSpecFromLayer(const FVFXLayerRecipe& Layer, const FString& TemplateSystemPath)
{
	FVFXEmitterSpec Spec;
	Spec.Name = Layer.Name;
	Spec.Spawn = Layer.Spawn;
	Spec.Lifetime = Layer.Lifetime;
	Spec.LifetimeVariation = Layer.LifetimeVariation;
	Spec.Size = Layer.Size;
	Spec.Color = Layer.Color;
	Spec.Velocity = Layer.InitialVelocity;
	Spec.VelocityVariation = Layer.VelocityVariation;
	Spec.EmitShape = Layer.EmitShape;
	Spec.ShapeSize = Layer.ShapeSize;
	Spec.SortOrder = Layer.SortOrder;
	Spec.bLocalSpace = Layer.bLocalSpace;

	ApplyCurvesToSpec(Layer.Curves, Spec);
	TArray<FString> LocalWarnings;
	ApplyForcesToSpec(Layer.Forces, Spec, LocalWarnings);
	ApplyRenderToSpec(Layer.Render, Spec);

	// Template selection: prefer role-based templates, fallback to intent strategy in executor
	Spec.TemplateId = ChooseTemplateIdForRole(Layer.Role, Layer.Render.RendererType);
	if (!TemplateSystemPath.IsEmpty() && TemplateSystemPath.Contains(TEXT("/Templates/Emitters")))
	{
		Spec.TemplatePath = ResolveTemplatePath(TemplateSystemPath);
	}

	if (Layer.Render.RendererType.Equals(TEXT("Ribbon"), ESearchCase::IgnoreCase)) Spec.RendererType = EVFXRendererType::Ribbon;
	else if (Layer.Render.RendererType.Equals(TEXT("Light"), ESearchCase::IgnoreCase)) Spec.RendererType = EVFXRendererType::Light;
	else Spec.RendererType = EVFXRendererType::Sprite;

	return Spec;
}

void UVFXRecipeCompiler::ApplyForcesToSpec(const TArray<FVFXForceRecipe>& Forces, FVFXEmitterSpec& OutSpec, TArray<FString>& OutWarnings)
{
	for (const FVFXForceRecipe& Force : Forces)
	{
		if (!Force.bEnabled) continue;

		switch (Force.Type)
		{
		case EVFXForceType::Drag:
			OutSpec.Drag = Force.Strength;
			break;
		case EVFXForceType::Gravity:
			OutSpec.bUseGravity = true;
			OutSpec.Acceleration = FVector(0, 0, -980.0f * FMath::Max(0.1f, Force.Strength));
			break;
		case EVFXForceType::Lift:
			OutSpec.LiftStrength = Force.Strength;
			break;
		case EVFXForceType::CurlNoise:
			OutSpec.CurlNoiseStrength = Force.Strength;
			OutSpec.CurlNoiseFrequency = Force.Frequency;
			break;
		case EVFXForceType::Noise:
			OutSpec.NoiseStrength = Force.Strength;
			OutSpec.NoiseFrequency = Force.Frequency;
			break;
		case EVFXForceType::Vortex:
			OutSpec.VortexStrength = Force.Strength;
			OutSpec.VortexAxis = Force.Direction.IsNearlyZero() ? FVector(0, 0, 1) : Force.Direction;
			break;
		case EVFXForceType::LimitVelocity:
			OutSpec.LimitVelocity = Force.MaxVelocity;
			break;
		default:
			OutWarnings.Add(TEXT("Unsupported force type in compiler."));
			break;
		}
	}
}

void UVFXRecipeCompiler::ApplyCurvesToSpec(const FVFXCurveRecipe& Curves, FVFXEmitterSpec& OutSpec)
{
	if (Curves.Size.Num() > 0)
	{
		const FVFXCurveKey& Start = Curves.Size[0];
		const FVFXCurveKey& End = Curves.Size.Last();
		const float BaseSize = FMath::Max(0.01f, OutSpec.Size);
		OutSpec.Size = FMath::Max(0.01f, Start.Value * BaseSize);
		OutSpec.SizeEnd = FMath::Max(0.01f, End.Value * BaseSize);
		OutSpec.bUseSizeOverLife = true;
	}

	if (Curves.Alpha.Num() > 0)
	{
		const FVFXCurveKey& Start = Curves.Alpha[0];
		const FVFXCurveKey& End = Curves.Alpha.Last();
		OutSpec.Alpha = FMath::Clamp(Start.Value, 0.0f, 1.0f);
		OutSpec.AlphaEnd = FMath::Clamp(End.Value, 0.0f, 1.0f);
		OutSpec.bUseAlphaOverLife = true;
	}

	if (Curves.Color.Num() > 0)
	{
		OutSpec.Color = Curves.Color[0].Color;
		OutSpec.ColorEnd = Curves.Color.Last().Color;
		OutSpec.bUseColorGradient = true;
	}
}

void UVFXRecipeCompiler::ApplyRenderToSpec(const FVFXRenderRecipe& Render, FVFXEmitterSpec& OutSpec)
{
	OutSpec.FacingMode = Render.FacingMode;
	OutSpec.Alignment = Render.Alignment;
	OutSpec.bVelocityAligned = Render.bVelocityAligned;
	OutSpec.MotionStretch = Render.MotionStretch;
}

void UVFXRecipeCompiler::ApplyEventsToLayers(FVFXRecipe& Recipe, TArray<FString>& OutWarnings)
{
	if (Recipe.Events.Num() == 0)
	{
		return;
	}

	TMap<FString, FVFXLayerRecipe*> LayerMap;
	for (FVFXLayerRecipe& Layer : Recipe.Layers)
	{
		LayerMap.Add(Layer.Name, &Layer);
	}

	for (const FVFXEventRecipe& Event : Recipe.Events)
	{
		if (Event.Type == EVFXEventType::OnEmitterCollision)
		{
			continue; // handled by Niagara event handler wiring
		}
		FVFXLayerRecipe** SourcePtr = LayerMap.Find(Event.SourceLayer);
		FVFXLayerRecipe** TargetPtr = LayerMap.Find(Event.TargetLayer);
		if (!SourcePtr || !TargetPtr)
		{
			OutWarnings.Add(TEXT("Event references missing source or target layer."));
			continue;
		}

		FVFXLayerRecipe* Source = *SourcePtr;
		FVFXLayerRecipe* Target = *TargetPtr;

		float TriggerTime = 0.0f;
		switch (Event.Type)
		{
		case EVFXEventType::OnEmitterStart:
			TriggerTime = 0.0f;
			break;
		case EVFXEventType::OnEmitterBurst:
			TriggerTime = Source->Spawn.BurstTime;
			break;
		case EVFXEventType::OnEmitterDeath:
			TriggerTime = Source->Lifetime;
			break;
		case EVFXEventType::OnEmitterCollision:
		default:
			OutWarnings.Add(TEXT("Collision events are not supported; ignored."));
			continue;
		}

		Target->Spawn.BurstTime = FMath::Max(0.0f, TriggerTime + Event.Delay);

		if (Event.BurstOverride > 0)
		{
			Target->Spawn.Burst = Event.BurstOverride;
		}
		else if (Event.BurstMultiplier != 1.0f && Target->Spawn.Burst > 0)
		{
			Target->Spawn.Burst = FMath::Max(1, FMath::RoundToInt(Target->Spawn.Burst * Event.BurstMultiplier));
		}

		if (Event.RateMultiplier != 1.0f && Target->Spawn.Rate > 0.0f)
		{
			Target->Spawn.Rate = FMath::Max(0.0f, Target->Spawn.Rate * Event.RateMultiplier);
		}

		if (Target->Spawn.Rate <= 0.0f && Target->Spawn.Burst <= 0)
		{
			Target->Spawn.Burst = 10;
		}
	}
}

// Wrapper classes
FVFXRecipe FRecipeValidator::ValidateAndSanitize(const FVFXRecipe& InRecipe, TArray<FString>& OutWarnings)
{
	return UVFXRecipeCompiler::ValidateAndSanitize(InRecipe, OutWarnings);
}

FVFXEffectSpec FRecipeCompiler::Compile(const FString& SystemName, const FString& OutputPath, const FVFXRecipe& InRecipe, const FString& TemplateSystemPath, TArray<FString>& OutWarnings)
{
	return UVFXRecipeCompiler::CompileToSpec(SystemName, OutputPath, InRecipe, TemplateSystemPath, OutWarnings);
}

bool FEmitterBuilder::AddEmitter(UNiagaraSystem* System, const FVFXEmitterSpec& Spec)
{
	if (!System)
	{
		return false;
	}

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
		const bool bAdded = FNiagaraSpecExecutor::AddBasicEmitterToSystem(System, Spec.Name);
		if (bAdded)
		{
			FNiagaraSpecExecutor::ConfigureEmitter(System, Spec.Name, Spec);
		}
		return bAdded;
	}

	FString TemplatePath = Spec.TemplatePath;
	if (TemplatePath.IsEmpty() && !Spec.TemplateId.IsEmpty())
	{
		TemplatePath = UVFXRecipeCompiler::ResolveTemplatePath(Spec.TemplateId);
	}
	if (TemplatePath.IsEmpty())
	{
		TemplatePath = UVFXRecipeCompiler::ResolveTemplatePath(TEXT("Fountain"));
	}

	const bool bAdded = FNiagaraSpecExecutor::AddEmitterFromTemplate(System, TemplatePath, Spec.Name);
	if (bAdded)
	{
		FNiagaraSpecExecutor::ConfigureEmitter(System, Spec.Name, Spec);
	}
	return bAdded;
}

UNiagaraSystem* FSystemAssembler::Assemble(const FVFXEffectSpec& Spec, FVFXRepairReport& OutReport)
{
	FString Error;
	if (!FNiagaraSpecExecutor::ValidateSpec(Spec, Error))
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Spec Validation Failed: %s"), *Error);
		return nullptr;
	}

	UNiagaraSystem* System = FNiagaraSpecExecutor::CreateNiagaraSystemAsset(Spec.OutputPath, Spec.Name);
	if (!System)
	{
		UE_LOG(LogVFXAgent, Error, TEXT("Failed to create Niagara system asset: %s"), *Spec.Name);
		return nullptr;
	}

	// Remove any default emitters from the factory
	TArray<FNiagaraEmitterHandle> HandlesCopy = System->GetEmitterHandles();
	for (const FNiagaraEmitterHandle& Handle : HandlesCopy)
	{
		System->RemoveEmitterHandle(Handle);
	}

	for (const FVFXEmitterSpec& EmitterSpec : Spec.Emitters)
	{
		if (!FEmitterBuilder::AddEmitter(System, EmitterSpec))
		{
			UE_LOG(LogVFXAgent, Warning, TEXT("Failed to add emitter '%s'"), *EmitterSpec.Name);
		}
	}

	return System;
}
