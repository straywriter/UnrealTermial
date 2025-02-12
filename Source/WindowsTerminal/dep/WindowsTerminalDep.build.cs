using System.IO;
using UnrealBuildTool;
 
public class WindowsTerminalDep : ModuleRules
{
	public WindowsTerminalDep(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
 
		string DepPath = Path.Combine(ModuleDirectory);
		
		PublicIncludePaths.AddRange(new string[]
		{
			Path.Combine(DepPath),
			Path.Combine(DepPath, "Console"),
			Path.Combine(DepPath, "CLI11"),
			Path.Combine(DepPath, "jsoncpp"),
			Path.Combine(DepPath, "telemetry"),
			Path.Combine(DepPath, "NT"),
			Path.Combine(DepPath, "Win32K"),
			Path.Combine(DepPath, "gsl/include")
		});
	}
}