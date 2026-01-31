#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Input/SCheckBox.h"
#include "Types/SlateEnums.h"
#include "VFXRecipe.h"

class ILLMProvider;

class SVFXAgentPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SVFXAgentPanel)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	virtual bool SupportsKeyboardFocus() const override { return true; }

private:
	// UI callbacks
	FReply OnGenerateClicked();
	FReply OnGenerateFromImageClicked();
	FReply OnApplyRefinementClicked();
	FReply OnChooseOutputPathClicked();
	FReply OnChooseImagePathClicked();
	FReply OnTestLLMClicked();
	FReply OnGenerateWithIterativeOptimizationClicked();

	// Helper functions
	void LogMessage(const FString& Message);
	void UpdateLastRecipe(const FVFXRecipe& Recipe);
	void RefreshLLMSettingsFromConfig();
	void PerformIterativeGeneration(const FString& Prompt, const FString& ImagePath, bool bUseOptimization);
	FVFXRecipe EnhanceRecipeForPrompt(const FVFXRecipe& Recipe, const FString& Prompt);

	// UI elements
	TSharedPtr<class SMultiLineEditableTextBox> PromptTextBox;
	TSharedPtr<class SMultiLineEditableTextBox> RefinementTextBox;
	TSharedPtr<class SEditableTextBox> OutputPathTextBox;
	TSharedPtr<class SEditableTextBox> AssetNameTextBox;
	TSharedPtr<class SEditableTextBox> ImagePathTextBox;
	TSharedPtr<class SMultiLineEditableTextBox> LogTextBox;
	TSharedPtr<class SCheckBox> EnableIterativeOptimizationCheckBox;
	TSharedPtr<SSpinBox<int32>> MaxIterationsSpinBox;
	TSharedPtr<SSpinBox<float>> TargetQualitySpinBox;

	// Data
	FVFXRecipe LastRecipe;
	FString LastPrompt;

	// LLM Provider
	UObject* LLMProviderObject = nullptr;
	ILLMProvider* LLMProvider = nullptr;

	// Cached LLM settings for logging/debug
	FString CachedLLMEndpoint;
	FString CachedLLMModel;
	FString CachedLLMBackend;
	float CachedLLMTimeoutSeconds = 30.0f;
	bool bCachedHasApiKey = false;

	bool bRequestInFlight = false;
};