#include "EffectSpecValidator.h"

static void AddError(TArray<FEffectSpecValidationError>& OutErrors, const FString& Path, const FString& Message)
{
	OutErrors.Add({Path, Message});
}

bool FEffectSpecValidator::Validate(const FEffectSpecV1& Spec, TArray<FEffectSpecValidationError>& OutErrors)
{
	OutErrors.Reset();

	if (Spec.EffectName.IsEmpty())
	{
		AddError(OutErrors, TEXT("effect_name"), TEXT("effect_name is required"));
	}
	if (Spec.Layers.Num() == 0)
	{
		AddError(OutErrors, TEXT("layers"), TEXT("at least one layer is required"));
	}
	if (Spec.Layers.Num() < 3)
	{
		AddError(OutErrors, TEXT("layers"), TEXT("at least 3 layers are required"));
	}

	for (int32 i = 0; i < Spec.Layers.Num(); ++i)
	{
		const FLayerSpecV1& Layer = Spec.Layers[i];
		const FString Prefix = FString::Printf(TEXT("layers[%d]"), i);

		if (Layer.Id.IsEmpty()) AddError(OutErrors, Prefix + TEXT(".id"), TEXT("id is required"));
		if (Layer.Name.IsEmpty()) AddError(OutErrors, Prefix + TEXT(".name"), TEXT("name is required"));
		if (Layer.Role.IsEmpty()) AddError(OutErrors, Prefix + TEXT(".role"), TEXT("role is required"));

		const FString RendererLower = Layer.RendererType.ToLower();
		if (!(RendererLower == TEXT("sprite") || RendererLower == TEXT("ribbon") || RendererLower == TEXT("mesh")))
		{
			AddError(OutErrors, Prefix + TEXT(".renderer_type"), TEXT("renderer_type must be sprite|ribbon|mesh"));
		}

		const FString ShadingLower = Layer.Material.Shading.ToLower();
		const FString BlendLower = Layer.Material.Blend.ToLower();
		if (!(ShadingLower == TEXT("unlit") || ShadingLower == TEXT("lit")))
		{
			AddError(OutErrors, Prefix + TEXT(".material.shading"), TEXT("shading must be unlit|lit"));
		}
		if (!(BlendLower == TEXT("additive") || BlendLower == TEXT("translucent") || BlendLower == TEXT("masked") || BlendLower == TEXT("opaque")))
		{
			AddError(OutErrors, Prefix + TEXT(".material.blend"), TEXT("blend must be additive|translucent|masked|opaque"));
		}

		if (Layer.Material.HLSLCustom.Enabled && Layer.Material.HLSLCustom.Code.IsEmpty())
		{
			AddError(OutErrors, Prefix + TEXT(".material.hlsl_custom.code"), TEXT("hlsl_custom.code is required when enabled"));
		}
	}

	return OutErrors.Num() == 0;
}

FString FEffectSpecValidator::FormatErrors(const TArray<FEffectSpecValidationError>& Errors)
{
	TArray<FString> Lines;
	for (const FEffectSpecValidationError& Err : Errors)
	{
		Lines.Add(FString::Printf(TEXT("%s: %s"), *Err.Path, *Err.Message));
	}
	return FString::Join(Lines, TEXT("\n"));
}
