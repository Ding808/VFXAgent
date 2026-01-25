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

	// Helper functions
	void LogMessage(const FString& Message);
	void UpdateLastRecipe(const FVFXRecipe& Recipe);

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
	ILLMProvider* LLMProvider = nullptr;
};