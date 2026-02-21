#include "VFXModuleLibrary.h"

static void EnsureCurve(TArray<FVFXCurveKey>& Curve, const TArray<FVFXCurveKey>& Defaults)
{
	if (Curve.Num() == 0)
	{
		Curve = Defaults;
	}
}

static void EnsureForce(TArray<FVFXForceRecipe>& Forces, EVFXForceType Type, float Strength, float Frequency = 0.0f, FVector Direction = FVector::ZeroVector, float Radius = 0.0f, float MaxVelocity = 0.0f)
{
	for (const FVFXForceRecipe& Force : Forces)
	{
		if (Force.Type == Type)
		{
			return;
		}
	}
	FVFXForceRecipe NewForce;
	NewForce.Type = Type;
	NewForce.Strength = Strength;
	NewForce.Frequency = Frequency;
	NewForce.Direction = Direction;
	NewForce.Radius = Radius;
	NewForce.MaxVelocity = MaxVelocity;
	NewForce.bEnabled = true;
	Forces.Add(NewForce);
}

void FVFXModuleLibrary::ApplyDefaults(FVFXLayerRecipe& Layer, TArray<FString>& OutWarnings)
{
	const FString RoleLower = Layer.Role.ToLower();

	// Defaults for common roles
	if (RoleLower.Contains(TEXT("core")))
	{
		Layer.Render.RendererType = Layer.Render.RendererType.IsEmpty() ? TEXT("Sprite") : Layer.Render.RendererType;
		Layer.Render.FacingMode = Layer.Render.FacingMode.IsEmpty() ? TEXT("Camera") : Layer.Render.FacingMode;
		Layer.Render.Alignment = Layer.Render.Alignment.IsEmpty() ? TEXT("Unaligned") : Layer.Render.Alignment;
		Layer.Render.bSoftParticles = true;

		{
			TArray<FVFXCurveKey> Defaults;
			Defaults.Add({0.0f, 0.0f});
			Defaults.Add({0.1f, 1.2f});
			Defaults.Add({0.3f, 1.0f});
			Defaults.Add({1.0f, 0.0f});
			EnsureCurve(Layer.Curves.Size, Defaults);
		}
		{
			TArray<FVFXCurveKey> Defaults;
			Defaults.Add({0.0f, 1.0f});
			Defaults.Add({0.5f, 0.8f});
			Defaults.Add({0.8f, 0.2f});
			Defaults.Add({1.0f, 0.0f});
			EnsureCurve(Layer.Curves.Alpha, Defaults);
		}

		EnsureForce(Layer.Forces, EVFXForceType::CurlNoise, 45.0f, 2.5f);
		EnsureForce(Layer.Forces, EVFXForceType::Drag, 0.5f);
		EnsureForce(Layer.Forces, EVFXForceType::LimitVelocity, 0.0f, 0.0f, FVector::ZeroVector, 0.0f, 1500.0f);
	}
	else if (RoleLower.Contains(TEXT("smoke")))
	{
		Layer.Render.RendererType = Layer.Render.RendererType.IsEmpty() ? TEXT("Sprite") : Layer.Render.RendererType;
		Layer.Render.FacingMode = Layer.Render.FacingMode.IsEmpty() ? TEXT("Camera") : Layer.Render.FacingMode;
		Layer.Render.Alignment = Layer.Render.Alignment.IsEmpty() ? TEXT("Unaligned") : Layer.Render.Alignment;
		Layer.Render.bSoftParticles = true;

		{
			TArray<FVFXCurveKey> Defaults;
			Defaults.Add({0.0f, 0.2f});
			Defaults.Add({0.5f, 1.5f});
			Defaults.Add({1.0f, 2.5f});
			EnsureCurve(Layer.Curves.Size, Defaults);
		}
		{
			TArray<FVFXCurveKey> Defaults;
			Defaults.Add({0.0f, 0.0f});
			Defaults.Add({0.2f, 0.8f});
			Defaults.Add({0.6f, 0.4f});
			Defaults.Add({1.0f, 0.0f});
			EnsureCurve(Layer.Curves.Alpha, Defaults);
		}

		EnsureForce(Layer.Forces, EVFXForceType::Noise, 25.0f, 1.2f);
		EnsureForce(Layer.Forces, EVFXForceType::Drag, 1.5f);
		EnsureForce(Layer.Forces, EVFXForceType::Lift, 120.0f);
	}
	else if (RoleLower.Contains(TEXT("spark")))
	{
		Layer.Render.RendererType = Layer.Render.RendererType.IsEmpty() ? TEXT("Sprite") : Layer.Render.RendererType;
		Layer.Render.FacingMode = Layer.Render.FacingMode.IsEmpty() ? TEXT("Camera") : Layer.Render.FacingMode;
		Layer.Render.Alignment = Layer.Render.Alignment.IsEmpty() ? TEXT("VelocityAligned") : Layer.Render.Alignment;
		Layer.Render.bVelocityAligned = true;
		Layer.Render.MotionStretch = FMath::Max(Layer.Render.MotionStretch, 1.5f);

		{
			TArray<FVFXCurveKey> Defaults;
			Defaults.Add({0.0f, 1.0f});
			Defaults.Add({0.2f, 1.5f});
			Defaults.Add({1.0f, 0.0f});
			EnsureCurve(Layer.Curves.Size, Defaults);
		}
		{
			TArray<FVFXCurveKey> Defaults;
			Defaults.Add({0.0f, 1.0f});
			Defaults.Add({0.8f, 0.8f});
			Defaults.Add({1.0f, 0.0f});
			EnsureCurve(Layer.Curves.Alpha, Defaults);
		}

		EnsureForce(Layer.Forces, EVFXForceType::Gravity, 1.5f);
		EnsureForce(Layer.Forces, EVFXForceType::Drag, 0.3f);
		EnsureForce(Layer.Forces, EVFXForceType::CurlNoise, 30.0f, 3.0f);
		EnsureForce(Layer.Forces, EVFXForceType::LimitVelocity, 0.0f, 0.0f, FVector::ZeroVector, 0.0f, 2000.0f);
	}
	else if (RoleLower.Contains(TEXT("trail")))
	{
		Layer.Render.RendererType = Layer.Render.RendererType.IsEmpty() ? TEXT("Ribbon") : Layer.Render.RendererType;
		Layer.Render.FacingMode = Layer.Render.FacingMode.IsEmpty() ? TEXT("Camera") : Layer.Render.FacingMode;
		Layer.Render.Alignment = Layer.Render.Alignment.IsEmpty() ? TEXT("VelocityAligned") : Layer.Render.Alignment;
		Layer.Render.bVelocityAligned = true;
		Layer.Render.MotionStretch = FMath::Max(Layer.Render.MotionStretch, 1.0f);

		{
			TArray<FVFXCurveKey> Defaults;
			Defaults.Add({0.0f, 1.0f});
			Defaults.Add({0.5f, 0.8f});
			Defaults.Add({1.0f, 0.0f});
			EnsureCurve(Layer.Curves.Size, Defaults);
		}
		{
			TArray<FVFXCurveKey> Defaults;
			Defaults.Add({0.0f, 1.0f});
			Defaults.Add({0.7f, 0.5f});
			Defaults.Add({1.0f, 0.0f});
			EnsureCurve(Layer.Curves.Alpha, Defaults);
		}

		EnsureForce(Layer.Forces, EVFXForceType::CurlNoise, 15.0f, 1.5f);
		EnsureForce(Layer.Forces, EVFXForceType::Drag, 1.5f);
	}
	else
	{
		// Generic fallback
		Layer.Render.RendererType = Layer.Render.RendererType.IsEmpty() ? TEXT("Sprite") : Layer.Render.RendererType;
		Layer.Render.FacingMode = Layer.Render.FacingMode.IsEmpty() ? TEXT("Camera") : Layer.Render.FacingMode;
		Layer.Render.Alignment = Layer.Render.Alignment.IsEmpty() ? TEXT("Unaligned") : Layer.Render.Alignment;
		{
			TArray<FVFXCurveKey> Defaults;
			Defaults.Add({0.0f, 1.0f});
			Defaults.Add({1.0f, 0.0f});
			EnsureCurve(Layer.Curves.Size, Defaults);
		}
		{
			TArray<FVFXCurveKey> Defaults;
			Defaults.Add({0.0f, 1.0f});
			Defaults.Add({1.0f, 0.0f});
			EnsureCurve(Layer.Curves.Alpha, Defaults);
		}
		EnsureForce(Layer.Forces, EVFXForceType::Drag, 0.2f);
		OutWarnings.Add(TEXT("Applied generic module defaults for unknown role."));
	}
}
