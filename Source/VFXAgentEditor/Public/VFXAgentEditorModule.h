#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FVFXAgentEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void RegisterMenus();
	void UnregisterMenus();
	
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);
	void PluginButtonClicked();

	FDelegateHandle ToolMenusStartupHandle;
	TWeakPtr<class SDockTab> SpawnedTab;
	TSharedPtr<class SVFXAgentPanel> PanelWidget;
};