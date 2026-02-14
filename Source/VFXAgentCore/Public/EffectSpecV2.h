#pragma once

#include "CoreMinimal.h"
#include "EffectSpecV2.generated.h"

// ============================================================================
// VFX Spec v2 — Layered timing, motion language, material skeleton,
//               behavior archetype references, and quality constraints.
// ============================================================================

// ---------------------------------------------------------------------------
// Behavior Archetype Tag — canonical effect families
// ---------------------------------------------------------------------------
UENUM()
enum class EVFXBehaviorArchetype : uint8
{
	Explosion   UMETA(DisplayName = "Explosion / Impact"),
	Magic       UMETA(DisplayName = "Magic / Aura / Healing"),
	Electric    UMETA(DisplayName = "Electric / Arc / Lightning"),
	Teleport    UMETA(DisplayName = "Teleport / Portal / Warp"),
	Fire        UMETA(DisplayName = "Fire / Combustion"),
	Smoke       UMETA(DisplayName = "Smoke / Fog / Dust"),
	Water       UMETA(DisplayName = "Water / Splash / Rain"),
	Custom      UMETA(DisplayName = "Custom")
};

// ---------------------------------------------------------------------------
// Timing Envelope — when a layer starts, peaks, and ends
// ---------------------------------------------------------------------------
USTRUCT()
struct FTimingEnvelopeV2
{
	GENERATED_BODY()

	UPROPERTY() float DelaySeconds = 0.0f;    // Delay before layer starts
	UPROPERTY() float AttackSeconds = 0.1f;    // Ramp-up to full intensity
	UPROPERTY() float SustainSeconds = 0.5f;   // Full-intensity hold
	UPROPERTY() float DecaySeconds = 0.4f;     // Fade-out
	UPROPERTY() float TotalLifetime = 1.0f;    // Particle lifetime
	UPROPERTY() bool bLoop = false;
};

// ---------------------------------------------------------------------------
// Motion Language — semantic motion description per layer
// ---------------------------------------------------------------------------
UENUM()
enum class EMotionVerbV2 : uint8
{
	Explode     UMETA(DisplayName = "Explode (radial outward)"),
	Implode     UMETA(DisplayName = "Implode (radial inward)"),
	Rise        UMETA(DisplayName = "Rise (upward column)"),
	Fall        UMETA(DisplayName = "Fall (gravity pull)"),
	Orbit       UMETA(DisplayName = "Orbit (circular)"),
	Spiral      UMETA(DisplayName = "Spiral (helical)"),
	Drift       UMETA(DisplayName = "Drift (slow wander)"),
	Snap        UMETA(DisplayName = "Snap (instant teleport)"),
	Pulse       UMETA(DisplayName = "Pulse (expand/contract)"),
	Stream      UMETA(DisplayName = "Stream (directional flow)"),
	Flutter     UMETA(DisplayName = "Flutter (chaotic light)"),
	Static      UMETA(DisplayName = "Static (stationary)")
};

USTRUCT()
struct FMotionDescV2
{
	GENERATED_BODY()

	UPROPERTY() EMotionVerbV2 Verb = EMotionVerbV2::Explode;
	UPROPERTY() FVector Axis = FVector(0, 0, 1);         // Primary motion axis
	UPROPERTY() float Speed = 200.0f;                     // Base speed (cm/s)
	UPROPERTY() float SpeedVariation = 0.3f;              // 0-1 random variation
	UPROPERTY() float CurlNoiseIntensity = 0.0f;          // Turbulence overlay
	UPROPERTY() float CurlNoiseFrequency = 1.0f;
	UPROPERTY() float DragCoefficient = 0.0f;             // Air resistance
	UPROPERTY() FString SemanticNote;                      // Free-form note for debugging
};

// ---------------------------------------------------------------------------
// Material Skeleton — fixed building blocks that compose a VFX material
// ---------------------------------------------------------------------------
USTRUCT()
struct FMaterialFeatureSetV2
{
	GENERATED_BODY()

	// Core features (the "skeleton")
	UPROPERTY() bool bFresnel = false;                     // Rim-lighting / edge glow
	UPROPERTY() float FresnelExponent = 3.0f;
	UPROPERTY() bool bDepthFade = true;                    // Soft particle blending
	UPROPERTY() float DepthFadeDistance = 50.0f;
	UPROPERTY() bool bUVDistortion = false;                // UV distortion for heat haze
	UPROPERTY() float DistortionStrength = 0.0f;
	UPROPERTY() bool bNoiseMask = false;                   // Procedural noise masking
	UPROPERTY() float NoiseTiling = 4.0f;
	UPROPERTY() float NoiseContrast = 2.0f;
	UPROPERTY() bool bErodeMask = false;                   // Dissolve / erode effect
	UPROPERTY() float ErodeThreshold = 0.5f;               // 0=fully visible, 1=fully eroded
	UPROPERTY() bool bPanUV = false;                       // Scrolling UV
	UPROPERTY() FVector2D PanSpeed = FVector2D(0, 0);
};

USTRUCT()
struct FMaterialSpecV2
{
	GENERATED_BODY()

	UPROPERTY() FString Shading = TEXT("unlit");           // unlit | lit
	UPROPERTY() FString Blend = TEXT("additive");          // additive | translucent | masked | opaque
	UPROPERTY() FLinearColor BaseColor = FLinearColor(1, 1, 1, 1);
	UPROPERTY() FLinearColor EmissiveColor = FLinearColor(1, 1, 1, 1);
	UPROPERTY() float EmissiveIntensity = 5.0f;
	UPROPERTY() float Opacity = 0.8f;

	// Feature set (the composable skeleton)
	UPROPERTY() FMaterialFeatureSetV2 Features;

	// Texture slots (name → usage hint)
	UPROPERTY() TMap<FString, FString> TextureSlots;

	// HLSL Custom Node (optional)
	UPROPERTY() bool bCustomHLSL = false;
	UPROPERTY() FString HLSLCode;
	UPROPERTY() FString HLSLContract;                      // Brief doc of what the code does
};

// ---------------------------------------------------------------------------
// Layer Spec v2 — a single effect layer (maps to one Niagara emitter)
// ---------------------------------------------------------------------------
UENUM()
enum class ELayerRoleV2 : uint8
{
	CoreBlast   UMETA(DisplayName = "Core Blast"),
	SecondaryFill UMETA(DisplayName = "Secondary Fill"),
	Sparks      UMETA(DisplayName = "Sparks / Debris"),
	Trail       UMETA(DisplayName = "Trail / Ribbon"),
	Smoke       UMETA(DisplayName = "Smoke / Atmosphere"),
	Glow        UMETA(DisplayName = "Glow / Light"),
	Distortion  UMETA(DisplayName = "Distortion / Shockwave"),
	Ground      UMETA(DisplayName = "Ground Scorch / Decal"),
	Custom      UMETA(DisplayName = "Custom")
};

USTRUCT()
struct FLayerSpawnV2
{
	GENERATED_BODY()

	UPROPERTY() FString Mode = TEXT("burst");  // burst | rate | event
	UPROPERTY() float Rate = 0.0f;
	UPROPERTY() int32 BurstCount = 0;
};

USTRUCT()
struct FLayerInitV2
{
	GENERATED_BODY()

	UPROPERTY() float Lifetime = 2.0f;
	UPROPERTY() float LifetimeVariation = 0.2f;
	UPROPERTY() FVector2D SizeRange = FVector2D(10.0f, 30.0f);
	UPROPERTY() FVector Velocity = FVector::ZeroVector;
};

USTRUCT()
struct FLayerUpdateV2
{
	GENERATED_BODY()

	UPROPERTY() float Drag = 0.0f;
	UPROPERTY() float CurlNoiseStrength = 0.0f;
	UPROPERTY() FString ColorOverLife;   // e.g., "warm_to_cool" semantic
	UPROPERTY() FString AlphaOverLife;   // e.g., "fade_out_smooth"
	UPROPERTY() FString SizeOverLife;    // e.g., "grow_then_shrink"
};

USTRUCT()
struct FLayerSpecV2
{
	GENERATED_BODY()

	UPROPERTY() FString Id;
	UPROPERTY() FString Name;
	UPROPERTY() ELayerRoleV2 Role = ELayerRoleV2::CoreBlast;
	UPROPERTY() FString RendererType = TEXT("sprite");     // sprite | ribbon | mesh | light
	UPROPERTY() int32 SortOrder = 0;

	// Timing & rhythm
	UPROPERTY() FTimingEnvelopeV2 Timing;

	// Spawn
	UPROPERTY() FLayerSpawnV2 Spawn;

	// Init / Update
	UPROPERTY() FLayerInitV2 Init;
	UPROPERTY() FLayerUpdateV2 Update;

	// Motion
	UPROPERTY() FMotionDescV2 Motion;

	// Material
	UPROPERTY() FMaterialSpecV2 Material;

	// Quality budget
	UPROPERTY() int32 MaxParticles = 500;
	UPROPERTY() FString PerfHint = TEXT("mid");            // low | mid | high
};

// ---------------------------------------------------------------------------
// Event Binding v2 — inter-layer event chains
// ---------------------------------------------------------------------------
UENUM()
enum class EEventTypeV2 : uint8
{
	OnDeath          UMETA(DisplayName = "On Death"),
	OnCollision      UMETA(DisplayName = "On Collision"),
	OnSpawn          UMETA(DisplayName = "On Spawn"),
	OnLifetimeExpire UMETA(DisplayName = "On Lifetime Expire"),
	Timed            UMETA(DisplayName = "Timed Trigger")
};

USTRUCT()
struct FEventBindingV2
{
	GENERATED_BODY()

	UPROPERTY() FString SourceLayerId;
	UPROPERTY() FString TargetLayerId;
	UPROPERTY() EEventTypeV2 Type = EEventTypeV2::OnDeath;
	UPROPERTY() float Delay = 0.0f;
	UPROPERTY() int32 SpawnCount = 10;                     // How many particles to spawn on event
};

// ---------------------------------------------------------------------------
// Niagara Feature Requirements — hard constraints
// ---------------------------------------------------------------------------
USTRUCT()
struct FNiagaraFeatureRequirementsV2
{
	GENERATED_BODY()

	UPROPERTY() bool bRequiresEvents = false;              // At least one event binding
	UPROPERTY() bool bRequiresForces = true;               // At least one force module (drag/noise/vortex)
	UPROPERTY() bool bRequiresCollision = false;           // Collision detection
	UPROPERTY() bool bRequiresLightRenderer = false;       // Light renderer for illumination
	UPROPERTY() bool bRequiresRibbonRenderer = false;      // At least one ribbon layer

	// How many of the above must be satisfied (min 2 by default)
	UPROPERTY() int32 MinFeatureCount = 2;
};

// ---------------------------------------------------------------------------
// Camera Readability Hints
// ---------------------------------------------------------------------------
USTRUCT()
struct FCameraReadabilityV2
{
	GENERATED_BODY()

	UPROPERTY() FString PreferredDistance = TEXT("medium"); // close | medium | far
	UPROPERTY() float BoundsRadius = 200.0f;               // Expected visual radius (cm)
	UPROPERTY() bool bNeedsSilhouette = true;              // Should have clear silhouette
	UPROPERTY() float ContrastTarget = 0.7f;               // Target visual contrast 0-1
};

// ---------------------------------------------------------------------------
// Global Style v2 — palette, feel, reference
// ---------------------------------------------------------------------------
USTRUCT()
struct FEffectStyleV2
{
	GENERATED_BODY()

	UPROPERTY() FString Palette;                           // e.g., "cool_electric", "warm_fire"
	UPROPERTY() FLinearColor PrimaryColor = FLinearColor(1, 1, 1, 1);
	UPROPERTY() FLinearColor SecondaryColor = FLinearColor(0.5f, 0.5f, 0.5f, 1);
	UPROPERTY() FLinearColor AccentColor = FLinearColor(1, 0.5f, 0, 1);
	UPROPERTY() float RealismToStylized = 0.5f;           // 0=photorealistic, 1=stylized/anime
	UPROPERTY() float Brightness = 1.0f;
	UPROPERTY() float Saturation = 1.0f;
	UPROPERTY() FString MoodTag;                           // "aggressive", "ethereal", "chaotic", etc.
};

// ---------------------------------------------------------------------------
// Top-Level: EffectSpec v2
// ---------------------------------------------------------------------------
USTRUCT()
struct VFXAGENTCORE_API FEffectSpecV2
{
	GENERATED_BODY()

	static constexpr int32 Version = 2;

	UPROPERTY() FString EffectName;
	UPROPERTY() EVFXBehaviorArchetype Archetype = EVFXBehaviorArchetype::Explosion;
	UPROPERTY() FString ArchetypeVariant;                  // e.g., "shockwave_explosion", "heal_burst"
	UPROPERTY() FEffectStyleV2 GlobalStyle;
	UPROPERTY() TArray<FLayerSpecV2> Layers;
	UPROPERTY() TArray<FEventBindingV2> Events;
	UPROPERTY() FNiagaraFeatureRequirementsV2 Requirements;
	UPROPERTY() FCameraReadabilityV2 CameraReadability;

	// Brief semantic description for logging/debugging
	UPROPERTY() FString Description;
};
