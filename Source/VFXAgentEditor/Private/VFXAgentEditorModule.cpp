#include "VFXAgentEditorModule.h"
#include "VFXAgentLog.h"
#include "SVFXAgentPanel.h"
#include "ToolMenus.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SWindow.h"
#include "Styling/AppStyle.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FVFXAgentEditorModule"

const FName VFXAgentTabName(TEXT("VFXAgent"));

void FVFXAgentEditorModule::StartupModule()
{
	UE_LOG(LogVFXAgent, Log, TEXT("VFXAgentEditor Module Started"));

	// Register menus
	if (FModuleManager::Get().IsModuleLoaded("ToolMenus"))
	{
		RegisterMenus();
	}
	else
	{
		ToolMenusStartupHandle = UToolMenus::RegisterStartupCallback(
			FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FVFXAgentEditorModule::RegisterMenus)
		);
	}
}

void FVFXAgentEditorModule::ShutdownModule()
{
	UE_LOG(LogVFXAgent, Log, TEXT("VFXAgentEditor Module Shutdown"));

	// Unregister menus
	if (FModuleManager::Get().IsModuleLoaded("ToolMenus"))
	{
		if (ToolMenusStartupHandle.IsValid())
		{
			UToolMenus::UnRegisterStartupCallback(ToolMenusStartupHandle);
			ToolMenusStartupHandle.Reset();
		}

		UnregisterMenus();
	}
}

void FVFXAgentEditorModule::RegisterMenus()
{
	// Register menu extension
	FToolMenuOwnerScoped OwnerScoped(this);

	// Add a new menu item under "Window"
	UToolMenu* WindowMenu = UToolMenus::Get()->ExtendMenu("MainFrame.MainMenu.Window");
	if (WindowMenu)
	{
		FToolMenuSection& NewSection = WindowMenu->AddSection("VFXAgent", FText::FromString("VFX Agent"));
		NewSection.AddMenuEntry(
			"OpenVFXAgent",
			FText::FromString("VFX Agent"),
			FText::FromString("Open the VFX Agent panel"),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateRaw(this, &FVFXAgentEditorModule::OpenVFXAgentPanel))
		);
	}
}

void FVFXAgentEditorModule::UnregisterMenus()
{
	if (FModuleManager::Get().IsModuleLoaded("ToolMenus"))
	{
		UToolMenus::Get()->RemoveSection("MainFrame.MainMenu.Window", "VFXAgent");
	}
}

void FVFXAgentEditorModule::OpenVFXAgentPanel()
{
	UE_LOG(LogVFXAgent, Log, TEXT("Opening VFXAgent Panel"));

	// Create the VFX Agent chat window
	TSharedRef<SWindow> Window = SNew(SWindow)
		.Title(FText::FromString("VFX Agent"))
		.ClientSize(FVector2D(520, 720))
		.SizingRule(ESizingRule::UserSized)
		.AutoCenter(EAutoCenter::PreferredWorkArea)
		.IsInitiallyMaximized(false)
		.HasCloseButton(true)
		.FocusWhenFirstShown(true)
		.ActivationPolicy(EWindowActivationPolicy::Always)
		.SupportsMinimize(true)
		.SupportsMaximize(true)
		[
			SNew(SVFXAgentPanel)
		];

	FSlateApplication::Get().AddWindow(Window);
	VFXAgentWindow = Window;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FVFXAgentEditorModule, VFXAgentEditor)