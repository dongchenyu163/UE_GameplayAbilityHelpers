// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/FActorAbilityBasic.h"
#include "Engine/StaticMeshActor.h"
#include "StaticMeshActorWithGAS.generated.h"

UCLASS()
class GAMEPLAYABILITYHELPERS_API AStaticMeshActorWithGAS : public AStaticMeshActor, public FActorAbilityBasic
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStaticMeshActorWithGAS();
	void SetupStaticMesh();

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void InitGameplayAbilitySystem(const TSoftObjectPtr<UDA_GAS_ActorInitializeInfo>& InInitializeDataAssetPtr) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Ability System 组件指针
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;

	// 蓝图指定用于初始化的DataAsset
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Initialize")
	TSoftObjectPtr<UDA_GAS_MeshActorInitializeInfo> InitializeDataAssetPtr = nullptr;
	TSoftObjectPtr<UDA_GAS_MeshActorInitializeInfo> OldInitializeDataAssetPtr = nullptr;

	// 仅保存
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	// 仅保存
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System")
	TArray<TSubclassOf<UGameplayEffect>> DefaultInitEffectList;

	// 本Actor当前具有的Tags，父类通过指针引用本变量。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tags")
	FGameplayTagContainer ActorTags;
};
