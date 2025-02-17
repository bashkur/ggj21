// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GGJ21 : ModuleRules
{
	public GGJ21(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",
			"UMG", "Slate", "SlateCore"
		});
	}
}
