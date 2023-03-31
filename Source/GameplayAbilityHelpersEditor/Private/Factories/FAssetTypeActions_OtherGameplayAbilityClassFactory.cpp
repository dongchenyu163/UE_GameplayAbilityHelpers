#include "Factories/FAssetTypeActions_OtherGameplayAbilityClassFactory.h"

#include "GameplayEffect.h"
#include "Factories/DongGameplayEffectBlueprint.h"
#include "Factories/OtherGameplayAbilityClassFactory.h"


UClass* FAssetTypeActions_OtherGameplayAbilityClassFactory::GetSupportedClass() const
{
	return UDongGameplayEffectBlueprint::StaticClass();
	// return UGameplayEffect::StaticClass();
}

UFactory* FAssetTypeActions_OtherGameplayAbilityClassFactory::GetFactoryForBlueprintType(UBlueprint* InBlueprint) const
{
	UOtherGameplayAbilityClassFactory* GameplayAbilitiesBlueprintFactory = NewObject<UOtherGameplayAbilityClassFactory>();
	// GameplayAbilitiesBlueprintFactory->ParentClass = TSubclassOf<UGameplayAbility>(*InBlueprint->GeneratedClass);
	return GameplayAbilitiesBlueprintFactory;
}
