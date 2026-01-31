#pragma once

#include "CoreMinimal.h"
#include "VFXRecipe.h"

/**
 * Input data for LLM generation request
 */
struct FVFXGenerationRequest
{
	// Text description of the desired effect
	FString TextPrompt;

	// Optional reference image path (can be local file or URL)
	FString ReferenceImagePath;

	// Optional reference image data (base64 encoded)
	FString ReferenceImageData;

	// Additional context or constraints
	FString AdditionalContext;

	// Whether to include material generation
	bool bGenerateMaterials = true;

	// Whether to include texture generation
	bool bGenerateTextures = true;

	// Target style (realistic, stylized, cartoon, etc.)
	FString TargetStyle = TEXT("realistic");
};

class ILLMProvider
{
public:
	virtual ~ILLMProvider() = default;
	
	/**
	 * Generate a VFX recipe from a text prompt
	 * @deprecated Use GenerateRecipeFromRequest instead
	 */
	virtual FVFXRecipe GenerateRecipe(const FString& Prompt) = 0;
	
	/**
	 * Generate a VFX recipe from a generation request (supports text and images)
	 */
	virtual FVFXRecipe GenerateRecipeFromRequest(const FVFXGenerationRequest& Request)
	{
		// Default implementation for backward compatibility
		return GenerateRecipe(Request.TextPrompt);
	}

	/**
	 * Refine an existing recipe based on feedback
	 */
	virtual FVFXRecipe RefineRecipe(const FVFXRecipe& OldRecipe, const FString& RefinementPrompt) = 0;

	/**
	 * Analyze a reference image and generate a description for VFX generation
	 */
	virtual FString AnalyzeReferenceImage(const FString& ImagePath)
	{
		return TEXT("Image analysis not supported by this provider");
	}

	/**
	 * Compare generated effect with reference and provide feedback
	 */
	virtual FString CompareWithReference(
		const FVFXRecipe& GeneratedRecipe,
		const FString& ReferenceImagePath,
		const FString& OriginalPrompt)
	{
		return TEXT("Visual comparison not supported by this provider");
	}
};