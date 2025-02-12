using System.IO;
using UnrealBuildTool;
 
public class WindowsTerminal : ModuleRules
{
	public WindowsTerminal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.NoPCHs;
        bEnableUndefinedIdentifierWarnings = false;
        bUseRTTI = true;
        Type = ModuleType.CPlusPlus;
        
        // todo
        OptimizeCode = CodeOptimization.Never;

        PublicDependencyModuleNames.AddRange(new string[]
        {
	        "Core",
	        "FTXUI",
	        "CoreUObject", 
	        "Engine", 
	        "WindowsTerminalOSS",
	        "WindowsTerminalDep",
	        "WindowsTerminalWIL"
        });
        
        // bPreprocessOnly = false;
        
        
		PrivateDependencyModuleNames.AddRange(new string[] { "UnrealTerminal" });
        
		PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "inc")});
		PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "terminal\\adapter")});
		PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "terminal\\input")});
		PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "terminal\\parser")});
		PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "tsf")});
		PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "types")});
		PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "renderer\\base")});
		PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "renderer\\inc")});
		PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "buffer\\out")});
		PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "cascadia\\TerminalCore")});
		PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "cascadia\\TerminalCore\\lib\\Generated Files")});

		// WIL 需要_WIN32_WINNT宏
		// PublicDefinitions.RemoveAll(ECFDefinition => ECFDefinition.StartsWith("_WIN32_WINNT"));
		//
		// PrivateDefinitions.RemoveAll(ECFDefinition => ECFDefinition.StartsWith("_WIN32_WINNT"));
		//
		//
		// PublicDefinitions.Add("_WIN32_WINNT=0x0A00"); // Windows10

		PublicAdditionalLibraries.Add("icuin.lib");
		PublicAdditionalLibraries.Add("icuuc.lib");
		PublicAdditionalLibraries.Add("Crypt32.lib");
		PublicAdditionalLibraries.Add("uiautomationcore.lib");
		PublicAdditionalLibraries.Add("runtimeobject.lib");
		PublicAdditionalLibraries.Add("shcore.lib");
		PublicAdditionalLibraries.Add("shlwapi.lib");
		PublicAdditionalLibraries.Add("pathcch.lib");
		PublicAdditionalLibraries.Add("propsys.lib");
		PublicAdditionalLibraries.Add("bcrypt.lib");
		PublicAdditionalLibraries.Add("ntdll.lib");
	}
}