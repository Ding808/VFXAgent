# VFX Agent v2.0 - Constraint-Aware Niagara Generation

## Developer Notes

### Overview

The VFX Agent plugin has been upgraded to support intelligent, constraint-aware Niagara VFX generation. The system now:

- **Stops always using Fountain/Burst templates** - Uses TemplateSelector to choose appropriate construction strategy
- **Enforces constraints by modifying Niagara stacks** - ModuleStripper removes forbidden modules
- **Adds real motion trajectories** - MotionModuleLibrary provides archetype-specific motion behaviors
- **Generates robust materials** - MaterialGenerator with fallback chains for base materials
- **Removes redundant "None" renderers** - RendererValidationFixer cleans up invalid renderers
- **Implements real quality scoring** - VFXQualityScorer evaluates structural correctness

### 2026-02 Pipeline Update (Short)

- **Intent-driven strategy**: TemplateSelector now chooses only BuildFromScratch or TemplateMinimal based on `FVFXIntent`.
- **Motion-driven stacks**: MotionModuleLibrary defines Orbit/Radial/Updraft/Ribbon behaviors with required modules.
- **Hard constraint enforcement**: ModuleStripper removes forbidden modules (by name, path, or class) and ModuleInserter adds required ones using deterministic phase ordering (Forces → Damping → Collision → EventWrite → Curves → RenderPrep → Kill).
- **Renderer cleanup**: RendererValidationFixer removes None-material renderers and ensures a valid sprite/ribbon renderer.
- **Material robustness**: MaterialGenerator builds a procedural unlit particle parent (noise + soft particles + optional Fresnel/dissolve) when no textures are supplied.

### Adding a New Archetype/Motion (Minimal Steps)

1) Add a new `EMotionArchetype` and config in `VFXMotionModuleLibrary.cpp::InitializeMotionConfigs()`.
2) Map `FVFXIntent` → `EMotionArchetype` in `DetermineMotionArchetype()`.
3) Adjust TemplateSelector if the archetype should force BuildFromScratch.
4) Add required module paths + default params in the motion config.
5) Add a prompt in the test plan with expected module stack outcomes.

### Architecture

#### New Component Pipeline

```
User Prompt
    ↓
LLM (2-stage) → VFXIntent + VFXEffectSpec
    ↓
VFXNiagaraSpecBuilder.BuildFromSpec()
    ├─ TemplateSelector → SelectStrategy()
    ├─ CreateEmitter (from template or scratch)
    ├─ ModuleStripper → EnforceConstraints()
    ├─ MotionModuleLibrary → ApplyMotionBehavior()
    ├─ RendererValidationFixer → ValidateAndFixRenderers()
    └─ VFXQualityScorer → ScoreSystem()
         ↓
    UNiagaraSystem (validated, constraint-compliant)
```

#### Key Components

**1. VFXMotionModuleLibrary** (`VFXMotionModuleLibrary.h/cpp`)
   - Defines motion archetypes: OrbitAroundAxis, RadialOutward, RadialInward, UpdraftColumn, Static, etc.
   - Maps VFX intent to required/forbidden modules
   - Provides module paths for Niagara built-in modules

**2. VFXTemplateSelector** (`VFXTemplateSelector.h/cpp`)
   - Chooses construction strategy: BuildFromScratch, TemplateMinimal, TemplateFountain, etc.
   - Determines when templates are incompatible with constraints
   - Builds list of modules to strip and modules to add

**3. VFXModuleStripper** (`VFXModuleStripper.h/cpp`)
   - Removes modules from Niagara emitter stacks by pattern matching
   - Supports stripping by: script name, path, display name
   - Category helpers: StripGravityModules(), StripConeVelocityModules(), StripNoiseModules()

**4. VFXRendererValidationFixer** (`VFXRendererValidationFixer.h/cpp`)
   - Removes renderers with null materials
   - Assigns default materials when needed
   - Ensures at least one valid renderer exists

**5. VFXQualityScorer** (`VFXQualityScorer.h/cpp`)
   - Structural quality scoring based on:
     - Renderer validity (30%)
     - Module stack correctness (25%)
     - Constraint compliance (25%)
     - Motion behavior (20%)
   - Replaces simple heuristic scoring with real Niagara stack inspection

**6. VFXNiagaraSpecBuilder** (`VFXNiagaraSpecBuilder.h/cpp`)
   - Orchestrates the new pipeline
   - Provides detailed build logs for debugging
   - Coordinates all components to build constraint-compliant VFX

### Data Flow

1. **User Input** → `"Make a tornado with swirling particles"`

2. **LLM Stage 1** → Generates `FVFXIntent`:
   ```cpp
   Intent.Archetype = EVFXArchetype::Tornado
   Intent.Motion.PrimaryModel = EVFXMotionModel::Vortex
   Intent.Avoidance.bAvoidConeVelocity = true
   ```

3. **LLM Stage 2** → Generates `FVFXEffectSpec` with emitters

4. **TemplateSelector** → Chooses `TemplateMinimal` strategy (Tornado conflicts with Fountain template)

5. **ModuleStripper** → Removes "Add Velocity In Cone" if present

6. **MotionModuleLibrary** → Requires Vortex Force module

7. **RendererValidationFixer** → Ensures sprite renderer has valid material

8. **QualityScorer** → Validates no forbidden modules remain, required modules present

### Adding a New Archetype/Motion Module

To add a new motion behavior (e.g., "Spiral Helix"):

1. **Define motion archetype** in `VFXMotionModuleLibrary.h`:
   ```cpp
   enum class EMotionArchetype : uint8
   {
       ...
       SpiralHelix,  // NEW
   };
   ```

2. **Add configuration** in `VFXMotionModuleLibrary.cpp::InitializeMotionConfigs()`:
   ```cpp
   {
       FMotionBehaviorConfig Config;
       Config.Archetype = EMotionArchetype::SpiralHelix;
       Config.Description = TEXT("Helical spiral motion");
       Config.bRequiresCustomVelocity = true;
       Config.bForbidsGravity = false;
       
       // Forbidden modules
       Config.ForbiddenModulePatterns.Add(TEXT("Add Velocity In Cone"));
       
       // Required modules
       FMotionModuleDescriptor VortexModule;
       VortexModule.ModulePath = TEXT("/Niagara/Modules/Vortex Velocity.Vortex Velocity");
       VortexModule.DisplayName = TEXT("Vortex Force");
       VortexModule.Phase = EModulePhase::Forces;
       VortexModule.Priority = 10;
       VortexModule.bRequired = true;
       Config.RequiredModules.Add(VortexModule);
       
       MotionConfigs.Add(EMotionArchetype::SpiralHelix, Config);
   }
   ```

3. **Map from VFXIntent** in `DetermineMotionArchetype()`:
   ```cpp
   case EVFXArchetype::MyNewArchetype:
       return EMotionArchetype::SpiralHelix;
   ```

4. **Update TemplateSelector** if a specific template is optimal:
   ```cpp
   case EVFXArchetype::MyNewArchetype:
       return EConstructionStrategy::TemplateMinimal;
   ```

5. **Test** using the test plan prompts

### Logging & Debugging

All components log their actions with `[BUILD]` prefix:
```
[BUILD] Strategy: TemplateMinimal - Clean base for Tornado
[BUILD] Created from template: /Niagara/DefaultAssets/Templates/Emitters/Minimal.Minimal
[BUILD] Stripping 1 forbidden module patterns
[BUILD]   Removed 1 modules: Add Velocity In Cone
[BUILD] Renderer validation: Renderers: 1 total, 0 removed (invalid), 0 fixed. Valid: YES
```

Enable `LogVFXAgent` for detailed output.

### Limitations & Future Work

1. **Module Insertion** - Currently logs what should be inserted but doesn't fully implement Niagara module stack manipulation
   - Requires deep reflection into UNiagaraEmitter script arrays
   - Need to handle different UE5 versions (5.3, 5.4, 5.5 have different APIs)

2. **Template Availability** - Template paths are hardcoded for UE5.5
   - Add version detection and fallback paths

3. **Material Compilation** - Material generation doesn't validate compilation
   - Add material compilation and error handling

4. **Motion Parameters** - Motion modules are inserted but parameters aren't fully set
   - Implement parameter binding (e.g., VortexStrength, OrbitRadius)

5. **Ribbon Trails** - RibbonTrailFollow motion not fully implemented
   - Requires ribbon-specific module setup

### Configuration

New settings can be added to `DefaultVFXAgent.ini`:

```ini
[/Script/VFXAgentEditor.VFXAgentSettings]
+ModuleSortRules="match=Vortex;phase=Forces;priority=10"
+ModuleSortRules="match=Curl Noise;phase=Forces;priority=5"
+ForbiddenTemplatesForTornado="Fountain"
+ForbiddenTemplatesForTornado="DirectionalBurst"
```

---

**Version:** 2.0  
**Date:** February 2026  
**Target UE Version:** 5.3+
