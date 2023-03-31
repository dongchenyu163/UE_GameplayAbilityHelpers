// Fill out your copyright notice in the Description page of Project Settings.


#include "UFuncLib_GameplayAbilityHelper.h"

#include "UObject/SavePackage.h"
#include "ContentBrowserModule.h"
#include "EditorAssetLibrary.h"
#include "IContentBrowserSingleton.h"
#include "Dialogs/Dialogs.h"
#include "UI/UI_BuffStatusIndicatorBase.h"
#include "ClassViewerModule.h"
#include "GameplayEffect.h"
#include "AssetRegistry/AssetRegistryModule.h"

void UUFuncLib_GameplayAbilityHelper::CreateDataTableAsset_ForBuffIndicatorData(
	FGameplayTagQuery GameplayEffectAssetTagsQuery)
{
	TArray<UClass*> ClassList;
	TArray<FString> EffectAssetNameList;
	GetDerivedClasses(UGameplayEffect::StaticClass(), ClassList);

	for (auto ItClass = ClassList.CreateConstIterator(); ItClass; ++ItClass)
	{
		auto& ClassPtr = *ItClass;

		if (!GetDefault<UGameplayEffect>(ClassPtr)->InheritableGameplayEffectTags.CombinedTags.MatchesQuery(GameplayEffectAssetTagsQuery))
		{
			continue;
		}
		FString ClassDisplayName = ClassPtr->GetName();
		if (ClassDisplayName.Find("SKEL_", ESearchCase::CaseSensitive) != INDEX_NONE)
		{
			continue;
		}

		EffectAssetNameList.Add(ClassDisplayName.LeftChop(2));  // Remove last "_C" chars.
	}

	// Initialize SaveAssetDialog config
	FSaveAssetDialogConfig SaveAssetDialogConfig;
	SaveAssetDialogConfig.DialogTitleOverride = FText::FromString("Create datatable for BuffIndicatorViewData");
	SaveAssetDialogConfig.DefaultPath = "/Game";
	SaveAssetDialogConfig.DefaultAssetName = "DT_BuffIndicatorViewData";
	SaveAssetDialogConfig.ExistingAssetPolicy = ESaveAssetDialogExistingAssetPolicy::AllowButWarn;

	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	FString SaveObjectPath = ContentBrowserModule.Get().CreateModalSaveAssetDialog(SaveAssetDialogConfig);
	FString ObjectDirectory, ObjectName;
	SaveObjectPath.Split(".", &ObjectDirectory, &ObjectName);

	const bool bAssetExist = UEditorAssetLibrary::DoesAssetExist(ObjectDirectory);


	UDataTable* BuffIndicatorViewDataTable;
	if (bAssetExist)
	{
		BuffIndicatorViewDataTable = LoadObject<UDataTable>(nullptr, *SaveObjectPath);
	}
	else
	{
		FString SaveObjectPath2 = SaveObjectPath;
		auto Outer = CreatePackage(*ObjectDirectory);
		BuffIndicatorViewDataTable = NewObject<UDataTable>(Outer, FName(ObjectName));
		BuffIndicatorViewDataTable->SetFlags(RF_Public | RF_Transactional | RF_Standalone);
		Outer->FullyLoad();
		BuffIndicatorViewDataTable->RowStruct = FBuffIndicatorDataTableRow::StaticStruct();
	}

	for (auto ItStr = EffectAssetNameList.CreateConstIterator(); ItStr; ++ItStr)
    {
    	auto& RowName = *ItStr;

    	const bool bIsRowNotExist = BuffIndicatorViewDataTable->FindRowUnchecked(FName(RowName)) == nullptr;
    	if (bIsRowNotExist)
    	{
    		BuffIndicatorViewDataTable->AddRow(FName(RowName), FBuffIndicatorDataTableRow());
    	}
    }
	
	// if (bAssetExist)
	{
		UPackage* Package = BuffIndicatorViewDataTable->GetPackage();
		if (IsValid(Package))
		{
			Package->SetDirtyFlag(true);
			FString PackagePathInGame = Package->GetPathName(BuffIndicatorViewDataTable);
			FString FullPathInSystem = FPackageName::LongPackageNameToFilename(PackagePathInGame, FPackageName::GetAssetPackageExtension());
			FSavePackageArgs Args;
			Args.TopLevelFlags = RF_Public | RF_Transactional | RF_Standalone;
			FSavePackageResultStruct SavingResult = UPackage::Save(Package, BuffIndicatorViewDataTable, *FullPathInSystem, Args);
		}
	}
	// else
	// {
	// 	UPackage* Package = BuffIndicatorViewDataTable->GetPackage();
	// 	if (IsValid(Package))
	// 	{
	// 		// UEditorAssetLibrary::SaveAsset(SaveObjectPath, false);
	// 		Package->SetIsExternallyReferenceable(true);
	//
	// 		// Notify the asset registry
	// 		FAssetRegistryModule::AssetCreated(BuffIndicatorViewDataTable);
	//
	// 		// analytics create record
	// 		// FAssetRegistryModule::AssetSaved()
	// 		// UAssetToolsImpl::OnNewCreateRecord(AssetClass, false);
	//
	// 		// Mark the package dirty...
	// 		Package->MarkPackageDirty();
	//
	//
	// 		FString PackagePathInGame = Package->GetPathName(BuffIndicatorViewDataTable);
	// 		FString FullPathInSystem = FPackageName::LongPackageNameToFilename(PackagePathInGame, FPackageName::GetAssetPackageExtension());
	// 		FSavePackageArgs Args;
	// 		Args.TopLevelFlags = RF_Public | RF_Transactional | RF_Standalone;
	// 		FSavePackageResultStruct SavingResult = UPackage::Save(Package, BuffIndicatorViewDataTable, *FullPathInSystem, Args);
	// 	}
	// }
}
