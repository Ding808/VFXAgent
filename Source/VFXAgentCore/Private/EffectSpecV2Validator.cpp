#include "EffectSpecV2Validator.h"
#include "BehaviorArchetypeLibrary.h"

bool FEffectSpecV2Validator::Validate(const FEffectSpecV2& Spec, TArray<FString>& OutErrors, TArray<FString>& OutWarnings)
{
	OutErrors.Reset();
	OutWarnings.Reset();

	// --- Basic structural checks ---
	if (Spec.EffectName.IsEmpty())
	{
		OutErrors.Add(TEXT("effect_name is required"));
	}

	if (Spec.Layers.Num() == 0)
	{
		OutErrors.Add(TEXT("At least one layer is required"));
	}

	// --- Per-layer validation ---
	TSet<FString> SeenIds;
	bool bHasRibbon = false;
	bool bHasLight = false;
	bool bHasForce = false;

	for (int32 i = 0; i < Spec.Layers.Num(); ++i)
	{
		const FLayerSpecV2& Layer = Spec.Layers[i];
		const FString Prefix = FString::Printf(TEXT("layers[%d]"), i);

		if (Layer.Id.IsEmpty())
			OutErrors.Add(Prefix + TEXT(": id is required"));
		else if (SeenIds.Contains(Layer.Id))
			OutErrors.Add(Prefix + TEXT(": duplicate id '") + Layer.Id + TEXT("'"));
		else
			SeenIds.Add(Layer.Id);

		if (Layer.Name.IsEmpty())
			OutErrors.Add(Prefix + TEXT(": name is required"));

		const FString RT = Layer.RendererType.ToLower();
		if (!(RT == TEXT("sprite") || RT == TEXT("ribbon") || RT == TEXT("mesh") || RT == TEXT("light")))
			OutErrors.Add(Prefix + TEXT(": renderer_type must be sprite|ribbon|mesh|light"));

		if (RT == TEXT("ribbon")) bHasRibbon = true;
		if (RT == TEXT("light")) bHasLight = true;

		// Check material shading/blend
		const FString Shading = Layer.Material.Shading.ToLower();
		const FString Blend = Layer.Material.Blend.ToLower();
		if (!(Shading == TEXT("unlit") || Shading == TEXT("lit")))
			OutErrors.Add(Prefix + TEXT(".material.shading must be unlit|lit"));
		if (!(Blend == TEXT("additive") || Blend == TEXT("translucent") || Blend == TEXT("masked") || Blend == TEXT("opaque")))
			OutErrors.Add(Prefix + TEXT(".material.blend must be additive|translucent|masked|opaque"));

		// Check timing sanity
		const FTimingEnvelopeV2& T = Layer.Timing;
		if (T.TotalLifetime <= 0.0f)
			OutWarnings.Add(Prefix + TEXT(": timing.lifetime should be > 0"));
		if (T.AttackSeconds + T.SustainSeconds + T.DecaySeconds > T.TotalLifetime * 2.0f)
			OutWarnings.Add(Prefix + TEXT(": timing envelope exceeds lifetime significantly"));

		// Forces present?
		if (Layer.Motion.DragCoefficient > 0 || Layer.Motion.CurlNoiseIntensity > 0 || Layer.Motion.Speed > 0)
			bHasForce = true;
		if (Layer.Update.Drag > 0 || Layer.Update.CurlNoiseStrength > 0)
			bHasForce = true;

		// Max particles sanity
		if (Layer.MaxParticles > 10000)
			OutWarnings.Add(Prefix + TEXT(": max_particles > 10000 may cause performance issues"));
	}

	// --- Niagara feature requirements ---
	{
		TArray<FString> FeatureErrors;
		ValidateNiagaraFeatures(Spec, FeatureErrors);
		OutErrors.Append(FeatureErrors);
	}

	// --- Archetype constraints ---
	{
		TArray<FString> ArchViolations = FBehaviorArchetypeLibrary::ValidateAgainstArchetype(Spec);
		for (const FString& V : ArchViolations)
		{
			OutWarnings.Add(FString::Printf(TEXT("Archetype constraint: %s"), *V));
		}
	}

	// --- Event validation ---
	for (int32 i = 0; i < Spec.Events.Num(); ++i)
	{
		const FEventBindingV2& Evt = Spec.Events[i];
		const FString Prefix = FString::Printf(TEXT("events[%d]"), i);

		if (!SeenIds.Contains(Evt.SourceLayerId))
			OutErrors.Add(Prefix + TEXT(": source layer '") + Evt.SourceLayerId + TEXT("' not found"));
		if (!SeenIds.Contains(Evt.TargetLayerId))
			OutErrors.Add(Prefix + TEXT(": target layer '") + Evt.TargetLayerId + TEXT("' not found"));
		if (Evt.SourceLayerId == Evt.TargetLayerId)
			OutWarnings.Add(Prefix + TEXT(": source and target are the same layer"));
	}

	return OutErrors.Num() == 0;
}

bool FEffectSpecV2Validator::HasMinimumLayers(const FEffectSpecV2& Spec, FString& OutError)
{
	const FBehaviorArchetypeDefinition& Def = FBehaviorArchetypeLibrary::GetDefinition(Spec.Archetype);
	if (Spec.Layers.Num() < Def.LayerPresets.Num())
	{
		OutError = FString::Printf(TEXT("Archetype '%s' requires at least %d layers, got %d"),
			*Def.DisplayName, Def.LayerPresets.Num(), Spec.Layers.Num());
		return false;
	}
	return true;
}

bool FEffectSpecV2Validator::ValidateNiagaraFeatures(const FEffectSpecV2& Spec, TArray<FString>& OutErrors)
{
	const FNiagaraFeatureRequirementsV2& Req = Spec.Requirements;

	int32 FeatureCount = 0;
	bool bHasEvent = Spec.Events.Num() > 0;
	bool bHasForce = false;
	bool bHasRibbon = false;
	bool bHasLight = false;

	for (const FLayerSpecV2& Layer : Spec.Layers)
	{
		if (Layer.Motion.DragCoefficient > 0 || Layer.Motion.CurlNoiseIntensity > 0)
			bHasForce = true;
		if (Layer.Update.Drag > 0 || Layer.Update.CurlNoiseStrength > 0)
			bHasForce = true;
		if (Layer.RendererType.ToLower() == TEXT("ribbon"))
			bHasRibbon = true;
		if (Layer.RendererType.ToLower() == TEXT("light"))
			bHasLight = true;
	}

	if (bHasEvent) ++FeatureCount;
	if (bHasForce) ++FeatureCount;
	if (bHasRibbon) ++FeatureCount;
	if (bHasLight) ++FeatureCount;
	// Collision counts if required and present (we track via events for now)
	if (Req.bRequiresCollision) // Collision = special event type
	{
		for (const FEventBindingV2& E : Spec.Events)
		{
			if (E.Type == EEventTypeV2::OnCollision)
			{
				++FeatureCount;
				break;
			}
		}
	}

	if (Req.bRequiresEvents && !bHasEvent)
		OutErrors.Add(TEXT("Niagara constraint: requires at least one event binding"));
	if (Req.bRequiresForces && !bHasForce)
		OutErrors.Add(TEXT("Niagara constraint: requires at least one force (drag/noise/velocity)"));
	if (Req.bRequiresRibbonRenderer && !bHasRibbon)
		OutErrors.Add(TEXT("Niagara constraint: requires at least one ribbon renderer"));
	if (Req.bRequiresLightRenderer && !bHasLight)
		OutErrors.Add(TEXT("Niagara constraint: requires at least one light renderer"));
	if (FeatureCount < Req.MinFeatureCount)
		OutErrors.Add(FString::Printf(TEXT("Niagara constraint: need %d+ features (events/forces/collision/light/ribbon), have %d"), Req.MinFeatureCount, FeatureCount));

	return OutErrors.Num() == 0;
}

FString FEffectSpecV2Validator::FormatReport(const TArray<FString>& Errors, const TArray<FString>& Warnings)
{
	FString Result;
	if (Errors.Num() > 0)
	{
		Result += TEXT("ERRORS:\n");
		for (const FString& E : Errors) Result += TEXT("  ✗ ") + E + TEXT("\n");
	}
	if (Warnings.Num() > 0)
	{
		Result += TEXT("WARNINGS:\n");
		for (const FString& W : Warnings) Result += TEXT("  ⚠ ") + W + TEXT("\n");
	}
	if (Errors.Num() == 0 && Warnings.Num() == 0)
	{
		Result = TEXT("✓ Validation passed.");
	}
	return Result;
}
