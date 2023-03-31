// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletalMeshActorWithGAS.h"

#include "Initialize/DA_GAS_MeshActorInitializeInfo.h"


// Sets default values
ASkeletalMeshActorWithGAS::ASkeletalMeshActorWithGAS()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	ActorTagsPtr = &ActorTags;
	AbilitySystemComponentImpl = AbilitySystemComponent;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASkeletalMeshActorWithGAS::InitAnimation() const
{
	if (!InitializeDataAssetPtr.IsNull())
	{
		return;
	}
	if (!InitializeDataAssetPtr->SkeletalMeshAsset.IsNull())
	{
		return;
	}
	GetSkeletalMeshComponent()->SetSkeletalMesh(InitializeDataAssetPtr->SkeletalMeshAsset.LoadSynchronous());

	if (!InitializeDataAssetPtr->SkeletalMeshAnimationClass)
	{
		return;
	}
	GetSkeletalMeshComponent()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetSkeletalMeshComponent()->SetAnimInstanceClass(InitializeDataAssetPtr->SkeletalMeshAnimationClass);
}

void ASkeletalMeshActorWithGAS::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	const bool bIsInitializeDataAssetChanged = OldInitializeDataAssetPtr != InitializeDataAssetPtr;
	if (bIsInitializeDataAssetChanged)
	{
		InitGameplayAbilitySystem(InitializeDataAssetPtr.Get());  // 因为TSoftObjectPtr无法直接进行类型转换，只能先转换成裸指针。
		InitAnimation();
		OldInitializeDataAssetPtr = InitializeDataAssetPtr;
	}
}

void ASkeletalMeshActorWithGAS::InitGameplayAbilitySystem(
	const TSoftObjectPtr<UDA_GAS_ActorInitializeInfo>& InInitializeDataAssetPtr)
{
	if (!InitializeDataAssetPtr)
	{
		return;
	}
	FActorAbilityBasic::InitGameplayAbilitySystem(InInitializeDataAssetPtr);
	
	DefaultAbilities = InInitializeDataAssetPtr->DefaultAbilities;
	DefaultInitEffectList = InInitializeDataAssetPtr->DefaultInitEffectList;
}

// Called when the game starts or when spawned
void ASkeletalMeshActorWithGAS::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkeletalMeshActorWithGAS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

