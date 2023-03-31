#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Initialize/DA_GAS_ActorInitializeInfo.h"


/**
*
*
头文件：
	继承：  , public FActorAbilityBasic
public:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void InitGameplayAbilitySystem(const TSoftObjectPtr<UDA_GAS_ActorInitializeInfo>& InInitializeDataAssetPtr) override;

protected:
	// Ability System 组件指针
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;

	// 蓝图指定用于初始化的DataAsset
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Initialize")
	TSoftObjectPtr<UDA_GAS_ActorInitializeInfo> InitializeDataAssetPtr = nullptr;
	TSoftObjectPtr<UDA_GAS_ActorInitializeInfo> OldInitializeDataAssetPtr = nullptr;

	// 仅保存
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	// 仅保存
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System")
	TArray<TSubclassOf<UGameplayEffect>> DefaultInitEffectList;

	// 本Actor当前具有的Tags，父类通过指针引用本变量。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tags")
	FGameplayTagContainer ActorTags;

构造函数：
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	ActorTagsPtr = &ActorTags;
	AbilitySystemComponentImpl = AbilitySystemComponent;
	
覆盖InitGameplayAbilitySystem，并添加
	FActorAbilityBasic::InitGameplayAbilitySystem(InInitializeDataAssetPtr);
	DefaultAbilities = InInitializeDataAssetPtr->DefaultAbilities;
	DefaultInitEffectList = InInitializeDataAssetPtr->DefaultInitEffectList;

覆盖OnConstruction，并添加
	const bool bIsInitializeDataAssetChanged = OldInitializeDataAssetPtr != InitializeDataAssetPtr;
	if (bIsInitializeDataAssetChanged)
	{
		InitGameplayAbilitySystem(InitializeDataAssetPtr);
		OldInitializeDataAssetPtr = InitializeDataAssetPtr;
	}
 */
class GAMEPLAYABILITYHELPERS_API FActorAbilityBasic : public IAbilitySystemInterface, public IGameplayTagAssetInterface
{
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponentImpl; }
    virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	virtual void InitGameplayAbilitySystem(const TSoftObjectPtr<UDA_GAS_ActorInitializeInfo>& InInitializeDataAssetPtr);

	template<typename ObjectType>
	static bool CheckAndLoadSoftObjectPtr(TSoftObjectPtr<ObjectType> InSoftObjPtr)
	{
		if (InSoftObjPtr.IsNull())
		{
			return false;
		}
		if (!InSoftObjPtr.IsValid())
		{
			InSoftObjPtr.LoadSynchronous();
		}
		return true;
	}

protected:
	UAbilitySystemComponent* AbilitySystemComponentImpl = nullptr;
	
	// 需要手动指向子类的TagContainer成员内存：FActorAbilityBasic类成员，指向子类的TagContainer成员内存，免除子类实装【GetOwnedGameplayTags】函数。
    FGameplayTagContainer* ActorTagsPtr = nullptr;
};
