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
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Framework/Application/SlateApplication.h"
#include "Misc/Paths.h"
#include "Misc/Paths.h"

#define LOCTEXT_NAMESPACE "SVFXAgentPanel"

void SVFXAgentPanel::Construct(const FArguments& InArgs)
{
	if (!LLMProvider)
	{
		UMockLLMProvider* ProviderObj = NewObject<UMockLLMProvider>(GetTransientPackage());
		if (ProviderObj)
		{
			ProviderObj->AddToRoot();
			LLMProvider = ProviderObj;
		}
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
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.FillWidth(1.0f)
					[
						SAssignNew(OutputPathTextBox, SEditableTextBox)
						.Text(FText::FromString(Settings->DefaultOutputPath))
						.IsReadOnly(false)
					]

					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(4.0f,0.0f)
					[
						SNew(SButton)
						.Text(FText::FromString("..."))
						.OnClicked(this, &SVFXAgentPanel::OnChooseOutputPathClicked)
					]
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

	// Validate and sanitize AssetName
	FString SafeAssetName = AssetName;
	if (SafeAssetName.IsEmpty())
	{
		SafeAssetName = TEXT("VFX_GeneratedEffect");
	}
	bool bAssetChanged = false;
	for (int32 i = 0; i < SafeAssetName.Len(); ++i)
	{
		TCHAR& C = SafeAssetName[i];
		if (!(FChar::IsAlnum(C) || C == TCHAR('_')))
		{
			C = TCHAR('_');
			bAssetChanged = true;
		}
	}
	if (bAssetChanged)
	{
		LogMessage(FString::Printf(TEXT("Note: Asset name contained invalid characters, sanitized to: %s"), *SafeAssetName));
	}

	// Validate OutputPath: accept /Game/... virtual paths or filesystem folders under Content/
	FString SafeOutputPath = OutputPath;
	SafeOutputPath = SafeOutputPath.TrimStartAndEnd();
	if (!SafeOutputPath.StartsWith(TEXT("/Game")))
	{
		// Maybe a filesystem path; convert to full
		FString FullSelected = FPaths::ConvertRelativePathToFull(SafeOutputPath);
		FString ContentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
		if (FullSelected.StartsWith(ContentDir))
		{
			FString Relative = FullSelected.Mid(ContentDir.Len());
			Relative = Relative.Replace(TEXT("\\"), TEXT("/"));
			Relative = Relative.TrimStartAndEnd();
			SafeOutputPath = FString::Printf(TEXT("/Game/%s"), *Relative);
			if (SafeOutputPath.EndsWith(TEXT("/")))
			{
				SafeOutputPath.LeftChopInline(1);
			}
			LogMessage(FString::Printf(TEXT("Converted filesystem path to virtual path: %s"), *SafeOutputPath));
		}
		else
		{
			LogMessage(FString::Printf(TEXT("ERROR: Output path must be inside the project's Content folder or start with /Game/: %s"), *OutputPath));
			return FReply::Handled();
		}
	}

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
	UNiagaraSystemGenerator* Generator = NewObject<UNiagaraSystemGenerator>(GetTransientPackage());
	if (Generator)
	{
		UE_LOG(LogVFXAgent, Log, TEXT("Created UNiagaraSystemGenerator: %p"), Generator);
		class UNiagaraSystem* System = Generator->GenerateNiagaraSystem(SafeAssetName, SafeOutputPath, Recipe);
		if (System)
		{
			LogMessage(FString::Printf(TEXT("Successfully generated Niagara System: %s"), *SafeAssetName));
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

	// Sanitize base asset name
	FString SafeBaseName = BaseAssetName;
	if (SafeBaseName.IsEmpty())
	{
		SafeBaseName = TEXT("VFX_GeneratedEffect");
	}
	for (int32 i = 0; i < SafeBaseName.Len(); ++i)
	{
		TCHAR& C = SafeBaseName[i];
		if (!(FChar::IsAlnum(C) || C == TCHAR('_')))
		{
			C = TCHAR('_');
		}
	}

	FString NewAssetName = FString::Printf(TEXT("%s_v%d"), *SafeBaseName, RefinedRecipe.Version);

	// Validate OutputPath (must be /Game/... or inside Content)
	FString SafeOutputPath = OutputPath.TrimStartAndEnd();
	if (!SafeOutputPath.StartsWith(TEXT("/Game")))
	{
		FString FullSelected = FPaths::ConvertRelativePathToFull(SafeOutputPath);
		FString ContentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
		if (FullSelected.StartsWith(ContentDir))
		{
			FString Relative = FullSelected.Mid(ContentDir.Len());
			Relative = Relative.Replace(TEXT("\\"), TEXT("/"));
			Relative = Relative.TrimStartAndEnd();
			SafeOutputPath = FString::Printf(TEXT("/Game/%s"), *Relative);
			if (SafeOutputPath.EndsWith(TEXT("/")))
			{
				SafeOutputPath.LeftChopInline(1);
			}
		}
		else
		{
			LogMessage(FString::Printf(TEXT("ERROR: Output path must be inside the project's Content folder or start with /Game/: %s"), *OutputPath));
			return FReply::Handled();
		}
	}

	UNiagaraSystemGenerator* Generator = NewObject<UNiagaraSystemGenerator>(GetTransientPackage());
	if (Generator)
	{
		UE_LOG(LogVFXAgent, Log, TEXT("Created UNiagaraSystemGenerator (refine): %p"), Generator);
		class UNiagaraSystem* System = Generator->GenerateNiagaraSystem(NewAssetName, SafeOutputPath, RefinedRecipe);
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


FReply SVFXAgentPanel::OnChooseOutputPathClicked()
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (!DesktopPlatform)
	{
		LogMessage("ERROR: DesktopPlatform not available");
		return FReply::Handled();
	}

	const void* ParentWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);

	FString DefaultPath = OutputPathTextBox.IsValid() ? OutputPathTextBox->GetText().ToString() : TEXT("");
	FString SelectedFolder;
	const bool bFolderPicked = DesktopPlatform->OpenDirectoryDialog(const_cast<void*>(ParentWindowHandle), TEXT("Choose Output Folder"), DefaultPath, SelectedFolder);

	if (bFolderPicked && !SelectedFolder.IsEmpty())
	{
		// Try to convert filesystem path under Content to /Game/ virtual path
		FString FullSelected = FPaths::ConvertRelativePathToFull(SelectedFolder);
		FString ContentDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
		FString NewPath;
		if (FullSelected.StartsWith(ContentDir))
		{
			FString Relative = FullSelected.RightChop(ContentDir.Len());
			Relative = Relative.TrimStartAndEnd();
			Relative = Relative.Replace(TEXT("\\"), TEXT("/"));
			NewPath = FString::Printf(TEXT("/Game/%s"), *Relative);
			if (NewPath.EndsWith(TEXT("/")))
			{
				NewPath.LeftChopInline(1);
			}
		}
		else
		{
			// Use raw filesystem path if not under Content
			NewPath = SelectedFolder;
		}

		if (OutputPathTextBox.IsValid())
		{
			OutputPathTextBox->SetText(FText::FromString(NewPath));
		}

		LogMessage(FString::Printf(TEXT("Selected Output Path: %s"), *NewPath));
	}

	return FReply::Handled();
}