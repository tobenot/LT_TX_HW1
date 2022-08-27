// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RT_Hwork1CPP : ModuleRules
{
	public RT_Hwork1CPP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
