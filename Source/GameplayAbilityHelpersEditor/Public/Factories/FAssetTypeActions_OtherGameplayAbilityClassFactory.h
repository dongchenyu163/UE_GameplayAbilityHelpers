#pragma once
#include "AssetTypeActions/AssetTypeActions_Blueprint.h"
// #include "Factories/Factory.h"


// class UFactory;

class FAssetTypeActions_OtherGameplayAbilityClassFactory : public FAssetTypeActions_Blueprint
{
public:
	virtual FText GetName() const override { return FText::FromString("Ability Classes"); }
	// IAssetTypeActions Implementation
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override { return EAssetTypeCategories::Gameplay; }
	// End IAssetTypeActions Implementation

	// FAssetTypeActions_Blueprint interface
	virtual UFactory* GetFactoryForBlueprintType(UBlueprint* InBlueprint) const override;

};