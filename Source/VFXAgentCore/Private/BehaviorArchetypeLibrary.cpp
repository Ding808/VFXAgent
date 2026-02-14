#include "BehaviorArchetypeLibrary.h"
#include "VFXAgentLog.h"

TArray<FBehaviorArchetypeDefinition> FBehaviorArchetypeLibrary::Definitions;
bool FBehaviorArchetypeLibrary::bInitialized = false;

// ---------------------------------------------------------------------------
// Helper: build a timing envelope
// ---------------------------------------------------------------------------
static FTimingEnvelopeV2 MakeTiming(float Delay, float Attack, float Sustain, float Decay, float Lifetime, bool bLoop = false)
{
	FTimingEnvelopeV2 T;
	T.DelaySeconds = Delay;
	T.AttackSeconds = Attack;
	T.SustainSeconds = Sustain;
	T.DecaySeconds = Decay;
	T.TotalLifetime = Lifetime;
	T.bLoop = bLoop;
	return T;
}

// ---------------------------------------------------------------------------
// Helper: build a layer preset
// ---------------------------------------------------------------------------
static FArchetypeLayerPreset MakePreset(
	ELayerRoleV2 Role, const FString& Name, const FString& Renderer,
	FTimingEnvelopeV2 Timing, EMotionVerbV2 Verb, float Speed,
	const FString& Blend, bool bFresnel, bool bDepthFade, bool bErode, bool bUVDist, int32 MaxP)
{
	FArchetypeLayerPreset P;
	P.Role = Role;
	P.DefaultName = Name;
	P.RendererType = Renderer;
	P.Timing = Timing;
	P.MotionVerb = Verb;
	P.MotionSpeed = Speed;
	P.BlendMode = Blend;
	P.bFresnel = bFresnel;
	P.bDepthFade = bDepthFade;
	P.bErodeMask = bErode;
	P.bUVDistortion = bUVDist;
	P.MaxParticles = MaxP;
	return P;
}

// ---------------------------------------------------------------------------
// Initialize all four canonical archetypes
// ---------------------------------------------------------------------------
void FBehaviorArchetypeLibrary::InitializeLibrary()
{
	if (bInitialized) return;
	bInitialized = true;
	Definitions.Reset();

	// =======================================================================
	// 1. EXPLOSION / IMPACT
	// =======================================================================
	{
		FBehaviorArchetypeDefinition Def;
		Def.Archetype = EVFXBehaviorArchetype::Explosion;
		Def.DisplayName = TEXT("Explosion / Impact");
		Def.Description = TEXT("Radial outward burst with shockwave, debris, sparks, and smoke aftermath.");

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::CoreBlast, TEXT("core_blast"), TEXT("sprite"),
			MakeTiming(0.0f, 0.05f, 0.15f, 0.3f, 0.5f), EMotionVerbV2::Explode, 600.0f,
			TEXT("additive"), false, true, false, false, 300));

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::Distortion, TEXT("shockwave"), TEXT("sprite"),
			MakeTiming(0.0f, 0.02f, 0.08f, 0.2f, 0.3f), EMotionVerbV2::Pulse, 800.0f,
			TEXT("translucent"), false, true, false, true, 1));

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::Sparks, TEXT("sparks"), TEXT("sprite"),
			MakeTiming(0.02f, 0.05f, 0.3f, 0.5f, 0.9f), EMotionVerbV2::Explode, 500.0f,
			TEXT("additive"), false, false, false, false, 200));

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::Smoke, TEXT("smoke"), TEXT("sprite"),
			MakeTiming(0.1f, 0.3f, 1.0f, 1.5f, 3.0f), EMotionVerbV2::Rise, 50.0f,
			TEXT("translucent"), false, true, true, false, 80));

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::Glow, TEXT("flash"), TEXT("light"),
			MakeTiming(0.0f, 0.01f, 0.05f, 0.15f, 0.2f), EMotionVerbV2::Static, 0.0f,
			TEXT("additive"), false, false, false, false, 1));

		Def.Requirements.bRequiresForces = true;
		Def.Requirements.bRequiresEvents = true;       // Death→smoke spawn
		Def.Requirements.bRequiresLightRenderer = true;
		Def.Requirements.MinFeatureCount = 3;

		Def.ForbiddenPatterns = {
			TEXT("Orbit"), TEXT("Vortex"), TEXT("Spiral"),
			TEXT("bCentripetal"), TEXT("RadialInward")
		};

		Def.DefaultStyle.Palette = TEXT("warm_fire");
		Def.DefaultStyle.PrimaryColor = FLinearColor(1.0f, 0.6f, 0.1f, 1.0f);
		Def.DefaultStyle.SecondaryColor = FLinearColor(1.0f, 0.3f, 0.0f, 1.0f);
		Def.DefaultStyle.AccentColor = FLinearColor(1.0f, 0.9f, 0.7f, 1.0f);
		Def.DefaultStyle.MoodTag = TEXT("aggressive");

		Def.CameraReadability.PreferredDistance = TEXT("medium");
		Def.CameraReadability.BoundsRadius = 300.0f;
		Def.CameraReadability.bNeedsSilhouette = true;
		Def.CameraReadability.ContrastTarget = 0.8f;

		Definitions.Add(MoveTemp(Def));
	}

	// =======================================================================
	// 2. MAGIC / AURA / HEALING
	// =======================================================================
	{
		FBehaviorArchetypeDefinition Def;
		Def.Archetype = EVFXBehaviorArchetype::Magic;
		Def.DisplayName = TEXT("Magic / Aura / Healing");
		Def.Description = TEXT("Orbiting particles, soft glow, ribbon trails, pulsing energy.");

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::CoreBlast, TEXT("core_orbs"), TEXT("sprite"),
			MakeTiming(0.0f, 0.2f, 2.0f, 0.5f, 3.0f, true), EMotionVerbV2::Orbit, 120.0f,
			TEXT("additive"), true, true, false, false, 50));

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::Trail, TEXT("ribbon_trail"), TEXT("ribbon"),
			MakeTiming(0.0f, 0.1f, 2.0f, 0.5f, 2.5f, true), EMotionVerbV2::Orbit, 100.0f,
			TEXT("additive"), true, true, false, false, 80));

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::SecondaryFill, TEXT("sparkle_fill"), TEXT("sprite"),
			MakeTiming(0.1f, 0.3f, 2.0f, 0.8f, 3.0f, true), EMotionVerbV2::Flutter, 30.0f,
			TEXT("additive"), false, true, false, false, 120));

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::Glow, TEXT("aura_glow"), TEXT("sprite"),
			MakeTiming(0.0f, 0.5f, 2.0f, 1.0f, 3.5f, true), EMotionVerbV2::Pulse, 10.0f,
			TEXT("additive"), true, true, false, false, 5));

		Def.Requirements.bRequiresForces = true;
		Def.Requirements.bRequiresRibbonRenderer = true;
		Def.Requirements.MinFeatureCount = 2;

		Def.ForbiddenPatterns = {
			TEXT("Gravity"), TEXT("Collision"), TEXT("Explode"),
			TEXT("AddVelocityCone"), TEXT("bUseGravity")
		};

		Def.DefaultStyle.Palette = TEXT("cool_magic");
		Def.DefaultStyle.PrimaryColor = FLinearColor(0.4f, 0.6f, 1.0f, 1.0f);
		Def.DefaultStyle.SecondaryColor = FLinearColor(0.7f, 0.4f, 1.0f, 1.0f);
		Def.DefaultStyle.AccentColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);
		Def.DefaultStyle.MoodTag = TEXT("ethereal");

		Def.CameraReadability.PreferredDistance = TEXT("close");
		Def.CameraReadability.BoundsRadius = 150.0f;
		Def.CameraReadability.bNeedsSilhouette = false;
		Def.CameraReadability.ContrastTarget = 0.5f;

		Definitions.Add(MoveTemp(Def));
	}

	// =======================================================================
	// 3. ELECTRIC / ARC / LIGHTNING
	// =======================================================================
	{
		FBehaviorArchetypeDefinition Def;
		Def.Archetype = EVFXBehaviorArchetype::Electric;
		Def.DisplayName = TEXT("Electric / Arc / Lightning");
		Def.Description = TEXT("Sharp branching arcs, ribbon lightning, spark showers, bright flash.");

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::CoreBlast, TEXT("arc_core"), TEXT("ribbon"),
			MakeTiming(0.0f, 0.01f, 0.08f, 0.05f, 0.15f), EMotionVerbV2::Snap, 1200.0f,
			TEXT("additive"), true, false, false, true, 30));

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::Trail, TEXT("arc_branches"), TEXT("ribbon"),
			MakeTiming(0.01f, 0.02f, 0.1f, 0.08f, 0.2f), EMotionVerbV2::Stream, 800.0f,
			TEXT("additive"), true, false, false, true, 50));

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::Sparks, TEXT("spark_shower"), TEXT("sprite"),
			MakeTiming(0.0f, 0.03f, 0.2f, 0.4f, 0.7f), EMotionVerbV2::Explode, 400.0f,
			TEXT("additive"), false, false, false, false, 300));

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::Glow, TEXT("flash_light"), TEXT("light"),
			MakeTiming(0.0f, 0.005f, 0.02f, 0.05f, 0.08f), EMotionVerbV2::Static, 0.0f,
			TEXT("additive"), false, false, false, false, 1));

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::Distortion, TEXT("emp_distortion"), TEXT("sprite"),
			MakeTiming(0.0f, 0.02f, 0.05f, 0.1f, 0.2f), EMotionVerbV2::Pulse, 500.0f,
			TEXT("translucent"), false, true, false, true, 2));

		Def.Requirements.bRequiresForces = true;
		Def.Requirements.bRequiresRibbonRenderer = true;
		Def.Requirements.bRequiresLightRenderer = true;
		Def.Requirements.MinFeatureCount = 3;

		Def.ForbiddenPatterns = {
			TEXT("Orbit"), TEXT("Vortex"), TEXT("bCentripetal"),
			TEXT("HeavyDrag"), TEXT("SlowMotion")
		};

		Def.DefaultStyle.Palette = TEXT("electric_blue");
		Def.DefaultStyle.PrimaryColor = FLinearColor(0.3f, 0.6f, 1.0f, 1.0f);
		Def.DefaultStyle.SecondaryColor = FLinearColor(0.8f, 0.9f, 1.0f, 1.0f);
		Def.DefaultStyle.AccentColor = FLinearColor(0.5f, 0.2f, 1.0f, 1.0f);
		Def.DefaultStyle.MoodTag = TEXT("sharp");

		Def.CameraReadability.PreferredDistance = TEXT("medium");
		Def.CameraReadability.BoundsRadius = 250.0f;
		Def.CameraReadability.bNeedsSilhouette = true;
		Def.CameraReadability.ContrastTarget = 0.9f;

		Definitions.Add(MoveTemp(Def));
	}

	// =======================================================================
	// 4. TELEPORT / PORTAL / WARP
	// =======================================================================
	{
		FBehaviorArchetypeDefinition Def;
		Def.Archetype = EVFXBehaviorArchetype::Teleport;
		Def.DisplayName = TEXT("Teleport / Portal / Warp");
		Def.Description = TEXT("Implosion to center, swirling vortex, flash, residual particles.");

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::CoreBlast, TEXT("vortex_core"), TEXT("sprite"),
			MakeTiming(0.0f, 0.3f, 0.5f, 0.3f, 1.2f), EMotionVerbV2::Implode, 300.0f,
			TEXT("additive"), true, true, true, false, 100));

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::Trail, TEXT("spiral_ribbons"), TEXT("ribbon"),
			MakeTiming(0.0f, 0.2f, 0.8f, 0.4f, 1.5f), EMotionVerbV2::Spiral, 200.0f,
			TEXT("additive"), true, true, false, false, 60));

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::Distortion, TEXT("warp_distortion"), TEXT("sprite"),
			MakeTiming(0.2f, 0.1f, 0.3f, 0.2f, 0.8f), EMotionVerbV2::Pulse, 150.0f,
			TEXT("translucent"), false, true, false, true, 3));

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::Glow, TEXT("flash_burst"), TEXT("light"),
			MakeTiming(0.5f, 0.02f, 0.05f, 0.15f, 0.3f), EMotionVerbV2::Static, 0.0f,
			TEXT("additive"), false, false, false, false, 1));

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::SecondaryFill, TEXT("residual_particles"), TEXT("sprite"),
			MakeTiming(0.8f, 0.2f, 0.5f, 1.0f, 2.0f), EMotionVerbV2::Drift, 20.0f,
			TEXT("additive"), false, true, true, false, 40));

		Def.Requirements.bRequiresForces = true;
		Def.Requirements.bRequiresRibbonRenderer = true;
		Def.Requirements.bRequiresEvents = true;   // Flash on collapse
		Def.Requirements.MinFeatureCount = 3;

		Def.ForbiddenPatterns = {
			TEXT("AddVelocityCone"), TEXT("bUseGravity"), TEXT("Collision"),
			TEXT("RadialOutward")
		};

		Def.DefaultStyle.Palette = TEXT("void_purple");
		Def.DefaultStyle.PrimaryColor = FLinearColor(0.5f, 0.1f, 0.9f, 1.0f);
		Def.DefaultStyle.SecondaryColor = FLinearColor(0.2f, 0.0f, 0.5f, 1.0f);
		Def.DefaultStyle.AccentColor = FLinearColor(0.8f, 0.6f, 1.0f, 1.0f);
		Def.DefaultStyle.MoodTag = TEXT("mysterious");

		Def.CameraReadability.PreferredDistance = TEXT("medium");
		Def.CameraReadability.BoundsRadius = 200.0f;
		Def.CameraReadability.bNeedsSilhouette = true;
		Def.CameraReadability.ContrastTarget = 0.75f;

		Definitions.Add(MoveTemp(Def));
	}

	// =======================================================================
	// Fallback archetypes (Fire, Smoke, Water, Custom) with minimal presets
	// =======================================================================
	auto AddMinimalArchetype = [&](EVFXBehaviorArchetype Arch, const FString& Name, const FString& Desc,
		FLinearColor Primary, const FString& Mood)
	{
		FBehaviorArchetypeDefinition Def;
		Def.Archetype = Arch;
		Def.DisplayName = Name;
		Def.Description = Desc;

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::CoreBlast, TEXT("core"), TEXT("sprite"),
			MakeTiming(0.0f, 0.1f, 0.5f, 0.5f, 1.5f), EMotionVerbV2::Rise, 100.0f,
			TEXT("additive"), false, true, false, false, 200));

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::SecondaryFill, TEXT("fill"), TEXT("sprite"),
			MakeTiming(0.1f, 0.2f, 0.8f, 0.6f, 2.0f), EMotionVerbV2::Drift, 30.0f,
			TEXT("translucent"), false, true, false, false, 100));

		Def.LayerPresets.Add(MakePreset(
			ELayerRoleV2::Glow, TEXT("glow"), TEXT("sprite"),
			MakeTiming(0.0f, 0.3f, 1.0f, 0.5f, 2.0f, true), EMotionVerbV2::Static, 0.0f,
			TEXT("additive"), true, true, false, false, 5));

		Def.Requirements.bRequiresForces = true;
		Def.Requirements.MinFeatureCount = 2;
		Def.DefaultStyle.PrimaryColor = Primary;
		Def.DefaultStyle.MoodTag = Mood;

		Definitions.Add(MoveTemp(Def));
	};

	AddMinimalArchetype(EVFXBehaviorArchetype::Fire, TEXT("Fire / Combustion"),
		TEXT("Rising flames with ember debris"), FLinearColor(1, 0.4f, 0, 1), TEXT("aggressive"));
	AddMinimalArchetype(EVFXBehaviorArchetype::Smoke, TEXT("Smoke / Fog / Dust"),
		TEXT("Soft volumetric wisps"), FLinearColor(0.3f, 0.3f, 0.35f, 1), TEXT("ambient"));
	AddMinimalArchetype(EVFXBehaviorArchetype::Water, TEXT("Water / Splash / Rain"),
		TEXT("Fluid splashes and droplets"), FLinearColor(0.2f, 0.5f, 0.9f, 1), TEXT("fluid"));
	AddMinimalArchetype(EVFXBehaviorArchetype::Custom, TEXT("Custom"),
		TEXT("User-defined effect"), FLinearColor(1, 1, 1, 1), TEXT("custom"));
}

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------
const TArray<FBehaviorArchetypeDefinition>& FBehaviorArchetypeLibrary::GetAllDefinitions()
{
	InitializeLibrary();
	return Definitions;
}

const FBehaviorArchetypeDefinition& FBehaviorArchetypeLibrary::GetDefinition(EVFXBehaviorArchetype Archetype)
{
	InitializeLibrary();
	for (const FBehaviorArchetypeDefinition& Def : Definitions)
	{
		if (Def.Archetype == Archetype)
		{
			return Def;
		}
	}
	// Fallback to Custom
	for (const FBehaviorArchetypeDefinition& Def : Definitions)
	{
		if (Def.Archetype == EVFXBehaviorArchetype::Custom)
		{
			return Def;
		}
	}
	// Should never reach here
	static FBehaviorArchetypeDefinition Empty;
	return Empty;
}

void FBehaviorArchetypeLibrary::ApplyArchetypeDefaults(FEffectSpecV2& OutSpec)
{
	const FBehaviorArchetypeDefinition& Def = GetDefinition(OutSpec.Archetype);

	// Apply style defaults if not already set
	if (OutSpec.GlobalStyle.Palette.IsEmpty())
	{
		OutSpec.GlobalStyle = Def.DefaultStyle;
	}

	// Apply camera readability
	OutSpec.CameraReadability = Def.CameraReadability;

	// Apply requirements
	OutSpec.Requirements = Def.Requirements;

	// If spec has no layers, populate from archetype presets
	if (OutSpec.Layers.Num() == 0)
	{
		int32 SortIdx = 0;
		for (const FArchetypeLayerPreset& Preset : Def.LayerPresets)
		{
			FLayerSpecV2 Layer;
			Layer.Id = FString::Printf(TEXT("L%d"), SortIdx + 1);
			Layer.Name = Preset.DefaultName;
			Layer.Role = Preset.Role;
			Layer.RendererType = Preset.RendererType;
			Layer.SortOrder = SortIdx;
			Layer.Timing = Preset.Timing;
			Layer.Motion.Verb = Preset.MotionVerb;
			Layer.Motion.Speed = Preset.MotionSpeed;
			Layer.Material.Blend = Preset.BlendMode;
			Layer.Material.Features.bFresnel = Preset.bFresnel;
			Layer.Material.Features.bDepthFade = Preset.bDepthFade;
			Layer.Material.Features.bErodeMask = Preset.bErodeMask;
			Layer.Material.Features.bUVDistortion = Preset.bUVDistortion;
			Layer.MaxParticles = Preset.MaxParticles;
			OutSpec.Layers.Add(MoveTemp(Layer));
			++SortIdx;
		}
	}
}

TArray<FString> FBehaviorArchetypeLibrary::ValidateAgainstArchetype(const FEffectSpecV2& Spec)
{
	TArray<FString> Violations;
	const FBehaviorArchetypeDefinition& Def = GetDefinition(Spec.Archetype);

	// Check minimum layer count
	if (Spec.Layers.Num() < Def.LayerPresets.Num())
	{
		Violations.Add(FString::Printf(TEXT("Archetype '%s' expects at least %d layers, got %d"),
			*Def.DisplayName, Def.LayerPresets.Num(), Spec.Layers.Num()));
	}

	// Check feature requirements
	const FNiagaraFeatureRequirementsV2& Req = Def.Requirements;
	int32 FeatureCount = 0;

	bool bHasEvent = Spec.Events.Num() > 0;
	bool bHasForce = false;
	bool bHasRibbon = false;
	bool bHasLight = false;

	for (const FLayerSpecV2& Layer : Spec.Layers)
	{
		if (Layer.Motion.DragCoefficient > 0 || Layer.Motion.CurlNoiseIntensity > 0 || Layer.Motion.Speed > 0)
		{
			bHasForce = true;
		}
		if (Layer.RendererType.ToLower() == TEXT("ribbon"))
		{
			bHasRibbon = true;
		}
		if (Layer.RendererType.ToLower() == TEXT("light"))
		{
			bHasLight = true;
		}
	}

	if (bHasEvent) ++FeatureCount;
	if (bHasForce) ++FeatureCount;
	if (bHasRibbon) ++FeatureCount;
	if (bHasLight) ++FeatureCount;

	if (Req.bRequiresEvents && !bHasEvent)
		Violations.Add(TEXT("Archetype requires event bindings but none found"));
	if (Req.bRequiresRibbonRenderer && !bHasRibbon)
		Violations.Add(TEXT("Archetype requires at least one ribbon renderer"));
	if (Req.bRequiresLightRenderer && !bHasLight)
		Violations.Add(TEXT("Archetype requires at least one light renderer"));
	if (FeatureCount < Req.MinFeatureCount)
		Violations.Add(FString::Printf(TEXT("Must use at least %d Niagara features (events/forces/collision/light/ribbon), have %d"), Req.MinFeatureCount, FeatureCount));

	return Violations;
}

EVFXBehaviorArchetype FBehaviorArchetypeLibrary::InferFromPrompt(const FString& Prompt)
{
	const FString Lower = Prompt.ToLower();

	// Electric/Lightning
	if (Lower.Contains(TEXT("electric")) || Lower.Contains(TEXT("lightning")) || Lower.Contains(TEXT("arc")) || Lower.Contains(TEXT("tesla")) || Lower.Contains(TEXT("shock")))
	{
		return EVFXBehaviorArchetype::Electric;
	}
	// Teleport/Portal
	if (Lower.Contains(TEXT("teleport")) || Lower.Contains(TEXT("portal")) || Lower.Contains(TEXT("warp")) || Lower.Contains(TEXT("blink")) || Lower.Contains(TEXT("void")))
	{
		return EVFXBehaviorArchetype::Teleport;
	}
	// Magic/Aura
	if (Lower.Contains(TEXT("magic")) || Lower.Contains(TEXT("aura")) || Lower.Contains(TEXT("heal")) || Lower.Contains(TEXT("enchant")) || Lower.Contains(TEXT("buff")) || Lower.Contains(TEXT("spell")))
	{
		return EVFXBehaviorArchetype::Magic;
	}
	// Fire
	if (Lower.Contains(TEXT("fire")) || Lower.Contains(TEXT("flame")) || Lower.Contains(TEXT("burn")) || Lower.Contains(TEXT("combust")) || Lower.Contains(TEXT("inferno")))
	{
		return EVFXBehaviorArchetype::Fire;
	}
	// Smoke
	if (Lower.Contains(TEXT("smoke")) || Lower.Contains(TEXT("fog")) || Lower.Contains(TEXT("dust")) || Lower.Contains(TEXT("mist")))
	{
		return EVFXBehaviorArchetype::Smoke;
	}
	// Water
	if (Lower.Contains(TEXT("water")) || Lower.Contains(TEXT("splash")) || Lower.Contains(TEXT("rain")) || Lower.Contains(TEXT("wave")))
	{
		return EVFXBehaviorArchetype::Water;
	}
	// Explosion (default for impact-like terms)
	if (Lower.Contains(TEXT("explo")) || Lower.Contains(TEXT("blast")) || Lower.Contains(TEXT("impact")) || Lower.Contains(TEXT("boom")) || Lower.Contains(TEXT("detonate")) || Lower.Contains(TEXT("burst")))
	{
		return EVFXBehaviorArchetype::Explosion;
	}

	return EVFXBehaviorArchetype::Custom;
}
