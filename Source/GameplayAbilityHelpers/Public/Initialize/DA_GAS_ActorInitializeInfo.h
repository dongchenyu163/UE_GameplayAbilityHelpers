// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DA_GAS_ActorInitializeInfo.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYABILITYHELPERS_API UDA_GAS_ActorInitializeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	// 配置默认存在于Actor的能力
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability System")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	// 配置默认存在于Actor的【属性集】
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability System")
	TArray<TSubclassOf<UAttributeSet>> DefaultAttributeSetList;

	// 本选项用来配置【属性集】的初始值：通过指定一系列Modifier，然后将其内部赋给一个临时的GameplayEffect，最终改变AttributeSet的初始值。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ability System")
	TArray<FGameplayModifierInfo> AttributeInitModifiers;

	// 配置额外的初始【效果】
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability System")
	TArray<TSubclassOf<UGameplayEffect>> DefaultInitEffectList;

	// 配置该Actor初始状态下应具有的Tag
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability System")
	FGameplayTagContainer InitAddToActorTags;
	
};
