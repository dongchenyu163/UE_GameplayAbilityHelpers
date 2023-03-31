using UnrealBuildTool;

public class GameplayAbilityHelpersEditor : ModuleRules
{
    public GameplayAbilityHelpersEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "UnrealEd", 
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UnrealEd", "GameplayAbilities",
                "AssetTools"
            }
        );
    }
}