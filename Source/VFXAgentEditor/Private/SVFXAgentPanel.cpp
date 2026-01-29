#include "SVFXAgentPanel.h"
#include "VFXAgentLog.h"
#include "VFXAgentSettings.h"
#include "ILLMProvider.h"
#include "MockLLMProvider.h"
#include "HttpLLMProvider.h"
#include "NiagaraSystemGenerator.h"
#include "JsonObjectConverter.h"
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

#include "Async/Async.h"

#define LOCTEXT_NAMESPACE "SVFXAgentPanel"

void SVFXAgentPanel::Construct(const FArguments& InArgs)
{
	RefreshLLMSettingsFromConfig();
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
				.FillHeight(1.0f)
				.MaxHeight(100.0f)
				.Padding(5.0f)
				[
					SAssignNew(PromptTextBox, SMultiLineEditableTextBox)
					.Text(FText::FromString("A blue electric arc explosion with smoke trails"))
					.HintText(FText::FromString("Describe your VFX..."))
					.AutoWrapText(true)
					.IsReadOnly(false)
					.SelectAllTextWhenFocused(false)
					.ClearKeyboardFocusOnCommit(false)
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
					SNew(STextBlock)
					.Text(FText::FromString("Reference Image (optional):"))
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
						SAssignNew(ImagePathTextBox, SEditableTextBox)
						.Text(FText::FromString(""))
						.IsReadOnly(false)
					]

					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(4.0f,0.0f)
					[
						SNew(SButton)
						.Text(FText::FromString("..."))
						.OnClicked(this, &SVFXAgentPanel::OnChooseImagePathClicked)
					]
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SNew(SButton)
					.Text(FText::FromString("Generate"))
					.IsEnabled_Lambda([this]() { return !bRequestInFlight; })
					.OnClicked(this, &SVFXAgentPanel::OnGenerateClicked)
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SNew(SButton)
					.Text(FText::FromString("Generate From Image"))
					.IsEnabled_Lambda([this]() { return !bRequestInFlight; })
					.OnClicked(this, &SVFXAgentPanel::OnGenerateFromImageClicked)
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SNew(SButton)
					.Text(FText::FromString("Test LLM Connection"))
					.IsEnabled_Lambda([this]() { return !bRequestInFlight; })
					.OnClicked(this, &SVFXAgentPanel::OnTestLLMClicked)
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
				.FillHeight(1.0f)
				.MaxHeight(80.0f)
				.Padding(5.0f)
				[
					SAssignNew(RefinementTextBox, SMultiLineEditableTextBox)
					.Text(FText::FromString("Make it red and slower"))
					.HintText(FText::FromString("Refine the VFX..."))
					.AutoWrapText(true)
					.IsReadOnly(false)
					.SelectAllTextWhenFocused(false)
					.ClearKeyboardFocusOnCommit(false)
				]

				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SNew(SButton)
					.Text(FText::FromString("Apply Refinement"))
					.IsEnabled_Lambda([this]() { return !bRequestInFlight; })
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
	RefreshLLMSettingsFromConfig();
	if (bRequestInFlight)
	{
		LogMessage(TEXT("NOTE: LLM request already in progress..."));
		return FReply::Handled();
	}
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
	LogMessage(FString::Printf(TEXT("LLM Settings: Backend=%s, Endpoint=%s, Model=%s, Timeout=%.1fs, ApiKey=%s"),
		*CachedLLMBackend,
		*CachedLLMEndpoint,
		*CachedLLMModel,
		CachedLLMTimeoutSeconds,
		bCachedHasApiKey ? TEXT("set") : TEXT("missing")));

	if (!LLMProvider)
	{
		LogMessage("ERROR: LLM Provider not initialized");
		return FReply::Handled();
	}

	bRequestInFlight = true;
	LogMessage(TEXT("Requesting recipe from LLM (async)..."));
	
	if (LLMProviderObject && LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
	{
		UHttpLLMProvider* HttpProvider = static_cast<UHttpLLMProvider*>(LLMProviderObject);
		HttpProvider->GenerateRecipeAsync(Prompt, [this, Prompt, SafeAssetName, SafeOutputPath](const FVFXRecipe& Recipe, const FString& Error)
		{
			if (!Error.IsEmpty())
			{
				bRequestInFlight = false;
				LogMessage(FString::Printf(TEXT("WARNING: LLM failed: %s"), *Error));
				return;
			}

			LastRecipe = Recipe;
			LastPrompt = Prompt;

			{
				FString RecipeJson;
				if (FJsonObjectConverter::UStructToJsonObjectString(Recipe, RecipeJson))
				{
					LogMessage(FString::Printf(TEXT("Recipe JSON (debug): %s"), *RecipeJson.Left(4000)));
				}
				else
				{
					LogMessage(TEXT("Recipe JSON (debug): <failed to serialize>"));
				}
			}

			LogMessage(FString::Printf(TEXT("Recipe generated:\nEmitters: %d\nLoop: %s\nDuration: %.2f\nVersion: %d"),
				Recipe.Emitters.Num(),
				Recipe.bLoop ? TEXT("true") : TEXT("false"),
				Recipe.Duration,
				Recipe.Version));

			if (Recipe.Emitters.Num() == 0)
			{
				bRequestInFlight = false;
				LogMessage(TEXT("WARNING: LLM returned no emitters."));
				return;
			}

			// Generate Niagara System
			try
			{
				UNiagaraSystemGenerator* Generator = NewObject<UNiagaraSystemGenerator>(GetTransientPackage(), NAME_None, RF_Transient);
				if (!Generator)
				{
					LogMessage("ERROR: Failed to create NiagaraSystemGenerator");
					return;
				}

				UE_LOG(LogVFXAgent, Log, TEXT("Created UNiagaraSystemGenerator: %p"), Generator);
				LogMessage("Generating Niagara System, please wait...");

				const UVFXAgentSettings* Settings = GetDefault<UVFXAgentSettings>();
				const bool bUseTemplates = Settings ? Settings->bUseTemplates : true;
				const FString TemplatePath = (Settings && bUseTemplates) ? Settings->DefaultTemplatePath : FString();
				FVFXRecipe FinalRecipe = Recipe;
				if (!bUseTemplates)
				{
					for (FVFXEmitterRecipe& Emitter : FinalRecipe.Emitters)
					{
						Emitter.TemplateName.Empty();
					}
				}
				class UNiagaraSystem* System = Generator->GenerateNiagaraSystem(SafeAssetName, SafeOutputPath, FinalRecipe, TemplatePath);
				if (System)
				{
					LogMessage(FString::Printf(TEXT("Successfully generated Niagara System: %s"), *SafeAssetName));
					LogMessage(TEXT("VFX generation completed!"));
				}
				else
				{
					LogMessage(TEXT("ERROR: Failed to generate Niagara System - check log for details"));
				}
			}
			catch (const std::exception& e)
			{
				LogMessage(FString::Printf(TEXT("ERROR: Exception during VFX generation: %s"), *FString(e.what())));
			}
			catch (...)
			{
				LogMessage(TEXT("ERROR: Unknown exception during VFX generation"));
			}

			bRequestInFlight = false;
		});
	}
	else
	{
		// Fallback (e.g. mock provider): synchronous call.
		FVFXRecipe Recipe = LLMProvider->GenerateRecipe(Prompt);
		bRequestInFlight = false;
		LastRecipe = Recipe;
		LastPrompt = Prompt;
		LogMessage(FString::Printf(TEXT("Recipe generated. Emitters: %d"), Recipe.Emitters.Num()));

		if (Recipe.Emitters.Num() == 0)
		{
			LogMessage(TEXT("WARNING: LLM returned no emitters."));
			return FReply::Handled();
		}

		UNiagaraSystemGenerator* Generator = NewObject<UNiagaraSystemGenerator>(GetTransientPackage(), NAME_None, RF_Transient);
		if (!Generator)
		{
			LogMessage(TEXT("ERROR: Failed to create NiagaraSystemGenerator"));
			return FReply::Handled();
		}

		const UVFXAgentSettings* Settings = GetDefault<UVFXAgentSettings>();
		const bool bUseTemplates = Settings ? Settings->bUseTemplates : true;
		const FString TemplatePath = (Settings && bUseTemplates) ? Settings->DefaultTemplatePath : FString();
		FVFXRecipe FinalRecipe = Recipe;
		if (!bUseTemplates)
		{
			for (FVFXEmitterRecipe& Emitter : FinalRecipe.Emitters)
			{
				Emitter.TemplateName.Empty();
			}
		}
		LogMessage(TEXT("Generating Niagara System, please wait..."));
		class UNiagaraSystem* System = Generator->GenerateNiagaraSystem(SafeAssetName, SafeOutputPath, FinalRecipe, TemplatePath);
		if (System)
		{
			LogMessage(FString::Printf(TEXT("Successfully generated Niagara System: %s"), *SafeAssetName));
			LogMessage(TEXT("VFX generation completed!"));
		}
		else
		{
			LogMessage(TEXT("ERROR: Failed to generate Niagara System - check log for details"));
		}
	}

	return FReply::Handled();
}

FReply SVFXAgentPanel::OnGenerateFromImageClicked()
{
	RefreshLLMSettingsFromConfig();
	if (bRequestInFlight)
	{
		LogMessage(TEXT("NOTE: LLM request already in progress..."));
		return FReply::Handled();
	}

	if (!ImagePathTextBox.IsValid())
	{
		LogMessage(TEXT("ERROR: Image path text box is not valid"));
		return FReply::Handled();
	}

	FString ImagePath = ImagePathTextBox->GetText().ToString();
	ImagePath = ImagePath.TrimStartAndEnd();
	if (ImagePath.IsEmpty())
	{
		LogMessage(TEXT("ERROR: Please choose a reference image first."));
		return FReply::Handled();
	}

	FString Prompt = PromptTextBox.IsValid() ? PromptTextBox->GetText().ToString() : FString();
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

	LogMessage(FString::Printf(TEXT("Generating VFX from image...\nImage: %s\nPrompt: %s\nOutput Path: %s\nAsset Name: %s"), *ImagePath, *Prompt, *OutputPath, *AssetName));
	LogMessage(FString::Printf(TEXT("LLM Settings: Backend=%s, Endpoint=%s, Model=%s, Timeout=%.1fs, ApiKey=%s"),
		*CachedLLMBackend,
		*CachedLLMEndpoint,
		*CachedLLMModel,
		CachedLLMTimeoutSeconds,
		bCachedHasApiKey ? TEXT("set") : TEXT("missing")));

	if (!LLMProvider)
	{
		LogMessage(TEXT("ERROR: LLM Provider not initialized"));
		return FReply::Handled();
	}

	bRequestInFlight = true;
	LogMessage(TEXT("Requesting recipe from LLM (image+prompt, async)..."));

	if (LLMProviderObject && LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
	{
		UHttpLLMProvider* HttpProvider = static_cast<UHttpLLMProvider*>(LLMProviderObject);
		HttpProvider->GenerateRecipeFromImageAsync(ImagePath, Prompt, [this, Prompt, SafeAssetName, SafeOutputPath](const FVFXRecipe& Recipe, const FString& Error)
		{
			if (!Error.IsEmpty())
			{
				bRequestInFlight = false;
				LogMessage(FString::Printf(TEXT("WARNING: LLM failed: %s"), *Error));
				return;
			}

			if (LLMProviderObject && LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
			{
				UHttpLLMProvider* Provider = static_cast<UHttpLLMProvider*>(LLMProviderObject);
				const FString RawJson = Provider->GetLastRawRecipeJson();
				if (!RawJson.IsEmpty())
				{
					LogMessage(FString::Printf(TEXT("Image Analysis JSON (raw): %s"), *RawJson.Left(4000)));
				}
			}

			LastRecipe = Recipe;
			LastPrompt = Prompt;

			{
				FString RecipeJson;
				if (FJsonObjectConverter::UStructToJsonObjectString(Recipe, RecipeJson))
				{
					LogMessage(FString::Printf(TEXT("Recipe JSON (debug): %s"), *RecipeJson.Left(4000)));
				}
				else
				{
					LogMessage(TEXT("Recipe JSON (debug): <failed to serialize>"));
				}
			}

			LogMessage(FString::Printf(TEXT("Recipe generated from image:\nEmitters: %d\nLoop: %s\nDuration: %.2f\nVersion: %d"),
				Recipe.Emitters.Num(),
				Recipe.bLoop ? TEXT("true") : TEXT("false"),
				Recipe.Duration,
				Recipe.Version));

			if (Recipe.Emitters.Num() == 0)
			{
				bRequestInFlight = false;
				LogMessage(TEXT("WARNING: LLM returned no emitters."));
				return;
			}

			try
			{
				UNiagaraSystemGenerator* Generator = NewObject<UNiagaraSystemGenerator>(GetTransientPackage(), NAME_None, RF_Transient);
				if (!Generator)
				{
					LogMessage(TEXT("ERROR: Failed to create NiagaraSystemGenerator"));
					return;
				}

				UE_LOG(LogVFXAgent, Log, TEXT("Created UNiagaraSystemGenerator: %p"), Generator);
				LogMessage(TEXT("Generating Niagara System, please wait..."));

				const UVFXAgentSettings* Settings = GetDefault<UVFXAgentSettings>();
				const bool bUseTemplates = Settings ? Settings->bUseTemplates : true;
				const FString TemplatePath = (Settings && bUseTemplates) ? Settings->DefaultTemplatePath : FString();
				FVFXRecipe FinalRecipe = Recipe;
				if (!bUseTemplates)
				{
					for (FVFXEmitterRecipe& Emitter : FinalRecipe.Emitters)
					{
						Emitter.TemplateName.Empty();
					}
				}
				class UNiagaraSystem* System = Generator->GenerateNiagaraSystem(SafeAssetName, SafeOutputPath, FinalRecipe, TemplatePath);
				if (System)
				{
					LogMessage(FString::Printf(TEXT("Successfully generated Niagara System: %s"), *SafeAssetName));
					LogMessage(TEXT("VFX generation completed!"));
				}
				else
				{
					LogMessage(TEXT("ERROR: Failed to generate Niagara System - check log for details"));
				}
			}
			catch (const std::exception& e)
			{
				LogMessage(FString::Printf(TEXT("ERROR: Exception during VFX generation: %s"), *FString(e.what())));
			}
			catch (...)
			{
				LogMessage(TEXT("ERROR: Unknown exception during VFX generation"));
			}

			bRequestInFlight = false;
		});
		return FReply::Handled();
	}

	LogMessage(TEXT("ERROR: Image-based generation requires the HTTP LLM provider."));
	bRequestInFlight = false;
	return FReply::Handled();
}

FReply SVFXAgentPanel::OnTestLLMClicked()
{
	RefreshLLMSettingsFromConfig();
	if (bRequestInFlight)
	{
		LogMessage(TEXT("NOTE: LLM request already in progress..."));
		return FReply::Handled();
	}
	LogMessage(TEXT("Testing LLM connection..."));
	LogMessage(FString::Printf(TEXT("LLM Settings: Backend=%s, Endpoint=%s, Model=%s, Timeout=%.1fs, ApiKey=%s"),
		*CachedLLMBackend,
		*CachedLLMEndpoint,
		*CachedLLMModel,
		CachedLLMTimeoutSeconds,
		bCachedHasApiKey ? TEXT("set") : TEXT("missing")));

	if (!LLMProvider)
	{
		LogMessage(TEXT("ERROR: LLM Provider not initialized"));
		return FReply::Handled();
	}

	const FString TestPrompt = TEXT("A small blue spark with a short smoke puff");
	bRequestInFlight = true;

	if (LLMProviderObject && LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
	{
		UHttpLLMProvider* HttpProvider = static_cast<UHttpLLMProvider*>(LLMProviderObject);
		HttpProvider->GenerateRecipeAsync(TestPrompt, [this](const FVFXRecipe& Recipe, const FString& Error)
		{
			bRequestInFlight = false;
			LogMessage(FString::Printf(TEXT("LLM test completed. Emitters: %d"), Recipe.Emitters.Num()));
			if (!Error.IsEmpty())
			{
				LogMessage(FString::Printf(TEXT("WARNING: LLM failed: %s"), *Error));
				return;
			}
			if (Recipe.Emitters.Num() == 0)
			{
				LogMessage(TEXT("WARNING: LLM returned no emitters. Check endpoint, API key, and network connectivity."));
			}
		});
	}
	else
	{
		FVFXRecipe Recipe = LLMProvider->GenerateRecipe(TestPrompt);
		bRequestInFlight = false;
		LogMessage(FString::Printf(TEXT("LLM test completed. Emitters: %d"), Recipe.Emitters.Num()));
	}

	return FReply::Handled();
}

FReply SVFXAgentPanel::OnApplyRefinementClicked()
{
	RefreshLLMSettingsFromConfig();
	if (bRequestInFlight)
	{
		LogMessage(TEXT("NOTE: LLM request already in progress..."));
		return FReply::Handled();
	}
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

	bRequestInFlight = true;
	LogMessage(TEXT("Requesting refinement from LLM (async)..."));

	if (LLMProviderObject && LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
	{
		UHttpLLMProvider* HttpProvider = static_cast<UHttpLLMProvider*>(LLMProviderObject);
		HttpProvider->RefineRecipeAsync(LastRecipe, RefinementPrompt, [this](const FVFXRecipe& RefinedRecipe, const FString& Error)
		{
			if (!Error.IsEmpty())
			{
				bRequestInFlight = false;
				LogMessage(FString::Printf(TEXT("WARNING: Refinement failed: %s"), *Error));
				return;
			}

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
					bRequestInFlight = false;
					return;
				}
			}

			UNiagaraSystemGenerator* Generator = NewObject<UNiagaraSystemGenerator>(GetTransientPackage(), NAME_None, RF_Transient);
			if (!Generator)
			{
				LogMessage("ERROR: Failed to create NiagaraSystemGenerator");
				bRequestInFlight = false;
				return;
			}

			try
			{
				UE_LOG(LogVFXAgent, Log, TEXT("Created UNiagaraSystemGenerator (refine): %p"), Generator);
				LogMessage("Generating refined Niagara System, please wait...");

				const UVFXAgentSettings* Settings = GetDefault<UVFXAgentSettings>();
				const bool bUseTemplates = Settings ? Settings->bUseTemplates : true;
				const FString TemplatePath = (Settings && bUseTemplates) ? Settings->DefaultTemplatePath : FString();
				FVFXRecipe FinalRecipe = RefinedRecipe;
				if (!bUseTemplates)
				{
					for (FVFXEmitterRecipe& Emitter : FinalRecipe.Emitters)
					{
						Emitter.TemplateName.Empty();
					}
				}
				class UNiagaraSystem* System = Generator->GenerateNiagaraSystem(NewAssetName, SafeOutputPath, FinalRecipe, TemplatePath);
				if (System)
				{
					LogMessage(FString::Printf(TEXT("Successfully generated refined Niagara System: %s"), *NewAssetName));
					LogMessage(TEXT("VFX refinement completed!"));
				}
				else
				{
					LogMessage(TEXT("ERROR: Failed to generate refined Niagara System - check log for details"));
				}
			}
			catch (const std::exception& e)
			{
				LogMessage(FString::Printf(TEXT("ERROR: Exception during refinement: %s"), *FString(e.what())));
			}
			catch (...)
			{
				LogMessage(TEXT("ERROR: Unknown exception during refinement"));
			}

			bRequestInFlight = false;
		});
		return FReply::Handled();
	}

	// Fallback: synchronous refine for mock provider.
	FVFXRecipe RefinedRecipe = LLMProvider->RefineRecipe(LastRecipe, RefinementPrompt);
	bRequestInFlight = false;
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

	UNiagaraSystemGenerator* Generator = NewObject<UNiagaraSystemGenerator>(GetTransientPackage(), NAME_None, RF_Transient);
	if (!Generator)
	{
		LogMessage("ERROR: Failed to create NiagaraSystemGenerator");
		return FReply::Handled();
	}

	try
	{
		UE_LOG(LogVFXAgent, Log, TEXT("Created UNiagaraSystemGenerator (refine): %p"), Generator);
		LogMessage("Generating refined Niagara System, please wait...");

		const UVFXAgentSettings* Settings = GetDefault<UVFXAgentSettings>();
		const bool bUseTemplates = Settings ? Settings->bUseTemplates : true;
		const FString TemplatePath = (Settings && bUseTemplates) ? Settings->DefaultTemplatePath : FString();
		FVFXRecipe FinalRecipe = RefinedRecipe;
		if (!bUseTemplates)
		{
			for (FVFXEmitterRecipe& Emitter : FinalRecipe.Emitters)
			{
				Emitter.TemplateName.Empty();
			}
		}
		class UNiagaraSystem* System = Generator->GenerateNiagaraSystem(NewAssetName, SafeOutputPath, FinalRecipe, TemplatePath);
		if (System)
		{
			LogMessage(FString::Printf(TEXT("Successfully generated refined Niagara System: %s"), *NewAssetName));
			LogMessage(TEXT("VFX refinement completed!"));
		}
		else
		{
			LogMessage(TEXT("ERROR: Failed to generate refined Niagara System - check log for details"));
		}
	}
	catch (const std::exception& e)
	{
		LogMessage(FString::Printf(TEXT("ERROR: Exception during refinement: %s"), *FString(e.what())));
	}
	catch (...)
	{
		LogMessage(TEXT("ERROR: Unknown exception during refinement"));
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
		CachedLLMBackend.Equals(TEXT("OpenAIChatCompletions"), ESearchCase::IgnoreCase);
	const bool bUseOllama = CachedLLMBackend.Equals(TEXT("Ollama"), ESearchCase::IgnoreCase);

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
			const EVFXAgentLLMBackend Backend = bUseOllama ? EVFXAgentLLMBackend::OllamaGenerate : EVFXAgentLLMBackend::OpenAIChatCompletions;
			ProviderObj->Configure(
				Backend,
				CachedLLMEndpoint,
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

FReply SVFXAgentPanel::OnChooseImagePathClicked()
{
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (!DesktopPlatform)
	{
		LogMessage(TEXT("ERROR: DesktopPlatform not available"));
		return FReply::Handled();
	}

	const void* ParentWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);

	FString DefaultPath = ImagePathTextBox.IsValid() ? ImagePathTextBox->GetText().ToString() : TEXT("");
	TArray<FString> OutFiles;
	const FString FileTypes = TEXT("Image Files (*.png;*.jpg;*.jpeg;*.webp)|*.png;*.jpg;*.jpeg;*.webp|All Files (*.*)|*.*");
	const bool bFilePicked = DesktopPlatform->OpenFileDialog(
		const_cast<void*>(ParentWindowHandle),
		TEXT("Choose Reference Image"),
		DefaultPath,
		TEXT(""),
		FileTypes,
		EFileDialogFlags::None,
		OutFiles);

	if (bFilePicked && OutFiles.Num() > 0)
	{
		const FString SelectedFile = OutFiles[0];
		if (ImagePathTextBox.IsValid())
		{
			ImagePathTextBox->SetText(FText::FromString(SelectedFile));
		}
		LogMessage(FString::Printf(TEXT("Selected Image: %s"), *SelectedFile));
	}

	return FReply::Handled();
}