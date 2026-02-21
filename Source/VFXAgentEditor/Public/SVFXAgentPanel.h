// Copyright VFXAgent. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Input/SCheckBox.h"
#include "Types/SlateEnums.h"
#include "VFXRecipe.h"
#include "VFXDirectorTypes.h"
#include "VFXMultiCandidatePipeline.h"

struct FSlateDynamicImageBrush;

class ILLMProvider;
class SVFXChatBubble;

// =============================================================================
// Chat attachment model
// =============================================================================
struct FVFXChatAttachment
{
	FString FilePath;
	FString DisplayName;
	FString Type; // "image", "gif", "video", "niagara_system"
	TSharedPtr<FSlateDynamicImageBrush> PreviewBrush; // Image preview thumbnail
};

// =============================================================================
// SVFXAgentPanel - Modern chat-based VFX Agent interface
// =============================================================================
class SVFXAgentPanel : public SCompoundWidget
{
public:
SLATE_BEGIN_ARGS(SVFXAgentPanel) {}
SLATE_END_ARGS()

void Construct(const FArguments& InArgs);
virtual bool SupportsKeyboardFocus() const override { return true; }
virtual FReply OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;
virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

// Public API
void AgentTextRequest(const FString& Action, const FString& Prompt);

private:
// --- Chat UI ---
void AddUserBubble(const FString& Message, const TArray<FVFXChatAttachment>& MessageAttachments = TArray<FVFXChatAttachment>());
void AddAgentBubble(const FString& Message);
void AddThinkingBubble();
void CompleteThinkingBubble(const FString& Summary);
void AddThinkingStep(const FString& Step);
void AddAssetLinkBubble(const FString& AssetPath, const FString& Message);
void AddErrorBubble(const FString& ErrorMsg);
void ScrollChatToBottom();

// --- Input handling ---
FReply OnSendClicked();
FReply OnAttachFileClicked();
FReply OnPickNiagaraSystemClicked();
FReply OnClearAttachmentsClicked();
FReply OnSettingsClicked();
FReply OnNewChatClicked();

// --- Action buttons in chat ---
FReply OnOpenAssetClicked(FString AssetPath);

// --- Core AI pipeline ---
void ProcessUserMessage(const FString& Message);
void ExecuteAsk(const FString& Prompt);
void ExecuteGenerate(const FString& Prompt);
void ExecuteModify(const FString& Prompt);
void ExecuteDebug(const FString& Prompt);
void ExecuteGenerateFromMedia(const FString& Prompt);

// --- Pipeline internals ---
void ExecuteRecipePipeline(const FString& Prompt, const FString& OutputPath, const FString& AssetName);
void ExecuteDirectorPipeline(const FString& Prompt, const FString& OutputPath, const FString& AssetName);

// --- LLM Provider ---
void RefreshLLMSettingsFromConfig();
FString GetModelDisplayName() const;

// --- Helpers ---
void LogMessage(const FString& Message);
void DrainPipelineLog();
FString SanitizeAssetName(const FString& Name) const;
FString SanitizeOutputPath(const FString& Path) const;
FVFXRecipe EnhanceRecipeForPrompt(const FVFXRecipe& Recipe, const FString& Prompt);
void UpdateLastRecipe(const FVFXRecipe& Recipe);
bool InferIsModifyRequest(const FString& Prompt) const;
bool InferIsDebugRequest(const FString& Prompt) const;
FString BuildDefaultOutputPath() const;
FString BuildDefaultAssetName(const FString& Prompt) const;

// --- UI construction ---
TSharedRef<SWidget> BuildHeader();
TSharedRef<SWidget> BuildChatArea();
TSharedRef<SWidget> BuildInputArea();
void UpdateAttachmentDisplay();
void UpdateStatusDisplay();
TSharedPtr<FSlateDynamicImageBrush> LoadImagePreview(const FString& FilePath, FVector2D PreviewSize = FVector2D(120, 90));

// --- UI callbacks ---
TSharedRef<SWidget> OnGenerateModeComboWidget(TSharedPtr<FString> InItem);
void OnModeSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);
FText GetSelectedModeText() const;

TSharedRef<SWidget> OnGenerateModelComboWidget(TSharedPtr<FString> InItem);
void OnModelSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);
FText GetSelectedModelText() const;

// --- UI widgets ---
TSharedPtr<class SComboBox<TSharedPtr<FString>>> ModeComboBox;
TSharedPtr<class SComboBox<TSharedPtr<FString>>> ModelComboBox;
TSharedPtr<class SScrollBox> ChatScrollBox;
TSharedPtr<class SVerticalBox> ChatListBox;
TSharedPtr<class SMultiLineEditableTextBox> PromptTextBox;
TSharedPtr<class STextBlock> ModelInfoText;
TSharedPtr<class STextBlock> StatusText;
TSharedPtr<class SHorizontalBox> AttachmentBar;
TSharedPtr<class SVerticalBox> AttachmentPreviewBox;
TSharedPtr<class SButton> SendButton;
TSharedPtr<SVFXChatBubble> CurrentThinkingBubble;

// --- State ---
TArray<TSharedPtr<FString>> AvailableModes;
TSharedPtr<FString> SelectedMode;

TArray<TSharedPtr<FString>> AvailableModels;
TSharedPtr<FString> SelectedModel;

// --- Attachments & context ---
TArray<FVFXChatAttachment> Attachments;
FString ReferencedNiagaraSystemPath;

// --- Pipeline state ---
FVFXRecipe LastRecipe;
FString LastPrompt;
FString LastDirectorJson;
FString LastEffectSpecJson;
FString LastEffectSpecV2Json;
FString LastGeneratedSystemPath;
FVFXExecutionReport LastExecutionReport;
FMultiCandidatePipelineResult LastV2Result;

// --- LLM Provider ---
UObject* LLMProviderObject = nullptr;
ILLMProvider* LLMProvider = nullptr;
FString CachedLLMEndpoint;
FString CachedLLMModel;
FString CachedLLMBackend;
float CachedLLMTimeoutSeconds = 30.0f;
bool bCachedHasApiKey = false;

// --- Flags ---
bool bRequestInFlight = false;
TArray<FString> PipelineLogLines;
bool bPipelineLogDirty = false;
int32 PipelineLogMaxLines = 500;
	mutable int32 GenerationCounter = 0;
};
