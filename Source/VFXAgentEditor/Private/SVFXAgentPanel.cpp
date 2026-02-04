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
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Layout/SSpacer.h"
#include "Widgets/Text/STextBlock.h"
#include "Types/SlateEnums.h"
#include "Styling/AppStyle.h"
#include "Styling/CoreStyle.h"
#include "DesktopPlatformModule.h"
#include "IDesktopPlatform.h"
#include "Framework/Application/SlateApplication.h"
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
					SAssignNew(UseDirectorPipelineCheckBox, SCheckBox)
					.IsChecked(ECheckBoxState::Checked)
					.Content()
					[
						SNew(STextBlock)
						.Text(FText::FromString("Use Director Pipeline (deterministic actions)"))
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

	LogMessage(FString::Printf(TEXT("Generating VFX...\nPrompt: %s\nOutput Path: %s\nAsset Name: %s"), *Prompt, *SafeOutputPath, *SafeAssetName));
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

	const bool bUseDirectorPipeline = UseDirectorPipelineCheckBox.IsValid() &&
		(UseDirectorPipelineCheckBox->GetCheckedState() == ECheckBoxState::Checked);
	if (bUseDirectorPipeline)
	{
		if (!LLMProviderObject || !LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
		{
			LogMessage(TEXT("ERROR: Director pipeline requires HttpLLMProvider"));
			bRequestInFlight = false;
			return FReply::Handled();
		}

		UHttpLLMProvider* HttpProvider = static_cast<UHttpLLMProvider*>(LLMProviderObject);
		LogMessage(TEXT("Requesting Director JSON (plan + actions) from LLM..."));
		HttpProvider->RequestDirectorJsonAsync(Prompt, FString(), [this, Prompt, SafeAssetName, SafeOutputPath](bool bSuccess, const FString& DirectorJson, const FString& Error)
		{
			if (!bSuccess)
			{
				bRequestInFlight = false;
				LogMessage(FString::Printf(TEXT("WARNING: Director JSON request failed: %s"), *Error));
				return;
			}

			LastDirectorJson = DirectorJson;
			FVFXDirectorPlan Plan;
			FString ParseError;
			if (!FVFXDirectorJson::ParseDirectorJson(DirectorJson, Plan, ParseError))
			{
				bRequestInFlight = false;
				LogMessage(FString::Printf(TEXT("ERROR: Director JSON parse failed: %s"), *ParseError));
				return;
			}

			FVFXNiagaraActionExecutor Executor;
			FVFXActionContext Context;
			Context.DefaultOutputPath = SafeOutputPath;
			LastExecutionReport = FVFXExecutionReport();
			Context.Report = &LastExecutionReport;

			LogMessage(TEXT("Executing Director action list..."));
			Executor.ExecuteActionList(Plan.Actions, Context);

			for (const FString& W : LastExecutionReport.Warnings)
			{
				LogMessage(FString::Printf(TEXT("WARN: %s"), *W));
			}
			for (const FString& E : LastExecutionReport.Errors)
			{
				LogMessage(FString::Printf(TEXT("ERROR: %s"), *E));
			}

			if (!LastExecutionReport.bSuccess)
			{
				LogMessage(TEXT("Director execution failed. Self-refinement is disabled; no retry will be attempted."));
				bRequestInFlight = false;
				return;
			}

			bRequestInFlight = false;
			LogMessage(TEXT("Director pipeline completed."));
		});

		return FReply::Handled();
	}
	
	// Standard generation
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

			LastPrompt = Prompt;
			FVFXRecipe EnhancedRecipe = EnhanceRecipeForPrompt(Recipe, Prompt);
			LastRecipe = EnhancedRecipe;
			if (EnhancedRecipe.Emitters.Num() != Recipe.Emitters.Num())
			{
				LogMessage(FString::Printf(TEXT("Enhanced recipe: %d -> %d emitters"), Recipe.Emitters.Num(), EnhancedRecipe.Emitters.Num()));
			}

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

			if (EnhancedRecipe.Emitters.Num() == 0)
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
				FVFXRecipe FinalRecipe = EnhancedRecipe;
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
		FVFXRecipe EnhancedRecipe = EnhanceRecipeForPrompt(Recipe, Prompt);
		LastRecipe = EnhancedRecipe;
		LastPrompt = Prompt;
		LogMessage(FString::Printf(TEXT("Recipe generated. Emitters: %d"), Recipe.Emitters.Num()));

		if (EnhancedRecipe.Emitters.Num() == 0)
		{
			if (LLMProviderObject && LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
			{
				UHttpLLMProvider* HttpProvider = static_cast<UHttpLLMProvider*>(LLMProviderObject);
				const FString LastError = HttpProvider->GetLastError();
				if (!LastError.IsEmpty())
				{
					LogMessage(FString::Printf(TEXT("LLM error: %s"), *LastError));
				}
				const FString RawJson = HttpProvider->GetLastRawRecipeJson();
				if (!RawJson.IsEmpty())
				{
					LogMessage(FString::Printf(TEXT("Raw LLM JSON (first 1000 chars): %s"), *RawJson.Left(1000)));
				}
			}
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
		FVFXRecipe FinalRecipe = EnhancedRecipe;
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

			LastPrompt = Prompt;
			FVFXRecipe EnhancedRecipe = EnhanceRecipeForPrompt(Recipe, Prompt);
			LastRecipe = EnhancedRecipe;
			if (EnhancedRecipe.Emitters.Num() != Recipe.Emitters.Num())
			{
				LogMessage(FString::Printf(TEXT("Enhanced recipe: %d -> %d emitters"), Recipe.Emitters.Num(), EnhancedRecipe.Emitters.Num()));
			}

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

			if (EnhancedRecipe.Emitters.Num() == 0)
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
				FVFXRecipe FinalRecipe = EnhancedRecipe;
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

static bool PromptHasAny(const FString& Prompt, const TArray<FString>& Tokens)
{
	for (const FString& Token : Tokens)
	{
		if (Prompt.Contains(Token, ESearchCase::IgnoreCase))
		{
			return true;
		}
	}
	return false;
}

static bool HasEmitterNamed(const FVFXRecipe& Recipe, const FString& Name)
{
	for (const FVFXEmitterRecipe& E : Recipe.Emitters)
	{
		if (E.Name.Equals(Name, ESearchCase::IgnoreCase))
		{
			return true;
		}
	}
	return false;
}

FVFXRecipe SVFXAgentPanel::EnhanceRecipeForPrompt(const FVFXRecipe& Recipe, const FString& Prompt)
{
	FVFXRecipe Out = Recipe;

	const bool bExplosion = PromptHasAny(Prompt, { TEXT("explosion"), TEXT("blast"), TEXT("爆炸"), TEXT("炸") });
	const bool bElectric = PromptHasAny(Prompt, { TEXT("electric"), TEXT("lightning"), TEXT("电") });
	const bool bSmoke = PromptHasAny(Prompt, { TEXT("smoke"), TEXT("烟"), TEXT("雾") });
	const bool bArc = PromptHasAny(Prompt, { TEXT("arc"), TEXT("电弧"), TEXT("弧") });

	if (!(bExplosion && bElectric))
	{
		return Out;
	}

	// Ensure non-looping explosion defaults
	Out.bLoop = false;
	if (Out.Duration <= 0.01f)
	{
		Out.Duration = 2.5f;
	}
	Out.Bounds = FVector(250.0f, 250.0f, 250.0f);

	// Add extra layers if too simple
	if (Out.Emitters.Num() < 4)
	{
		if (!HasEmitterNamed(Out, TEXT("CoreBurst")))
		{
			FVFXEmitterRecipe Core;
			Core.Name = TEXT("CoreBurst");
			Core.TemplateName = TEXT("OmnidirectionalBurst");
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
			Arc.TemplateName = TEXT("DynamicBeam");
			Arc.RendererType = TEXT("Ribbon");
			Arc.SpawnRate = bArc ? 45.0f : 30.0f;
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
			Sparks.TemplateName = TEXT("DirectionalBurst");
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
			Smoke.TemplateName = TEXT("HangingParticulates");
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
			Glow.TemplateName = TEXT("Minimal");
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