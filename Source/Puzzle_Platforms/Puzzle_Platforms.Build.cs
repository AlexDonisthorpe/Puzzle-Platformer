// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Puzzle_Platforms : ModuleRules
{
	public Puzzle_Platforms(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "OnlineSubsystem", "OnlineSubsystemSteam" });
	}
}
