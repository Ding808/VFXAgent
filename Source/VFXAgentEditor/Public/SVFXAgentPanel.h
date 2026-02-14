#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SCheckBox.h"
#include "Types/SlateEnums.h"
#include "VFXRecipe.h"
#include "VFXDirectorTypes.h"
#include "VFXMultiCandidatePipeline.h"

class ILLMProvider;

class SVFXAgentPanel : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SVFXAgentPanel)
	{}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	virtual bool SupportsKeyboardFocus() const override { return true; }
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

private:
	// UI callbacks
	FReply OnGenerateClicked();
	FReply OnGenerateFromImageClicked();
	FReply OnChooseOutputPathClicked();
	FReply OnChooseImagePathClicked();
	FReply OnTestLLMClicked();
	FReply OnGenerateSpecClicked();
	FReply OnValidateSpecClicked();
	FReply OnBuildSpecClicked();
	FReply OnPreviewClicked();
	FReply OnReviseSpecClicked();
	FReply OnCopyPipelineLogClicked();
	FReply OnExportPipelineLogClicked();

	// V2 pipeline callbacks
	FReply OnGenerateV2SpecClicked();
	FReply OnValidateV2SpecClicked();
	FReply OnBuildV2SpecClicked();

	// Helper functions
	void LogMessage(const FString& Message);
	void UpdateLastRecipe(const FVFXRecipe& Recipe);
	void RefreshLLMSettingsFromConfig();
	FVFXRecipe EnhanceRecipeForPrompt(const FVFXRecipe& Recipe, const FString& Prompt);
	void DrainPipelineLog();
	void UpdatePipelineLogText();
	FString BuildPipelineLogText() const;
	void DisplayV2CandidateResults(const FMultiCandidatePipelineResult& Result);

	// UI elements
	TSharedPtr<class SMultiLineEditableTextBox> PromptTextBox;
	TSharedPtr<class SMultiLineEditableTextBox> SpecTextBox;
	TSharedPtr<class SEditableTextBox> OutputPathTextBox;
	TSharedPtr<class SEditableTextBox> AssetNameTextBox;
	TSharedPtr<class SEditableTextBox> ImagePathTextBox;
	TSharedPtr<class SMultiLineEditableTextBox> LogTextBox;
	TSharedPtr<class SMultiLineEditableTextBox> PipelineLogTextBox;
	TSharedPtr<class SCheckBox> UseDirectorPipelineCheckBox;

	// Data
	FVFXRecipe LastRecipe;
	FString LastPrompt;
	FString LastDirectorJson;
	FString LastEffectSpecJson;
	FString LastGeneratedSystemPath;
	FVFXExecutionReport LastExecutionReport;

	// V2 pipeline data
	FMultiCandidatePipelineResult LastV2Result;
	FString LastEffectSpecV2Json;

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
	TArray<FString> PipelineLogLines;
	bool bPipelineLogDirty = false;
	int32 PipelineLogMaxLines = 500;
};