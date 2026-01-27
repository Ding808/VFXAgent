#include "MockLLMProvider.h"
#include "VFXAgentLog.h"

static FLinearColor GuessMainColor(const FString& Prompt)
{
	if (Prompt.Contains(TEXT("red"), ESearchCase::IgnoreCase) || Prompt.Contains(TEXT("红")))
	{
		return FLinearColor::Red;
	}
	if (Prompt.Contains(TEXT("blue"), ESearchCase::IgnoreCase) || Prompt.Contains(TEXT("蓝")))
	{
		return FLinearColor::Blue;
	}
	if (Prompt.Contains(TEXT("green"), ESearchCase::IgnoreCase) || Prompt.Contains(TEXT("绿")))
	{
		return FLinearColor::Green;
	}
	if (Prompt.Contains(TEXT("yellow"), ESearchCase::IgnoreCase) || Prompt.Contains(TEXT("黄")))
	{
		return FLinearColor(1.0f, 0.9f, 0.1f, 1.0f);
	}
	if (Prompt.Contains(TEXT("purple"), ESearchCase::IgnoreCase) || Prompt.Contains(TEXT("紫")))
	{
		return FLinearColor(0.6f, 0.2f, 0.9f, 1.0f);
	}
	if (Prompt.Contains(TEXT("cyan"), ESearchCase::IgnoreCase) || Prompt.Contains(TEXT("青")))
	{
		return FLinearColor(0.1f, 0.9f, 1.0f, 1.0f);
	}
	return FLinearColor::White;
}

FVFXRecipe UMockLLMProvider::GenerateRecipe(const FString& Prompt)
{
	UE_LOG(LogVFXAgent, Log, TEXT("MockLLMProvider: Generating recipe for prompt: %s"), *Prompt);

	FVFXRecipe Recipe;
	Recipe.bLoop = true;
	Recipe.Duration = 0.0f;
	Recipe.WarmupTime = 0.0f;
	Recipe.Bounds = FVector(100.0f, 100.0f, 100.0f);

	const FLinearColor MainColor = GuessMainColor(Prompt);

	auto AddEmitter = [&Recipe](float SpawnRate, int32 BurstCount, const FString& RendererType, const FLinearColor& Color, float Lifetime)
	{
		FVFXEmitterRecipe E;
		E.SpawnRate = SpawnRate;
		E.BurstCount = BurstCount;
		E.RendererType = RendererType;
		E.Color = Color;
		E.Lifetime = Lifetime;
		Recipe.Emitters.Add(E);
	};

	const bool bExplosion = Prompt.Contains(TEXT("explosion"), ESearchCase::IgnoreCase) || Prompt.Contains(TEXT("爆炸")) || Prompt.Contains(TEXT("炸"));
	const bool bSmoke = Prompt.Contains(TEXT("smoke"), ESearchCase::IgnoreCase) || Prompt.Contains(TEXT("烟")) || Prompt.Contains(TEXT("雾"));
	const bool bSparks = Prompt.Contains(TEXT("spark"), ESearchCase::IgnoreCase) || Prompt.Contains(TEXT("火花")) || Prompt.Contains(TEXT("sparks"), ESearchCase::IgnoreCase);
	const bool bTrail = Prompt.Contains(TEXT("trail"), ESearchCase::IgnoreCase) || Prompt.Contains(TEXT("拖尾")) || Prompt.Contains(TEXT("ribbon"), ESearchCase::IgnoreCase);
	const bool bShockwave = Prompt.Contains(TEXT("shockwave"), ESearchCase::IgnoreCase) || Prompt.Contains(TEXT("冲击波"));
	const bool bElectric = Prompt.Contains(TEXT("electric"), ESearchCase::IgnoreCase) || Prompt.Contains(TEXT("lightning"), ESearchCase::IgnoreCase) || Prompt.Contains(TEXT("电"));

	// Layered default: main + secondary.
	if (bExplosion)
	{
		// Core burst
		AddEmitter(0.0f, 200, TEXT("Sprite"), MainColor, 0.8f);
		// Sparks
		AddEmitter(bSparks ? 150.0f : 80.0f, 0, TEXT("Sprite"), FLinearColor(1.0f, 0.8f, 0.2f, 1.0f), 0.6f);
		// Smoke plume
		AddEmitter(bSmoke ? 30.0f : 15.0f, 0, TEXT("Sprite"), FLinearColor(0.25f, 0.25f, 0.25f, 0.8f), 4.5f);
		if (bShockwave)
		{
			AddEmitter(0.0f, 1, TEXT("Ribbon"), FLinearColor(1.0f, 1.0f, 1.0f, 0.8f), 0.8f);
		}
	}
	else if (bElectric)
	{
		// Electric arcs
		AddEmitter(20.0f, 0, TEXT("Ribbon"), MainColor, 1.2f);
		// Glow/sparks
		AddEmitter(60.0f, 0, TEXT("Sprite"), MainColor, 0.8f);
		if (bSmoke)
		{
			AddEmitter(12.0f, 0, TEXT("Sprite"), FLinearColor(0.2f, 0.2f, 0.2f, 0.6f), 3.5f);
		}
	}
	else
	{
		// Generic 2-layer effect
		AddEmitter(25.0f, 0, bTrail ? TEXT("Ribbon") : TEXT("Sprite"), MainColor, 2.5f);
		AddEmitter(10.0f, 0, TEXT("Sprite"), MainColor * 0.7f, 4.0f);
		if (bSmoke)
		{
			AddEmitter(8.0f, 0, TEXT("Sprite"), FLinearColor(0.25f, 0.25f, 0.25f, 0.6f), 5.0f);
		}
		if (bSparks)
		{
			AddEmitter(120.0f, 0, TEXT("Sprite"), FLinearColor(1.0f, 0.9f, 0.3f, 1.0f), 0.7f);
		}
	}

	// Guarantee at least 2 emitters unless the prompt explicitly asks for a single emitter.
	const bool bExplicitSingle = Prompt.Contains(TEXT("single"), ESearchCase::IgnoreCase) || Prompt.Contains(TEXT("一个发射器"));
	if (!bExplicitSingle && Recipe.Emitters.Num() == 1)
	{
		AddEmitter(8.0f, 0, TEXT("Sprite"), MainColor * 0.5f, 3.0f);
	}

	Recipe.Parameters.Add("Color", MainColor.ToFColor(true).ToHex());
	Recipe.Parameters.Add("Intensity", "1.0");

	FVFXMaterialRecipe Material;
	Material.Description = "Additive sprite material";
	Material.bIsAdditive = true;
	Recipe.Materials.Add(Material);

	Recipe.Version = 1;

	return Recipe;
}


FVFXRecipe UMockLLMProvider::RefineRecipe(const FVFXRecipe& OldRecipe, const FString& RefinementPrompt)
{
	UE_LOG(LogVFXAgent, Log, TEXT("MockLLMProvider: Refining recipe with prompt: %s"), *RefinementPrompt);

	FVFXRecipe NewRecipe = OldRecipe;
	NewRecipe.Version = OldRecipe.Version + 1;

	// Simple mock refinement: change all emitter colors if prompt requests a color
	const FLinearColor NewColor = GuessMainColor(RefinementPrompt);
	const bool bHasColor = !(NewColor == FLinearColor::White) || RefinementPrompt.Contains(TEXT("white"), ESearchCase::IgnoreCase) || RefinementPrompt.Contains(TEXT("白"));
	if (bHasColor)
	{
		for (FVFXEmitterRecipe& E : NewRecipe.Emitters)
		{
			E.Color = NewColor;
		}
		NewRecipe.Parameters["Color"] = NewColor.ToFColor(true).ToHex();
	}

	// Add layers if requested
	if (RefinementPrompt.Contains(TEXT("more smoke"), ESearchCase::IgnoreCase) || RefinementPrompt.Contains(TEXT("增加烟")))
	{
		FVFXEmitterRecipe Smoke;
		Smoke.SpawnRate = 15.0f;
		Smoke.BurstCount = 0;
		Smoke.RendererType = TEXT("Sprite");
		Smoke.Color = FLinearColor(0.25f, 0.25f, 0.25f, 0.6f);
		Smoke.Lifetime = 5.0f;
		NewRecipe.Emitters.Add(Smoke);
	}
	if (RefinementPrompt.Contains(TEXT("trail"), ESearchCase::IgnoreCase) || RefinementPrompt.Contains(TEXT("拖尾")))
	{
		FVFXEmitterRecipe Trail;
		Trail.SpawnRate = 10.0f;
		Trail.BurstCount = 0;
		Trail.RendererType = TEXT("Ribbon");
		Trail.Color = bHasColor ? NewColor : (NewRecipe.Emitters.Num() > 0 ? NewRecipe.Emitters[0].Color : FLinearColor::White);
		Trail.Lifetime = 2.0f;
		NewRecipe.Emitters.Add(Trail);
	}

	return NewRecipe;
}