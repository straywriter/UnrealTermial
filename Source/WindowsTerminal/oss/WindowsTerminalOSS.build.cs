using System.IO;
using UnrealBuildTool;
 
public class WindowsTerminalOSS : ModuleRules
{
	public WindowsTerminalOSS(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
 
		string OSSPath = Path.Combine(ModuleDirectory);
		
		PublicIncludePaths.AddRange(new string[]
		{
			Path.Combine(OSSPath, "chromium"),
			Path.Combine(OSSPath, "fmt\\include"),
			Path.Combine(OSSPath, "interval_tree"),
			Path.Combine(OSSPath, "stb"),
			Path.Combine(OSSPath, "pcg\\include"),
		});
		
		PublicDefinitions.Add("FMT_HEADER_ONLY");
	}
}