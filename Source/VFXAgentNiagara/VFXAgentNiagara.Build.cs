using UnrealBuildTool;

public class VFXAgentNiagara : ModuleRules
{
	public VFXAgentNiagara(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
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
				"NiagaraCore",
				"Niagara",
				"VFXAgentCore"
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"NiagaraCore",
				"Niagara",
				"NiagaraEditor",
				"UnrealEd",
				"AssetTools",
				"AssetRegistry",
				"EditorSubsystem",   // For UAssetEditorSubsystem
				"Sequencer",
				"VFXAgentCore"
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