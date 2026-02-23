#include "SVFXAgentPanel.h"
#include "VFXAgentLog.h"
#include "VFXAgentSettings.h"
#include "ILLMProvider.h"
#include "MockLLMProvider.h"
#include "HttpLLMProvider.h"
#include "NiagaraSystemGenerator.h"
#include "VFXDirectorJson.h"
#include "VFXActionExecutorNiagara.h"
#include "NiagaraSystem.h"
#include "JsonObjectConverter.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Images/SThrobber.h"
#include "Types/SlateEnums.h"
#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Framework/Application/SlateApplication.h"
#include "Misc/DateTime.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformApplicationMisc.h"
#include "HAL/FileManager.h"
#include "PipelineLog.h"
#include "EffectSpecParser.h"
#include "EffectSpecValidator.h"
#include "AssetBuildPipeline.h"
#include "VFXMultiCandidatePipeline.h"
#include "EffectSpecV2Parser.h"
#include "EffectSpecV2Validator.h"
#include "BehaviorArchetypeLibrary.h"
#include "AssetBuildPipelineV2.h"
#include "VFXPythonExecutor.h"  // Python-first execution (Architecture V3)
#include "Subsystems/AssetEditorSubsystem.h"
#include "Editor.h"
#include "ScopedTransaction.h"
#include "Async/Async.h"
#include "ISettingsModule.h"
#include "Widgets/Images/SImage.h"
#include "Brushes/SlateImageBrush.h"
#include "Brushes/SlateDynamicImageBrush.h"
#include "Rendering/SlateRenderer.h"
#include "IImageWrapperModule.h"
#include "IImageWrapper.h"

#define LOCTEXT_NAMESPACE "SVFXAgentPanel"

// Forward
static FString PipelineStageToString(EPipelineStage Stage);

// ============================================================================
// SVFXChatBubble: Modern chat message widget with thinking visualization
// ============================================================================
class SVFXChatBubble : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SVFXChatBubble)
        : _Role(TEXT("Agent"))
        , _Message(TEXT(""))
        , _IsThinking(false)
        , _IsError(false)
    {}
        SLATE_ARGUMENT(FString, Role)
        SLATE_ARGUMENT(FString, Message)
        SLATE_ARGUMENT(bool, IsThinking)
        SLATE_ARGUMENT(bool, IsError)
    SLATE_END_ARGS()

    void Construct(const FArguments& InArgs)
    {
        Role = InArgs._Role;
        Message = InArgs._Message;
        bIsThinking = InArgs._IsThinking;
        bIsError = InArgs._IsError;

        const bool bIsUser = Role.Equals(TEXT("User"), ESearchCase::IgnoreCase);

        // Colors
        FLinearColor RoleLabelColor = bIsUser
            ? FLinearColor(0.3f, 0.7f, 1.0f)    // Blue for user
            : FLinearColor(0.4f, 0.9f, 0.5f);   // Green for agent

        FLinearColor MessageColor = bIsError
            ? FLinearColor(1.0f, 0.4f, 0.4f)
            : FLinearColor(0.92f, 0.92f, 0.92f);

        FString RoleLabel = bIsUser ? TEXT("You") : TEXT("VFX Agent");

        TSharedPtr<SWidget> ContentWidget;

        if (bIsThinking)
        {
            ContentWidget = SNew(SVerticalBox)
                + SVerticalBox::Slot()
                .AutoHeight()
                [
                    SNew(SHorizontalBox)
                    + SHorizontalBox::Slot()
                    .AutoWidth()
                    .VAlign(VAlign_Center)
                    .Padding(0, 0, 6, 0)
                    [
                        SAssignNew(ThrobberWidget, SThrobber)
                        .Animate(SThrobber::EAnimation::VerticalAndOpacity)
                    ]
                    + SHorizontalBox::Slot()
                    .AutoWidth()
                    .VAlign(VAlign_Center)
                    [
                        SAssignNew(ThinkingLabel, STextBlock)
                        .Text(FText::FromString(TEXT("Thinking...")))
                        .Font(FCoreStyle::Get().GetFontStyle("SmallFont"))
                        .ColorAndOpacity(FSlateColor(FLinearColor(0.7f, 0.7f, 0.7f)))
                    ]
                ]
                + SVerticalBox::Slot()
                .AutoHeight()
                .Padding(16, 4, 0, 0)
                [
                    SAssignNew(StepsBox, SVerticalBox)
                ]
                + SVerticalBox::Slot()
                .AutoHeight()
                .Padding(0, 6, 0, 0)
                [
                    SAssignNew(ResultBox, SVerticalBox)
                ];
        }
        else
        {
            ContentWidget = SNew(STextBlock)
                .Text(FText::FromString(Message))
                .AutoWrapText(true)
                .ColorAndOpacity(MessageColor);
        }

        ChildSlot
        [
            SNew(SBorder)
            .Padding(FMargin(12.0f, 8.0f))
            .BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
            .BorderBackgroundColor(bIsUser ? FLinearColor(0.12f, 0.12f, 0.15f) : FLinearColor(0.08f, 0.08f, 0.10f))
            [
                SNew(SVerticalBox)
                + SVerticalBox::Slot()
                .AutoHeight()
                .Padding(0, 0, 0, 4)
                [
                    SNew(STextBlock)
                    .Text(FText::FromString(RoleLabel))
                    .Font(FAppStyle::GetFontStyle("DetailsView.CategoryFontStyle"))
                    .ColorAndOpacity(RoleLabelColor)
                ]
                + SVerticalBox::Slot()
                .AutoHeight()
                [
                    ContentWidget.ToSharedRef()
                ]
            ]
        ];
    }

    void AddStep(const FString& StepInfo)
    {
        if (!StepsBox.IsValid()) return;

        StepsBox->AddSlot()
            .AutoHeight()
            .Padding(0, 1)
            [
                SNew(SHorizontalBox)
                + SHorizontalBox::Slot()
                .AutoWidth()
                .Padding(0, 0, 4, 0)
                [
                    SNew(STextBlock)
                    .Text(FText::FromString(TEXT("\x2192")))
                    .Font(FCoreStyle::Get().GetFontStyle("SmallFont"))
                    .ColorAndOpacity(FLinearColor(0.5f, 0.8f, 1.0f))
                ]
                + SHorizontalBox::Slot()
                .FillWidth(1.0f)
                [
                    SNew(STextBlock)
                    .Text(FText::FromString(StepInfo))
                    .Font(FCoreStyle::Get().GetFontStyle("SmallFont"))
                    .ColorAndOpacity(FLinearColor(0.65f, 0.65f, 0.65f))
                    .AutoWrapText(true)
                ]
            ];
    }

    void Complete(const FString& FinalMessage)
    {
        // Hide throbber
        if (ThrobberWidget.IsValid())
        {
            ThrobberWidget->SetVisibility(EVisibility::Collapsed);
        }
        if (ThinkingLabel.IsValid())
        {
            ThinkingLabel->SetText(FText::FromString(TEXT("Done")));
            ThinkingLabel->SetColorAndOpacity(FSlateColor(FLinearColor(0.4f, 0.9f, 0.5f)));
        }

        if (ResultBox.IsValid() && !FinalMessage.IsEmpty())
        {
            ResultBox->AddSlot()
                .AutoHeight()
                [
                    SNew(STextBlock)
                    .Text(FText::FromString(FinalMessage))
                    .AutoWrapText(true)
                    .ColorAndOpacity(FLinearColor(0.92f, 0.92f, 0.92f))
                ];
        }
    }

    void AddActionButton(const FString& Label, FOnClicked OnClicked)
    {
        if (!ResultBox.IsValid()) return;

        ResultBox->AddSlot()
            .AutoHeight()
            .Padding(0, 4)
            [
                SNew(SButton)
                .OnClicked(OnClicked)
                .Content()
                [
                    SNew(STextBlock)
                    .Text(FText::FromString(Label))
                ]
            ];
    }

private:
    FString Role;
    FString Message;
    bool bIsThinking = false;
    bool bIsError = false;
    TSharedPtr<SVerticalBox> StepsBox;
    TSharedPtr<SVerticalBox> ResultBox;
    TSharedPtr<SThrobber> ThrobberWidget;
    TSharedPtr<STextBlock> ThinkingLabel;
};
// ============================================================================
// SVFXAgentPanel: Construct - Main UI layout
// ============================================================================
void SVFXAgentPanel::Construct(const FArguments& InArgs)
{
    AvailableModes.Add(MakeShared<FString>(TEXT("Agent")));
    AvailableModes.Add(MakeShared<FString>(TEXT("Ask")));
    SelectedMode = AvailableModes[0];

    AvailableModels.Add(MakeShared<FString>(TEXT("gpt-4o")));
    AvailableModels.Add(MakeShared<FString>(TEXT("gpt-5")));
    AvailableModels.Add(MakeShared<FString>(TEXT("gemini-3.1-pro")));
    AvailableModels.Add(MakeShared<FString>(TEXT("claude-3.5-sonnet")));
    SelectedModel = AvailableModels[0];

    RefreshLLMSettingsFromConfig();

    ChildSlot
    [
        SNew(SBorder)
        .BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
        .BorderBackgroundColor(FLinearColor(0.02f, 0.02f, 0.02f))
        [
            SNew(SVerticalBox)

            // === Header ===
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                BuildHeader()
            ]

            // === Chat Area (main content) ===
            + SVerticalBox::Slot()
            .FillHeight(1.0f)
            [
                BuildChatArea()
            ]

            // === Input Area (bottom) ===
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                BuildInputArea()
            ]
        ]
    ];

    // Welcome message
    AddAgentBubble(TEXT("Hello! I'm your VFX Agent. Here's what I can do:\n\n")
        TEXT("  - Describe an effect in natural language to generate it\n")
        TEXT("  - Attach an image, GIF, or video as reference\n")
        TEXT("  - Reference an existing Niagara System to modify or debug it\n\n")
        TEXT("Type what you want and press Enter to send! (Shift+Enter for newline)"));
}

TSharedRef<SWidget> SVFXAgentPanel::OnGenerateModeComboWidget(TSharedPtr<FString> InItem)
{
    return SNew(STextBlock).Text(FText::FromString(*InItem));
}

void SVFXAgentPanel::OnModeSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo)
{
    if (NewSelection.IsValid())
    {
        SelectedMode = NewSelection;
    }
}

FText SVFXAgentPanel::GetSelectedModeText() const
{
    return SelectedMode.IsValid() ? FText::FromString(*SelectedMode) : FText::FromString(TEXT("Agent"));
}

TSharedRef<SWidget> SVFXAgentPanel::OnGenerateModelComboWidget(TSharedPtr<FString> InItem)
{
    return SNew(STextBlock).Text(FText::FromString(*InItem));
}

void SVFXAgentPanel::OnModelSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo)
{
    if (NewSelection.IsValid())
    {
        SelectedModel = NewSelection;
        // Update settings
        UVFXAgentSettings* Settings = GetMutableDefault<UVFXAgentSettings>();
        if (Settings)
        {
            Settings->LLMModel = *NewSelection;
            Settings->SaveConfig();
            RefreshLLMSettingsFromConfig();
        }
    }
}

FText SVFXAgentPanel::GetSelectedModelText() const
{
    return SelectedModel.IsValid() ? FText::FromString(*SelectedModel) : FText::FromString(TEXT("gpt-4o"));
}

TSharedRef<SWidget> SVFXAgentPanel::BuildHeader()
{
    return SNew(SBorder)
        .BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
        .BorderBackgroundColor(FLinearColor(0.06f, 0.06f, 0.08f))
        .Padding(FMargin(12.0f, 8.0f))
        [
            SNew(SHorizontalBox)

            // Title
            + SHorizontalBox::Slot()
            .AutoWidth()
            .VAlign(VAlign_Center)
            [
                SNew(STextBlock)
                .Text(FText::FromString(TEXT("VFX Agent")))
                .Font(FCoreStyle::Get().GetFontStyle("HeadingExtraSmall"))
            ]

            // Mode Selector
            + SHorizontalBox::Slot()
            .AutoWidth()
            .VAlign(VAlign_Center)
            .Padding(12, 0, 0, 0)
            [
                SAssignNew(ModeComboBox, SComboBox<TSharedPtr<FString>>)
                .OptionsSource(&AvailableModes)
                .OnGenerateWidget(this, &SVFXAgentPanel::OnGenerateModeComboWidget)
                .OnSelectionChanged(this, &SVFXAgentPanel::OnModeSelectionChanged)
                [
                    SNew(STextBlock)
                    .Text(this, &SVFXAgentPanel::GetSelectedModeText)
                ]
            ]

            // Model Selector
            + SHorizontalBox::Slot()
            .AutoWidth()
            .VAlign(VAlign_Center)
            .Padding(8, 0, 0, 0)
            [
                SAssignNew(ModelComboBox, SComboBox<TSharedPtr<FString>>)
                .OptionsSource(&AvailableModels)
                .OnGenerateWidget(this, &SVFXAgentPanel::OnGenerateModelComboWidget)
                .OnSelectionChanged(this, &SVFXAgentPanel::OnModelSelectionChanged)
                [
                    SNew(STextBlock)
                    .Text(this, &SVFXAgentPanel::GetSelectedModelText)
                ]
            ]

            // Spacer
            + SHorizontalBox::Slot()
            .FillWidth(1.0f)
            [
                SNew(SSpacer)
            ]

            // Status indicator
            + SHorizontalBox::Slot()
            .AutoWidth()
            .VAlign(VAlign_Center)
            .Padding(8, 0, 0, 0)
            [
                SAssignNew(StatusText, STextBlock)
                .Text(FText::FromString(TEXT("Ready")))
                .ColorAndOpacity(FLinearColor(0.4f, 0.9f, 0.5f))
            ]

            // New Chat button
            + SHorizontalBox::Slot()
            .AutoWidth()
            .VAlign(VAlign_Center)
            .Padding(8, 0, 0, 0)
            [
                SNew(SButton)
                .ToolTipText(FText::FromString(TEXT("Start a new conversation")))
                .OnClicked(this, &SVFXAgentPanel::OnNewChatClicked)
                .ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("SimpleButton"))
                [
                    SNew(STextBlock)
                    .Text(FText::FromString(TEXT("New Chat")))
                    .ColorAndOpacity(FSlateColor::UseSubduedForeground())
                ]
            ]

            // Settings button
            + SHorizontalBox::Slot()
            .AutoWidth()
            .VAlign(VAlign_Center)
            .Padding(8, 0, 0, 0)
            [
                SNew(SButton)
                .ToolTipText(FText::FromString(TEXT("Open VFX Agent Settings")))
                .OnClicked(this, &SVFXAgentPanel::OnSettingsClicked)
                .ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("SimpleButton"))
                [
                    SNew(STextBlock)
                    .Text(FText::FromString(TEXT("Settings")))
                    .ColorAndOpacity(FSlateColor::UseSubduedForeground())
                ]
            ]
        ];
}

TSharedRef<SWidget> SVFXAgentPanel::BuildChatArea()
{
    return SNew(SBorder)
        .BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
        .BorderBackgroundColor(FLinearColor(0.03f, 0.03f, 0.04f))
        .Padding(FMargin(8.0f))
        [
            SAssignNew(ChatScrollBox, SScrollBox)
            + SScrollBox::Slot()
            [
                SAssignNew(ChatListBox, SVerticalBox)
            ]
        ];
}

TSharedRef<SWidget> SVFXAgentPanel::BuildInputArea()
{
    return SNew(SBorder)
        .BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
        .BorderBackgroundColor(FLinearColor(0.06f, 0.06f, 0.08f))
        .Padding(FMargin(10.0f, 8.0f))
        [
            SNew(SVerticalBox)

            // Attachment preview area (hidden by default)
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(0, 0, 0, 4)
            [
                SAssignNew(AttachmentBar, SHorizontalBox)
                .Visibility(EVisibility::Collapsed)
            ]

            // Attachment image preview (hidden by default)
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(0, 0, 0, 4)
            [
                SAssignNew(AttachmentPreviewBox, SVerticalBox)
                .Visibility(EVisibility::Collapsed)
            ]

            // Input row: attachment buttons + text + send
            + SVerticalBox::Slot()
            .AutoHeight()
            [
                SNew(SHorizontalBox)

                // Attach file button (image/gif/video)
                + SHorizontalBox::Slot()
                .AutoWidth()
                .VAlign(VAlign_Bottom)
                .Padding(0, 0, 4, 0)
                [
                    SNew(SButton)
                    .ToolTipText(FText::FromString(TEXT("Attach image, GIF, or video as reference")))
                    .OnClicked(this, &SVFXAgentPanel::OnAttachFileClicked)
                    [
                        SNew(STextBlock)
                        .Text(FText::FromString(TEXT("+")))
                        .Font(FCoreStyle::Get().GetFontStyle("HeadingSmall"))
                    ]
                ]

                // Pick Niagara System button
                + SHorizontalBox::Slot()
                .AutoWidth()
                .VAlign(VAlign_Bottom)
                .Padding(0, 0, 4, 0)
                [
                    SNew(SButton)
                    .ToolTipText(FText::FromString(TEXT("Reference an existing Niagara System for modification or debugging")))
                    .OnClicked(this, &SVFXAgentPanel::OnPickNiagaraSystemClicked)
                    [
                        SNew(STextBlock)
                        .Text(FText::FromString(TEXT("NS")))
                        .Font(FCoreStyle::Get().GetFontStyle("SmallFont"))
                    ]
                ]

                // Text input
                + SHorizontalBox::Slot()
                .FillWidth(1.0f)
                .VAlign(VAlign_Bottom)
                [
                    SAssignNew(PromptTextBox, SMultiLineEditableTextBox)
                    .HintText(FText::FromString(TEXT("Describe a VFX effect, ask for modifications, or describe a problem...")))
                    .AutoWrapText(true)
                ]

                // Send button
                + SHorizontalBox::Slot()
                .AutoWidth()
                .VAlign(VAlign_Bottom)
                .Padding(6, 0, 0, 0)
                [
                    SAssignNew(SendButton, SButton)
                    .OnClicked(this, &SVFXAgentPanel::OnSendClicked)
                    [
                        SNew(STextBlock)
                        .Text(FText::FromString(TEXT("Send")))
                    ]
                ]
            ]
        ];
}
// ============================================================================
// Chat bubble helpers
// ============================================================================
void SVFXAgentPanel::AddUserBubble(const FString& Message, const TArray<FVFXChatAttachment>& MessageAttachments)
{
    if (!ChatListBox.IsValid()) return;

    // Build a vertical box: image previews + text bubble
    TSharedRef<SVerticalBox> UserContent = SNew(SVerticalBox);

    // Add image thumbnails from attachments
    for (const FVFXChatAttachment& Att : MessageAttachments)
    {
        if (Att.PreviewBrush.IsValid() && (Att.Type == TEXT("image") || Att.Type == TEXT("gif")))
        {
            UserContent->AddSlot()
                .AutoHeight()
                .Padding(0, 0, 0, 4)
                [
                    SNew(SBorder)
                    .BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
                    .BorderBackgroundColor(FLinearColor(0.05f, 0.05f, 0.07f))
                    .Padding(4.0f)
                    [
                        SNew(SBox)
                        .WidthOverride(160)
                        .HeightOverride(160)
                        [
                            SNew(SImage)
                            .Image(Att.PreviewBrush.Get())
                        ]
                    ]
                ];
        }
    }

    // Add text bubble
    UserContent->AddSlot()
        .AutoHeight()
        [
            SNew(SVFXChatBubble)
            .Role(TEXT("User"))
            .Message(Message)
        ];

    ChatListBox->AddSlot()
        .AutoHeight()
        .Padding(40, 0, 0, 8)
        [
            UserContent
        ];

    ScrollChatToBottom();
}

void SVFXAgentPanel::AddAgentBubble(const FString& Message)
{
    if (!ChatListBox.IsValid()) return;

    ChatListBox->AddSlot()
        .AutoHeight()
        .Padding(0, 0, 40, 8)
        [
            SNew(SVFXChatBubble)
            .Role(TEXT("Agent"))
            .Message(Message)
        ];

    ScrollChatToBottom();
}

void SVFXAgentPanel::AddThinkingBubble()
{
    if (!ChatListBox.IsValid()) return;

    TSharedPtr<SVFXChatBubble> Bubble;
    ChatListBox->AddSlot()
        .AutoHeight()
        .Padding(0, 0, 40, 8)
        [
            SAssignNew(Bubble, SVFXChatBubble)
            .Role(TEXT("Agent"))
            .IsThinking(true)
        ];

    CurrentThinkingBubble = Bubble;
    ScrollChatToBottom();
}

void SVFXAgentPanel::CompleteThinkingBubble(const FString& Summary)
{
    if (CurrentThinkingBubble.IsValid())
    {
        CurrentThinkingBubble->Complete(Summary);
        CurrentThinkingBubble.Reset();
    }
    else
    {
        AddAgentBubble(Summary);
    }
    ScrollChatToBottom();
}

void SVFXAgentPanel::AddThinkingStep(const FString& Step)
{
    if (CurrentThinkingBubble.IsValid())
    {
        CurrentThinkingBubble->AddStep(Step);
        ScrollChatToBottom();
    }
}

void SVFXAgentPanel::AddAssetLinkBubble(const FString& AssetPath, const FString& Message)
{
    if (!ChatListBox.IsValid()) return;

    TSharedPtr<SVFXChatBubble> Bubble;
    ChatListBox->AddSlot()
        .AutoHeight()
        .Padding(0, 0, 40, 8)
        [
            SAssignNew(Bubble, SVFXChatBubble)
            .Role(TEXT("Agent"))
            .Message(Message)
        ];

    if (Bubble.IsValid())
    {
        Bubble->AddActionButton(TEXT("Open in Editor"), FOnClicked::CreateSP(this, &SVFXAgentPanel::OnOpenAssetClicked, AssetPath));
    }
    ScrollChatToBottom();
}

void SVFXAgentPanel::AddErrorBubble(const FString& ErrorMsg)
{
    if (!ChatListBox.IsValid()) return;

    ChatListBox->AddSlot()
        .AutoHeight()
        .Padding(0, 0, 40, 8)
        [
            SNew(SVFXChatBubble)
            .Role(TEXT("Agent"))
            .Message(ErrorMsg)
            .IsError(true)
        ];

    ScrollChatToBottom();
}

void SVFXAgentPanel::ScrollChatToBottom()
{
    if (ChatScrollBox.IsValid())
    {
        ChatScrollBox->ScrollToEnd();
    }
}

// ============================================================================
// Input handlers
// ============================================================================
FReply SVFXAgentPanel::OnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
    // Enter (without Shift) sends the message
    if (InKeyEvent.GetKey() == EKeys::Enter && !InKeyEvent.IsShiftDown())
    {
        OnSendClicked();
        return FReply::Handled();
    }
    return FReply::Unhandled();
}

FReply SVFXAgentPanel::OnSendClicked()
{
    RefreshLLMSettingsFromConfig();

    if (bRequestInFlight)
    {
        AddAgentBubble(TEXT("A request is already in progress. Please wait..."));
        return FReply::Handled();
    }

    if (!PromptTextBox.IsValid()) return FReply::Handled();

    FString Prompt = PromptTextBox->GetText().ToString().TrimStartAndEnd();
    if (Prompt.IsEmpty()) return FReply::Handled();

    // Show user message with image previews
    FString DisplayMessage = Prompt;
    if (!ReferencedNiagaraSystemPath.IsEmpty())
    {
        DisplayMessage += FString::Printf(TEXT("\n[Ref: %s]"), *ReferencedNiagaraSystemPath);
    }
    for (const FVFXChatAttachment& Att : Attachments)
    {
        DisplayMessage += FString::Printf(TEXT("\n[%s: %s]"), *Att.Type, *Att.DisplayName);
    }
    AddUserBubble(DisplayMessage, Attachments);

    // Clear input
    PromptTextBox->SetText(FText::GetEmpty());

    // Process
    ProcessUserMessage(Prompt);

    return FReply::Handled();
}

FReply SVFXAgentPanel::OnAttachFileClicked()
{
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (!DesktopPlatform) return FReply::Handled();

    const void* ParentWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);

    TArray<FString> OutFiles;
    const FString FileTypes = TEXT("Media Files (*.png;*.jpg;*.jpeg;*.webp;*.gif;*.mp4;*.mov;*.avi)|*.png;*.jpg;*.jpeg;*.webp;*.gif;*.mp4;*.mov;*.avi|All Files (*.*)|*.*");
    const bool bFilePicked = DesktopPlatform->OpenFileDialog(
        const_cast<void*>(ParentWindowHandle),
        TEXT("Choose Reference Media"),
        TEXT(""),
        TEXT(""),
        FileTypes,
        EFileDialogFlags::None,
        OutFiles);

    if (bFilePicked && OutFiles.Num() > 0)
    {
        const FString SelectedFile = OutFiles[0];
        FString Ext = FPaths::GetExtension(SelectedFile).ToLower();

        FVFXChatAttachment Att;
        Att.FilePath = SelectedFile;
        Att.DisplayName = FPaths::GetCleanFilename(SelectedFile);

        if (Ext == TEXT("gif"))
            Att.Type = TEXT("gif");
        else if (Ext == TEXT("mp4") || Ext == TEXT("mov") || Ext == TEXT("avi"))
            Att.Type = TEXT("video");
        else
            Att.Type = TEXT("image");

        // Create preview brush for images
        if (Att.Type == TEXT("image") || Att.Type == TEXT("gif"))
        {
            Att.PreviewBrush = LoadImagePreview(SelectedFile);
        }

        Attachments.Add(Att);
        UpdateAttachmentDisplay();
    }

    return FReply::Handled();
}

FReply SVFXAgentPanel::OnPickNiagaraSystemClicked()
{
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (!DesktopPlatform) return FReply::Handled();

    const void* ParentWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);

    TArray<FString> OutFiles;
    const FString FileTypes = TEXT("Niagara System (*.uasset)|*.uasset|All Files (*.*)|*.*");
    const bool bFilePicked = DesktopPlatform->OpenFileDialog(
        const_cast<void*>(ParentWindowHandle),
        TEXT("Choose Niagara System"),
        FPaths::ProjectContentDir(),
        TEXT(""),
        FileTypes,
        EFileDialogFlags::None,
        OutFiles);

    if (bFilePicked && OutFiles.Num() > 0)
    {
        FString FullPath = FPaths::ConvertRelativePathToFull(OutFiles[0]);
        FString ContentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());

        if (FullPath.StartsWith(ContentDir))
        {
            FString Relative = FullPath.Mid(ContentDir.Len());
            Relative = Relative.Replace(TEXT("\\"), TEXT("/"));
            Relative = FPaths::GetBaseFilename(Relative, false);
            ReferencedNiagaraSystemPath = FString::Printf(TEXT("/Game/%s"), *Relative);
        }
        else
        {
            ReferencedNiagaraSystemPath = OutFiles[0];
        }

        FVFXChatAttachment Att;
        Att.FilePath = ReferencedNiagaraSystemPath;
        Att.DisplayName = FPaths::GetBaseFilename(ReferencedNiagaraSystemPath);
        Att.Type = TEXT("niagara_system");
        Attachments.Add(Att);

        UpdateAttachmentDisplay();
    }

    return FReply::Handled();
}

FReply SVFXAgentPanel::OnClearAttachmentsClicked()
{
    Attachments.Empty();
    ReferencedNiagaraSystemPath.Empty();
    UpdateAttachmentDisplay();
    return FReply::Handled();
}

FReply SVFXAgentPanel::OnSettingsClicked()
{
    // Try to open VFXAgent settings in the Project Settings editor
    ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings");
    if (SettingsModule)
    {
        SettingsModule->ShowViewer(TEXT("Project"), TEXT("Plugins"), TEXT("VFXAgent"));
    }
    else
    {
        AddAgentBubble(TEXT("You can find VFX Agent settings in:\n  Edit -> Project Settings -> VFX Agent\n\nConfigure LLM endpoint, API key, model, output paths and more."));
    }
    return FReply::Handled();
}

FReply SVFXAgentPanel::OnNewChatClicked()
{
    // Clear chat
    if (ChatListBox.IsValid())
    {
        ChatListBox->ClearChildren();
    }

    // Reset state
    Attachments.Empty();
    ReferencedNiagaraSystemPath.Empty();
    LastRecipe = FVFXRecipe();
    LastPrompt.Empty();
    LastDirectorJson.Empty();
    LastEffectSpecJson.Empty();
    LastEffectSpecV2Json.Empty();
    LastGeneratedSystemPath.Empty();
    PipelineLogLines.Empty();
    CurrentThinkingBubble.Reset();
    UpdateAttachmentDisplay();

    AddAgentBubble(TEXT("Chat cleared. How can I help you with VFX today?"));
    return FReply::Handled();
}

FReply SVFXAgentPanel::OnOpenAssetClicked(FString AssetPath)
{
    if (AssetPath.IsEmpty()) return FReply::Handled();

    UNiagaraSystem* System = LoadObject<UNiagaraSystem>(nullptr, *AssetPath);
    if (System && GEditor)
    {
        UAssetEditorSubsystem* Subsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
        if (Subsystem)
        {
            Subsystem->OpenEditorForAsset(System);
        }
    }
    else
    {
        AddErrorBubble(FString::Printf(TEXT("Failed to open asset: %s"), *AssetPath));
    }
    return FReply::Handled();
}

void SVFXAgentPanel::UpdateAttachmentDisplay()
{
    if (!AttachmentBar.IsValid() || !AttachmentPreviewBox.IsValid()) return;

    if (Attachments.Num() == 0)
    {
        AttachmentBar->SetVisibility(EVisibility::Collapsed);
        AttachmentPreviewBox->SetVisibility(EVisibility::Collapsed);
        return;
    }

    // Rebuild attachment bar with labels + clear button
    AttachmentBar->ClearChildren();
    AttachmentBar->SetVisibility(EVisibility::Visible);

    for (const FVFXChatAttachment& Att : Attachments)
    {
        AttachmentBar->AddSlot()
            .AutoWidth()
            .Padding(0, 0, 8, 0)
            .VAlign(VAlign_Center)
            [
                SNew(STextBlock)
                .Text(FText::FromString(FString::Printf(TEXT("[%s] %s"), *Att.Type.ToUpper(), *Att.DisplayName)))
                .ColorAndOpacity(FLinearColor(0.5f, 0.8f, 1.0f))
                .Font(FCoreStyle::Get().GetFontStyle("SmallFont"))
            ];
    }

    AttachmentBar->AddSlot()
        .AutoWidth()
        .Padding(4, 0, 0, 0)
        [
            SNew(SButton)
            .ToolTipText(FText::FromString(TEXT("Clear attachments")))
            .OnClicked(this, &SVFXAgentPanel::OnClearAttachmentsClicked)
            .ButtonStyle(&FAppStyle::Get().GetWidgetStyle<FButtonStyle>("SimpleButton"))
            [
                SNew(STextBlock)
                .Text(FText::FromString(TEXT("X")))
                .ColorAndOpacity(FLinearColor(1.0f, 0.4f, 0.4f))
            ]
        ];

    // Rebuild image preview area
    AttachmentPreviewBox->ClearChildren();
    bool bHasPreview = false;

    for (const FVFXChatAttachment& Att : Attachments)
    {
        if (Att.PreviewBrush.IsValid())
        {
            bHasPreview = true;
            AttachmentPreviewBox->AddSlot()
                .AutoHeight()
                .Padding(0, 0, 0, 4)
                [
                    SNew(SBorder)
                    .BorderImage(FCoreStyle::Get().GetBrush("GenericWhiteBox"))
                    .BorderBackgroundColor(FLinearColor(0.05f, 0.05f, 0.07f))
                    .Padding(4.0f)
                    [
                        SNew(SBox)
                        .WidthOverride(120)
                        .HeightOverride(120)
                        [
                            SNew(SImage)
                            .Image(Att.PreviewBrush.Get())
                        ]
                    ]
                ];
        }
    }

    AttachmentPreviewBox->SetVisibility(bHasPreview ? EVisibility::Visible : EVisibility::Collapsed);
}

void SVFXAgentPanel::UpdateStatusDisplay()
{
    if (StatusText.IsValid())
    {
        if (bRequestInFlight)
        {
            StatusText->SetText(FText::FromString(TEXT("Working...")));
            StatusText->SetColorAndOpacity(FLinearColor(1.0f, 0.8f, 0.2f));
        }
        else
        {
            StatusText->SetText(FText::FromString(TEXT("Ready")));
            StatusText->SetColorAndOpacity(FLinearColor(0.4f, 0.9f, 0.5f));
        }
    }
}
// ============================================================================
// LoadImagePreview - Create a Slate brush from an image file
// ============================================================================
TSharedPtr<FSlateDynamicImageBrush> SVFXAgentPanel::LoadImagePreview(const FString& FilePath, FVector2D PreviewSize)
{
    TArray<uint8> RawData;
    if (!FFileHelper::LoadFileToArray(RawData, *FilePath))
    {
        UE_LOG(LogVFXAgent, Warning, TEXT("LoadImagePreview: Failed to load file %s"), *FilePath);
        return nullptr;
    }

    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));

    EImageFormat DetectedFormat = ImageWrapperModule.DetectImageFormat(RawData.GetData(), RawData.Num());
    if (DetectedFormat == EImageFormat::Invalid)
    {
        UE_LOG(LogVFXAgent, Warning, TEXT("LoadImagePreview: Invalid image format for %s"), *FilePath);
        return nullptr;
    }

    TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(DetectedFormat);
    if (!ImageWrapper.IsValid() || !ImageWrapper->SetCompressed(RawData.GetData(), RawData.Num()))
    {
        return nullptr;
    }

    TArray<uint8> DecompressedData;
    if (!ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, DecompressedData))
    {
        return nullptr;
    }

    const int32 Width = ImageWrapper->GetWidth();
    const int32 Height = ImageWrapper->GetHeight();

    // Create a unique texture name
    FString TextureName = FString::Printf(TEXT("VFXAgentPreview_%s_%d"), *FPaths::GetBaseFilename(FilePath), FMath::Rand());

    TSharedPtr<FSlateDynamicImageBrush> Brush = FSlateDynamicImageBrush::CreateWithImageData(
        FName(*TextureName),
        FVector2D(Width, Height),
        DecompressedData);

    return Brush;
}

// ============================================================================
// Core AI Pipeline - Message processing & intent detection
// ============================================================================
void SVFXAgentPanel::ProcessUserMessage(const FString& Message)
{
    LastPrompt = Message;

    if (SelectedMode.IsValid() && SelectedMode->Equals(TEXT("Ask")))
    {
        ExecuteAsk(Message);
        return;
    }

    // Check if we have media attachments
    bool bHasMedia = false;
    FString MediaPath;
    for (const FVFXChatAttachment& Att : Attachments)
    {
        if (Att.Type == TEXT("image") || Att.Type == TEXT("gif") || Att.Type == TEXT("video"))
        {
            bHasMedia = true;
            MediaPath = Att.FilePath;
            break;
        }
    }

    // Detect intent
    if (InferIsDebugRequest(Message) && !ReferencedNiagaraSystemPath.IsEmpty())
    {
        ExecuteDebug(Message);
    }
    else if (InferIsModifyRequest(Message) && (!LastGeneratedSystemPath.IsEmpty() || !ReferencedNiagaraSystemPath.IsEmpty()))
    {
        ExecuteModify(Message);
    }
    else if (bHasMedia)
    {
        ExecuteGenerateFromMedia(Message);
    }
    else
    {
        ExecuteGenerate(Message);
    }
}

void SVFXAgentPanel::ExecuteAsk(const FString& Prompt)
{
    AddThinkingBubble();
    UpdateStatusDisplay();
    AddThinkingStep(TEXT("Asking AI..."));

    if (!LLMProviderObject || !LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
    {
        CompleteThinkingBubble(TEXT(""));
        AddErrorBubble(TEXT("Ask mode requires an HTTP LLM provider. Please configure one in Settings."));
        return;
    }

    UHttpLLMProvider* HttpProvider = static_cast<UHttpLLMProvider*>(LLMProviderObject);
    bRequestInFlight = true;
    UpdateStatusDisplay();

    HttpProvider->AskAsync(Prompt, [this](bool bSuccess, const FString& Response, const FString& Error)
    {
        bRequestInFlight = false;
        UpdateStatusDisplay();

        if (!bSuccess)
        {
            CompleteThinkingBubble(TEXT(""));
            AddErrorBubble(FString::Printf(TEXT("Ask failed: %s"), *Error));
            return;
        }

        CompleteThinkingBubble(TEXT(""));
        AddAgentBubble(Response);
    });
}

bool SVFXAgentPanel::InferIsModifyRequest(const FString& Prompt) const
{
    static const TArray<FString> ModifyKeywords = {
        TEXT("modify"), TEXT("change"), TEXT("adjust"), TEXT("tweak"), TEXT("update"),
        TEXT("make it"), TEXT("more"), TEXT("less"), TEXT("brighter"), TEXT("darker"),
        TEXT("faster"), TEXT("slower"), TEXT("bigger"), TEXT("smaller"),
        TEXT("add more"), TEXT("remove"), TEXT("reduce"),
        TEXT("refine"), TEXT("revise"), TEXT("improve"),
        TEXT("修改"), TEXT("调整"), TEXT("改"), TEXT("调"), TEXT("更"),
        TEXT("increase"), TEXT("decrease"),
    };
    for (const FString& Kw : ModifyKeywords)
    {
        if (Prompt.Contains(Kw, ESearchCase::IgnoreCase)) return true;
    }
    return false;
}

bool SVFXAgentPanel::InferIsDebugRequest(const FString& Prompt) const
{
    static const TArray<FString> DebugKeywords = {
        TEXT("debug"), TEXT("fix"), TEXT("bug"), TEXT("issue"), TEXT("problem"),
        TEXT("not working"), TEXT("broken"), TEXT("error"), TEXT("wrong"),
        TEXT("why"), TEXT("diagnose"), TEXT("analyze"), TEXT("inspect"),
        TEXT("问题"), TEXT("修复"), TEXT("错误"), TEXT("调试"), TEXT("检查"),
    };
    for (const FString& Kw : DebugKeywords)
    {
        if (Prompt.Contains(Kw, ESearchCase::IgnoreCase)) return true;
    }
    return false;
}

// ============================================================================
// Execute Generate - create new VFX from scratch
// ============================================================================
void SVFXAgentPanel::ExecuteGenerate(const FString& Prompt)
{
    AddThinkingBubble();
    UpdateStatusDisplay();

    const FString OutputPath = BuildDefaultOutputPath();
    const FString AssetName = BuildDefaultAssetName(Prompt);

    AddThinkingStep(TEXT("Analyzing prompt..."));

    const UVFXAgentSettings* Settings = GetDefault<UVFXAgentSettings>();
    const bool bUseV2 = Settings ? Settings->bUseV2Pipeline : true;

    if (bUseV2 && LLMProviderObject && LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
    {
        // V2 pipeline: multi-candidate
        AddThinkingStep(TEXT("Using V2 multi-candidate pipeline..."));

        UHttpLLMProvider* HttpProvider = static_cast<UHttpLLMProvider*>(LLMProviderObject);

        FMultiCandidateConfig Config;
        Config.NumCandidates = Settings ? Settings->V2NumCandidates : 3;
        Config.TargetScore = Settings ? Settings->V2TargetScore : 0.85f;
        Config.MinAcceptScore = Settings ? Settings->V2MinAcceptScore : 0.6f;
        Config.MaxRevisionPasses = Settings ? Settings->V2MaxRevisionPasses : 2;

        bRequestInFlight = true;
        UpdateStatusDisplay();

        FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Orchestrator, TEXT("V2 pipeline started"));

        FVFXMultiCandidatePipeline::RunAsync(HttpProvider, Prompt, Config,
            [this, OutputPath, AssetName, HttpProvider](const FMultiCandidatePipelineResult& Result)
            {
                bRequestInFlight = false;
                UpdateStatusDisplay();
                LastV2Result = Result;

                if (!Result.bSuccess)
                {
                    CompleteThinkingBubble(TEXT(""));

                    // Build detailed error from pipeline log and candidate issues
                    FString DetailedError = TEXT("Generation failed.");

                    // Collect unique errors from all candidates
                    TSet<FString> SeenErrors;
                    for (const FVFXCandidate& Cand : Result.AllCandidates)
                    {
                        for (const FString& Issue : Cand.Issues)
                        {
                            if (!SeenErrors.Contains(Issue))
                            {
                                SeenErrors.Add(Issue);
                            }
                        }
                    }

                    // Also extract key messages from pipeline log
                    for (const FString& LogLine : Result.PipelineLog)
                    {
                        if (LogLine.Contains(TEXT("failed"), ESearchCase::IgnoreCase) ||
                            LogLine.Contains(TEXT("error"), ESearchCase::IgnoreCase) ||
                            LogLine.Contains(TEXT("missing"), ESearchCase::IgnoreCase) ||
                            LogLine.Contains(TEXT("placeholder"), ESearchCase::IgnoreCase))
                        {
                            if (!SeenErrors.Contains(LogLine))
                            {
                                SeenErrors.Add(LogLine);
                            }
                        }
                    }

                    if (SeenErrors.Num() > 0)
                    {
                        DetailedError += TEXT("\n\nDetails:");
                        for (const FString& Err : SeenErrors)
                        {
                            DetailedError += TEXT("\n  - ") + Err;
                        }
                    }
                    else
                    {
                        DetailedError += TEXT(" No viable candidates were produced. Please try a different description.");
                    }

                    AddErrorBubble(DetailedError);
                    return;
                }

                LastEffectSpecV2Json = Result.SelectedCandidate.RawJson;

                AddThinkingStep(FString::Printf(TEXT("Generated %d candidates, selected best (score: %.2f)"),
                    Result.AllCandidates.Num(), Result.SelectedCandidate.Score));
                AddThinkingStep(TEXT("Building Niagara System from selected spec..."));

                // Build the selected spec via Python (Architecture V3)
                // We pass the selected spec JSON back to the LLM asking for a Python script,
                // then execute it with FVFXPythonExecutor — no C++ Niagara assembly.
                FEffectSpecV2 Parsed;
                FString ParseError;
                if (FEffectSpecV2Parser::ParseFromJson(Result.SelectedCandidate.RawJson, Parsed, ParseError))
                {
                    AddThinkingStep(TEXT("Requesting Python script from AI for selected spec..."));

                    // Build a contextual prompt that includes the scored spec
                    const FString PythonPrompt = FString::Printf(
                        TEXT("Using the following VFX effect specification as your creative brief, ")
                        TEXT("generate the Niagara System Python script.\n\n")
                        TEXT("Effect name: %s\n")
                        TEXT("Output path: /Game/VFXAgent/Generated/%s\n")
                        TEXT("Layers: %d\n")
                        TEXT("Quality score: %.0f%%\n\n")
                        TEXT("Spec summary:\n%s"),
                        *AssetName, *AssetName,
                        Parsed.Layers.Num(),
                        Result.SelectedCandidate.Score * 100.0f,
                        *Result.SelectedCandidate.RawJson.Left(1500));

                    bRequestInFlight = true;
                    UpdateStatusDisplay();

                    HttpProvider->RequestPythonScriptAsync(PythonPrompt,
                        [this, OutputPath, AssetName, ScorePct = Result.SelectedCandidate.Score * 100.0f, NumLayers = Parsed.Layers.Num()]
                        (bool bPySuccess, const FString& PythonCode, const FString& PyError)
                    {
                        bRequestInFlight = false;
                        UpdateStatusDisplay();

                        if (!bPySuccess || !PyError.IsEmpty())
                        {
                            CompleteThinkingBubble(TEXT(""));
                            AddErrorBubble(FString::Printf(TEXT("Python script request failed: %s"), *PyError));
                            return;
                        }

                        const FString CleanCode = FVFXPythonExecutor::SanitizeLLMPythonOutput(PythonCode);
                        if (CleanCode.IsEmpty())
                        {
                            CompleteThinkingBubble(TEXT(""));
                            AddErrorBubble(TEXT("LLM returned an empty Python script for the selected spec."));
                            return;
                        }

                        AddThinkingStep(TEXT("Executing Python script..."));
                        FString PyExecError;
                        const bool bExecSuccess = FVFXPythonExecutor::ExecutePythonScript(CleanCode, PyExecError);

                        if (bExecSuccess)
                        {
                            LastGeneratedSystemPath = FString::Printf(TEXT("/Game/VFXAgent/Generated/%s"), *AssetName);
                            FString Summary = FString::Printf(
                                TEXT("Successfully created Niagara System!\n\nAsset: %s\nLayers: %d\nScore: %.0f%%"),
                                *LastGeneratedSystemPath, NumLayers, ScorePct);
                            CompleteThinkingBubble(TEXT(""));
                            AddAssetLinkBubble(LastGeneratedSystemPath, Summary);
                            AddAgentBubble(TEXT("You can now modify this effect by describing changes, or reference another system to work with."));
                        }
                        else
                        {
                            CompleteThinkingBubble(TEXT(""));
                            AddErrorBubble(FString::Printf(
                                TEXT("Python script execution failed:\n%s"),
                                *PyExecError));
                        }
                    });
                }
                else
                {
                    CompleteThinkingBubble(TEXT(""));
                    AddErrorBubble(FString::Printf(TEXT("Spec parse failed: %s"), *ParseError));
                }
            });
    }
    else
    {
        // Standard recipe-based pipeline
        ExecuteRecipePipeline(Prompt, OutputPath, AssetName);
    }
}

// ============================================================================
// Execute Modify - modify existing VFX
// ============================================================================
void SVFXAgentPanel::ExecuteModify(const FString& Prompt)
{
    AddThinkingBubble();
    UpdateStatusDisplay();
    AddThinkingStep(TEXT("Analyzing modification request..."));

    if (LastRecipe.Emitters.Num() == 0 && ReferencedNiagaraSystemPath.IsEmpty())
    {
        CompleteThinkingBubble(TEXT(""));
        AddErrorBubble(TEXT("No previous generation or referenced system to modify. Please generate a VFX first or reference an existing Niagara System."));
        return;
    }

    if (!LLMProviderObject || !LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
    {
        CompleteThinkingBubble(TEXT(""));
        AddErrorBubble(TEXT("Modification requires an HTTP LLM provider. Please configure one in Settings."));
        return;
    }

    UHttpLLMProvider* HttpProvider = static_cast<UHttpLLMProvider*>(LLMProviderObject);
    bRequestInFlight = true;
    UpdateStatusDisplay();

    AddThinkingStep(TEXT("Sending refinement request to AI..."));

    HttpProvider->RefineRecipeAsync(LastRecipe, Prompt, [this](const FVFXRecipe& NewRecipe, const FString& Error)
    {
        bRequestInFlight = false;
        UpdateStatusDisplay();

        if (!Error.IsEmpty())
        {
            CompleteThinkingBubble(TEXT(""));
            AddErrorBubble(FString::Printf(TEXT("Modification failed: %s"), *Error));
            return;
        }

        UpdateLastRecipe(NewRecipe);

        AddThinkingStep(TEXT("Recipe updated, rebuilding Niagara System..."));

        UNiagaraSystemGenerator* Generator = NewObject<UNiagaraSystemGenerator>(GetTransientPackage(), NAME_None, RF_Transient);
        if (Generator)
        {
            const UVFXAgentSettings* Settings = GetDefault<UVFXAgentSettings>();
            const bool bDisallowTemplates = Settings ? Settings->bDisallowTemplates : true;
            const bool bUseTemplates = !bDisallowTemplates && Settings && Settings->bUseTemplates;
            const FString TemplatePath = (Settings && bUseTemplates) ? Settings->DefaultTemplatePath : FString();

            FVFXRecipe FinalRecipe = NewRecipe;
            if (!bUseTemplates)
            {
                for (FVFXEmitterRecipe& Emitter : FinalRecipe.Emitters)
                {
                    Emitter.TemplateName.Empty();
                }
            }

            UNiagaraSystem* ExistingSystem = nullptr;
            if (!ReferencedNiagaraSystemPath.IsEmpty())
            {
                ExistingSystem = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), nullptr, *ReferencedNiagaraSystemPath));
            }
            else if (!LastGeneratedSystemPath.IsEmpty())
            {
                ExistingSystem = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), nullptr, *LastGeneratedSystemPath));
            }

            if (ExistingSystem)
            {
                // Modify existing system with Undo support
                GEditor->BeginTransaction(FText::FromString(TEXT("VFX Agent Modification")));
                ExistingSystem->Modify();

                bool bSuccess = Generator->UpdateNiagaraSystem(ExistingSystem, FinalRecipe);
                
                if (bSuccess)
                {
                    ExistingSystem->RequestCompile(true);
                    ExistingSystem->WaitForCompilationComplete(true, true);
                    ExistingSystem->PostEditChange();

                    GEditor->EndTransaction();
                    CompleteThinkingBubble(TEXT(""));
                    AddAssetLinkBubble(ExistingSystem->GetPathName(),
                        FString::Printf(TEXT("Modified existing effect successfully!\n\nAsset: %s\nEmitters: %d"),
                        *ExistingSystem->GetPathName(), FinalRecipe.Emitters.Num()));
                }
                else
                {
                    GEditor->CancelTransaction(0);
                    CompleteThinkingBubble(TEXT(""));
                    AddErrorBubble(TEXT("Failed to update the existing Niagara System."));
                }
            }
            else
            {
                // Generate new system
                const FString OutputPath = BuildDefaultOutputPath();
                const FString AssetName = BuildDefaultAssetName(LastPrompt);

                UNiagaraSystem* System = Generator->GenerateNiagaraSystem(AssetName, OutputPath, FinalRecipe, TemplatePath);
                if (System)
                {
                    LastGeneratedSystemPath = OutputPath / AssetName;
                    CompleteThinkingBubble(TEXT(""));
                    AddAssetLinkBubble(LastGeneratedSystemPath,
                        FString::Printf(TEXT("Modified effect rebuilt successfully!\n\nAsset: %s\nEmitters: %d"),
                        *LastGeneratedSystemPath, FinalRecipe.Emitters.Num()));
                }
                else
                {
                    CompleteThinkingBubble(TEXT(""));
                    AddErrorBubble(TEXT("Failed to rebuild the Niagara System after modification."));
                }
            }
        }
        else
        {
            CompleteThinkingBubble(TEXT(""));
            AddErrorBubble(TEXT("Failed to create NiagaraSystemGenerator."));
        }
    });
}

// ============================================================================
// Execute Debug - analyze and suggest fixes for existing VFX
// ============================================================================
void SVFXAgentPanel::ExecuteDebug(const FString& Prompt)
{
    AddThinkingBubble();
    UpdateStatusDisplay();
    AddThinkingStep(TEXT("Analyzing problem description..."));

    if (ReferencedNiagaraSystemPath.IsEmpty() && LastGeneratedSystemPath.IsEmpty())
    {
        CompleteThinkingBubble(TEXT(""));
        AddErrorBubble(TEXT("Please reference a Niagara System first (use the NS button) so I can analyze it."));
        return;
    }

    if (!LLMProviderObject || !LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
    {
        CompleteThinkingBubble(TEXT(""));
        AddErrorBubble(TEXT("Debug mode requires an HTTP LLM provider. Please configure one in Settings."));
        return;
    }

    const FString SystemPath = !ReferencedNiagaraSystemPath.IsEmpty() ? ReferencedNiagaraSystemPath : LastGeneratedSystemPath;
    AddThinkingStep(FString::Printf(TEXT("Inspecting system: %s"), *SystemPath));

    // Load the system to get basic info
    UNiagaraSystem* System = LoadObject<UNiagaraSystem>(nullptr, *SystemPath);
    FString SystemInfo;
    if (System)
    {
        SystemInfo = FString::Printf(TEXT("System: %s\nEmitters: %d"),
            *System->GetName(), System->GetNumEmitters());
        AddThinkingStep(FString::Printf(TEXT("Found system with %d emitters"), System->GetNumEmitters()));
    }
    else
    {
        SystemInfo = TEXT("Could not load the referenced system.");
        AddThinkingStep(TEXT("Warning: Could not load referenced system"));
    }

    // Ask the LLM for debugging assistance
    UHttpLLMProvider* HttpProvider = static_cast<UHttpLLMProvider*>(LLMProviderObject);
    bRequestInFlight = true;
    UpdateStatusDisplay();

    FString DebugPrompt = FString::Printf(
        TEXT("The user has a Niagara VFX system and needs debugging help.\n\n")
        TEXT("System Info:\n%s\n\n")
        TEXT("User's Problem Description:\n%s\n\n")
        TEXT("Please analyze the problem and provide:\n")
        TEXT("1. Likely causes\n")
        TEXT("2. Suggested fixes (be specific about Niagara modules and parameters)\n")
        TEXT("3. Step-by-step resolution approach"),
        *SystemInfo, *Prompt);

    AddThinkingStep(TEXT("Consulting AI for diagnosis..."));

    HttpProvider->RequestDirectorJsonInternalAsync(DebugPrompt, TEXT("You are an expert Niagara VFX debugging assistant. Provide clear diagnostic analysis and fix suggestions. Respond in plain text, not JSON."),
        [this](bool bSuccess, const FString& Response, const FString& Error)
        {
            bRequestInFlight = false;
            UpdateStatusDisplay();

            if (!bSuccess)
            {
                CompleteThinkingBubble(TEXT(""));
                AddErrorBubble(FString::Printf(TEXT("Debug analysis failed: %s"), *Error));
                return;
            }

            CompleteThinkingBubble(TEXT("Analysis complete."));
            AddAgentBubble(Response);
            AddAgentBubble(TEXT("Would you like me to apply any of these fixes? If so, describe which fix to apply."));
        });
}

// ============================================================================
// Execute from media (image/gif/video reference)
// ============================================================================
void SVFXAgentPanel::ExecuteGenerateFromMedia(const FString& Prompt)
{
    AddThinkingBubble();
    UpdateStatusDisplay();

    FString MediaPath;
    for (const FVFXChatAttachment& Att : Attachments)
    {
        if (Att.Type == TEXT("image") || Att.Type == TEXT("gif") || Att.Type == TEXT("video"))
        {
            MediaPath = Att.FilePath;
            break;
        }
    }

    if (MediaPath.IsEmpty())
    {
        CompleteThinkingBubble(TEXT(""));
        AddErrorBubble(TEXT("No media file attached."));
        return;
    }

    if (!LLMProviderObject || !LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
    {
        CompleteThinkingBubble(TEXT(""));
        AddErrorBubble(TEXT("Image-based generation requires an HTTP LLM provider. Please configure one in Settings."));
        return;
    }

    AddThinkingStep(FString::Printf(TEXT("Analyzing reference media: %s"), *FPaths::GetCleanFilename(MediaPath)));

    UHttpLLMProvider* HttpProvider = static_cast<UHttpLLMProvider*>(LLMProviderObject);
    const FString OutputPath = BuildDefaultOutputPath();
    const FString AssetName = BuildDefaultAssetName(Prompt.IsEmpty() ? TEXT("MediaRef") : Prompt);

    bRequestInFlight = true;
    UpdateStatusDisplay();

    AddThinkingStep(TEXT("Sending to AI for visual analysis..."));
    FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::LLM, TEXT("Generating recipe from media..."), CachedLLMBackend);

    HttpProvider->GenerateRecipeFromImageAsync(MediaPath, Prompt, [this, OutputPath, AssetName](const FVFXRecipe& Recipe, const FString& Error)
    {
        if (!Error.IsEmpty())
        {
            bRequestInFlight = false;
            UpdateStatusDisplay();
            CompleteThinkingBubble(TEXT(""));
            AddErrorBubble(FString::Printf(TEXT("Media analysis failed: %s"), *Error));
            return;
        }

        AddThinkingStep(FString::Printf(TEXT("Generated recipe with %d emitters from visual analysis"), Recipe.Emitters.Num()));

        FVFXRecipe EnhancedRecipe = EnhanceRecipeForPrompt(Recipe, LastPrompt);
        LastRecipe = EnhancedRecipe;

        if (EnhancedRecipe.Emitters.Num() == 0)
        {
            bRequestInFlight = false;
            UpdateStatusDisplay();
            CompleteThinkingBubble(TEXT(""));
            AddErrorBubble(TEXT("AI could not generate emitters from the reference media. Try adding a text description."));
            return;
        }

        AddThinkingStep(TEXT("Building Niagara System..."));

        UNiagaraSystemGenerator* Generator = NewObject<UNiagaraSystemGenerator>(GetTransientPackage(), NAME_None, RF_Transient);
        if (!Generator)
        {
            bRequestInFlight = false;
            UpdateStatusDisplay();
            CompleteThinkingBubble(TEXT(""));
            AddErrorBubble(TEXT("Failed to create NiagaraSystemGenerator."));
            return;
        }

        const UVFXAgentSettings* Settings = GetDefault<UVFXAgentSettings>();
        const bool bDisallowTemplates = Settings ? Settings->bDisallowTemplates : true;
        const bool bUseTemplates = !bDisallowTemplates && Settings && Settings->bUseTemplates;
        const FString TemplatePath = (Settings && bUseTemplates) ? Settings->DefaultTemplatePath : FString();

        FVFXRecipe FinalRecipe = EnhancedRecipe;
        if (!bUseTemplates)
        {
            for (FVFXEmitterRecipe& Emitter : FinalRecipe.Emitters)
            {
                Emitter.TemplateName.Empty();
            }
        }

        UNiagaraSystem* System = Generator->GenerateNiagaraSystem(AssetName, OutputPath, FinalRecipe, TemplatePath);
        bRequestInFlight = false;
        UpdateStatusDisplay();

        if (System)
        {
            LastGeneratedSystemPath = OutputPath / AssetName;
            CompleteThinkingBubble(TEXT(""));
            AddAssetLinkBubble(LastGeneratedSystemPath,
                FString::Printf(TEXT("Generated VFX from reference media!\n\nAsset: %s\nEmitters: %d"),
                    *LastGeneratedSystemPath, FinalRecipe.Emitters.Num()));
        }
        else
        {
            CompleteThinkingBubble(TEXT(""));
            AddErrorBubble(TEXT("Failed to generate Niagara System from media analysis."));
        }
    });
}
// ============================================================================
// Recipe pipeline (standard, non-V2)
// ============================================================================
void SVFXAgentPanel::ExecuteRecipePipeline(const FString& Prompt, const FString& OutputPath, const FString& AssetName)
{
    if (!LLMProvider)
    {
        CompleteThinkingBubble(TEXT(""));
        AddErrorBubble(TEXT("LLM Provider not initialized. Please configure one in Settings."));
        return;
    }

    bRequestInFlight = true;
    UpdateStatusDisplay();
    AddThinkingStep(TEXT("Generating VFX recipe from AI..."));
    FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::LLM, TEXT("Generating Recipe..."), CachedLLMBackend);

    if (LLMProviderObject && LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
    {
        // ----------------------------------------------------------------
        // VFXAgent Architecture V3: Python-First Generation
        // The LLM returns a raw UE5 Python script; we execute it directly
        // via FVFXPythonExecutor instead of parsing a JSON recipe.
        // ----------------------------------------------------------------
        UHttpLLMProvider* HttpProvider = static_cast<UHttpLLMProvider*>(LLMProviderObject);
        HttpProvider->RequestPythonScriptAsync(Prompt,
            [this, Prompt, AssetName, OutputPath](bool bSuccess, const FString& PythonCode, const FString& Error)
        {
            if (!bSuccess || !Error.IsEmpty())
            {
                bRequestInFlight = false;
                UpdateStatusDisplay();
                CompleteThinkingBubble(TEXT(""));
                AddErrorBubble(FString::Printf(TEXT("LLM request failed: %s"), *Error));
                return;
            }

            AddThinkingStep(TEXT("LLM returned Python script. Executing..."));
            FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara, TEXT("Executing LLM Python script..."), CachedLLMBackend);

            // Sanitize: strip markdown fences the LLM may have added
            const FString CleanCode = FVFXPythonExecutor::SanitizeLLMPythonOutput(PythonCode);

            if (CleanCode.IsEmpty())
            {
                bRequestInFlight = false;
                UpdateStatusDisplay();
                CompleteThinkingBubble(TEXT(""));
                AddErrorBubble(TEXT("LLM returned an empty Python script. Try a more descriptive prompt."));
                return;
            }

            // Execute the Python script — this creates the Niagara asset in-engine
            FString PyExecError;
            const bool bExecSuccess = FVFXPythonExecutor::ExecutePythonScript(CleanCode, PyExecError);
            bRequestInFlight = false;
            UpdateStatusDisplay();

            if (bExecSuccess)
            {
                LastGeneratedSystemPath = FString::Printf(TEXT("/Game/VFXAgent/Generated/%s"), *AssetName);
                FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara, TEXT("Python script executed — VFX asset created."));
                CompleteThinkingBubble(TEXT(""));
                AddAssetLinkBubble(LastGeneratedSystemPath,
                    FString::Printf(TEXT("VFX generation complete!\n\nThe Python script ran successfully.\nCheck /Game/VFXAgent/Generated/ for the new Niagara System asset.\n\nGenerated for: %s"), *Prompt));
                AddAgentBubble(TEXT("You can describe changes to refine this effect, or start a new generation."));
            }
            else
            {
                FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::Niagara, TEXT("Python script execution failed."));
                CompleteThinkingBubble(TEXT(""));
                AddErrorBubble(FString::Printf(
                    TEXT("Python script execution failed:\n%s"),
                    *PyExecError));
            }
        });
    }
    else
    {
        // Synchronous fallback (mock provider)
        FVFXRecipe Recipe = LLMProvider->GenerateRecipe(Prompt);
        FVFXRecipe EnhancedRecipe = EnhanceRecipeForPrompt(Recipe, Prompt);
        LastRecipe = EnhancedRecipe;

        if (EnhancedRecipe.Emitters.Num() == 0)
        {
            bRequestInFlight = false;
            UpdateStatusDisplay();
            CompleteThinkingBubble(TEXT(""));
            AddErrorBubble(TEXT("Mock LLM returned no emitters."));
            return;
        }

        AddThinkingStep(FString::Printf(TEXT("Recipe generated (mock): %d emitters"), EnhancedRecipe.Emitters.Num()));

        UNiagaraSystemGenerator* Generator = NewObject<UNiagaraSystemGenerator>(GetTransientPackage(), NAME_None, RF_Transient);
        if (Generator)
        {
            const UVFXAgentSettings* Settings = GetDefault<UVFXAgentSettings>();
            const bool bDisallowTemplates = Settings ? Settings->bDisallowTemplates : true;
            const bool bUseTemplates = !bDisallowTemplates && Settings && Settings->bUseTemplates;
            const FString TemplatePath = (Settings && bUseTemplates) ? Settings->DefaultTemplatePath : FString();

            FVFXRecipe FinalRecipe = EnhancedRecipe;
            if (!bUseTemplates)
            {
                for (FVFXEmitterRecipe& Emitter : FinalRecipe.Emitters)
                {
                    Emitter.TemplateName.Empty();
                }
            }

            UNiagaraSystem* System = Generator->GenerateNiagaraSystem(AssetName, OutputPath, FinalRecipe, TemplatePath);
            bRequestInFlight = false;
            UpdateStatusDisplay();

            if (System)
            {
                LastGeneratedSystemPath = OutputPath / AssetName;
                CompleteThinkingBubble(TEXT(""));
                AddAssetLinkBubble(LastGeneratedSystemPath,
                    FString::Printf(TEXT("Generated Niagara System (mock)!\n\nAsset: %s\nEmitters: %d"),
                        *LastGeneratedSystemPath, FinalRecipe.Emitters.Num()));
            }
            else
            {
                CompleteThinkingBubble(TEXT(""));
                AddErrorBubble(TEXT("Failed to generate Niagara System."));
            }
        }
        else
        {
            bRequestInFlight = false;
            UpdateStatusDisplay();
            CompleteThinkingBubble(TEXT(""));
            AddErrorBubble(TEXT("Failed to create NiagaraSystemGenerator."));
        }
    }
}

// ============================================================================
// Director pipeline
// ============================================================================
void SVFXAgentPanel::ExecuteDirectorPipeline(const FString& Prompt, const FString& OutputPath, const FString& AssetName)
{
    if (!LLMProviderObject || !LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
    {
        CompleteThinkingBubble(TEXT(""));
        AddErrorBubble(TEXT("Director pipeline requires HttpLLMProvider."));
        return;
    }

    UHttpLLMProvider* HttpProvider = static_cast<UHttpLLMProvider*>(LLMProviderObject);
    bRequestInFlight = true;
    UpdateStatusDisplay();

    AddThinkingStep(TEXT("Requesting Director plan from AI..."));
    FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::LLM, TEXT("Generating Director JSON..."), CachedLLMBackend);

    HttpProvider->RequestDirectorJsonAsync(Prompt, FString(), [this, OutputPath](bool bSuccess, const FString& DirectorJson, const FString& Error)
    {
        if (!bSuccess)
        {
            bRequestInFlight = false;
            UpdateStatusDisplay();
            CompleteThinkingBubble(TEXT(""));
            AddErrorBubble(FString::Printf(TEXT("Director plan failed: %s"), *Error));
            return;
        }

        LastDirectorJson = DirectorJson;
        FVFXDirectorPlan Plan;
        FString ParseError;
        if (!FVFXDirectorJson::ParseDirectorJson(DirectorJson, Plan, ParseError))
        {
            bRequestInFlight = false;
            UpdateStatusDisplay();
            CompleteThinkingBubble(TEXT(""));
            AddErrorBubble(FString::Printf(TEXT("Director JSON parse failed: %s"), *ParseError));
            return;
        }

        AddThinkingStep(FString::Printf(TEXT("Plan: %d actions to execute"), Plan.Actions.Num()));
        AddThinkingStep(TEXT("Executing Director actions..."));

        FVFXNiagaraActionExecutor Executor;
        FVFXActionContext Context;
        Context.DefaultOutputPath = OutputPath;
        LastExecutionReport = FVFXExecutionReport();
        Context.Report = &LastExecutionReport;

        Executor.ExecuteActionList(Plan.Actions, Context);

        bRequestInFlight = false;
        UpdateStatusDisplay();

        if (LastExecutionReport.bSuccess)
        {
            FString Summary = TEXT("Director pipeline completed successfully!");
            if (LastExecutionReport.GeneratedAssets.Num() > 0)
            {
                LastGeneratedSystemPath = LastExecutionReport.GeneratedAssets[0];
                Summary += FString::Printf(TEXT("\n\nGenerated: %s"), *LastGeneratedSystemPath);
            }
            CompleteThinkingBubble(TEXT(""));
            if (!LastGeneratedSystemPath.IsEmpty())
            {
                AddAssetLinkBubble(LastGeneratedSystemPath, Summary);
            }
            else
            {
                AddAgentBubble(Summary);
            }
        }
        else
        {
            FString ErrorSummary = TEXT("Director execution encountered issues:");
            for (const FString& Err : LastExecutionReport.Errors)
            {
                ErrorSummary += TEXT("\n  - ") + Err;
            }
            CompleteThinkingBubble(TEXT(""));
            AddErrorBubble(ErrorSummary);
        }
    });
}
// ============================================================================
// AgentTextRequest - public API entry point
// ============================================================================
void SVFXAgentPanel::AgentTextRequest(const FString& Action, const FString& Prompt)
{
    if (Action.Equals(TEXT("generate"), ESearchCase::IgnoreCase))
    {
        ExecuteGenerate(Prompt);
    }
    else if (Action.Equals(TEXT("modify"), ESearchCase::IgnoreCase) || Action.Equals(TEXT("refine"), ESearchCase::IgnoreCase))
    {
        ExecuteModify(Prompt);
    }
    else if (Action.Equals(TEXT("debug"), ESearchCase::IgnoreCase))
    {
        ExecuteDebug(Prompt);
    }
    else if (Action.Equals(TEXT("plan"), ESearchCase::IgnoreCase))
    {
        AddThinkingBubble();
        ExecuteDirectorPipeline(Prompt, BuildDefaultOutputPath(), BuildDefaultAssetName(Prompt));
    }
    else
    {
        // Default to generate
        ExecuteGenerate(Prompt);
    }
}

// ============================================================================
// Tick - drain pipeline log
// ============================================================================
void SVFXAgentPanel::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
    DrainPipelineLog();
}

void SVFXAgentPanel::DrainPipelineLog()
{
    TArray<FPipelineLogEntry> Entries;
    FPipelineLog::Get().Drain(Entries);
    if (Entries.Num() == 0) return;

    for (const FPipelineLogEntry& Entry : Entries)
    {
        // Feed steps into current thinking bubble
        if (CurrentThinkingBubble.IsValid() && Entry.Level != EPipelineLogLevel::Error)
        {
            FString StepText = FString::Printf(TEXT("[%s] %s"),
                *PipelineStageToString(Entry.Stage),
                *Entry.Message);
            CurrentThinkingBubble->AddStep(StepText);
        }

        // Also maintain log lines
        const FString TimeStr = Entry.Timestamp.ToString(TEXT("%H:%M:%S"));
        const FString Level = Entry.Level == EPipelineLogLevel::Error ? TEXT("Error") :
            Entry.Level == EPipelineLogLevel::Warning ? TEXT("Warn") : TEXT("Info");
        const FString Stage = PipelineStageToString(Entry.Stage);
        FString Provider = Entry.Provider.IsEmpty() ? TEXT("") : FString::Printf(TEXT("[%s]"), *Entry.Provider);
        FString Progress;
        if (Entry.TotalSteps > 0)
        {
            Progress = FString::Printf(TEXT("[%d/%d %.0f%%] "), Entry.CurrentStep, Entry.TotalSteps, Entry.Percent * 100.0f);
        }
        PipelineLogLines.Add(FString::Printf(TEXT("[%s][%s][%s]%s %s%s"),
            *TimeStr, *Stage, *Level, *Provider, *Progress, *Entry.Message));
    }

    while (PipelineLogLines.Num() > PipelineLogMaxLines)
    {
        PipelineLogLines.RemoveAt(0);
    }
}

// ============================================================================
// Helpers
// ============================================================================
void SVFXAgentPanel::LogMessage(const FString& Message)
{
    UE_LOG(LogVFXAgent, Log, TEXT("%s"), *Message);
}

void SVFXAgentPanel::UpdateLastRecipe(const FVFXRecipe& Recipe)
{
    LastRecipe = Recipe;
}

FString SVFXAgentPanel::GetModelDisplayName() const
{
    if (CachedLLMBackend.IsEmpty() || CachedLLMBackend.Equals(TEXT("Mock"), ESearchCase::IgnoreCase))
    {
        return TEXT("Mock Provider");
    }
    FString Display = CachedLLMBackend;
    if (!CachedLLMModel.IsEmpty())
    {
        Display += TEXT(" | ") + CachedLLMModel;
    }
    return Display;
}

FString SVFXAgentPanel::SanitizeAssetName(const FString& Name) const
{
    FString Safe = Name;
    if (Safe.IsEmpty()) Safe = TEXT("VFX_Generated");

    for (int32 i = 0; i < Safe.Len(); ++i)
    {
        TCHAR& C = Safe[i];
        if (!(FChar::IsAlnum(C) || C == TCHAR('_')))
        {
            C = TCHAR('_');
        }
    }
    return Safe;
}

FString SVFXAgentPanel::SanitizeOutputPath(const FString& Path) const
{
    FString Safe = Path.TrimStartAndEnd();
    if (Safe.IsEmpty()) return TEXT("/Game/VFXAgent/Generated");

    if (!Safe.StartsWith(TEXT("/Game")))
    {
        FString FullSelected = FPaths::ConvertRelativePathToFull(Safe);
        FString ContentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
        if (FullSelected.StartsWith(ContentDir))
        {
            FString Relative = FullSelected.Mid(ContentDir.Len());
            Relative = Relative.Replace(TEXT("\\"), TEXT("/")).TrimStartAndEnd();
            Safe = FString::Printf(TEXT("/Game/%s"), *Relative);
            if (Safe.EndsWith(TEXT("/"))) Safe.LeftChopInline(1);
        }
    }
    return Safe;
}

FString SVFXAgentPanel::BuildDefaultOutputPath() const
{
    const UVFXAgentSettings* Settings = GetDefault<UVFXAgentSettings>();
    return Settings ? Settings->DefaultOutputPath : TEXT("/Game/VFXAgent/Generated");
}

FString SVFXAgentPanel::BuildDefaultAssetName(const FString& Prompt) const
{
    const UVFXAgentSettings* Settings = GetDefault<UVFXAgentSettings>();
    FString Prefix = Settings ? Settings->AssetNamePrefix : TEXT("VFX_");

    // Generate a name from prompt
    FString Base = Prompt.Left(20);
    Base = Base.Replace(TEXT(" "), TEXT("_"));
    Base = SanitizeAssetName(Base);

    if (Base.IsEmpty()) Base = TEXT("Generated");

    return Prefix + Base + FString::Printf(TEXT("_%d"), GenerationCounter++);
}

void SVFXAgentPanel::RefreshLLMSettingsFromConfig()
{
    const UVFXAgentSettings* Settings = GetDefault<UVFXAgentSettings>();
    CachedLLMEndpoint = Settings ? Settings->LLMEndpoint : TEXT("");
    CachedLLMModel = Settings ? Settings->LLMModel : TEXT("");
    CachedLLMBackend = Settings ? Settings->LLMBackend : TEXT("Mock");
    CachedLLMTimeoutSeconds = Settings ? Settings->LLMTimeoutSeconds : 30.0f;
    bCachedHasApiKey = Settings && !Settings->LLMApiKey.IsEmpty();

    const bool bUseOpenAI =
        CachedLLMBackend.Equals(TEXT("OpenAI"), ESearchCase::IgnoreCase) ||
        CachedLLMBackend.Equals(TEXT("ChatGPT"), ESearchCase::IgnoreCase) ||
        CachedLLMBackend.Equals(TEXT("GPT5o"), ESearchCase::IgnoreCase) ||
        CachedLLMBackend.Equals(TEXT("GPT-5o"), ESearchCase::IgnoreCase) ||
        CachedLLMBackend.Equals(TEXT("OpenAIChatCompletions"), ESearchCase::IgnoreCase) ||
        CachedLLMBackend.Equals(TEXT("OpenAIResponses"), ESearchCase::IgnoreCase);
    const bool bUseOllama = CachedLLMBackend.Equals(TEXT("Ollama"), ESearchCase::IgnoreCase);

    // Only use Responses API if the backend string explicitly says so,
    // OR if the endpoint URL is already /v1/responses.
    // GPT-5o works fine with Chat Completions API — no auto-switch.
    const bool bExplicitResponsesAPI =
        CachedLLMBackend.Equals(TEXT("OpenAIResponses"), ESearchCase::IgnoreCase) ||
        CachedLLMEndpoint.Contains(TEXT("/v1/responses"));

    if (bUseOpenAI || bUseOllama)
    {
        UHttpLLMProvider* ProviderObj = (LLMProviderObject && LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
            ? static_cast<UHttpLLMProvider*>(LLMProviderObject)
            : nullptr;
        if (!ProviderObj)
        {
            ProviderObj = NewObject<UHttpLLMProvider>(GetTransientPackage());
            if (ProviderObj)
            {
                ProviderObj->AddToRoot();
                LLMProviderObject = ProviderObj;
                LLMProvider = ProviderObj;
            }
        }

        if (ProviderObj)
        {
            EVFXAgentLLMBackend Backend;
            if (bUseOllama)
            {
                Backend = EVFXAgentLLMBackend::OllamaGenerate;
            }
            else if (bExplicitResponsesAPI)
            {
                // Only use Responses API if explicitly configured
                Backend = EVFXAgentLLMBackend::OpenAIResponses;
            }
            else
            {
                Backend = EVFXAgentLLMBackend::OpenAIChatCompletions;
            }

            // Use endpoint as configured; no auto-switching
            FString FinalEndpoint = CachedLLMEndpoint;
            if (FinalEndpoint.IsEmpty())
            {
                FinalEndpoint = TEXT("https://api.openai.com/v1/chat/completions");
            }
            ProviderObj->Configure(
                Backend,
                FinalEndpoint,
                CachedLLMModel,
                Settings ? Settings->LLMApiKey : TEXT(""),
                CachedLLMTimeoutSeconds);
        }
    }
    else
    {
        const bool bHasMock = LLMProviderObject && LLMProviderObject->IsA(UMockLLMProvider::StaticClass());
        if (!LLMProvider || !bHasMock)
        {
            UMockLLMProvider* ProviderObj = NewObject<UMockLLMProvider>(GetTransientPackage());
            if (ProviderObj)
            {
                ProviderObj->AddToRoot();
                LLMProviderObject = ProviderObj;
                LLMProvider = ProviderObj;
            }
        }
    }

    // Update model display
    if (ModelInfoText.IsValid())
    {
        ModelInfoText->SetText(FText::FromString(GetModelDisplayName()));
    }
}

// ============================================================================
// EnhanceRecipeForPrompt (preserved from original)
// ============================================================================
static bool PromptHasAny(const FString& Prompt, const TArray<FString>& Tokens)
{
    for (const FString& Token : Tokens)
    {
        if (Prompt.Contains(Token, ESearchCase::IgnoreCase)) return true;
    }
    return false;
}

static bool HasEmitterNamed(const FVFXRecipe& Recipe, const FString& Name)
{
    for (const FVFXEmitterRecipe& E : Recipe.Emitters)
    {
        if (E.Name.Equals(Name, ESearchCase::IgnoreCase)) return true;
    }
    return false;
}

FVFXRecipe SVFXAgentPanel::EnhanceRecipeForPrompt(const FVFXRecipe& Recipe, const FString& Prompt)
{
    FVFXRecipe Out = Recipe;

    const bool bExplosion = PromptHasAny(Prompt, { TEXT("explosion"), TEXT("blast"), TEXT("explode"), TEXT("detonate") });
    const bool bElectric = PromptHasAny(Prompt, { TEXT("electric"), TEXT("lightning"), TEXT("thunder"), TEXT("spark") });
    const bool bSmoke = PromptHasAny(Prompt, { TEXT("smoke"), TEXT("fog"), TEXT("mist") });

    if (!(bExplosion && bElectric)) return Out;

    Out.bLoop = false;
    if (Out.Duration <= 0.01f) Out.Duration = 2.5f;
    Out.Bounds = FVector(250.0f, 250.0f, 250.0f);

    if (Out.Emitters.Num() < 4)
    {
        if (!HasEmitterNamed(Out, TEXT("CoreBurst")))
        {
            FVFXEmitterRecipe Core;
            Core.Name = TEXT("CoreBurst");
            Core.RendererType = TEXT("Sprite");
            Core.BurstCount = 220;
            Core.Color = FLinearColor(0.9f, 0.95f, 1.0f, 1.0f);
            Core.ColorEnd = FLinearColor(0.0f, 0.5f, 1.0f, 0.0f);
            Core.bUseColorGradient = true;
            Core.Lifetime = 0.4f;
            Core.Size = 22.0f;
            Core.SizeEnd = 85.0f;
            Core.bUseSizeOverLife = true;
            Core.Velocity = FVector(0, 0, 180);
            Core.Drag = 2.0f;
            Core.Acceleration = FVector(0, 0, -200);
            Core.bUseGravity = false;
            Core.SortOrder = 3;
            Out.Emitters.Add(Core);
        }

        if (!HasEmitterNamed(Out, TEXT("ArcRibbons")))
        {
            FVFXEmitterRecipe Arc;
            Arc.Name = TEXT("ArcRibbons");
            Arc.RendererType = TEXT("Ribbon");
            Arc.SpawnRate = 30.0f;
            Arc.Color = FLinearColor(0.2f, 0.6f, 1.0f, 1.0f);
            Arc.ColorEnd = FLinearColor(0.9f, 0.95f, 1.0f, 1.0f);
            Arc.bUseColorGradient = true;
            Arc.Lifetime = 0.9f;
            Arc.Size = 6.0f;
            Arc.SizeEnd = 10.0f;
            Arc.bUseSizeOverLife = true;
            Arc.Velocity = FVector(0, 0, 120);
            Arc.Drag = 1.5f;
            Arc.SortOrder = 4;
            Out.Emitters.Add(Arc);
        }

        if (!HasEmitterNamed(Out, TEXT("Sparks")))
        {
            FVFXEmitterRecipe Sparks;
            Sparks.Name = TEXT("Sparks");
            Sparks.RendererType = TEXT("Sprite");
            Sparks.SpawnRate = 140.0f;
            Sparks.Color = FLinearColor(0.7f, 0.85f, 1.0f, 1.0f);
            Sparks.ColorEnd = FLinearColor(0.2f, 0.6f, 1.0f, 0.0f);
            Sparks.bUseColorGradient = true;
            Sparks.Lifetime = 0.9f;
            Sparks.Size = 4.0f;
            Sparks.SizeEnd = 2.0f;
            Sparks.bUseSizeOverLife = true;
            Sparks.Velocity = FVector(0, 0, 420);
            Sparks.Acceleration = FVector(0, 0, -520);
            Sparks.bUseGravity = true;
            Sparks.Drag = 0.6f;
            Sparks.SortOrder = 2;
            Out.Emitters.Add(Sparks);
        }

        if (bSmoke && !HasEmitterNamed(Out, TEXT("SmokeTrails")))
        {
            FVFXEmitterRecipe Smoke;
            Smoke.Name = TEXT("SmokeTrails");
            Smoke.RendererType = TEXT("Sprite");
            Smoke.SpawnRate = 25.0f;
            Smoke.Color = FLinearColor(0.18f, 0.18f, 0.2f, 0.7f);
            Smoke.ColorEnd = FLinearColor(0.08f, 0.08f, 0.09f, 0.25f);
            Smoke.bUseColorGradient = true;
            Smoke.Lifetime = 3.6f;
            Smoke.Size = 32.0f;
            Smoke.SizeEnd = 90.0f;
            Smoke.bUseSizeOverLife = true;
            Smoke.Velocity = FVector(0, 0, 35);
            Smoke.Drag = 5.0f;
            Smoke.Acceleration = FVector(0, 0, 15);
            Smoke.bUseGravity = false;
            Smoke.SortOrder = 1;
            Out.Emitters.Add(Smoke);
        }

        if (!HasEmitterNamed(Out, TEXT("Glow")))
        {
            FVFXEmitterRecipe Glow;
            Glow.Name = TEXT("Glow");
            Glow.RendererType = TEXT("Sprite");
            Glow.SpawnRate = 6.0f;
            Glow.Color = FLinearColor(0.2f, 0.6f, 1.0f, 1.0f);
            Glow.Lifetime = 1.2f;
            Glow.Size = 90.0f;
            Glow.SizeEnd = 120.0f;
            Glow.bUseSizeOverLife = true;
            Glow.SortOrder = 0;
            Out.Emitters.Add(Glow);
        }
    }

    return Out;
}

// ============================================================================
// Pipeline stage to string
// ============================================================================
FString PipelineStageToString(EPipelineStage Stage)
{
    switch(Stage)
    {
        case EPipelineStage::Orchestrator: return TEXT("Orchestrator");
        case EPipelineStage::LLM: return TEXT("Thinking");
        case EPipelineStage::ImageGen: return TEXT("Image Gen");
        case EPipelineStage::ImageTo3D: return TEXT("3D Gen");
        case EPipelineStage::Import: return TEXT("Importing");
        case EPipelineStage::Material: return TEXT("Materials");
        case EPipelineStage::Niagara: return TEXT("Niagara");
        case EPipelineStage::Validate: return TEXT("Validating");
        case EPipelineStage::Fallback: return TEXT("Fallback");
        default: return TEXT("Unknown");
    }
}

#undef LOCTEXT_NAMESPACE