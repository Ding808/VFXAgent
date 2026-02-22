#include "VFXMotionModuleLibrary.h"
#include "VFXAgentLog.h"
#include "NiagaraScript.h"

TMap<EMotionArchetype, FMotionBehaviorConfig> FVFXMotionModuleLibrary::MotionConfigs;

EModulePhase ClassifyScriptPhase(UNiagaraScript* Script)
{
	if (!Script) return EModulePhase::Unknown;
	const FString Name = Script->GetName().ToLower();
	
	if (Name.Contains(TEXT("initialize")) || Name.Contains(TEXT("set ")) || Name.Contains(TEXT("setvariables"))) 
		return EModulePhase::PreSim;
	if (Name.Contains(TEXT("curl")) || Name.Contains(TEXT("noise")) || Name.Contains(TEXT("vortex")) || 
		Name.Contains(TEXT("gravity")) || Name.Contains(TEXT("force")) || Name.Contains(TEXT("attractor"))) 
		return EModulePhase::Forces;
	if (Name.Contains(TEXT("drag")) || Name.Contains(TEXT("damp")) || Name.Contains(TEXT("scale velocity"))) 
		return EModulePhase::Damping;
	if (Name.Contains(TEXT("limit velocity")) || Name.Contains(TEXT("clamp")) || Name.Contains(TEXT("kill by speed"))) 
		return EModulePhase::Clamp;
	if (Name.Contains(TEXT("integrate"))) 
		return EModulePhase::Integrate;
	if (Name.Contains(TEXT("collision")) && !Name.Contains(TEXT("event"))) 
		return EModulePhase::CollisionDetect;
	if (Name.Contains(TEXT("event")) || Name.Contains(TEXT("generate collision")) || Name.Contains(TEXT("receive collision"))) 
		return EModulePhase::EventWrite;
	if (Name.Contains(TEXT("bounce")) || Name.Contains(TEXT("friction")) || Name.Contains(TEXT("post"))) 
		return EModulePhase::PostCollisionResponse;
	if (Name.Contains(TEXT("color")) || Name.Contains(TEXT("alpha")) || Name.Contains(TEXT("size over life")) || 
		Name.Contains(TEXT("scale color")) || Name.Contains(TEXT("scale sprite"))) 
		return EModulePhase::Curves;
	if (Name.Contains(TEXT("align")) || Name.Contains(TEXT("facing")) || Name.Contains(TEXT("stretch")) || 
		Name.Contains(TEXT("subuv")) || Name.Contains(TEXT("soft"))) 
		return EModulePhase::RenderPrep;
	if (Name.Contains(TEXT("kill")) || Name.Contains(TEXT("cull"))) 
		return EModulePhase::KillCull;
	
	return EModulePhase::Unknown;
}

void FVFXMotionModuleLibrary::InitializeMotionConfigs()
{
	if (MotionConfigs.Num() > 0) return; // Already initialized
	
	// OrbitAroundAxis - Tornado/Vortex swirl behavior
	{
		FMotionBehaviorConfig Config;
		Config.Archetype = EMotionArchetype::OrbitAroundAxis;
		Config.Description = TEXT("Tornado-like orbital motion with height-dependent radius");
		Config.bRequiresCustomVelocity = true;
		Config.bForbidsGravity = false; // Can have gravity pulling down while orbiting
		Config.bForbidsNoise = false;
		
		// Forbidden patterns - NO fountain/cone spray
		Config.ForbiddenModulePatterns.Add(TEXT("Add Velocity In Cone"));
		Config.ForbiddenModulePatterns.Add(TEXT("Add Velocity"));
		
		// Required modules for orbit behavior
		FMotionModuleDescriptor VortexModule;
		VortexModule.ModulePath = GetModulePath_Vortex();
		VortexModule.DisplayName = TEXT("Vortex Force");
		VortexModule.Phase = EModulePhase::Forces;
		VortexModule.Priority = 10;
		VortexModule.bRequired = true;
		VortexModule.DefaultParams.Add(TEXT("VortexStrength"), 500.0f);
		VortexModule.DefaultParamsVector.Add(TEXT("VortexAxis"), FVector(0.0f, 0.0f, 1.0f));
		VortexModule.DefaultParamsBool.Add(TEXT("bLocalSpace"), false);
		Config.RequiredModules.Add(VortexModule);

		FMotionModuleDescriptor AttractorModule;
		AttractorModule.ModulePath = GetModulePath_PointAttractor();
		AttractorModule.DisplayName = TEXT("Point Attractor");
		AttractorModule.Phase = EModulePhase::Forces;
		AttractorModule.Priority = 8;
		AttractorModule.bRequired = true;
		AttractorModule.DefaultParams.Add(TEXT("AttractorStrength"), 800.0f);
		AttractorModule.DefaultParamsVector.Add(TEXT("AttractorPosition"), FVector::ZeroVector);
		AttractorModule.DefaultParamsBool.Add(TEXT("bLocalSpace"), false);
		Config.RequiredModules.Add(AttractorModule);
		
		FMotionModuleDescriptor CurlModule;
		CurlModule.ModulePath = GetModulePath_CurlNoise();
		CurlModule.DisplayName = TEXT("Curl Noise");
		CurlModule.Phase = EModulePhase::Forces;
		CurlModule.Priority = 5;
		CurlModule.bRequired = false;
		CurlModule.DefaultParams.Add(TEXT("NoiseStrength"), 100.0f);
		CurlModule.DefaultParamsVector.Add(TEXT("NoiseOffset"), FVector::ZeroVector);
		CurlModule.DefaultParamsBool.Add(TEXT("bLocalSpace"), false);
		Config.RequiredModules.Add(CurlModule);
		
		MotionConfigs.Add(EMotionArchetype::OrbitAroundAxis, Config);
	}
	
	// RadialOutward - Explosion burst
	{
		FMotionBehaviorConfig Config;
		Config.Archetype = EMotionArchetype::RadialOutward;
		Config.Description = TEXT("Radial explosion outward from center");
		Config.bRequiresCustomVelocity = true;
		Config.bForbidsGravity = false;
		Config.bForbidsNoise = false;
		
		// Use cone velocity but with 360-degree spread
		Config.ForbiddenModulePatterns.Add(TEXT("Vortex"));

		FMotionModuleDescriptor AddVelocityModule;
		AddVelocityModule.ModulePath = GetModulePath_AddVelocity();
		AddVelocityModule.DisplayName = TEXT("Add Velocity");
		AddVelocityModule.Phase = EModulePhase::Forces;
		AddVelocityModule.Priority = 10;
		AddVelocityModule.bRequired = true;
		AddVelocityModule.DefaultParams.Add(TEXT("VelocityStrength"), 400.0f);
		Config.RequiredModules.Add(AddVelocityModule);

		FMotionModuleDescriptor ScaleVelocityModule;
		ScaleVelocityModule.ModulePath = GetModulePath_ScaleVelocity();
		ScaleVelocityModule.DisplayName = TEXT("Scale Velocity");
		ScaleVelocityModule.Phase = EModulePhase::Damping;
		ScaleVelocityModule.Priority = 12;
		ScaleVelocityModule.bRequired = false;
		ScaleVelocityModule.DefaultParams.Add(TEXT("Scale"), 1.0f);
		Config.RequiredModules.Add(ScaleVelocityModule);
		
		MotionConfigs.Add(EMotionArchetype::RadialOutward, Config);
	}
	
	// RadialInward - Vortex suction
	{
		FMotionBehaviorConfig Config;
		Config.Archetype = EMotionArchetype::RadialInward;
		Config.Description = TEXT("Attraction/suction toward center point");
		Config.bRequiresCustomVelocity = true;
		Config.bForbidsGravity = true; // Gravity conflicts with inward pull
		Config.bForbidsNoise = false;
		
		Config.ForbiddenModulePatterns.Add(TEXT("Add Velocity In Cone"));
		Config.ForbiddenModulePatterns.Add(TEXT("Gravity"));
		
		FMotionModuleDescriptor AttractorModule;
		AttractorModule.ModulePath = GetModulePath_PointAttractor();
		AttractorModule.DisplayName = TEXT("Point Attractor");
		AttractorModule.Phase = EModulePhase::Forces;
		AttractorModule.Priority = 10;
		AttractorModule.bRequired = true;
		AttractorModule.bIncompatibleWithGravity = true;
		AttractorModule.DefaultParams.Add(TEXT("AttractorStrength"), 1000.0f);
		AttractorModule.DefaultParamsVector.Add(TEXT("AttractorPosition"), FVector::ZeroVector);
		AttractorModule.DefaultParamsBool.Add(TEXT("bLocalSpace"), false);
		Config.RequiredModules.Add(AttractorModule);
		
		MotionConfigs.Add(EMotionArchetype::RadialInward, Config);
	}
	
	// UpdraftColumn - Rising smoke/fire
	{
		FMotionBehaviorConfig Config;
		Config.Archetype = EMotionArchetype::UpdraftColumn;
		Config.Description = TEXT("Upward buoyancy with turbulence");
		Config.bRequiresCustomVelocity = true;
		Config.bForbidsGravity = true; // Use lift instead
		Config.bForbidsNoise = false;
		
		Config.ForbiddenModulePatterns.Add(TEXT("Gravity"));
		Config.ForbiddenModulePatterns.Add(TEXT("Add Velocity In Cone"));

		FMotionModuleDescriptor AddVelocityModule;
		AddVelocityModule.ModulePath = GetModulePath_AddVelocity();
		AddVelocityModule.DisplayName = TEXT("Add Velocity");
		AddVelocityModule.Phase = EModulePhase::Forces;
		AddVelocityModule.Priority = 9;
		AddVelocityModule.bRequired = true;
		AddVelocityModule.DefaultParams.Add(TEXT("UpwardVelocity"), 300.0f);
		Config.RequiredModules.Add(AddVelocityModule);
		
		// Custom upward velocity + curl noise for turbulence
		FMotionModuleDescriptor CurlModule;
		CurlModule.ModulePath = GetModulePath_CurlNoise();
		CurlModule.DisplayName = TEXT("Curl Noise");
		CurlModule.Phase = EModulePhase::Forces;
		CurlModule.Priority = 5;
		CurlModule.bRequired = true;
		CurlModule.DefaultParams.Add(TEXT("NoiseStrength"), 150.0f);
		CurlModule.DefaultParamsVector.Add(TEXT("NoiseOffset"), FVector::ZeroVector);
		CurlModule.DefaultParamsBool.Add(TEXT("bLocalSpace"), false);
		Config.RequiredModules.Add(CurlModule);
		
		FMotionModuleDescriptor DragModule;
		DragModule.ModulePath = GetModulePath_Drag();
		DragModule.DisplayName = TEXT("Drag");
		DragModule.Phase = EModulePhase::Damping;
		DragModule.Priority = 10;
		DragModule.bRequired = false;
		DragModule.DefaultParams.Add(TEXT("DragCoefficient"), 0.5f);
		Config.RequiredModules.Add(DragModule);
		
		MotionConfigs.Add(EMotionArchetype::UpdraftColumn, Config);
	}

	// RibbonTrailFollow - Trails with ribbon renderer
	{
		FMotionBehaviorConfig Config;
		Config.Archetype = EMotionArchetype::RibbonTrailFollow;
		Config.Description = TEXT("Ribbon trail following motion" );
		Config.bRequiresCustomVelocity = false;
		Config.bForbidsGravity = false;
		Config.bForbidsNoise = false;

		Config.ForbiddenModulePatterns.Add(TEXT("Add Velocity In Cone"));

		FMotionModuleDescriptor SpawnRibbonId;
		SpawnRibbonId.ModulePath = GetModulePath_SpawnRibbonID();
		SpawnRibbonId.DisplayName = TEXT("Spawn Ribbon ID");
		SpawnRibbonId.Phase = EModulePhase::PreSim;
		SpawnRibbonId.Priority = 5;
		SpawnRibbonId.bRequired = true;
		Config.RequiredModules.Add(SpawnRibbonId);

		FMotionModuleDescriptor InitRibbon;
		InitRibbon.ModulePath = GetModulePath_InitializeRibbon();
		InitRibbon.DisplayName = TEXT("Initialize Ribbon");
		InitRibbon.Phase = EModulePhase::PreSim;
		InitRibbon.Priority = 6;
		InitRibbon.bRequired = true;
		Config.RequiredModules.Add(InitRibbon);

		MotionConfigs.Add(EMotionArchetype::RibbonTrailFollow, Config);
	}
	
	// Static - Stationary particles
	{
		FMotionBehaviorConfig Config;
		Config.Archetype = EMotionArchetype::Static;
		Config.Description = TEXT("Stationary particles with minimal movement");
		Config.bRequiresCustomVelocity = false;
		Config.bForbidsGravity = true;
		Config.bForbidsNoise = true;
		
		// Remove all motion modules
		Config.ForbiddenModulePatterns.Add(TEXT("Add Velocity"));
		Config.ForbiddenModulePatterns.Add(TEXT("Gravity"));
		Config.ForbiddenModulePatterns.Add(TEXT("Curl Noise"));
		Config.ForbiddenModulePatterns.Add(TEXT("Vortex"));
		Config.ForbiddenModulePatterns.Add(TEXT("Noise"));
		
		MotionConfigs.Add(EMotionArchetype::Static, Config);
	}
	
	// DirectionalCone - Fountain/spray
	{
		FMotionBehaviorConfig Config;
		Config.Archetype = EMotionArchetype::DirectionalCone;
		Config.Description = TEXT("Directional spray in cone shape");
		Config.bRequiresCustomVelocity = true;
		Config.bForbidsGravity = false;
		Config.bForbidsNoise = false;
		
		// This one CAN use cone velocity
		
		MotionConfigs.Add(EMotionArchetype::DirectionalCone, Config);
	}
	
	// Turbulent - Chaotic noise-driven
	{
		FMotionBehaviorConfig Config;
		Config.Archetype = EMotionArchetype::Turbulent;
		Config.Description = TEXT("Chaotic turbulent motion");
		Config.bRequiresCustomVelocity = false;
		Config.bForbidsGravity = false;
		Config.bForbidsNoise = false;
		
		FMotionModuleDescriptor CurlModule;
		CurlModule.ModulePath = GetModulePath_CurlNoise();
		CurlModule.DisplayName = TEXT("Curl Noise");
		CurlModule.Phase = EModulePhase::Forces;
		CurlModule.Priority = 10;
		CurlModule.bRequired = true;
		CurlModule.DefaultParams.Add(TEXT("NoiseStrength"), 300.0f);
		CurlModule.DefaultParamsVector.Add(TEXT("NoiseOffset"), FVector::ZeroVector);
		CurlModule.DefaultParamsBool.Add(TEXT("bLocalSpace"), false);
		Config.RequiredModules.Add(CurlModule);
		
		MotionConfigs.Add(EMotionArchetype::Turbulent, Config);
	}
}

EMotionArchetype FVFXMotionModuleLibrary::DetermineMotionArchetype(const FVFXIntent& Intent)
{
	// Map from VFXMotionModel to our motion archetype
	switch (Intent.Motion.PrimaryModel)
	{
		case EVFXMotionModel::Orbit:
		case EVFXMotionModel::Vortex:
			return EMotionArchetype::OrbitAroundAxis;
		
		case EVFXMotionModel::Radial:
			return EMotionArchetype::RadialOutward;
		
		case EVFXMotionModel::RadialInward:
			return EMotionArchetype::RadialInward;
		
		case EVFXMotionModel::Vertical:
			// Check if upward (smoke/fire) or downward
			if (Intent.Motion.MotionAxis.Z > 0)
				return EMotionArchetype::UpdraftColumn;
			else
				return EMotionArchetype::DirectionalCone;
		
		case EVFXMotionModel::Directional:
			return EMotionArchetype::DirectionalCone;
		
		case EVFXMotionModel::Turbulent:
			return EMotionArchetype::Turbulent;
		
		case EVFXMotionModel::Static:
			return EMotionArchetype::Static;
		
		default:
			break;
	}
	
	// Fallback based on archetype
	switch (Intent.Archetype)
	{
		case EVFXArchetype::Trail:
			return EMotionArchetype::RibbonTrailFollow;
		case EVFXArchetype::Tornado:
			return EMotionArchetype::OrbitAroundAxis;
		
		case EVFXArchetype::Explosion:
		case EVFXArchetype::Impact:
			return EMotionArchetype::RadialOutward;
		
		case EVFXArchetype::Smoke:
		case EVFXArchetype::Fire:
			return EMotionArchetype::UpdraftColumn;
		
		case EVFXArchetype::Fountain:
		case EVFXArchetype::Beam:
			return EMotionArchetype::DirectionalCone;
		
		case EVFXArchetype::Aura:
			return EMotionArchetype::Static;
		
		case EVFXArchetype::Dust:
			return EMotionArchetype::Turbulent;
		
		default:
			return EMotionArchetype::Custom;
	}
}

FMotionBehaviorConfig FVFXMotionModuleLibrary::GetMotionConfig(EVFXArchetype VFXArchetype, EVFXMotionModel MotionModel)
{
	InitializeMotionConfigs();
	
	FVFXIntent TempIntent;
	TempIntent.Archetype = VFXArchetype;
	TempIntent.Motion.PrimaryModel = MotionModel;
	
	EMotionArchetype Archetype = DetermineMotionArchetype(TempIntent);
	return GetMotionConfigByArchetype(Archetype);
}

FMotionBehaviorConfig FVFXMotionModuleLibrary::GetMotionConfigByArchetype(EMotionArchetype MotionArchetype)
{
	InitializeMotionConfigs();
	
	if (FMotionBehaviorConfig* Found = MotionConfigs.Find(MotionArchetype))
	{
		return *Found;
	}
	
	// Return empty config for custom
	FMotionBehaviorConfig EmptyConfig;
	EmptyConfig.Archetype = EMotionArchetype::Custom;
	EmptyConfig.Description = TEXT("Custom motion behavior");
	return EmptyConfig;
}

bool FVFXMotionModuleLibrary::IsModuleForbidden(const FString& ModuleName, const FMotionBehaviorConfig& Config)
{
	for (const FString& Pattern : Config.ForbiddenModulePatterns)
	{
		if (ModuleName.Contains(Pattern, ESearchCase::IgnoreCase))
		{
			return true;
		}
	}
	return false;
}

TMap<FString, float> FVFXMotionModuleLibrary::GenerateMotionParameters(EMotionArchetype Archetype, const FVFXIntent& Intent)
{
	TMap<FString, float> Params;
	
	switch (Archetype)
	{
		case EMotionArchetype::OrbitAroundAxis:
			Params.Add(TEXT("VortexStrength"), 500.0f);
			Params.Add(TEXT("OrbitRadius"), 200.0f);
			if (Intent.Motion.bRadiusDependsOnHeight)
				Params.Add(TEXT("RadiusGrowthRate"), 0.5f);
			break;

		case EMotionArchetype::RadialOutward:
			Params.Add(TEXT("VelocityStrength"), 500.0f);
			break;
		
		case EMotionArchetype::RadialInward:
			Params.Add(TEXT("AttractorStrength"), Intent.Motion.CentripetalStrength * 1000.0f);
			break;
		
		case EMotionArchetype::UpdraftColumn:
			Params.Add(TEXT("UpwardVelocity"), 300.0f);
			Params.Add(TEXT("NoiseStrength"), 150.0f);
			Params.Add(TEXT("DragCoefficient"), 0.5f);
			break;
		
		default:
			break;
	}
	
	return Params;
}

// Module path getters - these return paths to built-in Niagara modules
FString FVFXMotionModuleLibrary::GetModulePath_CurlNoise()
{
	return TEXT("/Niagara/Modules/Curl Noise Force.Curl Noise Force");
}

FString FVFXMotionModuleLibrary::GetModulePath_Vortex()
{
	return TEXT("/Niagara/Modules/Vortex Velocity.Vortex Velocity");
}

FString FVFXMotionModuleLibrary::GetModulePath_Drag()
{
	return TEXT("/Niagara/Modules/Drag.Drag");
}

FString FVFXMotionModuleLibrary::GetModulePath_Gravity()
{
	return TEXT("/Niagara/Modules/Gravity Force.Gravity Force");
}

FString FVFXMotionModuleLibrary::GetModulePath_PointAttractor()
{
	return TEXT("/Niagara/Modules/Point Attraction Force.Point Attraction Force");
}

FString FVFXMotionModuleLibrary::GetModulePath_ScaleVelocity()
{
	return TEXT("/Niagara/Modules/Scale Velocity.Scale Velocity");
}

FString FVFXMotionModuleLibrary::GetModulePath_AddVelocity()
{
	return TEXT("/Niagara/Modules/Add Velocity.Add Velocity");
}

FString FVFXMotionModuleLibrary::GetModulePath_SolveForces()
{
	return TEXT("/Niagara/Modules/Solve Forces and Velocity.Solve Forces and Velocity");
}

FString FVFXMotionModuleLibrary::GetModulePath_SpawnRibbonID()
{
	return TEXT("/Niagara/Modules/Spawn/Spawn Ribbon ID.Spawn Ribbon ID");
}

FString FVFXMotionModuleLibrary::GetModulePath_InitializeRibbon()
{
	return TEXT("/Niagara/Modules/Initialize Ribbon.Initialize Ribbon");
}
