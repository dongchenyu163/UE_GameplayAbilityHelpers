// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "UObject/Object.h"
// #include "Toolkits/IToolkitHost.h"
#include "AssetTypeActions/AssetTypeActions_Blueprint.h"
#include "Factories/BlueprintFactory.h"
#include "OtherGameplayAbilityClassFactory.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYABILITYHELPERSEDITOR_API UOtherGameplayAbilityClassFactory : public UBlueprintFactory
{
	GENERATED_BODY()

	UOtherGameplayAbilityClassFactory(const FObjectInitializer& ObjectInitializer);
	// // The type of blueprint that will be created
	// UPROPERTY(EditAnywhere, Category=OtherGameplayAbilityClassFactory)
	// TEnumAsByte<enum EBlueprintType> BlueprintType;
	//
	// // The parent class of the created blueprint
	// UPROPERTY(EditAnywhere, Category=OtherGameplayAbilityClassFactory, meta=(AllowAbstract = ""))
	// UClass* ParentClass;

public:
	// virtual uint32 GetMenuCategories() const override;

private:
	virtual FString GetDefaultNewAssetName() const override;
	//~ Begin UFactory Interface
	virtual bool ConfigureProperties() override;
	// virtual bool ShouldShowInNewMenu() const override;
	// virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;
	// virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

