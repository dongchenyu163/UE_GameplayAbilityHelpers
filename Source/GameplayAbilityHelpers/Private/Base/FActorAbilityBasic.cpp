#include "Base/FActorAbilityBasic.h"

#include "GameplayAbilitySpec.h"
#include "AbilityHelperLog.h"

void FActorAbilityBasic::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	if (!ActorTagsPtr)
	{
		ULOG_ABILITYHELPERLOG_ERR("[ActorTagsPtr] is NULL, maybe forgot assign pointer in the child class");
		TagContainer = FGameplayTagContainer();
		return;
	}
	
	TagContainer = *ActorTagsPtr;
}

void FActorAbilityBasic::InitGameplayAbilitySystem(const TSoftObjectPtr<UDA_GAS_ActorInitializeInfo>& InInitializeDataAssetPtr)
{
	if (!InInitializeDataAssetPtr)
	{
		return;
	}
	
	// 配置默认存在于Actor的能力
	for (auto ItAbility = InInitializeDataAssetPtr->DefaultAbilities.CreateConstIterator(); ItAbility; ++ItAbility)
	{
		FGameplayAbilitySpec AbilitySpec = AbilitySystemComponentImpl->BuildAbilitySpecFromClass(*ItAbility);
		AbilitySystemComponentImpl->GiveAbility(AbilitySpec);
	}

	// 配置默认存在于Actor的【属性集】
	for (auto ItAttr = InInitializeDataAssetPtr->DefaultAttributeSetList.CreateConstIterator(); ItAttr; ++ItAttr)
	{
		AbilitySystemComponentImpl->InitStats(*ItAttr, nullptr);
	}

	// 本选项用来配置【属性集】的初始值：通过指定一系列Modifier，然后将其内部赋给一个临时的GameplayEffect，最终改变AttributeSet的初始值。
	{
		UGameplayEffect* TempEffectObj = NewObject<UGameplayEffect>();
		TempEffectObj->Modifiers = InInitializeDataAssetPtr->AttributeInitModifiers;
		// FGameplayEffectContextHandle aaa;
		// aaa.AddActors();
		// 这里的Self体现在AbilitySystemComponentImpl对象上。
		AbilitySystemComponentImpl->ApplyGameplayEffectToSelf(TempEffectObj, 0, FGameplayEffectContextHandle());
	}

	// 配置额外的初始【效果】
	for (auto ItEffectClass = InInitializeDataAssetPtr->DefaultInitEffectList.CreateConstIterator(); ItEffectClass; ++ItEffectClass)
	{
		// FGameplayEffectContextHandle EffectContextHandle;
		auto& EffectClass = *ItEffectClass;
		const UGameplayEffect* GameplayEffect = EffectClass->GetDefaultObject<UGameplayEffect>();
		AbilitySystemComponentImpl->ApplyGameplayEffectToSelf(GameplayEffect, 0, FGameplayEffectContextHandle());
	}

	// 配置该Actor初始状态下应具有的Tag
	*ActorTagsPtr = InInitializeDataAssetPtr->InitAddToActorTags;

}
