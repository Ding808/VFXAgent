#include "EffectSpecV2Parser.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------
static FString GetStr(const TSharedPtr<FJsonObject>& Obj, const TCHAR* Key, const FString& Default = FString())
{
	if (!Obj.IsValid()) return Default;
	FString V;
	return Obj->TryGetStringField(Key, V) ? V : Default;
}

static double GetNum(const TSharedPtr<FJsonObject>& Obj, const TCHAR* Key, double Default = 0.0)
{
	if (!Obj.IsValid()) return Default;
	double V = Default;
	Obj->TryGetNumberField(Key, V);
	return V;
}

static bool GetBool(const TSharedPtr<FJsonObject>& Obj, const TCHAR* Key, bool Default = false)
{
	if (!Obj.IsValid()) return Default;
	bool V = Default;
	Obj->TryGetBoolField(Key, V);
	return V;
}

static FLinearColor GetColor(const TSharedPtr<FJsonObject>& Obj, const TCHAR* Key, FLinearColor Default = FLinearColor::White)
{
	if (!Obj.IsValid()) return Default;
	const TArray<TSharedPtr<FJsonValue>>* Arr = nullptr;
	if (Obj->TryGetArrayField(Key, Arr) && Arr && Arr->Num() >= 3)
	{
		float R = (float)(*Arr)[0]->AsNumber();
		float G = (float)(*Arr)[1]->AsNumber();
		float B = (float)(*Arr)[2]->AsNumber();
		float A = (Arr->Num() > 3) ? (float)(*Arr)[3]->AsNumber() : 1.0f;
		return FLinearColor(R, G, B, A);
	}
	// Try as hex string: "#RRGGBB"
	FString Hex;
	if (Obj->TryGetStringField(Key, Hex) && Hex.StartsWith(TEXT("#")))
	{
		return FLinearColor(FColor::FromHex(Hex));
	}
	return Default;
}

static EVFXBehaviorArchetype ParseArchetype(const FString& S)
{
	const FString L = S.ToLower();
	if (L.Contains(TEXT("explo")) || L.Contains(TEXT("impact"))) return EVFXBehaviorArchetype::Explosion;
	if (L.Contains(TEXT("magic")) || L.Contains(TEXT("aura")) || L.Contains(TEXT("heal"))) return EVFXBehaviorArchetype::Magic;
	if (L.Contains(TEXT("electric")) || L.Contains(TEXT("arc")) || L.Contains(TEXT("lightning"))) return EVFXBehaviorArchetype::Electric;
	if (L.Contains(TEXT("teleport")) || L.Contains(TEXT("portal")) || L.Contains(TEXT("warp"))) return EVFXBehaviorArchetype::Teleport;
	if (L.Contains(TEXT("fire")) || L.Contains(TEXT("flame"))) return EVFXBehaviorArchetype::Fire;
	if (L.Contains(TEXT("smoke")) || L.Contains(TEXT("fog")) || L.Contains(TEXT("dust"))) return EVFXBehaviorArchetype::Smoke;
	if (L.Contains(TEXT("water")) || L.Contains(TEXT("splash"))) return EVFXBehaviorArchetype::Water;
	return EVFXBehaviorArchetype::Custom;
}

static EMotionVerbV2 ParseMotionVerb(const FString& S)
{
	const FString L = S.ToLower();
	if (L == TEXT("explode"))  return EMotionVerbV2::Explode;
	if (L == TEXT("implode"))  return EMotionVerbV2::Implode;
	if (L == TEXT("rise"))     return EMotionVerbV2::Rise;
	if (L == TEXT("fall"))     return EMotionVerbV2::Fall;
	if (L == TEXT("orbit"))    return EMotionVerbV2::Orbit;
	if (L == TEXT("spiral"))   return EMotionVerbV2::Spiral;
	if (L == TEXT("drift"))    return EMotionVerbV2::Drift;
	if (L == TEXT("snap"))     return EMotionVerbV2::Snap;
	if (L == TEXT("pulse"))    return EMotionVerbV2::Pulse;
	if (L == TEXT("stream"))   return EMotionVerbV2::Stream;
	if (L == TEXT("flutter"))  return EMotionVerbV2::Flutter;
	return EMotionVerbV2::Static;
}

static ELayerRoleV2 ParseLayerRole(const FString& S)
{
	const FString L = S.ToLower();
	if (L.Contains(TEXT("core")) || L.Contains(TEXT("blast"))) return ELayerRoleV2::CoreBlast;
	if (L.Contains(TEXT("secondary")) || L.Contains(TEXT("fill"))) return ELayerRoleV2::SecondaryFill;
	if (L.Contains(TEXT("spark")) || L.Contains(TEXT("debris"))) return ELayerRoleV2::Sparks;
	if (L.Contains(TEXT("trail")) || L.Contains(TEXT("ribbon"))) return ELayerRoleV2::Trail;
	if (L.Contains(TEXT("smoke")) || L.Contains(TEXT("atmosphere"))) return ELayerRoleV2::Smoke;
	if (L.Contains(TEXT("glow")) || L.Contains(TEXT("light")) || L.Contains(TEXT("flash"))) return ELayerRoleV2::Glow;
	if (L.Contains(TEXT("distortion")) || L.Contains(TEXT("shock"))) return ELayerRoleV2::Distortion;
	if (L.Contains(TEXT("ground")) || L.Contains(TEXT("decal"))) return ELayerRoleV2::Ground;
	return ELayerRoleV2::Custom;
}

static EEventTypeV2 ParseEventType(const FString& S)
{
	const FString L = S.ToLower();
	if (L.Contains(TEXT("death")))     return EEventTypeV2::OnDeath;
	if (L.Contains(TEXT("collision"))) return EEventTypeV2::OnCollision;
	if (L.Contains(TEXT("spawn")))     return EEventTypeV2::OnSpawn;
	if (L.Contains(TEXT("lifetime")))  return EEventTypeV2::OnLifetimeExpire;
	if (L.Contains(TEXT("timed")))     return EEventTypeV2::Timed;
	return EEventTypeV2::OnDeath;
}

// ---------------------------------------------------------------------------
// Parse layer
// ---------------------------------------------------------------------------
static FLayerSpecV2 ParseLayer(const TSharedPtr<FJsonObject>& LObj)
{
	FLayerSpecV2 Layer;
	if (!LObj.IsValid()) return Layer;

	Layer.Id = GetStr(LObj, TEXT("id"));
	Layer.Name = GetStr(LObj, TEXT("name"));
	Layer.Role = ParseLayerRole(GetStr(LObj, TEXT("role")));
	Layer.RendererType = GetStr(LObj, TEXT("renderer_type"), TEXT("sprite"));
	Layer.SortOrder = (int32)GetNum(LObj, TEXT("sort_order"), 0);
	Layer.MaxParticles = (int32)GetNum(LObj, TEXT("max_particles"), 500);
	Layer.PerfHint = GetStr(LObj, TEXT("perf_hint"), TEXT("mid"));

	// Timing
	const TSharedPtr<FJsonObject>* TimingObj = nullptr;
	if (LObj->TryGetObjectField(TEXT("timing"), TimingObj) && TimingObj && TimingObj->IsValid())
	{
		Layer.Timing.DelaySeconds = (float)GetNum(*TimingObj, TEXT("delay"), 0);
		Layer.Timing.AttackSeconds = (float)GetNum(*TimingObj, TEXT("attack"), 0.1);
		Layer.Timing.SustainSeconds = (float)GetNum(*TimingObj, TEXT("sustain"), 0.5);
		Layer.Timing.DecaySeconds = (float)GetNum(*TimingObj, TEXT("decay"), 0.4);
		Layer.Timing.TotalLifetime = (float)GetNum(*TimingObj, TEXT("lifetime"), 1.0);
		Layer.Timing.bLoop = GetBool(*TimingObj, TEXT("loop"), false);
	}

	// Spawn
	const TSharedPtr<FJsonObject>* SpawnObj = nullptr;
	if (LObj->TryGetObjectField(TEXT("spawn"), SpawnObj) && SpawnObj && SpawnObj->IsValid())
	{
		Layer.Spawn.Mode = GetStr(*SpawnObj, TEXT("mode"), TEXT("burst"));
		Layer.Spawn.Rate = (float)GetNum(*SpawnObj, TEXT("rate"), 0);
		Layer.Spawn.BurstCount = (int32)GetNum(*SpawnObj, TEXT("burst_count"), 0);
	}

	// Init
	const TSharedPtr<FJsonObject>* InitObj = nullptr;
	if (LObj->TryGetObjectField(TEXT("init"), InitObj) && InitObj && InitObj->IsValid())
	{
		Layer.Init.Lifetime = (float)GetNum(*InitObj, TEXT("lifetime"), 2.0);
		Layer.Init.LifetimeVariation = (float)GetNum(*InitObj, TEXT("lifetime_variation"), 0.2);
		const TArray<TSharedPtr<FJsonValue>>* SizeArr = nullptr;
		if ((*InitObj)->TryGetArrayField(TEXT("size_range"), SizeArr) && SizeArr && SizeArr->Num() >= 2)
		{
			Layer.Init.SizeRange.X = (float)(*SizeArr)[0]->AsNumber();
			Layer.Init.SizeRange.Y = (float)(*SizeArr)[1]->AsNumber();
		}
		const TSharedPtr<FJsonObject>* VelObj = nullptr;
		if ((*InitObj)->TryGetObjectField(TEXT("velocity"), VelObj) && VelObj && VelObj->IsValid())
		{
			Layer.Init.Velocity.X = GetNum(*VelObj, TEXT("x"), 0);
			Layer.Init.Velocity.Y = GetNum(*VelObj, TEXT("y"), 0);
			Layer.Init.Velocity.Z = GetNum(*VelObj, TEXT("z"), 0);
		}
	}

	// Update
	const TSharedPtr<FJsonObject>* UpdateObj = nullptr;
	if (LObj->TryGetObjectField(TEXT("update"), UpdateObj) && UpdateObj && UpdateObj->IsValid())
	{
		Layer.Update.Drag = (float)GetNum(*UpdateObj, TEXT("drag"), 0);
		Layer.Update.CurlNoiseStrength = (float)GetNum(*UpdateObj, TEXT("curl_noise_strength"), 0);
		Layer.Update.ColorOverLife = GetStr(*UpdateObj, TEXT("color_over_life"));
		Layer.Update.AlphaOverLife = GetStr(*UpdateObj, TEXT("alpha_over_life"));
		Layer.Update.SizeOverLife = GetStr(*UpdateObj, TEXT("size_over_life"));
	}

	// Motion
	const TSharedPtr<FJsonObject>* MotionObj = nullptr;
	if (LObj->TryGetObjectField(TEXT("motion"), MotionObj) && MotionObj && MotionObj->IsValid())
	{
		Layer.Motion.Verb = ParseMotionVerb(GetStr(*MotionObj, TEXT("verb"), TEXT("static")));
		const TSharedPtr<FJsonObject>* AxisObj = nullptr;
		if ((*MotionObj)->TryGetObjectField(TEXT("axis"), AxisObj) && AxisObj && AxisObj->IsValid())
		{
			Layer.Motion.Axis.X = GetNum(*AxisObj, TEXT("x"), 0);
			Layer.Motion.Axis.Y = GetNum(*AxisObj, TEXT("y"), 0);
			Layer.Motion.Axis.Z = GetNum(*AxisObj, TEXT("z"), 1);
		}
		Layer.Motion.Speed = (float)GetNum(*MotionObj, TEXT("speed"), 200);
		Layer.Motion.SpeedVariation = (float)GetNum(*MotionObj, TEXT("speed_variation"), 0.3);
		Layer.Motion.CurlNoiseIntensity = (float)GetNum(*MotionObj, TEXT("curl_noise_intensity"), 0);
		Layer.Motion.CurlNoiseFrequency = (float)GetNum(*MotionObj, TEXT("curl_noise_frequency"), 1);
		Layer.Motion.DragCoefficient = (float)GetNum(*MotionObj, TEXT("drag"), 0);
		Layer.Motion.SemanticNote = GetStr(*MotionObj, TEXT("note"));
	}

	// Material
	const TSharedPtr<FJsonObject>* MatObj = nullptr;
	if (LObj->TryGetObjectField(TEXT("material"), MatObj) && MatObj && MatObj->IsValid())
	{
		Layer.Material.Shading = GetStr(*MatObj, TEXT("shading"), TEXT("unlit"));
		Layer.Material.Blend = GetStr(*MatObj, TEXT("blend"), TEXT("additive"));
		Layer.Material.BaseColor = GetColor(*MatObj, TEXT("base_color"), FLinearColor::White);
		Layer.Material.EmissiveColor = GetColor(*MatObj, TEXT("emissive_color"), FLinearColor::White);
		Layer.Material.EmissiveIntensity = (float)GetNum(*MatObj, TEXT("emissive_intensity"), 5.0);
		Layer.Material.Opacity = (float)GetNum(*MatObj, TEXT("opacity"), 0.8);

		const TSharedPtr<FJsonObject>* FeatObj = nullptr;
		if ((*MatObj)->TryGetObjectField(TEXT("features"), FeatObj) && FeatObj && FeatObj->IsValid())
		{
			Layer.Material.Features.bFresnel = GetBool(*FeatObj, TEXT("fresnel"), false);
			Layer.Material.Features.FresnelExponent = (float)GetNum(*FeatObj, TEXT("fresnel_exponent"), 3.0);
			Layer.Material.Features.bDepthFade = GetBool(*FeatObj, TEXT("depth_fade"), true);
			Layer.Material.Features.DepthFadeDistance = (float)GetNum(*FeatObj, TEXT("depth_fade_distance"), 50.0);
			Layer.Material.Features.bUVDistortion = GetBool(*FeatObj, TEXT("uv_distortion"), false);
			Layer.Material.Features.DistortionStrength = (float)GetNum(*FeatObj, TEXT("distortion_strength"), 0);
			Layer.Material.Features.bNoiseMask = GetBool(*FeatObj, TEXT("noise_mask"), false);
			Layer.Material.Features.NoiseTiling = (float)GetNum(*FeatObj, TEXT("noise_tiling"), 4.0);
			Layer.Material.Features.NoiseContrast = (float)GetNum(*FeatObj, TEXT("noise_contrast"), 2.0);
			Layer.Material.Features.bErodeMask = GetBool(*FeatObj, TEXT("erode_mask"), false);
			Layer.Material.Features.ErodeThreshold = (float)GetNum(*FeatObj, TEXT("erode_threshold"), 0.5);
			Layer.Material.Features.bPanUV = GetBool(*FeatObj, TEXT("pan_uv"), false);
		}

		Layer.Material.bCustomHLSL = GetBool(*MatObj, TEXT("custom_hlsl"), false);
		Layer.Material.HLSLCode = GetStr(*MatObj, TEXT("hlsl_code"));
		Layer.Material.HLSLContract = GetStr(*MatObj, TEXT("hlsl_contract"));

		const TSharedPtr<FJsonObject>* TexObj = nullptr;
		if ((*MatObj)->TryGetObjectField(TEXT("texture_slots"), TexObj) && TexObj && TexObj->IsValid())
		{
			for (const auto& KV : (*TexObj)->Values)
			{
				Layer.Material.TextureSlots.Add(KV.Key, KV.Value->AsString());
			}
		}
	}

	return Layer;
}

// ---------------------------------------------------------------------------
// Main parse entry point
// ---------------------------------------------------------------------------
bool FEffectSpecV2Parser::ParseFromJson(const FString& Json, FEffectSpecV2& OutSpec, FString& OutError)
{
	// Strip markdown code fences
	FString Clean = Json;
	Clean.TrimStartAndEndInline();
	if (Clean.StartsWith(TEXT("```")))
	{
		int32 Nl = Clean.Find(TEXT("\n"), ESearchCase::IgnoreCase, ESearchDir::FromStart, 3);
		if (Nl != INDEX_NONE) Clean = Clean.Mid(Nl + 1);
		int32 Back = Clean.Find(TEXT("```"), ESearchCase::IgnoreCase, ESearchDir::FromEnd);
		if (Back != INDEX_NONE) Clean = Clean.Left(Back);
		Clean.TrimStartAndEndInline();
	}

	TSharedPtr<FJsonObject> Root;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Clean);
	if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
	{
		OutError = TEXT("Invalid JSON");
		return false;
	}

	OutSpec.EffectName = GetStr(Root, TEXT("effect_name"));
	if (OutSpec.EffectName.IsEmpty())
	{
		OutError = TEXT("Missing 'effect_name'");
		return false;
	}

	OutSpec.Archetype = ParseArchetype(GetStr(Root, TEXT("archetype"), TEXT("custom")));
	OutSpec.ArchetypeVariant = GetStr(Root, TEXT("archetype_variant"));
	OutSpec.Description = GetStr(Root, TEXT("description"));

	// Global style
	const TSharedPtr<FJsonObject>* StyleObj = nullptr;
	if (Root->TryGetObjectField(TEXT("global_style"), StyleObj) && StyleObj && StyleObj->IsValid())
	{
		OutSpec.GlobalStyle.Palette = GetStr(*StyleObj, TEXT("palette"));
		OutSpec.GlobalStyle.PrimaryColor = GetColor(*StyleObj, TEXT("primary_color"), FLinearColor::White);
		OutSpec.GlobalStyle.SecondaryColor = GetColor(*StyleObj, TEXT("secondary_color"));
		OutSpec.GlobalStyle.AccentColor = GetColor(*StyleObj, TEXT("accent_color"));
		OutSpec.GlobalStyle.RealismToStylized = (float)GetNum(*StyleObj, TEXT("realism_to_stylized"), 0.5);
		OutSpec.GlobalStyle.Brightness = (float)GetNum(*StyleObj, TEXT("brightness"), 1.0);
		OutSpec.GlobalStyle.Saturation = (float)GetNum(*StyleObj, TEXT("saturation"), 1.0);
		OutSpec.GlobalStyle.MoodTag = GetStr(*StyleObj, TEXT("mood"));
	}

	// Layers
	const TArray<TSharedPtr<FJsonValue>>* LayersArr = nullptr;
	if (!Root->TryGetArrayField(TEXT("layers"), LayersArr) || !LayersArr || LayersArr->Num() == 0)
	{
		OutError = TEXT("Missing or empty 'layers' array");
		return false;
	}
	for (const TSharedPtr<FJsonValue>& V : *LayersArr)
	{
		OutSpec.Layers.Add(ParseLayer(V->AsObject()));
	}

	// Events
	const TArray<TSharedPtr<FJsonValue>>* EventsArr = nullptr;
	if (Root->TryGetArrayField(TEXT("events"), EventsArr) && EventsArr)
	{
		for (const TSharedPtr<FJsonValue>& V : *EventsArr)
		{
			const TSharedPtr<FJsonObject> EObj = V->AsObject();
			if (!EObj.IsValid()) continue;
			FEventBindingV2 Evt;
			Evt.SourceLayerId = GetStr(EObj, TEXT("source"));
			Evt.TargetLayerId = GetStr(EObj, TEXT("target"));
			Evt.Type = ParseEventType(GetStr(EObj, TEXT("type"), TEXT("on_death")));
			Evt.Delay = (float)GetNum(EObj, TEXT("delay"), 0);
			Evt.SpawnCount = (int32)GetNum(EObj, TEXT("spawn_count"), 10);
			OutSpec.Events.Add(MoveTemp(Evt));
		}
	}

	// Requirements
	const TSharedPtr<FJsonObject>* ReqObj = nullptr;
	if (Root->TryGetObjectField(TEXT("requirements"), ReqObj) && ReqObj && ReqObj->IsValid())
	{
		OutSpec.Requirements.bRequiresEvents = GetBool(*ReqObj, TEXT("events"), false);
		OutSpec.Requirements.bRequiresForces = GetBool(*ReqObj, TEXT("forces"), true);
		OutSpec.Requirements.bRequiresCollision = GetBool(*ReqObj, TEXT("collision"), false);
		OutSpec.Requirements.bRequiresLightRenderer = GetBool(*ReqObj, TEXT("light_renderer"), false);
		OutSpec.Requirements.bRequiresRibbonRenderer = GetBool(*ReqObj, TEXT("ribbon_renderer"), false);
		OutSpec.Requirements.MinFeatureCount = (int32)GetNum(*ReqObj, TEXT("min_features"), 2);
	}

	// Camera
	const TSharedPtr<FJsonObject>* CamObj = nullptr;
	if (Root->TryGetObjectField(TEXT("camera_readability"), CamObj) && CamObj && CamObj->IsValid())
	{
		OutSpec.CameraReadability.PreferredDistance = GetStr(*CamObj, TEXT("distance"), TEXT("medium"));
		OutSpec.CameraReadability.BoundsRadius = (float)GetNum(*CamObj, TEXT("bounds_radius"), 200);
		OutSpec.CameraReadability.bNeedsSilhouette = GetBool(*CamObj, TEXT("needs_silhouette"), true);
		OutSpec.CameraReadability.ContrastTarget = (float)GetNum(*CamObj, TEXT("contrast_target"), 0.7);
	}

	return true;
}

// ---------------------------------------------------------------------------
// Serialization to JSON string (for logging)
// ---------------------------------------------------------------------------
FString FEffectSpecV2Parser::ToJson(const FEffectSpecV2& Spec)
{
	TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
	Root->SetStringField(TEXT("effect_name"), Spec.EffectName);
	Root->SetNumberField(TEXT("version"), FEffectSpecV2::Version);
	Root->SetStringField(TEXT("description"), Spec.Description);

	// Archetype
	switch (Spec.Archetype)
	{
	case EVFXBehaviorArchetype::Explosion: Root->SetStringField(TEXT("archetype"), TEXT("explosion")); break;
	case EVFXBehaviorArchetype::Magic:     Root->SetStringField(TEXT("archetype"), TEXT("magic")); break;
	case EVFXBehaviorArchetype::Electric:  Root->SetStringField(TEXT("archetype"), TEXT("electric")); break;
	case EVFXBehaviorArchetype::Teleport:  Root->SetStringField(TEXT("archetype"), TEXT("teleport")); break;
	case EVFXBehaviorArchetype::Fire:      Root->SetStringField(TEXT("archetype"), TEXT("fire")); break;
	case EVFXBehaviorArchetype::Smoke:     Root->SetStringField(TEXT("archetype"), TEXT("smoke")); break;
	case EVFXBehaviorArchetype::Water:     Root->SetStringField(TEXT("archetype"), TEXT("water")); break;
	default:                               Root->SetStringField(TEXT("archetype"), TEXT("custom")); break;
	}

	Root->SetNumberField(TEXT("layer_count"), Spec.Layers.Num());
	Root->SetNumberField(TEXT("event_count"), Spec.Events.Num());

	FString Output;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Output);
	FJsonSerializer::Serialize(Root, Writer);
	return Output;
}
