using UnrealBuildTool;

public class VFXAgentNiagara : ModuleRules
{
	public VFXAgentNiagara(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		IWYUSupport = IWYUSupport.Full;
		
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
				"Niagara",
				"VFXAgentCore"
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"HTTP",
				"Json",
				"JsonUtilities",
				"Renderer",
				"NiagaraEditor",
				"UnrealEd",
				"AssetTools",
				"AssetRegistry",
				"ImageWrapper",
				"EditorSubsystem",   // For UAssetEditorSubsystem
				"Sequencer",
				"MaterialEditor",    // For material generation
				"RenderCore",        // For texture generation
				"RHI",               // For texture operations
				"Projects"
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