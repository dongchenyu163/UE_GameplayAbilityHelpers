// Fill out your copyright notice in the Description page of Project Settings.


#include "Factories/OtherGameplayAbilityClassFactory.h"

#include "AnimNotify_GameplayCue.h"
#include "AssetTypeCategories.h"
#include "ClassViewerModule.h"
#include "GameplayCueNotify_Actor.h"
#include "GameplayCueNotify_Static.h"
#include "GameplayEffect.h"
#include "GameplayEffectCalculation.h"
#include "GameplayEffectCustomApplicationRequirement.h"
#include "GameplayEffectUIData.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "ClassViewer/Private/UnloadedBlueprintData.h"
#include "Factories/DongGameplayEffectBlueprint.h"
#include "Kismet2/SClassPickerDialog.h"


UOtherGameplayAbilityClassFactory::UOtherGameplayAbilityClassFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UDongGameplayEffectBlueprint::StaticClass();
	// SupportedClass = UGameplayEffect::StaticClass();
}

FString UOtherGameplayAbilityClassFactory::GetDefaultNewAssetName() const
{
	if (ParentClass == UGameplayAbility::StaticClass())
	{
		return FString("GA_");
	}
	// if (ParentClass == UGameplayTask::StaticClass())
	// {
	// 	return FString("GTask_");
	// }
	if (ParentClass == UGameplayEffect::StaticClass())
	{
		return FString("GE_");
	}
	if (ParentClass == AGameplayCueNotify_Actor::StaticClass())
	{
		return FString("CueNotify_");
	}
	if (ParentClass == UGameplayEffectUIData::StaticClass())
	{
		return FString("GEUIDAT_");
	}
	return Super::GetDefaultNewAssetName();
}

class FGameplayAbilityBlueprintParentFilter : public IClassViewerFilter
{
public:
	/** All children of these classes will be included unless filtered out by another setting. */
	TSet< const UClass* > AllowedChildrenOfClasses;

	FGameplayAbilityBlueprintParentFilter() {}

	virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override
	{
		// If it appears on the allowed child-of classes list (or there is nothing on that list)
		return InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InClass) != EFilterReturn::Failed;
	}

	virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef< const IUnloadedBlueprintData > InUnloadedClassData, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override
	{
		// If it appears on the allowed child-of classes list (or there is nothing on that list)
		return InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InUnloadedClassData) != EFilterReturn::Failed;
	}
};

bool UOtherGameplayAbilityClassFactory::ConfigureProperties()
{
	{
		FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");

		// Fill in options
		FClassViewerInitializationOptions Options;
		Options.DisplayMode = EClassViewerDisplayMode::Type::TreeView;
		Options.Mode = EClassViewerMode::ClassPicker;
		Options.bShowNoneOption = false;
		Options.bExpandAllNodes = true;

		TSharedPtr<FGameplayAbilityBlueprintParentFilter> Filter = MakeShareable(new FGameplayAbilityBlueprintParentFilter);
		Options.ClassFilters.Add(Filter.ToSharedRef());
		Options.ExtraPickerCommonClasses.Add(UGameplayAbility::StaticClass());
		// Options.ExtraPickerCommonClasses.Add(UGameplayTask::StaticClass());
		Options.ExtraPickerCommonClasses.Add(UGameplayEffect::StaticClass());
		Options.ExtraPickerCommonClasses.Add(AGameplayCueNotify_Actor::StaticClass());
		Options.ExtraPickerCommonClasses.Add(UGameplayEffectUIData::StaticClass());
		
		Filter->AllowedChildrenOfClasses.Add(AGameplayAbilityTargetActor::StaticClass());
		Filter->AllowedChildrenOfClasses.Add(AGameplayAbilityWorldReticle::StaticClass());
		Filter->AllowedChildrenOfClasses.Add(UGameplayCueNotify_Static::StaticClass());
		Filter->AllowedChildrenOfClasses.Add(UGameplayEffectCalculation::StaticClass());
		Filter->AllowedChildrenOfClasses.Add(UGameplayEffectCustomApplicationRequirement::StaticClass());
		Filter->AllowedChildrenOfClasses.Add(UAnimNotify_GameplayCue::StaticClass());
		Filter->AllowedChildrenOfClasses.Add(UAnimNotify_GameplayCueState::StaticClass());

		const FText TitleText = FText::FromString("Pick Base Class for other Ability class");

		UClass* ChosenParentClass = nullptr;
		SClassPickerDialog::PickClass(TitleText, Options, ChosenParentClass, UGameplayEffect::StaticClass());
		ParentClass = ChosenParentClass ? ChosenParentClass : UGameplayEffect::StaticClass();
	}
	return true;
}

// UObject* UOtherGameplayAbilityClassFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name,
// 	EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
// {
// 	return Super::FactoryCreateNew(Class, InParent, Name, Flags, Context, Warn, CallingContext);
// }
//
// UObject* UOtherGameplayAbilityClassFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name,
// 	EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
// {
// 	return FactoryCreateNew(Class, InParent, Name, Flags, Context, Warn, NAME_None);
// }

