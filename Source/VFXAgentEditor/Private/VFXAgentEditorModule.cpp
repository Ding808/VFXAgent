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
#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "UObject/UObjectArray.h"

#define LOCTEXT_NAMESPACE "FVFXAgentEditorModule"

const FName VFXAgentTabName(TEXT("VFXAgent"));

static void LogModuleStartupDiagnostics(const TCHAR* ModuleName)
{
	const FString ModuleNameStr(ModuleName);
	FString ModuleFilename;
	if (FModuleManager::Get().QueryModule(ModuleNameStr, ModuleFilename))
	{
		UE_LOG(LogVFXAgent, Log, TEXT("[%s] QueryModule filename: %s"), ModuleName, *ModuleFilename);
	}
	else
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("[%s] QueryModule failed, module may not be registered yet"), ModuleName);
	}

	if (const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("VFXAgent")))
	{
		const FString PluginDir = Plugin->GetBaseDir();
		const FString ExpectedDll = FPaths::Combine(PluginDir, TEXT("Binaries/Win64"), FString::Printf(TEXT("UnrealEditor-%s.dll"), ModuleName));
		UE_LOG(LogVFXAgent, Log, TEXT("[%s] PluginDir=%s"), ModuleName, *PluginDir);
		UE_LOG(LogVFXAgent, Log, TEXT("[%s] ExpectedDLL=%s Exists=%s"), ModuleName, *ExpectedDll, FPaths::FileExists(ExpectedDll) ? TEXT("true") : TEXT("false"));
	}
	else
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("[%s] Plugin 'VFXAgent' not found in IPluginManager"), ModuleName);
	}
}

void FVFXAgentEditorModule::StartupModule()
{
	UE_LOG(LogVFXAgent, Log, TEXT("VFXAgentEditor Module Started"));
	LogModuleStartupDiagnostics(TEXT("VFXAgentEditor"));

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

	if (SpawnedTab.IsValid())
	{
		SpawnedTab.Pin()->RequestCloseTab();
		SpawnedTab.Reset();
	}
	PanelWidget.Reset();

	if (!UObjectInitialized())
	{
		UE_LOG(LogVFXAgent, Warning, TEXT("Skipping tab/menu unregistration because UObject subsystem is not initialized."));
		return;
	}

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
	TSharedRef<SDockTab> Tab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab);

	PanelWidget = SNew(SVFXAgentPanel);
	Tab->SetContent(PanelWidget.ToSharedRef());
	SpawnedTab = Tab;
	return Tab;
}

void FVFXAgentEditorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(VFXAgentTabName);
}

#undef LOCTEXT_NAMESPACE

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FVFXAgentEditorModule, VFXAgentEditor)