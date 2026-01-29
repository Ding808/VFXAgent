using UnrealBuildTool;

public class VFXAgentEditor : ModuleRules
{
	public VFXAgentEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				System.IO.Path.Combine(ModuleDirectory, "..")
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"EditorStyle",
				"UnrealEd",
				"ToolMenus",
				"DeveloperSettings",
				"Niagara",
				"NiagaraEditor",
				"VFXAgentCore",
				"VFXAgentNiagara"
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"SlateCore",
				"EditorStyle",
				"VFXAgentCore",
				"UnrealEd",
				"ToolMenus",
				"AssetTools",
				"Json",
				"JsonUtilities",
				"Niagara",
				"NiagaraEditor",
				"Sequencer"
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}