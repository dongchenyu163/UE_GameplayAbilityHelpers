#include "GameplayAbilityHelpersEditor.h"

#include "Factories/FAssetTypeActions_OtherGameplayAbilityClassFactory.h"
// #include "Factories/OtherGameplayAbilityClassFactory.h"

#define LOCTEXT_NAMESPACE "FGameplayAbilityHelpersEditorModule"

void FGameplayAbilityHelpersEditorModule::StartupModule()
{
	// Register asset types
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	TSharedRef<IAssetTypeActions> GABAction = MakeShareable(new FAssetTypeActions_OtherGameplayAbilityClassFactory());
	AssetTools.RegisterAssetTypeActions(GABAction);
	CreatedAssetTypeActions.Add(GABAction);
}

void FGameplayAbilityHelpersEditorModule::ShutdownModule()
{
	// Unregister all the asset types that we registered
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 Index = 0; Index < CreatedAssetTypeActions.Num(); ++Index)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[Index].ToSharedRef());
		}
	}
	CreatedAssetTypeActions.Empty();
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FGameplayAbilityHelpersEditorModule, GameplayAbilityHelpersEditor)