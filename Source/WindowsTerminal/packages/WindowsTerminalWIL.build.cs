using System.IO;
using UnrealBuildTool;
 
public class WindowsTerminalWIL : ModuleRules
{
	public WindowsTerminalWIL(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory,
			"Microsoft.Windows.ImplementationLibrary.1.0.240122.1", 
			"include"));
		
		PublicDefinitions.Add("__WIL_RESOURCE_ENABLE_QUIRKS");

	}
}