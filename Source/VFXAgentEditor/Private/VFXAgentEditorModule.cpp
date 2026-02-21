#include "VFXAgentEditorModule.h"
#include "VFXAgentLog.h"
#include "SVFXAgentPanel.h"
#include "ToolMenus.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Framework/Docking/TabManager.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SWindow.h"
#include "Styling/AppStyle.h"
#include "Modules/ModuleManager.h"
#include "WorkspaceMenuStructure.h"
#include "WorkspaceMenuStructureModule.h"

#define LOCTEXT_NAMESPACE "FVFXAgentEditorModule"

const FName VFXAgentTabName(TEXT("VFXAgent"));

void FVFXAgentEditorModule::StartupModule()
{
	UE_LOG(LogVFXAgent, Log, TEXT("VFXAgentEditor Module Started"));

	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(VFXAgentTabName, FOnSpawnTab::CreateRaw(this, &FVFXAgentEditorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FVFXAgentTabTitle", "VFX Agent"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);

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

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(VFXAgentTabName);

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
			FUIAction(FExecuteAction::CreateRaw(this, &FVFXAgentEditorModule::PluginButtonClicked))
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

TSharedRef<SDockTab> FVFXAgentEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SVFXAgentPanel)
		];
}

void FVFXAgentEditorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(VFXAgentTabName);
}

#undef LOCTEXT_NAMESPACE

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FVFXAgentEditorModule, VFXAgentEditor)