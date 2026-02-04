#pragma once

#include "CoreMinimal.h"
#include "VFXRecipe.h"

class UNiagaraEmitter;
class UNiagaraScript;

/**
 * Motion Module Library - Provides reusable motion behaviors for Niagara VFX
 * Each motion behavior consists of a set of modules, parameters, and curves.
 */

// Module phase classification (must be declared before FMotionModuleDescriptor)
enum class EModulePhase : uint8
{
	PreSim = 0,
	Forces = 1,
	Damping = 2,
	Clamp = 3,
	Integrate = 4,
	CollisionDetect = 5,
	EventWrite = 6,
	PostCollisionResponse = 7,
	Curves = 8,
	RenderPrep = 9,
	KillCull = 10,
	Unknown = 99
};

enum class EMotionArchetype : uint8
{
	OrbitAroundAxis,      // Tornado-like swirl
	RadialOutward,        // Explosion expansion
	RadialInward,         // Vortex suction/attraction
	UpdraftColumn,        // Smoke/fire rising with buoyancy
	DirectionalCone,      // Fountain/spray
	RibbonTrailFollow,    // For ribbon trails
	Static,               // Stationary/minimal movement
	Turbulent,            // Chaotic noise-driven
	Custom                // User-defined
};

// Motion module descriptor
struct FMotionModuleDescriptor
{
	FString ModulePath;          // Path to Niagara script module
	FString DisplayName;         // Human-readable name
	EModulePhase Phase;          // Where to insert in stack
	int32 Priority;              // Insertion priority
	TMap<FString, float> DefaultParams; // Default parameter values
	bool bRequired;              // Must be present for this motion
	bool bIncompatibleWithGravity; // Can't coexist with gravity
	bool bIncompatibleWithCone;    // Can't coexist with cone velocity
};

// Motion behavior configuration
struct FMotionBehaviorConfig
{
	EMotionArchetype Archetype;
	TArray<FMotionModuleDescriptor> RequiredModules;
	TArray<FString> ForbiddenModulePatterns; // Modules to strip (e.g., "Add Velocity In Cone")
	bool bRequiresCustomVelocity;
	bool bForbidsGravity;
	bool bForbidsNoise;
	FString Description;
};

class VFXAGENTNIAGARA_API FVFXMotionModuleLibrary
{
public:
	// Get motion configuration for a given archetype
	static FMotionBehaviorConfig GetMotionConfig(EVFXArchetype VFXArchetype, EVFXMotionModel MotionModel);
	
	// Get motion configuration directly from archetype
	static FMotionBehaviorConfig GetMotionConfigByArchetype(EMotionArchetype MotionArchetype);
	
	// Map VFX intent to motion archetype
	static EMotionArchetype DetermineMotionArchetype(const FVFXIntent& Intent);
	
	// Get module paths for common Niagara modules
	static FString GetModulePath_CurlNoise();
	static FString GetModulePath_Vortex();
	static FString GetModulePath_Drag();
	static FString GetModulePath_Gravity();
	static FString GetModulePath_PointAttractor();
	static FString GetModulePath_ScaleVelocity();
	static FString GetModulePath_AddVelocity();
	static FString GetModulePath_SolveForces();
	static FString GetModulePath_SpawnRibbonID();
	static FString GetModulePath_InitializeRibbon();
	
	// Check if a module is forbidden for given motion
	static bool IsModuleForbidden(const FString& ModuleName, const FMotionBehaviorConfig& Config);
	
	// Generate motion-specific parameter overrides
	static TMap<FString, float> GenerateMotionParameters(EMotionArchetype Archetype, const FVFXIntent& Intent);

private:
	static void InitializeMotionConfigs();
	static TMap<EMotionArchetype, FMotionBehaviorConfig> MotionConfigs;
};

// Helper to classify script by phase
EModulePhase ClassifyScriptPhase(UNiagaraScript* Script);
