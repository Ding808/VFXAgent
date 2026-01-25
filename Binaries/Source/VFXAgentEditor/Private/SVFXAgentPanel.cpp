#include "SVFXAgentPanel.h"
#include "VFXAgentLog.h"
#include "VFXAgentSettings.h"
#include "ILLMProvider.h"
#include "MockLLMProvider.h"
#include "NiagaraSystemGenerator.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Text/STextBlock.h"
#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"

#define LOCTEXT_NAMESPACE "SVFXAgentPanel"

void SVFXAgentPanel::Construct(const FArguments& InArgs)
{
	if (!LLMProvider)
	{
		LLMProvider = NewObject<UMockLLMProvider>();
	}

	const UVFXAgentSettings* Settings = GetDefault<UVFXAgentSettings>();

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(10.0f)
		[
			SNew(STextBlock)
			.Text(FText::FromString("VFX Agent - AI-Powered Niagara VFX Generator"))
			.Font(FAppStyle::GetFontStyle("DetailsView.CategoryFontStyle"))
		]

		// Prompt Input Section
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(10.0f)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Generate VFX"))
					.Font(FAppStyle::GetFontStyle("DetailsView.CategoryFontStyle"))
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Describe your desired VFX effect:"))
					.Font(FCoreStyle::Get().GetFontStyle("SmallFont"))
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SAssignNew(PromptTextBox, SMultiLineEditableTextBox)
					.Text(FText::FromString("A blue electric arc explosion with smoke trails"))
					.HintText(FText::FromString("Describe your VFX..."))
					.AutoWrapText(true)
					.IsReadOnly(false)
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Output Path:"))
					.Font(FCoreStyle::Get().GetFontStyle("SmallFont"))
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SAssignNew(OutputPathTextBox, SEditableTextBox)
					.Text(FText::FromString(Settings->DefaultOutputPath))
					.IsReadOnly(false)
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Asset Name:"))
					.Font(FCoreStyle::Get().GetFontStyle("SmallFont"))
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SAssignNew(AssetNameTextBox, SEditableTextBox)
					.Text(FText::FromString(Settings->AssetNamePrefix + "GeneratedEffect_01"))
					.IsReadOnly(false)
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SNew(SButton)
					.Text(FText::FromString("Generate"))
					.OnClicked(this, &SVFXAgentPanel::OnGenerateClicked)
				]
			]
		]

		// Refinement Section
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(10.0f)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Refine VFX"))
					.Font(FAppStyle::GetFontStyle("DetailsView.CategoryFontStyle"))
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Natural language refinement (iterative editing):"))
					.Font(FCoreStyle::Get().GetFontStyle("SmallFont"))
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SAssignNew(RefinementTextBox, SMultiLineEditableTextBox)
					.Text(FText::FromString("Make it red and slower"))
					.HintText(FText::FromString("Refine the VFX..."))
					.AutoWrapText(true)
					.IsReadOnly(false)
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SNew(SButton)
					.Text(FText::FromString("Apply Refinement"))
					.OnClicked(this, &SVFXAgentPanel::OnApplyRefinementClicked)
				]
			]
		]

		// Log Section
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.Padding(10.0f)
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SNew(STextBlock)
					.Text(FText::FromString("Log"))
					.Font(FAppStyle::GetFontStyle("DetailsView.CategoryFontStyle"))
				]

				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				.Padding(5.0f)
				[
					SAssignNew(LogTextBox, SMultiLineEditableTextBox)
					.Text(FText::FromString("Ready. Waiting for input..."))
					.IsReadOnly(true)
					.AutoWrapText(true)
				]
			]
		]
	];

	LogMessage("VFXAgent Panel initialized");
}

FReply SVFXAgentPanel::OnGenerateClicked()
{
	if (!PromptTextBox.IsValid())
	{
		LogMessage("ERROR: Prompt text box is not valid");
		return FReply::Handled();
	}

	FString Prompt = PromptTextBox->GetText().ToString();
	FString OutputPath = OutputPathTextBox.IsValid() ? OutputPathTextBox->GetText().ToString() : "/Game/VFXAgent/Generated";
	FString AssetName = AssetNameTextBox.IsValid() ? AssetNameTextBox->GetText().ToString() : "VFX_GeneratedEffect";

	LogMessage(FString::Printf(TEXT("Generating VFX...\nPrompt: %s\nOutput Path: %s\nAsset Name: %s"), *Prompt, *OutputPath, *AssetName));

	if (!LLMProvider)
	{
		LogMessage("ERROR: LLM Provider not initialized");
		return FReply::Handled();
	}

	// Call LLM to generate recipe
	FVFXRecipe Recipe = LLMProvider->GenerateRecipe(Prompt);
	LastRecipe = Recipe;
	LastPrompt = Prompt;

	LogMessage(FString::Printf(TEXT("Recipe generated:\nEmitters: %d\nLoop: %s\nDuration: %.2f\nVersion: %d"),
		Recipe.Emitters.Num(),
		Recipe.bLoop ? TEXT("true") : TEXT("false"),
		Recipe.Duration,
		Recipe.Version));

	// Generate Niagara System
	UNiagaraSystemGenerator* Generator = NewObject<UNiagaraSystemGenerator>();
	if (Generator)
	{
		class UNiagaraSystem* System = Generator->GenerateNiagaraSystem(AssetName, OutputPath, Recipe);
		if (System)
		{
			LogMessage(FString::Printf(TEXT("Successfully generated Niagara System: %s"), *AssetName));
		}
		else
		{
			LogMessage(FString::Printf(TEXT("ERROR: Failed to generate Niagara System")));
		}
	}
	else
	{
		LogMessage("ERROR: Failed to create NiagaraSystemGenerator");
	}

	return FReply::Handled();
}

FReply SVFXAgentPanel::OnApplyRefinementClicked()
{
	if (!RefinementTextBox.IsValid())
	{
		LogMessage("ERROR: Refinement text box is not valid");
		return FReply::Handled();
	}

	FString RefinementPrompt = RefinementTextBox->GetText().ToString();

	LogMessage(FString::Printf(TEXT("Applying refinement...\nRefinement: %s"), *RefinementPrompt));

	if (!LLMProvider)
	{
		LogMessage("ERROR: LLM Provider not initialized");
		return FReply::Handled();
	}

	// Refine the recipe
	FVFXRecipe RefinedRecipe = LLMProvider->RefineRecipe(LastRecipe, RefinementPrompt);
	LastRecipe = RefinedRecipe;

	LogMessage(FString::Printf(TEXT("Recipe refined:\nVersion: %d\nEmitters: %d"),
		RefinedRecipe.Version,
		RefinedRecipe.Emitters.Num()));

	// Generate a new version of the Niagara System
	FString OutputPath = OutputPathTextBox.IsValid() ? OutputPathTextBox->GetText().ToString() : "/Game/VFXAgent/Generated";
	FString BaseAssetName = AssetNameTextBox.IsValid() ? AssetNameTextBox->GetText().ToString() : "VFX_GeneratedEffect";
	FString NewAssetName = FString::Printf(TEXT("%s_v%d"), *BaseAssetName, RefinedRecipe.Version);

	UNiagaraSystemGenerator* Generator = NewObject<UNiagaraSystemGenerator>();
	if (Generator)
	{
		class UNiagaraSystem* System = Generator->GenerateNiagaraSystem(NewAssetName, OutputPath, RefinedRecipe);
		if (System)
		{
			LogMessage(FString::Printf(TEXT("Successfully generated refined Niagara System: %s"), *NewAssetName));
		}
		else
		{
			LogMessage("ERROR: Failed to generate refined Niagara System");
		}
	}
	else
	{
		LogMessage("ERROR: Failed to create NiagaraSystemGenerator");
	}

	return FReply::Handled();
}

void SVFXAgentPanel::LogMessage(const FString& Message)
{
	if (LogTextBox.IsValid())
	{
		FString CurrentText = LogTextBox->GetText().ToString();
		FString NewText = CurrentText + "\n" + Message;
		LogTextBox->SetText(FText::FromString(NewText));
		UE_LOG(LogVFXAgent, Log, TEXT("%s"), *Message);
	}
}

void SVFXAgentPanel::UpdateLastRecipe(const FVFXRecipe& Recipe)
{
	LastRecipe = Recipe;
}

#undef LOCTEXT_NAMESPACE