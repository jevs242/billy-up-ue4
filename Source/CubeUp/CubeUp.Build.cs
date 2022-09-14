// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CubeUp : ModuleRules
{
	public CubeUp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" , "UMG" });
	}
}
