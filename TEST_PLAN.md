# VFX Agent - Test Plan
## Constraint-Aware Generation Validation

### Acceptance Test Suite

## Quick 6-Prompt Module Stack Outcomes

1) **"Make a stationary glowing orb. No spawn velocity. No gravity. Only pulse size and alpha."**
  - Expected: No `Add Velocity`, no `Gravity`, no `Noise`; has size/alpha over life; valid material.

2) **"A spinning tornado with particles, visible swirl."**
  - Expected: `Vortex`/`Point Attractor` present, no `Add Velocity In Cone`, 2–3 layers, valid sprite materials.

3) **"Explosion burst outward, short life."**
  - Expected: `Add Velocity` (radial outward), burst spawn, short lifetime curve, valid emissive material.

4) **"Suction vortex pulling inward."**
  - Expected: `Point Attraction` present, gravity removed, no cone velocity.

5) **"Rising smoke column with soft turbulence."**
  - Expected: upward `Add Velocity`, `Curl Noise` + `Drag`, gravity removed, soft particles enabled.

6) **"Fast ribbon trail following a projectile."**
  - Expected: ribbon renderer present, `Spawn Ribbon ID` + `Initialize Ribbon` inserted, no None-material renderers.

---

## Test 1: Stationary Glowing Orb (No Motion)

**Prompt:**
```
"Make a stationary glowing orb. No spawn velocity. No gravity. Only pulse size and alpha."
```

**Expected Recipe/Intent:**
- Archetype: `Aura` or `Custom`
- MotionModel: `Static`
- Avoidance:
  - `bAvoidConeVelocity = true`
  - `bAvoidUniformGravity = true`

**Expected Niagara Stack:**
```
✅ NO Add Velocity module
✅ NO Add Velocity In Cone module
✅ NO Gravity module
✅ HAS Scale Sprite Size Over Life (pulse)
✅ HAS Scale Color Over Life (alpha fade)
✅ Valid renderer with material
```

**Quality Score Requirements:**
- Total Score: >= 0.75
- RendererScore: 1.0 (valid sprite renderer)
- ModuleScore: >= 0.8 (no forbidden modules)
- ConstraintScore: >= 0.8 (static constraints met)

**Validation:**
```cpp
FQualityScoreBreakdown score = FVFXQualityScorer::ScoreSystem(system, intent, config);
ASSERT(score.ForbiddenModulesFound == 0);
ASSERT(score.InvalidRenderers == 0);
ASSERT(!HasModule(emitter, "Add Velocity"));
ASSERT(!HasModule(emitter, "Gravity"));
```

---

## Test 2: Spinning Tornado (Vortex Swirl)

**Prompt:**
```
"A spinning tornado with particles, visible swirl."
```

**Expected Recipe/Intent:**
- Archetype: `Tornado`
- MotionModel: `Vortex` or `Orbit`
- Avoidance:
  - `bAvoidConeVelocity = true` (no fountain spray)
- RequiredForces: `["vortex", "centripetal"]`
- SuggestedEmitterCount: 3 (core funnel, debris, dust)

**Expected Niagara Stack:**
```
✅ NO Add Velocity In Cone module
✅ HAS Vortex Force module OR Curl Noise Force
✅ 2-3 emitters/layers
✅ Valid renderers on all emitters
❌ MUST NOT be a simple fountain with cone spray
```

**Construction Strategy:**
- Expected: `TemplateMinimal` or `BuildFromScratch`
- NOT: `TemplateFountain` (fountain has cone velocity)

**Quality Score Requirements:**
- Total Score: >= 0.7
- ModuleScore: >= 0.75 (vortex/curl present, cone removed)
- Layers: >= 2

**Validation:**
```cpp
ASSERT(!HasModule(emitter, "Add Velocity In Cone"));
ASSERT(HasModule(emitter, "Vortex") || HasModule(emitter, "Curl Noise"));
ASSERT(system->GetNumEmitters() >= 2);
ASSERT(score.ForbiddenModulesFound == 0);
```

---

## Test 3: Explosion Burst Outward

**Prompt:**
```
"Explosion burst outward, short life."
```

**Expected Recipe/Intent:**
- Archetype: `Explosion`
- MotionModel: `Radial`
- BurstCount: > 0
- Lifetime: < 2.0s
- VelocityVariation: high

**Expected Niagara Stack:**
```
✅ HAS Burst spawn (not continuous)
✅ HAS radial/outward velocity (cone or radial expansion)
✅ Lifetime ~1-2 seconds
✅ Valid renderer with bright/emissive material
✅ Proper curves (alpha fade, size change)
```

**Construction Strategy:**
- Expected: `TemplateBurst` or `TemplateMinimal`

**Quality Score Requirements:**
- Total Score: >= 0.75
- RendererScore: 1.0
- Burst configured

**Validation:**
```cpp
ASSERT(emitterSpec.BurstCount > 0);
ASSERT(emitterSpec.Lifetime < 3.0f);
ASSERT(score.InvalidRenderers == 0);
```

---

## Test 4: No "None" Material Renderers

**Prompt:** (Any generation)

**Requirement:**
```
After generation, ZERO renderers should have:
- Material = nullptr
- Material = None
- Invalid renderer properties
```

**Validation:**
```cpp
FRendererValidationReport report = FVFXRendererValidationFixer::ValidateAndFixRenderers(emitter, nullptr);
ASSERT(report.InvalidRenderersRemoved >= 0); // May find and remove some
ASSERT(report.bHasValidRenderer == true);   // Must have at least one valid
ASSERT(CountRenderersWithNullMaterial(emitter) == 0);
```

**Post-Condition:**
- Every emitter has exactly 1+ valid renderer
- All renderers have non-null materials
- Material paths resolve successfully

---

## Test 5: Build Log Evidence

**Prompt:** (Any tornado/vortex)

**Requirement:**
```
Build log must show:
1. Chosen strategy (BuildFromScratch / TemplateMinimal)
2. Modules removed (e.g., "Add Velocity In Cone")
3. Modules inserted (e.g., "Vortex Force")
4. Renderers fixed
5. Material assigned
```

**Validation:**
```cpp
FNiagaraBuildContext context;
UNiagaraSystem* sys = FVFXNiagaraSpecBuilder::BuildFromSpec(spec, context);

ASSERT(context.BuildLog.ContainsByPredicate([](const FString& log) {
    return log.Contains("Strategy:");
}));

ASSERT(context.BuildLog.ContainsByPredicate([](const FString& log) {
    return log.Contains("Removed") && log.Contains("module");
}));

ASSERT(context.BuildLog.ContainsByPredicate([](const FString& log) {
    return log.Contains("Renderer validation");
}));
```

---

## Test 6: Quality Scoring Realism

**Prompt:** (Tornado with forbidden cone velocity still present)

**Setup:**
Manually inject an "Add Velocity In Cone" module into a tornado emitter.

**Expected Score:**
```cpp
FQualityScoreBreakdown score = FVFXQualityScorer::ScoreSystem(system, intent, config);

ASSERT(score.ForbiddenModulesFound > 0);
ASSERT(score.ModuleScore < 1.0); // Penalized
ASSERT(score.TotalScore < 0.75); // Should NOT pass threshold
ASSERT(score.Issues.Num() > 0);
ASSERT(score.Issues[0].Contains("Forbidden module"));
```

**Requirement:**
- Quality scorer must detect the violation
- Total score must be < 0.75 (not acceptable)
- Issue must be logged in breakdown

---

## Regression Tests

### R1: Fountain Template Still Works
When appropriate (directional spray), Fountain template should still be used.

**Prompt:** `"Water fountain spray upward"`
- Expected Strategy: `TemplateFountain`
- Expected: Cone velocity IS allowed
- Quality: >= 0.75

### R2: Existing Recipe Compatibility
Old recipes without Intent field should still work (legacy mode).

**Validation:**
```cpp
FVFXRecipe oldRecipe;
// ... populate without Intent
UNiagaraSystem* sys = GenerateFromRecipe(oldRecipe);
ASSERT(sys != nullptr); // Should not crash
```

### R3: Material Path Fallback Chain
If primary material path fails, should fall back gracefully.

**Validation:**
```cpp
FVFXMaterialRecipe recipe;
recipe.BaseMaterialPath = TEXT("/Invalid/Path/DoesNotExist");
UMaterial* mat = UMaterialGenerator::GetParentMaterial(recipe);
ASSERT(mat != nullptr); // Fallback should succeed
```

---

## Performance Tests

### P1: Build Time
Generation should complete within reasonable time.

**Metric:** < 2 seconds for single emitter system
**Metric:** < 5 seconds for 3-emitter system

### P2: Module Stripping Performance
Stripping modules should be efficient.

**Metric:** < 100ms for pattern-based strip on emitter with 20 modules

---

## Integration Test

**Full Pipeline Test:**
```cpp
// 1. Generate recipe from prompt
FVFXRecipe recipe = LLMProvider->GenerateRecipe("spinning tornado");

// 2. Validate intent
ASSERT(recipe.Spec.bHasIntent);
ASSERT(recipe.Spec.Intent.Archetype == EVFXArchetype::Tornado);

// 3. Build with new pipeline
FNiagaraBuildContext context;
UNiagaraSystem* system = FVFXNiagaraSpecBuilder::BuildFromSpec(recipe.Spec, context);
ASSERT(system != nullptr);

// 4. Validate quality
FMotionBehaviorConfig config = FVFXMotionModuleLibrary::GetMotionConfig(
    recipe.Spec.Intent.Archetype,
    recipe.Spec.Intent.Motion.PrimaryModel
);
FQualityScoreBreakdown score = FVFXQualityScorer::ScoreSystem(system, recipe.Spec.Intent, config);

// 5. Assert quality
ASSERT(score.TotalScore >= 0.6f);
ASSERT(score.ForbiddenModulesFound == 0);
ASSERT(score.InvalidRenderers == 0);

// 6. Check build log
ASSERT(context.BuildLog.Num() > 0);
UE_LOG(LogTest, Log, TEXT("Build completed: %s"), *context.SelectedStrategy.StrategyReason);
```

---

## Manual Validation Checklist

After running tests, manually verify in Niagara Editor:

- [ ] Tornado: Particles visibly swirl (not fountain spray)
- [ ] Static orb: Particles stay in place (no drift)
- [ ] Explosion: Radial burst clearly visible
- [ ] All effects: No pink "missing material" squares
- [ ] All effects: Preview plays immediately (no compile errors)
- [ ] Module stack: Logical order (spawn → forces → integrate → curves → render)

---

## Test Execution

Run in UE5 Editor with VFXAgent plugin loaded:

```cpp
// In test suite or console command
RunVFXAgentAcceptanceTests();
```

Or use individual test commands:
```
VFXAgent.Test.StationaryOrb
VFXAgent.Test.TornadoSwirl
VFXAgent.Test.ExplosionBurst
VFXAgent.Test.NoInvalidRenderers
VFXAgent.Test.BuildLogEvidence
VFXAgent.Test.QualityScoring
```

---

**Test Coverage Goal:** 95%+ of core pipeline components  
**Last Updated:** February 2, 2026
