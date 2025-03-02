// 2017 - Community based open project

using UnrealBuildTool;

public class OceanProject : ModuleRules
{
	public OceanProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "OceanPlugin" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	}
}
