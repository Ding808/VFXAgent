#include "VFXMultiCandidatePipeline.h"
#include "HttpLLMProvider.h"
#include "BehaviorArchetypeLibrary.h"
#include "EffectSpecV2Parser.h"
#include "EffectSpecV2Validator.h"
#include "PipelineLog.h"
#include "VFXAgentLog.h"
#include "Async/Async.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"

// ============================================================================
// FVFXSpecScorer — structural scoring without building Niagara assets
// ============================================================================

float FVFXSpecScorer::ScoreLayerDiversity(const FEffectSpecV2& Spec, TArray<FString>& S, TArray<FString>& I)
{
	if (Spec.Layers.Num() == 0) { I.Add(TEXT("No layers")); return 0.0f; }

	// Count distinct roles
	TSet<ELayerRoleV2> Roles;
	TSet<FString> RendererTypes;
	for (const FLayerSpecV2& L : Spec.Layers)
	{
		Roles.Add(L.Role);
		RendererTypes.Add(L.RendererType.ToLower());
	}

	float Score = 0.0f;

	// Layer count scoring: 3+ is good, 4-5 is great
	if (Spec.Layers.Num() >= 5) { Score += 0.35f; S.Add(TEXT("Excellent layer count (5+)")); }
	else if (Spec.Layers.Num() >= 4) { Score += 0.3f; S.Add(TEXT("Good layer count (4)")); }
	else if (Spec.Layers.Num() >= 3) { Score += 0.2f; }
	else { I.Add(TEXT("Only " + FString::FromInt(Spec.Layers.Num()) + " layers — need 3+")); Score += 0.1f; }

	// Role diversity
	if (Roles.Num() >= 4) { Score += 0.35f; S.Add(TEXT("Diverse roles (" + FString::FromInt(Roles.Num()) + " distinct)")); }
	else if (Roles.Num() >= 3) { Score += 0.25f; }
	else { I.Add(TEXT("Low role diversity (" + FString::FromInt(Roles.Num()) + ")")); Score += 0.1f; }

	// Renderer diversity (sprite + ribbon, or sprite + light, etc.)
	if (RendererTypes.Num() >= 3) { Score += 0.3f; S.Add(TEXT("Multiple renderer types")); }
	else if (RendererTypes.Num() >= 2) { Score += 0.2f; S.Add(TEXT("Two renderer types")); }
	else { I.Add(TEXT("Only one renderer type")); Score += 0.05f; }

	return FMath::Clamp(Score, 0.0f, 1.0f);
}

float FVFXSpecScorer::ScoreTimingRhythm(const FEffectSpecV2& Spec, TArray<FString>& S, TArray<FString>& I)
{
	if (Spec.Layers.Num() == 0) return 0.0f;

	// Good rhythm = layers don't all start at the same time
	TArray<float> Delays;
	bool bAnyDelayed = false;
	bool bAnyLooped = false;
	for (const FLayerSpecV2& L : Spec.Layers)
	{
		Delays.Add(L.Timing.DelaySeconds);
		if (L.Timing.DelaySeconds > 0.01f) bAnyDelayed = true;
		if (L.Timing.bLoop) bAnyLooped = true;
	}

	float Score = 0.0f;

	// Staggered timing
	if (bAnyDelayed)
	{
		Score += 0.5f;
		S.Add(TEXT("Staggered layer timing (good rhythm)"));
	}
	else
	{
		I.Add(TEXT("All layers start simultaneously — no rhythm"));
		Score += 0.1f;
	}

	// Different lifetimes
	float MinLife = FLT_MAX, MaxLife = 0.0f;
	for (const FLayerSpecV2& L : Spec.Layers)
	{
		MinLife = FMath::Min(MinLife, L.Timing.TotalLifetime);
		MaxLife = FMath::Max(MaxLife, L.Timing.TotalLifetime);
	}
	if (MaxLife > 0.0f && (MaxLife - MinLife) / MaxLife > 0.3f)
	{
		Score += 0.3f;
		S.Add(TEXT("Varied lifetimes across layers"));
	}
	else
	{
		I.Add(TEXT("Lifetimes too similar across layers"));
		Score += 0.1f;
	}

	// Attack/decay variation
	bool bHasVariedEnvelope = false;
	for (const FLayerSpecV2& L : Spec.Layers)
	{
		if (L.Timing.AttackSeconds > 0.0f && L.Timing.DecaySeconds > 0.0f)
		{
			bHasVariedEnvelope = true;
			break;
		}
	}
	if (bHasVariedEnvelope) { Score += 0.2f; }
	else { I.Add(TEXT("No attack/decay envelope defined")); }

	return FMath::Clamp(Score, 0.0f, 1.0f);
}

float FVFXSpecScorer::ScoreMaterialRichness(const FEffectSpecV2& Spec, TArray<FString>& S, TArray<FString>& I)
{
	if (Spec.Layers.Num() == 0) return 0.0f;

	int32 FeaturedCount = 0;
	bool bAnyFresnel = false, bAnyDepthFade = false, bAnyNoise = false;
	bool bAnyDistortion = false, bAnyErode = false, bAnyHLSL = false;

	for (const FLayerSpecV2& L : Spec.Layers)
	{
		const FMaterialFeatureSetV2& F = L.Material.Features;
		int32 LayerFeatures = 0;
		if (F.bFresnel) { bAnyFresnel = true; ++LayerFeatures; }
		if (F.bDepthFade) { bAnyDepthFade = true; ++LayerFeatures; }
		if (F.bNoiseMask) { bAnyNoise = true; ++LayerFeatures; }
		if (F.bUVDistortion) { bAnyDistortion = true; ++LayerFeatures; }
		if (F.bErodeMask) { bAnyErode = true; ++LayerFeatures; }
		if (L.Material.bCustomHLSL) { bAnyHLSL = true; ++LayerFeatures; }
		if (LayerFeatures >= 2) ++FeaturedCount;
	}

	float Score = 0.0f;

	// Depth fade is baseline expectation
	if (bAnyDepthFade) { Score += 0.15f; } else { I.Add(TEXT("No depth fade on any layer")); }

	// Rich features
	int32 TotalFeatures = (bAnyFresnel ? 1 : 0) + (bAnyDepthFade ? 1 : 0) + (bAnyNoise ? 1 : 0) +
		(bAnyDistortion ? 1 : 0) + (bAnyErode ? 1 : 0) + (bAnyHLSL ? 1 : 0);

	if (TotalFeatures >= 4) { Score += 0.5f; S.Add(TEXT("Rich material feature set (" + FString::FromInt(TotalFeatures) + " features)")); }
	else if (TotalFeatures >= 3) { Score += 0.35f; S.Add(TEXT("Good material features (" + FString::FromInt(TotalFeatures) + ")")); }
	else if (TotalFeatures >= 2) { Score += 0.2f; }
	else { I.Add(TEXT("Minimal material features")); Score += 0.05f; }

	// Multiple layers have features
	if (FeaturedCount >= 3) { Score += 0.25f; S.Add(TEXT("Multiple layers with material features")); }
	else if (FeaturedCount >= 2) { Score += 0.15f; }
	else { Score += 0.05f; }

	// HLSL custom code bonus
	if (bAnyHLSL) { Score += 0.1f; S.Add(TEXT("Custom HLSL material code")); }

	return FMath::Clamp(Score, 0.0f, 1.0f);
}

float FVFXSpecScorer::ScoreMotionLanguage(const FEffectSpecV2& Spec, TArray<FString>& S, TArray<FString>& I)
{
	if (Spec.Layers.Num() == 0) return 0.0f;

	TSet<EMotionVerbV2> Verbs;
	int32 WithDrag = 0, WithNoise = 0;
	for (const FLayerSpecV2& L : Spec.Layers)
	{
		Verbs.Add(L.Motion.Verb);
		if (L.Motion.DragCoefficient > 0.0f || L.Update.Drag > 0.0f) ++WithDrag;
		if (L.Motion.CurlNoiseIntensity > 0.0f || L.Update.CurlNoiseStrength > 0.0f) ++WithNoise;
	}

	float Score = 0.0f;

	// Motion verb diversity
	if (Verbs.Num() >= 3) { Score += 0.4f; S.Add(TEXT("Diverse motion verbs (" + FString::FromInt(Verbs.Num()) + ")")); }
	else if (Verbs.Num() >= 2) { Score += 0.25f; }
	else { I.Add(TEXT("All layers use same motion")); Score += 0.1f; }

	// Force usage
	if (WithDrag >= 2) { Score += 0.2f; S.Add(TEXT("Good drag usage")); }
	else if (WithDrag >= 1) { Score += 0.1f; }
	else { I.Add(TEXT("No drag on any layer")); }

	if (WithNoise >= 1) { Score += 0.2f; S.Add(TEXT("Curl noise for organic motion")); }
	else { I.Add(TEXT("No turbulence/noise")); }

	// Non-static motion
	bool bAllStatic = true;
	for (const FLayerSpecV2& L : Spec.Layers)
	{
		if (L.Motion.Verb != EMotionVerbV2::Static && L.Motion.Speed > 0.0f)
		{
			bAllStatic = false;
			break;
		}
	}
	if (!bAllStatic) { Score += 0.2f; } else { I.Add(TEXT("All motion is static")); }

	return FMath::Clamp(Score, 0.0f, 1.0f);
}

float FVFXSpecScorer::ScoreFeatureCoverage(const FEffectSpecV2& Spec, TArray<FString>& S, TArray<FString>& I)
{
	int32 Features = 0;
	bool bHasEvent = Spec.Events.Num() > 0;
	bool bHasRibbon = false, bHasLight = false, bHasForce = false;

	for (const FLayerSpecV2& L : Spec.Layers)
	{
		if (L.RendererType.ToLower() == TEXT("ribbon")) bHasRibbon = true;
		if (L.RendererType.ToLower() == TEXT("light")) bHasLight = true;
		if (L.Motion.DragCoefficient > 0 || L.Motion.CurlNoiseIntensity > 0 ||
			L.Update.Drag > 0 || L.Update.CurlNoiseStrength > 0) bHasForce = true;
	}

	if (bHasEvent) { ++Features; S.Add(TEXT("Event bindings present")); }
	if (bHasForce) { ++Features; S.Add(TEXT("Force modules present")); }
	if (bHasRibbon) { ++Features; S.Add(TEXT("Ribbon renderer present")); }
	if (bHasLight) { ++Features; S.Add(TEXT("Light renderer present")); }

	// Target: at least 2 features, bonus for 3+
	if (Features >= 4) return 1.0f;
	if (Features >= 3) return 0.85f;
	if (Features >= 2) return 0.6f;

	I.Add(FString::Printf(TEXT("Only %d Niagara features (need 2+)"), Features));
	return Features > 0 ? 0.3f : 0.0f;
}

float FVFXSpecScorer::ScoreArchetypeCompliance(const FEffectSpecV2& Spec, TArray<FString>& S, TArray<FString>& I)
{
	TArray<FString> Violations = FBehaviorArchetypeLibrary::ValidateAgainstArchetype(Spec);
	if (Violations.Num() == 0)
	{
		S.Add(TEXT("Fully compliant with archetype constraints"));
		return 1.0f;
	}

	for (const FString& V : Violations)
	{
		I.Add(V);
	}

	float Penalty = FMath::Min((float)Violations.Num() * 0.2f, 0.8f);
	return FMath::Clamp(1.0f - Penalty, 0.0f, 1.0f);
}

float FVFXSpecScorer::Score(const FEffectSpecV2& Spec, TArray<FString>& OutStrengths, TArray<FString>& OutIssues)
{
	OutStrengths.Reset();
	OutIssues.Reset();

	// Weighted scoring
	constexpr float WLayer = 0.20f;
	constexpr float WTiming = 0.15f;
	constexpr float WMaterial = 0.20f;
	constexpr float WMotion = 0.15f;
	constexpr float WFeature = 0.15f;
	constexpr float WArchetype = 0.15f;

	float Total = 0.0f;
	Total += ScoreLayerDiversity(Spec, OutStrengths, OutIssues) * WLayer;
	Total += ScoreTimingRhythm(Spec, OutStrengths, OutIssues) * WTiming;
	Total += ScoreMaterialRichness(Spec, OutStrengths, OutIssues) * WMaterial;
	Total += ScoreMotionLanguage(Spec, OutStrengths, OutIssues) * WMotion;
	Total += ScoreFeatureCoverage(Spec, OutStrengths, OutIssues) * WFeature;
	Total += ScoreArchetypeCompliance(Spec, OutStrengths, OutIssues) * WArchetype;

	return FMath::Clamp(Total, 0.0f, 1.0f);
}

// ============================================================================
// VFX Grammar / Style Bible — V2 System Prompt
// ============================================================================

FString FVFXMultiCandidatePipeline::BuildV2SystemPrompt(EVFXBehaviorArchetype Archetype)
{
	const FBehaviorArchetypeDefinition& Def = FBehaviorArchetypeLibrary::GetDefinition(Archetype);

	// Build forbidden patterns string
	FString ForbiddenStr;
	for (const FString& F : Def.ForbiddenPatterns)
	{
		ForbiddenStr += TEXT("  - ") + F + TEXT("\n");
	}

	// Build layer preset hint
	FString LayerHintStr;
	for (int32 i = 0; i < Def.LayerPresets.Num(); ++i)
	{
		const FArchetypeLayerPreset& P = Def.LayerPresets[i];
		FString VerbStr;
		switch (P.MotionVerb)
		{
		case EMotionVerbV2::Explode: VerbStr = TEXT("explode"); break;
		case EMotionVerbV2::Implode: VerbStr = TEXT("implode"); break;
		case EMotionVerbV2::Rise:    VerbStr = TEXT("rise"); break;
		case EMotionVerbV2::Orbit:   VerbStr = TEXT("orbit"); break;
		case EMotionVerbV2::Spiral:  VerbStr = TEXT("spiral"); break;
		case EMotionVerbV2::Drift:   VerbStr = TEXT("drift"); break;
		case EMotionVerbV2::Snap:    VerbStr = TEXT("snap"); break;
		case EMotionVerbV2::Pulse:   VerbStr = TEXT("pulse"); break;
		case EMotionVerbV2::Stream:  VerbStr = TEXT("stream"); break;
		case EMotionVerbV2::Flutter: VerbStr = TEXT("flutter"); break;
		default:                     VerbStr = TEXT("static"); break;
		}

		LayerHintStr += FString::Printf(
			TEXT("  Layer %d: \"%s\" [%s] motion=%s speed=%.0f blend=%s\n"),
			i + 1, *P.DefaultName, *P.RendererType, *VerbStr, P.MotionSpeed, *P.BlendMode);
	}

	return FString::Printf(TEXT(
		"=== VFX GRAMMAR / STYLE BIBLE v2 ===\n\n"
		"You are generating an EffectSpec v2 JSON for a real-time VFX system (Unreal Niagara).\n"
		"Your output must be STRICT JSON. No markdown, no commentary, no code blocks.\n\n"

		"=== DETECTED ARCHETYPE: %s ===\n"
		"%s\n\n"

		"=== REQUIRED LAYER LAYOUT ===\n"
		"(At least these layers, you may add more)\n"
		"%s\n"

		"=== FORBIDDEN PATTERNS ===\n"
		"(Do NOT use these behaviors for this archetype)\n"
		"%s\n"

		"=== TIMING / RHYTHM RULES ===\n"
		"- Layers must NOT all start at the same time (stagger with delay).\n"
		"- Core layer: fast attack, short sustain.\n"
		"- Smoke/atmosphere: delayed start, slow decay.\n"
		"- Flash/light: near-instant (<0.1s lifetime).\n"
		"- Use the timing envelope: {delay, attack, sustain, decay, lifetime}.\n\n"

		"=== MOTION LANGUAGE ===\n"
		"Each layer must have a motion.verb from:\n"
		"  explode | implode | rise | fall | orbit | spiral | drift | snap | pulse | stream | flutter | static\n"
		"Different layers should use DIFFERENT motion verbs for visual complexity.\n"
		"Motion must include: speed (cm/s), drag, curl_noise_intensity.\n\n"

		"=== MATERIAL COMPOSER (Feature Skeleton) ===\n"
		"Each layer's material.features can enable:\n"
		"  fresnel: rim-lighting glow (great for magic/energy)\n"
		"  depth_fade: soft particle blending (REQUIRED for most layers)\n"
		"  uv_distortion: heat haze / energy distortion\n"
		"  noise_mask: procedural noise masking for organic shapes\n"
		"  erode_mask: dissolve / erode effect (threshold 0-1)\n"
		"  pan_uv: scrolling UV for flowing textures\n"
		"Pro effects should use 2-3 features per layer. At least one layer should have fresnel.\n\n"

		"=== NIAGARA HARD CONSTRAINTS ===\n"
		"The generated effect MUST use at least %d of these features:\n"
		"  1. Event bindings (death->spawn, collision->burst, etc.)\n"
		"  2. Force modules (drag, curl noise, vortex)\n"
		"  3. Collision detection\n"
		"  4. Light renderer (at least one emitter as dynamic light)\n"
		"  5. Ribbon renderer (trails, arcs, ribbons)\n"
		"Include an \"events\" array with inter-layer event bindings.\n\n"

		"=== CAMERA READABILITY ===\n"
		"  preferred_distance: %s\n"
		"  bounds_radius: %.0f cm\n"
		"  needs_silhouette: %s\n"
		"  contrast_target: %.2f\n\n"

		"=== OUTPUT SCHEMA (EffectSpec v2) ===\n"
		"{\n"
		"  \"effect_name\": \"string\",\n"
		"  \"archetype\": \"explosion|magic|electric|teleport|fire|smoke|water|custom\",\n"
		"  \"archetype_variant\": \"optional_subtype\",\n"
		"  \"description\": \"brief semantic description\",\n"
		"  \"global_style\": {\n"
		"    \"palette\": \"string\", \"primary_color\": [r,g,b,a], \"secondary_color\": [r,g,b,a],\n"
		"    \"accent_color\": [r,g,b,a], \"realism_to_stylized\": 0.0-1.0,\n"
		"    \"brightness\": 1.0, \"saturation\": 1.0, \"mood\": \"string\"\n"
		"  },\n"
		"  \"layers\": [\n"
		"    {\n"
		"      \"id\": \"L1\", \"name\": \"string\", \"role\": \"core_blast|secondary_fill|sparks|trail|smoke|glow|distortion|ground|custom\",\n"
		"      \"renderer_type\": \"sprite|ribbon|mesh|light\",\n"
		"      \"sort_order\": 0, \"max_particles\": 500,\n"
		"      \"timing\": {\"delay\": 0, \"attack\": 0.1, \"sustain\": 0.5, \"decay\": 0.4, \"lifetime\": 1.0, \"loop\": false},\n"
		"      \"spawn\": {\"mode\": \"burst|rate\", \"rate\": 0, \"burst_count\": 0},\n"
		"      \"init\": {\"lifetime\": 2.0, \"lifetime_variation\": 0.2, \"size_range\": [10,30], \"velocity\": {\"x\":0,\"y\":0,\"z\":0}},\n"
		"      \"update\": {\"drag\": 0, \"curl_noise_strength\": 0, \"color_over_life\": \"\", \"alpha_over_life\": \"\", \"size_over_life\": \"\"},\n"
		"      \"motion\": {\"verb\": \"explode\", \"axis\": {\"x\":0,\"y\":0,\"z\":1}, \"speed\": 200, \"speed_variation\": 0.3, \"curl_noise_intensity\": 0, \"drag\": 0},\n"
		"      \"material\": {\n"
		"        \"shading\": \"unlit|lit\", \"blend\": \"additive|translucent|masked\",\n"
		"        \"base_color\": [1,1,1,1], \"emissive_color\": [1,1,1,1], \"emissive_intensity\": 5.0, \"opacity\": 0.8,\n"
		"        \"features\": {\"fresnel\": false, \"depth_fade\": true, \"uv_distortion\": false, \"noise_mask\": false, \"erode_mask\": false, \"pan_uv\": false}\n"
		"      }\n"
		"    }\n"
		"  ],\n"
		"  \"events\": [\n"
		"    {\"source\": \"L1\", \"target\": \"L2\", \"type\": \"on_death|on_collision|on_spawn|timed\", \"delay\": 0, \"spawn_count\": 10}\n"
		"  ],\n"
		"  \"requirements\": {\"events\": true, \"forces\": true, \"collision\": false, \"light_renderer\": false, \"ribbon_renderer\": false, \"min_features\": 2},\n"
		"  \"camera_readability\": {\"distance\": \"medium\", \"bounds_radius\": 200, \"needs_silhouette\": true, \"contrast_target\": 0.7}\n"
		"}\n\n"
		"OUTPUT ONLY THE JSON. NO MARKDOWN, NO EXPLANATIONS."
	),
		*Def.DisplayName,
		*Def.Description,
		*LayerHintStr,
		*ForbiddenStr,
		Def.Requirements.MinFeatureCount,
		*Def.CameraReadability.PreferredDistance,
		Def.CameraReadability.BoundsRadius,
		Def.CameraReadability.bNeedsSilhouette ? TEXT("true") : TEXT("false"),
		Def.CameraReadability.ContrastTarget
	);
}

// ============================================================================
// Revision prompt
// ============================================================================

FString FVFXMultiCandidatePipeline::BuildRevisionPrompt(const FEffectSpecV2& Spec, const TArray<FString>& Issues)
{
	FString IssueList;
	for (const FString& I : Issues)
	{
		IssueList += TEXT("  - ") + I + TEXT("\n");
	}

	FString SpecJson = FEffectSpecV2Parser::ToJson(Spec);

	return FString::Printf(TEXT(
		"Revise the following EffectSpec v2 JSON to fix these issues:\n\n"
		"ISSUES:\n%s\n"
		"CURRENT SPEC SUMMARY:\n%s\n\n"
		"Output a complete corrected EffectSpec v2 JSON. Fix ALL listed issues.\n"
		"Respond with JSON only."
	), *IssueList, *SpecJson);
}

// ============================================================================
// Multi-Candidate Pipeline — async orchestration
// ============================================================================

void FVFXMultiCandidatePipeline::RunAsync(
	UHttpLLMProvider* Provider,
	const FString& UserPrompt,
	const FMultiCandidateConfig& Config,
	FOnPipelineComplete OnComplete)
{
	if (!Provider || !OnComplete)
	{
		if (OnComplete)
		{
			FMultiCandidatePipelineResult Fail;
			Fail.PipelineLog.Add(TEXT("ERROR: Provider is null"));
			OnComplete(Fail);
		}
		return;
	}

	// Infer archetype from user prompt
	EVFXBehaviorArchetype Archetype = FBehaviorArchetypeLibrary::InferFromPrompt(UserPrompt);

	// Build the V2 system prompt
	FString V2SystemPrompt = BuildV2SystemPrompt(Archetype);

	// Shared state for the pipeline (captured in lambdas)
	struct FPipelineState
	{
		TArray<FVFXCandidate> Candidates;
		int32 CompletedCount = 0;
		int32 TotalRequested = 0;
		int32 TotalLLMCalls = 0;
		int32 RevisionPass = 0;
		FMultiCandidateConfig Config;
		FString UserPrompt;
		FString SystemPrompt;
		EVFXBehaviorArchetype Archetype;
		TArray<FString> Log;
		FOnPipelineComplete OnComplete;
		UHttpLLMProvider* Provider = nullptr;
		FCriticalSection Mutex;

		void LogMsg(const FString& Msg)
		{
			FScopeLock Lock(&Mutex);
			Log.Add(Msg);
			UE_LOG(LogVFXAgent, Log, TEXT("[MultiCandidate] %s"), *Msg);
			FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Orchestrator, Msg);
		}
	};

	TSharedRef<FPipelineState> State = MakeShared<FPipelineState>();
	State->Config = Config;
	State->UserPrompt = UserPrompt;
	State->SystemPrompt = V2SystemPrompt;
	State->Archetype = Archetype;
	State->OnComplete = OnComplete;
	State->Provider = Provider;
	State->TotalRequested = Config.NumCandidates;

	const FBehaviorArchetypeDefinition& ArchDef = FBehaviorArchetypeLibrary::GetDefinition(Archetype);
	State->LogMsg(FString::Printf(TEXT("Pipeline start: archetype=%s, candidates=%d, max_revisions=%d"),
		*ArchDef.DisplayName, Config.NumCandidates, Config.MaxRevisionPasses));

	// Save prompts for debugging
	{
		FString LogDir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("VFXAgent"), TEXT("Logs"));
		IFileManager::Get().MakeDirectory(*LogDir, true);
		FFileHelper::SaveStringToFile(V2SystemPrompt, *FPaths::Combine(LogDir, TEXT("v2_system_prompt.txt")));
		FFileHelper::SaveStringToFile(UserPrompt, *FPaths::Combine(LogDir, TEXT("v2_user_prompt.txt")));
	}

	// Lambda: called when a single candidate LLM response comes back
	auto OnCandidateReceived = [State](int32 CandidateIndex, bool bSuccess, const FString& Json, const FString& Error)
	{
		FVFXCandidate Candidate;
		Candidate.Index = CandidateIndex;
		Candidate.RawJson = Json;

		if (!bSuccess)
		{
			Candidate.bValid = false;
			Candidate.Issues.Add(FString::Printf(TEXT("LLM call failed: %s"), *Error));
			State->LogMsg(FString::Printf(TEXT("Candidate %d: LLM failed — %s"), CandidateIndex, *Error));
		}
		else
		{
			// Parse
			FString ParseError;
			if (!FEffectSpecV2Parser::ParseFromJson(Json, Candidate.Spec, ParseError))
			{
				Candidate.bValid = false;
				Candidate.Issues.Add(FString::Printf(TEXT("Parse failed: %s"), *ParseError));
				State->LogMsg(FString::Printf(TEXT("Candidate %d: Parse failed — %s"), CandidateIndex, *ParseError));
			}
			else
			{
				// Apply archetype defaults for anything missing
				if (Candidate.Spec.Archetype == EVFXBehaviorArchetype::Custom && State->Archetype != EVFXBehaviorArchetype::Custom)
				{
					Candidate.Spec.Archetype = State->Archetype;
				}

				// Validate
				TArray<FString> Errors, Warnings;
				FEffectSpecV2Validator::Validate(Candidate.Spec, Errors, Warnings);

				if (Errors.Num() > 0)
				{
					Candidate.bValid = false;
					Candidate.Issues.Append(Errors);
					Candidate.Issues.Append(Warnings);
					State->LogMsg(FString::Printf(TEXT("Candidate %d: Validation failed (%d errors)"), CandidateIndex, Errors.Num()));
				}
				else
				{
					Candidate.bValid = true;
					// Score
					TArray<FString> Strengths, Issues;
					Candidate.Score = FVFXSpecScorer::Score(Candidate.Spec, Strengths, Issues);
					Candidate.Strengths = Strengths;
					Candidate.Issues.Append(Warnings);
					Candidate.Issues.Append(Issues);
					State->LogMsg(FString::Printf(TEXT("Candidate %d: Valid, score=%.2f, layers=%d"),
						CandidateIndex, Candidate.Score, Candidate.Spec.Layers.Num()));
				}
			}
		}

		// Store result and check if all candidates done
		bool bAllDone = false;
		{
			FScopeLock Lock(&State->Mutex);
			State->Candidates.Add(MoveTemp(Candidate));
			State->CompletedCount++;
			State->TotalLLMCalls++;
			bAllDone = (State->CompletedCount >= State->TotalRequested);
		}

		if (!bAllDone)
		{
			return; // Wait for remaining candidates
		}

		// === All candidates received — select best ===
		int32 BestIdx = -1;
		float BestScore = -1.0f;
		for (int32 i = 0; i < State->Candidates.Num(); ++i)
		{
			if (State->Candidates[i].bValid && State->Candidates[i].Score > BestScore)
			{
				BestScore = State->Candidates[i].Score;
				BestIdx = i;
			}
		}

		if (BestIdx < 0)
		{
			State->LogMsg(TEXT("All candidates failed validation. No viable result."));
			FMultiCandidatePipelineResult Result;
			Result.bSuccess = false;
			Result.AllCandidates = State->Candidates;
			Result.TotalLLMCalls = State->TotalLLMCalls;
			Result.PipelineLog = State->Log;
			AsyncTask(ENamedThreads::GameThread, [State, Result]() { State->OnComplete(Result); });
			return;
		}

		State->LogMsg(FString::Printf(TEXT("Best candidate: #%d, score=%.2f"), BestIdx, BestScore));

		// Check if revision is needed
		FVFXCandidate& Best = State->Candidates[BestIdx];
		const bool bNeedsRevision = Best.Score < State->Config.TargetScore && State->RevisionPass < State->Config.MaxRevisionPasses;

		if (bNeedsRevision && Best.Issues.Num() > 0)
		{
			State->RevisionPass++;
			State->LogMsg(FString::Printf(TEXT("Score %.2f < target %.2f — starting revision pass %d/%d"),
				Best.Score, State->Config.TargetScore, State->RevisionPass, State->Config.MaxRevisionPasses));

			FString RevisionPrompt = BuildRevisionPrompt(Best.Spec, Best.Issues);

			// Fire a single revision request
			State->Provider->RequestEffectSpecJsonAsync(
				RevisionPrompt,
				FString(), // No style refs
				[State, BestIdx](bool bOk, const FString& RevisedJson, const FString& RevError)
				{
					FScopeLock Lock(&State->Mutex);
					State->TotalLLMCalls++;

					if (bOk)
					{
						FEffectSpecV2 RevisedSpec;
						FString ParseErr;
						if (FEffectSpecV2Parser::ParseFromJson(RevisedJson, RevisedSpec, ParseErr))
						{
							TArray<FString> S2, I2;
							float NewScore = FVFXSpecScorer::Score(RevisedSpec, S2, I2);
							State->LogMsg(FString::Printf(TEXT("Revision result: score=%.2f (was %.2f)"),
								NewScore, State->Candidates[BestIdx].Score));

							if (NewScore > State->Candidates[BestIdx].Score)
							{
								State->Candidates[BestIdx].Spec = RevisedSpec;
								State->Candidates[BestIdx].Score = NewScore;
								State->Candidates[BestIdx].Strengths = S2;
								State->Candidates[BestIdx].Issues = I2;
								State->Candidates[BestIdx].RawJson = RevisedJson;
								State->LogMsg(TEXT("Revision accepted (improved score)."));
							}
							else
							{
								State->LogMsg(TEXT("Revision rejected (no improvement)."));
							}
						}
						else
						{
							State->LogMsg(FString::Printf(TEXT("Revision parse failed: %s"), *ParseErr));
						}
					}
					else
					{
						State->LogMsg(FString::Printf(TEXT("Revision LLM failed: %s"), *RevError));
					}

					// Finalize
					FMultiCandidatePipelineResult Result;
					Result.bSuccess = true;
					Result.SelectedIndex = BestIdx;
					Result.SelectedCandidate = State->Candidates[BestIdx];
					Result.AllCandidates = State->Candidates;
					Result.TotalLLMCalls = State->TotalLLMCalls;
					Result.PipelineLog = State->Log;
					AsyncTask(ENamedThreads::GameThread, [State, Result]() { State->OnComplete(Result); });
				});
			return;
		}

		// No revision needed — finalize
		State->LogMsg(FString::Printf(TEXT("Pipeline complete. Score=%.2f, LLM calls=%d"), BestScore, State->TotalLLMCalls));

		FMultiCandidatePipelineResult Result;
		Result.bSuccess = true;
		Result.SelectedIndex = BestIdx;
		Result.SelectedCandidate = Best;
		Result.AllCandidates = State->Candidates;
		Result.TotalLLMCalls = State->TotalLLMCalls;
		Result.PipelineLog = State->Log;
		AsyncTask(ENamedThreads::GameThread, [State, Result]() { State->OnComplete(Result); });
	};

	// Fire N candidate requests
	for (int32 i = 0; i < Config.NumCandidates; ++i)
	{
		const int32 Idx = i;
		// Use the internal method with custom system prompt
		Provider->RequestDirectorJsonInternalAsync(
			UserPrompt + TEXT("\nRespond with JSON."),
			V2SystemPrompt,
			[OnCandidateReceived, Idx](bool bSuccess, const FString& Json, const FString& Error)
			{
				OnCandidateReceived(Idx, bSuccess, Json, Error);
			});
	}
}
