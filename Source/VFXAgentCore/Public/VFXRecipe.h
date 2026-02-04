#pragma once

#include "CoreMinimal.h"
#include "VFXRecipe.generated.h"

// ============================================================================
// VFX INTENT LAYER - Director-level semantic understanding
// ============================================================================

UENUM(BlueprintType)
enum class EVFXArchetype : uint8
{
	Explosion UMETA(DisplayName = "Explosion"),
	Tornado UMETA(DisplayName = "Tornado"),
	Aura UMETA(DisplayName = "Aura"),
	Trail UMETA(DisplayName = "Trail"),
	Fountain UMETA(DisplayName = "Fountain"),
	Beam UMETA(DisplayName = "Beam"),
	Dust UMETA(DisplayName = "Dust"),
	Smoke UMETA(DisplayName = "Smoke"),
	Fire UMETA(DisplayName = "Fire"),
	Sparks UMETA(DisplayName = "Sparks"),
	Impact UMETA(DisplayName = "Impact"),
	Custom UMETA(DisplayName = "Custom")
};

UENUM(BlueprintType)
enum class EVFXMotionModel : uint8
{
	Radial UMETA(DisplayName = "Radial (Outward Explosion)"),
	RadialInward UMETA(DisplayName = "Radial Inward (Vortex Attraction)"),
	Orbit UMETA(DisplayName = "Orbit (Circular Motion)"),
	Vortex UMETA(DisplayName = "Vortex (Swirling)"),
	Directional UMETA(DisplayName = "Directional (Cone/Beam)"),
	Vertical UMETA(DisplayName = "Vertical (Upward/Downward)"),
	Turbulent UMETA(DisplayName = "Turbulent (Chaotic)"),
	Static UMETA(DisplayName = "Static (Stationary)")
};

// Behaviors that should NEVER be used for a given effect
USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXPatternAvoidance
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avoidance")
	bool bAvoidConeVelocity = false; // No outward cone spray

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avoidance")
	bool bAvoidRadialExplosion = false; // No radial burst

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avoidance")
	bool bAvoidUniformGravity = false; // No downward gravity

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avoidance")
	bool bAvoidUniformRotation = false; // No simple spin

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avoidance")
	bool bAvoidHighSpread = false; // Stay tight/focused
};

// Motion behavior definition for directing Niagara composition
USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXMotionBehavior
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion")
	EVFXMotionModel PrimaryModel = EVFXMotionModel::Radial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion")
	FVector MotionAxis = FVector(0, 0, 1); // For orbit/vortex

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion")
	bool bRadiusDependsOnHeight = false; // Funnel effect

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion")
	bool bAngularVelocityIncreases = false; // Faster at top

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion")
	bool bCentripetal = false; // Attract to center

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion")
	float CentripetalStrength = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion")
	bool bHeightDriven = false; // Different behavior at different heights
};

// Visual hierarchy - what is dominant and secondary
USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXVisualHierarchy
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hierarchy")
	FString DominantElement; // Main visual (e.g., "core_funnel")

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hierarchy")
	float DominantWeight = 1.0f; // Visual priority (0-1)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hierarchy")
	TArray<FString> SecondaryElements; // Supporting visuals

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hierarchy")
	TArray<float> SecondaryWeights; // Individual priorities
};

// The VFX Intent - Director's understanding BEFORE generating Niagara
USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXIntent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intent")
	EVFXArchetype Archetype = EVFXArchetype::Custom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intent")
	FVFXMotionBehavior Motion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intent")
	FVFXVisualHierarchy Hierarchy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intent")
	FVFXPatternAvoidance Avoidance;

	// Required effect layers (names like "core_funnel", "debris", "dust")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intent")
	TArray<FString> RequiredLayers;

	// Key physics behaviors needed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intent")
	TArray<FString> RequiredForces; // e.g., "vortex", "centripetal", "lift"

	// How many emitters needed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intent")
	int32 SuggestedEmitterCount = 1;

	// Semantic description for logging
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intent")
	FString Description;
};

// ============================================================================
// RECIPE STRUCTURES (Niagara-level compilation targets)
// ============================================================================

USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXEmitterRecipe
{
	GENERATED_BODY()

	// Optional human-readable layer name/purpose (e.g. "CoreBurst", "Sparks", "Smoke", "Shockwave").
	// Used for naming within the generated Niagara System.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FString Name;

	// === Spawn Parameters ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float SpawnRate = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	int32 BurstCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float BurstTime = 0.0f; // When to trigger burst (0 = at start)

	// === Renderer ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Renderer")
	FString RendererType = "Sprite"; // Sprite, Mesh, Ribbon

	// New: Specify a preferred Niagara template to base this emitter on.
	// Examples: "Fountain", "DirectionalBurst", "HangingParticulates", "OmnidirectionalBurst", "UpwardMeshBurst", "Beam"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FString TemplateName = "Fountain";

	// === Color & Appearance ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor Color = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor ColorEnd = FLinearColor::White; // Color at end of lifetime (for gradient)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	bool bUseColorGradient = false;

	// === Lifetime & Size ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lifetime")
	float Lifetime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lifetime")
	float LifetimeVariation = 0.0f; // Random variation (0-1, multiplier)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Size")
	float Size = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Size")
	float SizeEnd = 10.0f; // Size at end of lifetime

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Size")
	bool bUseSizeOverLife = false; // Scale from Size to SizeEnd

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Size")
	float SizeVariation = 0.0f; // Random size variation (0-1, multiplier)

	// === Velocity & Movement ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")
	FVector Velocity = FVector(0, 0, 100); // Initial velocity

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")
	float VelocityVariation = 0.0f; // Random velocity variation (0-1, multiplier)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")
	FVector Acceleration = FVector(0, 0, -980); // Gravity or constant acceleration

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")
	float Drag = 0.0f; // Air resistance (0-10, 0=no drag)

	// === Rotation ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float InitialRotation = 0.0f; // Initial rotation in degrees

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float RotationRate = 0.0f; // Rotation speed in degrees/second

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float RotationRateVariation = 0.0f; // Random rotation variation

	// === Physics & Forces ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	bool bUseGravity = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics")
	float Mass = 1.0f;

	// === Emitter Shape ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape")
	FString EmitShape = "Point"; // Point, Sphere, Box, Cone, Cylinder

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape")
	FVector ShapeSize = FVector(100, 100, 100); // Size/radius of emit shape

	// === Material Assignment ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	int32 MaterialIndex = -1; // Index into Materials array, -1 for default

	// === Sorting & Rendering ===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")
	int32 SortOrder = 0; // Higher values render later (on top)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")
	bool bLocalSpace = false; // Particles move with emitter
};

USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXTextureRecipe
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	FString Name = "GeneratedTexture";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	FString Type = "Gradient"; // Gradient, Noise, Perlin, Voronoi, Custom

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	FLinearColor PrimaryColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	FLinearColor SecondaryColor = FLinearColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	int32 Resolution = 256; // Texture resolution (256, 512, 1024, etc.)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	float NoiseScale = 1.0f; // For noise-based textures

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	int32 Octaves = 4; // For fractal noise

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Texture")
	FString Description;
};

USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXMaterialRecipe
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FString Name = "GeneratedMaterial";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FString Description = "Basic additive material";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	bool bIsAdditive = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	bool bIsUnlit = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FString BaseMaterialPath = "/Niagara/DefaultAssets/DefaultSpriteMaterial.DefaultSpriteMaterial";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FLinearColor BaseColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FLinearColor EmissiveColor = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	float EmissiveStrength = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	float Opacity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	float Roughness = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	float Metallic = 0.0f;

	// Textures to use (can reference generated textures)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FString BaseColorTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FString EmissiveTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FString OpacityTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	FString NormalTexture;

	// Auto-generate textures based on these recipes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	TArray<FVFXTextureRecipe> GeneratedTextures;
};

// --- New Schema for Niagara Spec ---

UENUM(BlueprintType)
enum class EVFXRendererType : uint8
{
	Sprite UMETA(DisplayName = "Sprite"),
	Ribbon UMETA(DisplayName = "Ribbon"),
	Light UMETA(DisplayName = "Light")
};

USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXPerSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float Rate = 0.0f; // If > 0, use SpawnRate

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	int32 Burst = 0; // If > 0, use Burst

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float BurstTime = 0.0f; // Time for burst spawn (0 = immediate)
};

UENUM(BlueprintType)
enum class EVFXForceType : uint8
{
	CurlNoise UMETA(DisplayName = "CurlNoise"),
	Noise UMETA(DisplayName = "Noise"),
	Drag UMETA(DisplayName = "Drag"),
	Gravity UMETA(DisplayName = "Gravity"),
	Vortex UMETA(DisplayName = "Vortex"),
	Lift UMETA(DisplayName = "Lift"),
	LimitVelocity UMETA(DisplayName = "LimitVelocity")
};

USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXCurveKey
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Curve")
	float Time = 0.0f; // 0-1

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Curve")
	float Value = 0.0f;
};

USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXColorKey
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Curve")
	float Time = 0.0f; // 0-1

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Curve")
	FLinearColor Color = FLinearColor::White;
};

USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXCurveRecipe
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Curve")
	TArray<FVFXCurveKey> Size;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Curve")
	TArray<FVFXCurveKey> Alpha;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Curve")
	TArray<FVFXColorKey> Color;
};

USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXForceRecipe
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Force")
	EVFXForceType Type = EVFXForceType::CurlNoise;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Force")
	float Strength = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Force")
	float Frequency = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Force")
	FVector Direction = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Force")
	float Radius = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Force")
	float MaxVelocity = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Force")
	bool bEnabled = true;
};

USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXRenderRecipe
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Render")
	FString RendererType = "Sprite"; // Sprite, Mesh, Ribbon, Light

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Render")
	FString FacingMode = "Camera"; // Camera, Velocity, Custom

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Render")
	FString Alignment = "Unaligned"; // Unaligned, VelocityAligned, Custom

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Render")
	bool bSoftParticles = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Render")
	bool bVelocityAligned = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Render")
	float MotionStretch = 0.0f;
};

USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXLayerRecipe
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layer")
	FString Name = "Layer";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layer")
	FString Role = "core"; // core/smoke/sparks/trail/etc

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	FVFXPerSpawnInfo Spawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lifetime")
	float Lifetime = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lifetime")
	float LifetimeVariation = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Size")
	float Size = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor Color = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")
	FVector InitialVelocity = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity")
	float VelocityVariation = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Forces")
	TArray<FVFXForceRecipe> Forces;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Curves")
	FVFXCurveRecipe Curves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Render")
	FVFXRenderRecipe Render;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape")
	FString EmitShape = "Point";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape")
	FVector ShapeSize = FVector(100, 100, 100);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")
	int32 SortOrder = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rendering")
	bool bLocalSpace = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	int32 MaterialIndex = -1;
};

UENUM(BlueprintType)
enum class EVFXEventType : uint8
{
	OnEmitterStart UMETA(DisplayName = "OnEmitterStart"),
	OnEmitterBurst UMETA(DisplayName = "OnEmitterBurst"),
	OnEmitterDeath UMETA(DisplayName = "OnEmitterDeath"),
	OnEmitterCollision UMETA(DisplayName = "OnEmitterCollision")
};

USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXEventRecipe
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	FString SourceLayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	FString TargetLayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	EVFXEventType Type = EVFXEventType::OnEmitterDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	float Delay = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	float BurstMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	float RateMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
	int32 BurstOverride = 0;
};

USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXEmitterSpec
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FString Name;

	// Path to a Niagara System or Emitter asset to use as template
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FString TemplatePath;

	// Or a known ID like "Fountain", "Beam" if we support mapping
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FString TemplateId; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	EVFXRendererType RendererType = EVFXRendererType::Sprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FVFXPerSpawnInfo Spawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FLinearColor Color = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FLinearColor ColorEnd = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	bool bUseColorGradient = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	float Lifetime = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	float LifetimeVariation = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	float Size = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	float SizeEnd = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	bool bUseSizeOverLife = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	float SizeVariation = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	float VelocityVariation = 0.0f;

	// Forces (module-driven)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Forces")
	float CurlNoiseStrength = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Forces")
	float CurlNoiseFrequency = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Forces")
	float NoiseStrength = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Forces")
	float NoiseFrequency = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Forces")
	float LimitVelocity = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Forces")
	float VortexStrength = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Forces")
	FVector VortexAxis = FVector(0, 0, 1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Forces")
	float LiftStrength = 0.0f;

	// Physics
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Physics")
	float Drag = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Physics")
	FVector Acceleration = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Physics")
	bool bUseGravity = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Physics")
	float Mass = 1.0f;

	// Rotation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Rotation")
	float RotationRate = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Rotation")
	float InitialRotation = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Rotation")
	float RotationRateVariation = 0.0f;

	// Alpha over life
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Color")
	float Alpha = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Color")
	float AlphaEnd = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Color")
	bool bUseAlphaOverLife = false;

	// Render options
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Rendering")
	FString FacingMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Rendering")
	FString Alignment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Rendering")
	bool bVelocityAligned = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Rendering")
	float MotionStretch = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Rendering")
	int32 SortOrder = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Rendering")
	bool bLocalSpace = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Shape")
	FString EmitShape;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter|Shape")
	FVector ShapeSize = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitter")
	FString Notes;
};

USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXEffectSpec
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	FString OutputPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	TArray<FVFXEmitterSpec> Emitters;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	TArray<FVFXMaterialRecipe> Materials;
	
	// NEW: Intent for constraint-aware generation (non-optional for simplicity)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	FVFXIntent Intent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect")
	bool bHasIntent = false;
};

USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXRepairReport
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Report")
	FString SystemPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Report")
	bool bCompileSuccess = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Report")
	TArray<FString> Errors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Report")
	TArray<FString> Warnings;
};

USTRUCT(BlueprintType)
struct VFXAGENTCORE_API FVFXRecipe
{
	GENERATED_BODY()

	// ========== NEW: VFX Intent Layer (Director's Understanding) ==========
	// This is the semantic understanding of WHAT the effect is, BEFORE Niagara modules
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intent")
	FVFXIntent Intent;
	
	// ========== NEW: Niagara Spec (Constraint-aware compilation target) ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spec")
	FVFXEffectSpec Spec;

	// ========== System-level properties ==========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "System")
	bool bLoop = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "System")
	float Duration = 0.0f; // 0 for infinite

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "System")
	float WarmupTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "System")
	FVector Bounds = FVector(100.0f, 100.0f, 100.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Emitters")
	TArray<FVFXEmitterRecipe> Emitters;

	// New layered recipe format
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Layers")
	TArray<FVFXLayerRecipe> Layers;

	// Event chain between layers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Events")
	TArray<FVFXEventRecipe> Events;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	TMap<FString, FString> Parameters; // User parameters like color, intensity

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	TArray<FVFXMaterialRecipe> Materials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dependencies")
	TArray<FString> Dependencies; // Texture/Model paths

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Version")
	int32 Version = 1;
};