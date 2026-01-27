#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "VFXRecipe.h"

class ILLMProvider;

class SVFXAgentPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SVFXAgentPanel)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	// UI callbacks
	FReply OnGenerateClicked();
	FReply OnApplyRefinementClicked();
	FReply OnChooseOutputPathClicked();
	FReply OnTestLLMClicked();

	// Helper functions
	void LogMessage(const FString& Message);
	void UpdateLastRecipe(const FVFXRecipe& Recipe);
	void RefreshLLMSettingsFromConfig();

	// UI elements
	TSharedPtr<class SMultiLineEditableTextBox> PromptTextBox;
	TSharedPtr<class SMultiLineEditableTextBox> RefinementTextBox;
	TSharedPtr<class SEditableTextBox> OutputPathTextBox;
	TSharedPtr<class SEditableTextBox> AssetNameTextBox;
	TSharedPtr<class SMultiLineEditableTextBox> LogTextBox;

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