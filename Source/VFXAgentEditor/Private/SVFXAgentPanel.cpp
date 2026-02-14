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
#include "Subsystems/AssetEditorSubsystem.h"
#include "Editor.h"

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

		// Effect Spec Section
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
					.Text(FText::FromString("Effect Spec"))
					.Font(FAppStyle::GetFontStyle("DetailsView.CategoryFontStyle"))
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(4.0f,0.0f)
					[
						SNew(SButton)
						.Text(FText::FromString("Generate Spec"))
						.IsEnabled_Lambda([this]() { return !bRequestInFlight; })
						.OnClicked(this, &SVFXAgentPanel::OnGenerateSpecClicked)
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(4.0f,0.0f)
					[
						SNew(SButton)
						.Text(FText::FromString("Validate"))
						.OnClicked(this, &SVFXAgentPanel::OnValidateSpecClicked)
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(4.0f,0.0f)
					[
						SNew(SButton)
						.Text(FText::FromString("Build"))
						.OnClicked(this, &SVFXAgentPanel::OnBuildSpecClicked)
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(4.0f,0.0f)
					[
						SNew(SButton)
						.Text(FText::FromString("Preview"))
						.OnClicked(this, &SVFXAgentPanel::OnPreviewClicked)
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(4.0f,0.0f)
					[
						SNew(SButton)
						.Text(FText::FromString("Revise"))
						.OnClicked(this, &SVFXAgentPanel::OnReviseSpecClicked)
					]
				]

				// V2 Pipeline Buttons
				+ SVerticalBox::Slot()
				.AutoHeight()
				.Padding(5.0f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(4.0f,0.0f)
					[
						SNew(SButton)
						.Text(FText::FromString("Generate V2 Spec"))
						.ToolTipText(FText::FromString("Multi-candidate pipeline with scoring & revision"))
						.IsEnabled_Lambda([this]() { return !bRequestInFlight; })
						.OnClicked(this, &SVFXAgentPanel::OnGenerateV2SpecClicked)
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(4.0f,0.0f)
					[
						SNew(SButton)
						.Text(FText::FromString("Validate V2"))
						.ToolTipText(FText::FromString("Validate the spec in the editor as EffectSpec v2"))
						.OnClicked(this, &SVFXAgentPanel::OnValidateV2SpecClicked)
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(4.0f,0.0f)
					[
						SNew(SButton)
						.Text(FText::FromString("Build V2"))
						.ToolTipText(FText::FromString("Build Niagara system from EffectSpec v2"))
						.IsEnabled_Lambda([this]() { return !bRequestInFlight; })
						.OnClicked(this, &SVFXAgentPanel::OnBuildV2SpecClicked)
					]
				]
				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				.Padding(5.0f)
				[
					SAssignNew(SpecTextBox, SMultiLineEditableTextBox)
					.Text(FText::FromString(
						"{\n"
						"  \"effect_name\": \"Example\",\n"
						"  \"layers\": [\n"
						"    {\"id\": \"L1\", \"name\": \"core\", \"role\": \"core_blast\", \"renderer_type\": \"sprite\", \"spawn\": {\"mode\": \"burst\", \"burst_count\": 40}, \"init\": {\"lifetime\": 1.5, \"size_range\": [10, 30], \"velocity\": {\"x\": 0, \"y\": 0, \"z\": 200}}, \"update\": {\"drag\": 1.0, \"curl_noise_strength\": 5.0}, \"material\": {\"shading\": \"unlit\", \"blend\": \"additive\"}},\n"
						"    {\"id\": \"L2\", \"name\": \"sparks\", \"role\": \"sparks\", \"renderer_type\": \"sprite\", \"spawn\": {\"mode\": \"burst\", \"burst_count\": 80}, \"init\": {\"lifetime\": 1.0, \"size_range\": [2, 8], \"velocity\": {\"x\": 200, \"y\": 0, \"z\": 100}}, \"update\": {\"drag\": 2.0, \"curl_noise_strength\": 2.0}, \"material\": {\"shading\": \"unlit\", \"blend\": \"additive\"}},\n"
						"    {\"id\": \"L3\", \"name\": \"trail\", \"role\": \"trail\", \"renderer_type\": \"ribbon\", \"spawn\": {\"mode\": \"rate\", \"rate\": 30}, \"init\": {\"lifetime\": 2.0, \"size_range\": [4, 12], \"velocity\": {\"x\": 0, \"y\": 0, \"z\": 120}}, \"update\": {\"drag\": 0.5, \"curl_noise_strength\": 3.0}, \"material\": {\"shading\": \"unlit\", \"blend\": \"translucent\"}}\n"
						"  ]\n"
						"}\n"
					))
					.IsReadOnly(false)
					.AutoWrapText(true)
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

		// Pipeline Log Section
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
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.FillWidth(1.0f)
					[
						SNew(STextBlock)
						.Text(FText::FromString("Pipeline Log"))
						.Font(FAppStyle::GetFontStyle("DetailsView.CategoryFontStyle"))
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(4.0f,0.0f)
					[
						SNew(SButton)
						.Text(FText::FromString("Copy"))
						.OnClicked(this, &SVFXAgentPanel::OnCopyPipelineLogClicked)
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(4.0f,0.0f)
					[
						SNew(SButton)
						.Text(FText::FromString("Export"))
						.OnClicked(this, &SVFXAgentPanel::OnExportPipelineLogClicked)
					]
				]

				+ SVerticalBox::Slot()
				.FillHeight(1.0f)
				.Padding(5.0f)
				[
					SAssignNew(PipelineLogTextBox, SMultiLineEditableTextBox)
					.Text(FText::FromString("Pipeline log ready. Waiting for updates..."))
					.IsReadOnly(true)
					.AutoWrapText(true)
				]
			]
		]
	];

	LogMessage("VFXAgent Panel initialized");
}

void SVFXAgentPanel::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	DrainPipelineLog();
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

	const bool bDirectorCheckboxOn = UseDirectorPipelineCheckBox.IsValid() &&
		(UseDirectorPipelineCheckBox->GetCheckedState() == ECheckBoxState::Checked);

	// Director pipeline requires templates; auto-skip when bDisallowTemplates=true.
	const UVFXAgentSettings* DirSettings = GetDefault<UVFXAgentSettings>();
	const bool bUseDirectorPipeline = bDirectorCheckboxOn && !(DirSettings && DirSettings->bDisallowTemplates);
	if (bDirectorCheckboxOn && !bUseDirectorPipeline)
	{
		LogMessage(TEXT("NOTE: Director pipeline requires templates but bDisallowTemplates=true. Using standard recipe pipeline instead."));
		FPipelineLog::Get().Push(EPipelineLogLevel::Warning, EPipelineStage::Orchestrator, TEXT("Director pipeline skipped (template policy), using recipe pipeline"));
	}

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
		FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::LLM, TEXT("Generating Director JSON..."), CachedLLMBackend);
		HttpProvider->RequestDirectorJsonAsync(Prompt, FString(), [this, Prompt, SafeAssetName, SafeOutputPath](bool bSuccess, const FString& DirectorJson, const FString& Error)
		{
			if (!bSuccess)
			{
				bRequestInFlight = false;
				LogMessage(FString::Printf(TEXT("WARNING: Director JSON request failed: %s"), *Error));
				FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::LLM, TEXT("Director JSON failed"), CachedLLMBackend);
				return;
			}

			LastDirectorJson = DirectorJson;
			FVFXDirectorPlan Plan;
			FString ParseError;
			if (!FVFXDirectorJson::ParseDirectorJson(DirectorJson, Plan, ParseError))
			{
				bRequestInFlight = false;
				LogMessage(FString::Printf(TEXT("ERROR: Director JSON parse failed: %s"), *ParseError));
				FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::LLM, TEXT("Director JSON parse failed"), CachedLLMBackend);
				return;
			}

			FVFXNiagaraActionExecutor Executor;
			FVFXActionContext Context;
			Context.DefaultOutputPath = SafeOutputPath;
			LastExecutionReport = FVFXExecutionReport();
			Context.Report = &LastExecutionReport;

			LogMessage(TEXT("Executing Director action list..."));
			FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Orchestrator, TEXT("Executing Director actions..."));
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
				FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::Orchestrator, TEXT("Director execution failed"));
				bRequestInFlight = false;
				return;
			}

			bRequestInFlight = false;
			LogMessage(TEXT("Director pipeline completed."));
			FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Orchestrator, TEXT("Director pipeline completed"));
		});

		return FReply::Handled();
	}
	
	// Standard generation
	LogMessage(TEXT("Requesting recipe from LLM (async)..."));
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::LLM, TEXT("Generating Recipe..."), CachedLLMBackend);
	
	if (LLMProviderObject && LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
	{
		UHttpLLMProvider* HttpProvider = static_cast<UHttpLLMProvider*>(LLMProviderObject);
		HttpProvider->GenerateRecipeAsync(Prompt, [this, Prompt, SafeAssetName, SafeOutputPath](const FVFXRecipe& Recipe, const FString& Error)
		{
			if (!Error.IsEmpty())
			{
				bRequestInFlight = false;
				LogMessage(FString::Printf(TEXT("WARNING: LLM failed: %s"), *Error));
				FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::LLM, TEXT("Recipe generation failed"), CachedLLMBackend);
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
				const bool bDisallowTemplates = Settings ? Settings->bDisallowTemplates : true;
				const bool bUseTemplates = !bDisallowTemplates && Settings && Settings->bUseTemplates;
				const FString TemplatePath = (Settings && bUseTemplates) ? Settings->DefaultTemplatePath : FString();
				if (bDisallowTemplates)
				{
					FPipelineLog::Get().Push(EPipelineLogLevel::Warning, EPipelineStage::Niagara, TEXT("Template usage blocked"));
				}
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
					FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara, TEXT("Niagara build completed"));
				}
				else
				{
					LogMessage(TEXT("ERROR: Failed to generate Niagara System - check log for details"));
					FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::Niagara, TEXT("Niagara build failed"));
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
		FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::LLM, TEXT("Recipe generation completed"), CachedLLMBackend);
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
		const bool bDisallowTemplates = Settings ? Settings->bDisallowTemplates : true;
		const bool bUseTemplates = !bDisallowTemplates && Settings && Settings->bUseTemplates;
		const FString TemplatePath = (Settings && bUseTemplates) ? Settings->DefaultTemplatePath : FString();
		if (bDisallowTemplates)
		{
			FPipelineLog::Get().Push(EPipelineLogLevel::Warning, EPipelineStage::Niagara, TEXT("Template usage blocked"));
		}
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
			FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara, TEXT("Niagara build completed"));
		}
		else
		{
			LogMessage(TEXT("ERROR: Failed to generate Niagara System - check log for details"));
			FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::Niagara, TEXT("Niagara build failed"));
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
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::LLM, TEXT("Generating Recipe (image+prompt)..."), CachedLLMBackend);

	if (LLMProviderObject && LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
	{
		UHttpLLMProvider* HttpProvider = static_cast<UHttpLLMProvider*>(LLMProviderObject);
		HttpProvider->GenerateRecipeFromImageAsync(ImagePath, Prompt, [this, Prompt, SafeAssetName, SafeOutputPath](const FVFXRecipe& Recipe, const FString& Error)
		{
			if (!Error.IsEmpty())
			{
				bRequestInFlight = false;
				LogMessage(FString::Printf(TEXT("WARNING: LLM failed: %s"), *Error));
				FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::LLM, TEXT("Recipe generation failed"), CachedLLMBackend);
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
				const bool bDisallowTemplates = Settings ? Settings->bDisallowTemplates : true;
				const bool bUseTemplates = !bDisallowTemplates && Settings && Settings->bUseTemplates;
				const FString TemplatePath = (Settings && bUseTemplates) ? Settings->DefaultTemplatePath : FString();
				if (bDisallowTemplates)
				{
					FPipelineLog::Get().Push(EPipelineLogLevel::Warning, EPipelineStage::Niagara, TEXT("Template usage blocked"));
				}
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
					FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara, TEXT("Niagara build completed"));
				}
				else
				{
					LogMessage(TEXT("ERROR: Failed to generate Niagara System - check log for details"));
					FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::Niagara, TEXT("Niagara build failed"));
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

FReply SVFXAgentPanel::OnGenerateSpecClicked()
{
	RefreshLLMSettingsFromConfig();
	if (bRequestInFlight)
	{
		LogMessage(TEXT("NOTE: LLM request already in progress..."));
		return FReply::Handled();
	}

	if (!LLMProviderObject || !LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
	{
		LogMessage(TEXT("ERROR: EffectSpec generation requires HttpLLMProvider"));
		return FReply::Handled();
	}

	const FString Prompt = PromptTextBox.IsValid() ? PromptTextBox->GetText().ToString() : FString();
	UHttpLLMProvider* HttpProvider = static_cast<UHttpLLMProvider*>(LLMProviderObject);
	LogMessage(TEXT("Requesting EffectSpec JSON (strict schema) from LLM..."));
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::LLM, TEXT("Generating EffectSpec..."), CachedLLMBackend);
	bRequestInFlight = true;

	HttpProvider->RequestEffectSpecJsonAsync(Prompt, FString(), [this](bool bSuccess, const FString& SpecJson, const FString& Error)
	{
		bRequestInFlight = false;
		if (!bSuccess)
		{
			LogMessage(FString::Printf(TEXT("ERROR: EffectSpec request failed: %s"), *Error));
			FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::LLM, TEXT("EffectSpec request failed"), CachedLLMBackend);
			return;
		}

		LastEffectSpecJson = SpecJson;
		if (SpecTextBox.IsValid())
		{
			SpecTextBox->SetText(FText::FromString(SpecJson));
		}
		{
			const FString LogDir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("VFXAgent"), TEXT("Logs"));
			IFileManager::Get().MakeDirectory(*LogDir, true);
			FFileHelper::SaveStringToFile(SpecJson, *(FPaths::Combine(LogDir, TEXT("effectspec_response.txt"))));
		}
		LogMessage(TEXT("EffectSpec JSON received."));
		FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::LLM, TEXT("EffectSpec received"), CachedLLMBackend);
	});

	return FReply::Handled();
}

FReply SVFXAgentPanel::OnValidateSpecClicked()
{
	const FString SpecJson = SpecTextBox.IsValid() ? SpecTextBox->GetText().ToString() : FString();
	FEffectSpecV1 Spec;
	FString ParseError;
	if (!FEffectSpecParser::ParseFromJsonString(SpecJson, Spec, ParseError))
	{
		LogMessage(FString::Printf(TEXT("Spec parse failed: %s"), *ParseError));
		FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::Validate, TEXT("Spec parse failed"));
		return FReply::Handled();
	}
	TArray<FEffectSpecValidationError> Errors;
	if (!FEffectSpecValidator::Validate(Spec, Errors))
	{
		const FString Msg = FEffectSpecValidator::FormatErrors(Errors);
		LogMessage(FString::Printf(TEXT("Spec validation failed:\n%s"), *Msg));
		FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::Validate, TEXT("Spec validation failed"));
		return FReply::Handled();
	}
	LogMessage(TEXT("Spec validation OK."));
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Validate, TEXT("Spec validation OK"));
	return FReply::Handled();
}

FReply SVFXAgentPanel::OnBuildSpecClicked()
{
	if (bRequestInFlight)
	{
		LogMessage(TEXT("NOTE: Request already in progress..."));
		return FReply::Handled();
	}

	const FString SpecJson = SpecTextBox.IsValid() ? SpecTextBox->GetText().ToString() : FString();
	const FString OutputPath = OutputPathTextBox.IsValid() ? OutputPathTextBox->GetText().ToString() : TEXT("/Game/Generated/VFX");
	LogMessage(TEXT("Building assets from EffectSpec..."));
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara, TEXT("Building from EffectSpec..."));
	
	bRequestInFlight = true;
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, SpecJson, OutputPath]()
	{
		FEffectSpecV1 Parsed;
		FString ParseError;
		TArray<FEffectSpecValidationError> Errors;
		const bool bParsed = FEffectSpecParser::ParseFromJsonString(SpecJson, Parsed, ParseError);
		const bool bValid = bParsed && FEffectSpecValidator::Validate(Parsed, Errors);

		AsyncTask(ENamedThreads::GameThread, [this, bParsed, bValid, ParseError, Errors, SpecJson, OutputPath]()
		{
			if (!bParsed)
			{
				bRequestInFlight = false;
				LogMessage(FString::Printf(TEXT("Spec parse failed: %s"), *ParseError));
				return;
			}
			if (!bValid)
			{
				bRequestInFlight = false;
				LogMessage(FString::Printf(TEXT("Spec validation failed:\n%s"), *FEffectSpecValidator::FormatErrors(Errors)));
				return;
			}

			FAssetBuildResult Result;
			if (!FAssetBuildPipeline::BuildFromJsonSpec(SpecJson, OutputPath, Result))
			{
				LogMessage(TEXT("EffectSpec build failed."));
				for (const FString& Err : Result.Errors)
				{
					LogMessage(FString::Printf(TEXT("ERROR: %s"), *Err));
				}
				bRequestInFlight = false;
				return;
			}

			LastGeneratedSystemPath = Result.SystemPath;
			LogMessage(FString::Printf(TEXT("EffectSpec build completed: %s"), *LastGeneratedSystemPath));
			bRequestInFlight = false;
		});
	});

	return FReply::Handled();
}

FReply SVFXAgentPanel::OnPreviewClicked()
{
	if (LastGeneratedSystemPath.IsEmpty())
	{
		LogMessage(TEXT("No generated system to preview."));
		return FReply::Handled();
	}

	UNiagaraSystem* System = LoadObject<UNiagaraSystem>(nullptr, *LastGeneratedSystemPath);
	if (!System)
	{
		LogMessage(TEXT("Failed to load generated system for preview."));
		return FReply::Handled();
	}

	if (GEditor)
	{
		UAssetEditorSubsystem* Subsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
		if (Subsystem)
		{
			Subsystem->OpenEditorForAsset(System);
			LogMessage(TEXT("Opened Niagara System editor for preview."));
		}
	}

	return FReply::Handled();
}

FReply SVFXAgentPanel::OnReviseSpecClicked()
{
	RefreshLLMSettingsFromConfig();
	if (bRequestInFlight)
	{
		LogMessage(TEXT("NOTE: LLM request already in progress..."));
		return FReply::Handled();
	}

	if (!LLMProviderObject || !LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
	{
		LogMessage(TEXT("ERROR: Spec revision requires HttpLLMProvider"));
		return FReply::Handled();
	}

	const FString Prompt = PromptTextBox.IsValid() ? PromptTextBox->GetText().ToString() : FString();
	const FString SpecJson = SpecTextBox.IsValid() ? SpecTextBox->GetText().ToString() : FString();
	const FString Combined = FString::Printf(TEXT("Revise this EffectSpec JSON to match the new prompt.\nPrompt: %s\n\nEffectSpec JSON:\n%s"), *Prompt, *SpecJson);

	UHttpLLMProvider* HttpProvider = static_cast<UHttpLLMProvider*>(LLMProviderObject);
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::LLM, TEXT("Revising EffectSpec..."), CachedLLMBackend);
	bRequestInFlight = true;
	HttpProvider->RequestEffectSpecJsonAsync(Combined, FString(), [this](bool bSuccess, const FString& NewJson, const FString& Error)
	{
		bRequestInFlight = false;
		if (!bSuccess)
		{
			LogMessage(FString::Printf(TEXT("ERROR: Spec revision failed: %s"), *Error));
			FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::LLM, TEXT("Spec revision failed"), CachedLLMBackend);
			return;
		}
		LastEffectSpecJson = NewJson;
		if (SpecTextBox.IsValid())
		{
			SpecTextBox->SetText(FText::FromString(NewJson));
		}
		LogMessage(TEXT("Spec revision completed."));
		FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::LLM, TEXT("Spec revision completed"), CachedLLMBackend);
	});

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

FReply SVFXAgentPanel::OnCopyPipelineLogClicked()
{
	const FString Text = BuildPipelineLogText();
	FPlatformApplicationMisc::ClipboardCopy(*Text);
	return FReply::Handled();
}

FReply SVFXAgentPanel::OnExportPipelineLogClicked()
{
	const FString LogDir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("VFXAgent"), TEXT("Logs"));
	IFileManager::Get().MakeDirectory(*LogDir, true);
	const FString UiLogPath = FPaths::Combine(LogDir, TEXT("ui_log.txt"));
	const FString Text = BuildPipelineLogText();
	FFileHelper::SaveStringToFile(Text, *UiLogPath);
	LogMessage(FString::Printf(TEXT("Pipeline log exported: %s"), *UiLogPath));
	return FReply::Handled();
}

void SVFXAgentPanel::DrainPipelineLog()
{
	TArray<FPipelineLogEntry> Entries;
	FPipelineLog::Get().Drain(Entries);
	if (Entries.Num() == 0)
	{
		return;
	}

	for (const FPipelineLogEntry& Entry : Entries)
	{
		const FString Level = Entry.Level == EPipelineLogLevel::Error ? TEXT("Error") :
			Entry.Level == EPipelineLogLevel::Warning ? TEXT("Warn") : TEXT("Info");
		const FString Stage =
			Entry.Stage == EPipelineStage::LLM ? TEXT("LLM") :
			Entry.Stage == EPipelineStage::ImageGen ? TEXT("ImageGen") :
			Entry.Stage == EPipelineStage::ImageTo3D ? TEXT("ImageTo3D") :
			Entry.Stage == EPipelineStage::Import ? TEXT("Import") :
			Entry.Stage == EPipelineStage::Material ? TEXT("Material") :
			Entry.Stage == EPipelineStage::Niagara ? TEXT("Niagara") :
			Entry.Stage == EPipelineStage::Validate ? TEXT("Validate") :
			Entry.Stage == EPipelineStage::Fallback ? TEXT("Fallback") : TEXT("Orchestrator");

		const FString TimeStr = Entry.Timestamp.ToString(TEXT("%H:%M:%S"));
		FString Provider = Entry.Provider.IsEmpty() ? TEXT("") : FString::Printf(TEXT("[%s]"), *Entry.Provider);
		FString Progress;
		if (Entry.TotalSteps > 0)
		{
			Progress = FString::Printf(TEXT("[%d/%d %.0f%%] "), Entry.CurrentStep, Entry.TotalSteps, Entry.Percent * 100.0f);
		}
		const FString Line = FString::Printf(TEXT("[%s][%s][%s]%s %s%s"), *TimeStr, *Stage, *Level, *Provider, *Progress, *Entry.Message);
		PipelineLogLines.Add(Line);
	}

	while (PipelineLogLines.Num() > PipelineLogMaxLines)
	{
		PipelineLogLines.RemoveAt(0);
	}

	bPipelineLogDirty = true;
	UpdatePipelineLogText();
}

FString SVFXAgentPanel::BuildPipelineLogText() const
{
	return FString::Join(PipelineLogLines, TEXT("\n"));
}

void SVFXAgentPanel::UpdatePipelineLogText()
{
	if (!bPipelineLogDirty || !PipelineLogTextBox.IsValid())
	{
		return;
	}

	PipelineLogTextBox->SetText(FText::FromString(BuildPipelineLogText()));
	bPipelineLogDirty = false;
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
			EVFXAgentLLMBackend Backend;
			if (bUseOllama)
			{
				Backend = EVFXAgentLLMBackend::OllamaGenerate;
			}
			else if (CachedLLMEndpoint.Contains(TEXT("/v1/responses")))
			{
				Backend = EVFXAgentLLMBackend::OpenAIResponses;
			}
			else
			{
				Backend = EVFXAgentLLMBackend::OpenAIChatCompletions;
			}
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

// ============================================================================
// V2 Pipeline: Generate V2 Spec (multi-candidate)
// ============================================================================

FReply SVFXAgentPanel::OnGenerateV2SpecClicked()
{
	RefreshLLMSettingsFromConfig();
	if (bRequestInFlight)
	{
		LogMessage(TEXT("NOTE: LLM request already in progress..."));
		return FReply::Handled();
	}

	if (!LLMProviderObject || !LLMProviderObject->IsA(UHttpLLMProvider::StaticClass()))
	{
		LogMessage(TEXT("ERROR: V2 pipeline requires HttpLLMProvider"));
		return FReply::Handled();
	}

	const FString Prompt = PromptTextBox.IsValid() ? PromptTextBox->GetText().ToString() : FString();
	if (Prompt.IsEmpty())
	{
		LogMessage(TEXT("ERROR: Please enter a prompt."));
		return FReply::Handled();
	}

	UHttpLLMProvider* HttpProvider = static_cast<UHttpLLMProvider*>(LLMProviderObject);
	const UVFXAgentSettings* Settings = GetDefault<UVFXAgentSettings>();

	// Build config from settings
	FMultiCandidateConfig Config;
	Config.NumCandidates = Settings ? Settings->V2NumCandidates : 3;
	Config.TargetScore = Settings ? Settings->V2TargetScore : 0.85f;
	Config.MinAcceptScore = Settings ? Settings->V2MinAcceptScore : 0.6f;
	Config.MaxRevisionPasses = Settings ? Settings->V2MaxRevisionPasses : 2;

	EVFXBehaviorArchetype InferredArchetype = FBehaviorArchetypeLibrary::InferFromPrompt(Prompt);
	const FBehaviorArchetypeDefinition& ArchDef = FBehaviorArchetypeLibrary::GetDefinition(InferredArchetype);

	LogMessage(FString::Printf(TEXT("Starting V2 multi-candidate pipeline...")));
	LogMessage(FString::Printf(TEXT("  Archetype: %s"), *ArchDef.DisplayName));
	LogMessage(FString::Printf(TEXT("  Candidates: %d, Target Score: %.2f, Max Revisions: %d"),
		Config.NumCandidates, Config.TargetScore, Config.MaxRevisionPasses));
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Orchestrator,
		FString::Printf(TEXT("V2 pipeline: archetype=%s, candidates=%d"), *ArchDef.DisplayName, Config.NumCandidates));

	bRequestInFlight = true;

	FVFXMultiCandidatePipeline::RunAsync(HttpProvider, Prompt, Config,
		[this](const FMultiCandidatePipelineResult& Result)
		{
			bRequestInFlight = false;
			LastV2Result = Result;

			if (!Result.bSuccess)
			{
				LogMessage(TEXT("V2 pipeline FAILED. No viable candidate."));
				FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::Orchestrator, TEXT("V2 pipeline failed"));
				for (const FString& Line : Result.PipelineLog)
				{
					LogMessage(FString::Printf(TEXT("  [V2] %s"), *Line));
				}
				return;
			}

			// Display results
			DisplayV2CandidateResults(Result);

			// Store the selected spec JSON in the editor
			LastEffectSpecV2Json = Result.SelectedCandidate.RawJson;
			if (SpecTextBox.IsValid())
			{
				SpecTextBox->SetText(FText::FromString(Result.SelectedCandidate.RawJson));
			}

			// Save to disk
			const FString LogDir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("VFXAgent"), TEXT("Logs"));
			IFileManager::Get().MakeDirectory(*LogDir, true);
			FFileHelper::SaveStringToFile(Result.SelectedCandidate.RawJson, *FPaths::Combine(LogDir, TEXT("effectspec_v2_selected.json")));

			// Save all candidates
			for (int32 i = 0; i < Result.AllCandidates.Num(); ++i)
			{
				FFileHelper::SaveStringToFile(
					Result.AllCandidates[i].RawJson,
					*FPaths::Combine(LogDir, FString::Printf(TEXT("effectspec_v2_candidate_%d.json"), i)));
			}

			LogMessage(FString::Printf(TEXT("V2 pipeline completed. Selected candidate #%d, score=%.2f, LLM calls=%d"),
				Result.SelectedIndex, Result.SelectedCandidate.Score, Result.TotalLLMCalls));
			FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Orchestrator,
				FString::Printf(TEXT("V2 pipeline done: score=%.2f, calls=%d"), Result.SelectedCandidate.Score, Result.TotalLLMCalls));
		});

	return FReply::Handled();
}

void SVFXAgentPanel::DisplayV2CandidateResults(const FMultiCandidatePipelineResult& Result)
{
	LogMessage(TEXT("=== V2 Pipeline Results ==="));
	LogMessage(FString::Printf(TEXT("Total Candidates: %d, LLM Calls: %d"), Result.AllCandidates.Num(), Result.TotalLLMCalls));

	for (int32 i = 0; i < Result.AllCandidates.Num(); ++i)
	{
		const FVFXCandidate& C = Result.AllCandidates[i];
		const FString Marker = (i == Result.SelectedIndex) ? TEXT(" ★ SELECTED") : TEXT("");
		LogMessage(FString::Printf(TEXT("  Candidate #%d: valid=%s, score=%.2f%s"),
			i, C.bValid ? TEXT("YES") : TEXT("NO"), C.Score, *Marker));
		for (const FString& S : C.Strengths)
		{
			LogMessage(FString::Printf(TEXT("    + %s"), *S));
		}
		for (const FString& I : C.Issues)
		{
			LogMessage(FString::Printf(TEXT("    - %s"), *I));
		}
	}

	// Pipeline log
	for (const FString& Line : Result.PipelineLog)
	{
		LogMessage(FString::Printf(TEXT("  [V2] %s"), *Line));
	}
}

// ============================================================================
// V2 Pipeline: Validate V2 Spec
// ============================================================================

FReply SVFXAgentPanel::OnValidateV2SpecClicked()
{
	const FString SpecJson = SpecTextBox.IsValid() ? SpecTextBox->GetText().ToString() : FString();
	FEffectSpecV2 Spec;
	FString ParseError;
	if (!FEffectSpecV2Parser::ParseFromJson(SpecJson, Spec, ParseError))
	{
		LogMessage(FString::Printf(TEXT("V2 Spec parse failed: %s"), *ParseError));
		FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::Validate, TEXT("V2 spec parse failed"));
		return FReply::Handled();
	}

	TArray<FString> Errors, Warnings;
	FEffectSpecV2Validator::Validate(Spec, Errors, Warnings);

	if (Errors.Num() > 0)
	{
		LogMessage(FString::Printf(TEXT("V2 Spec validation FAILED (%d errors, %d warnings):"), Errors.Num(), Warnings.Num()));
		for (const FString& E : Errors) { LogMessage(FString::Printf(TEXT("  ERROR: %s"), *E)); }
		for (const FString& W : Warnings) { LogMessage(FString::Printf(TEXT("  WARN: %s"), *W)); }
		FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::Validate, TEXT("V2 spec validation failed"));
		return FReply::Handled();
	}

	// Score it
	TArray<FString> Strengths, Issues;
	float Score = FVFXSpecScorer::Score(Spec, Strengths, Issues);
	LogMessage(FString::Printf(TEXT("V2 Spec validation OK. Score: %.2f"), Score));
	LogMessage(FString::Printf(TEXT("  Layers: %d, Events: %d, Archetype: %s"),
		Spec.Layers.Num(), Spec.Events.Num(), *Spec.EffectName));
	for (const FString& S : Strengths) { LogMessage(FString::Printf(TEXT("  + %s"), *S)); }
	for (const FString& I : Issues) { LogMessage(FString::Printf(TEXT("  - %s"), *I)); }
	if (Warnings.Num() > 0)
	{
		for (const FString& W : Warnings) { LogMessage(FString::Printf(TEXT("  WARN: %s"), *W)); }
	}
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Validate,
		FString::Printf(TEXT("V2 spec OK, score=%.2f"), Score));
	return FReply::Handled();
}

// ============================================================================
// V2 Pipeline: Build V2 Spec
// ============================================================================

FReply SVFXAgentPanel::OnBuildV2SpecClicked()
{
	if (bRequestInFlight)
	{
		LogMessage(TEXT("NOTE: Request already in progress..."));
		return FReply::Handled();
	}

	const FString SpecJson = SpecTextBox.IsValid() ? SpecTextBox->GetText().ToString() : FString();
	const FString OutputPath = OutputPathTextBox.IsValid() ? OutputPathTextBox->GetText().ToString() : TEXT("/Game/Generated/VFX");
	LogMessage(TEXT("Building Niagara system from V2 EffectSpec..."));
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara, TEXT("V2 Build starting..."));

	bRequestInFlight = true;
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, SpecJson, OutputPath]()
	{
		FEffectSpecV2 Parsed;
		FString ParseError;
		const bool bParsed = FEffectSpecV2Parser::ParseFromJson(SpecJson, Parsed, ParseError);

		TArray<FString> Errors, Warnings;
		const bool bValid = bParsed && FEffectSpecV2Validator::Validate(Parsed, Errors, Warnings);

		AsyncTask(ENamedThreads::GameThread, [this, bParsed, bValid, ParseError, Errors, Warnings, SpecJson, OutputPath, Parsed]()
		{
			if (!bParsed)
			{
				bRequestInFlight = false;
				LogMessage(FString::Printf(TEXT("V2 Spec parse failed: %s"), *ParseError));
				return;
			}
			if (!bValid)
			{
				bRequestInFlight = false;
				LogMessage(FString::Printf(TEXT("V2 Spec validation failed:\n%s"),
					*FEffectSpecV2Validator::FormatReport(Errors, Warnings)));
				return;
			}

			FAssetBuildResult Result;
			if (!FAssetBuildPipelineV2::BuildFromV2Spec(Parsed, OutputPath, Result))
			{
				LogMessage(TEXT("V2 build failed."));
				for (const FString& Err : Result.Errors)
				{
					LogMessage(FString::Printf(TEXT("  ERROR: %s"), *Err));
				}
				bRequestInFlight = false;
				return;
			}

			LastGeneratedSystemPath = Result.SystemPath;
			LogMessage(FString::Printf(TEXT("V2 Build completed: %s"), *LastGeneratedSystemPath));
			for (const FString& W : Result.Warnings)
			{
				LogMessage(FString::Printf(TEXT("  WARN: %s"), *W));
			}
			FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara,
				FString::Printf(TEXT("V2 Build done: %s"), *LastGeneratedSystemPath));
			bRequestInFlight = false;
		});
	});

	return FReply::Handled();
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