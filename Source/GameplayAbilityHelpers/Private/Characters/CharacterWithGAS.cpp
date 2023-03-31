// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CharacterWithGAS.h"



// Sets default values
ACharacterWithGAS::ACharacterWithGAS()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	ActorTagsPtr = &ActorTags;
	AbilitySystemComponentImpl = AbilitySystemComponent;
	
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACharacterWithGAS::InitAnimation() const
{
	// if (!InitializeDataAssetPtr)
	// {
	// 	return;
	// }
	// // auto DataAssetPtr = InitializeDataAssetPtr;
	// // static auto DataAssetPtr = InitializeDataAssetPtr.LoadSynchronous();
	//
	// if (!InitializeDataAssetPtr->SkeletalMeshAsset.LoadSynchronous())
	// {
	// 	return;
	// }
	GetMesh()->SetSkeletalMesh(InitializeDataAssetPtr->SkeletalMeshAsset.LoadSynchronous());

	if (!InitializeDataAssetPtr->SkeletalMeshAnimationClass)
	{
		return;
	}
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimInstanceClass(InitializeDataAssetPtr->SkeletalMeshAnimationClass);
}

void ACharacterWithGAS::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!CheckAndLoadSoftObjectPtr(InitializeDataAssetPtr))
	{
		return;
	}

	if (!CheckAndLoadSoftObjectPtr(InitializeDataAssetPtr->SkeletalMeshAsset))
	{
		return;
	}
	
	const bool bIsInitializeDataAssetChanged = OldInitializeDataAssetPtr != InitializeDataAssetPtr;
	if (bIsInitializeDataAssetChanged)
	{
		InitGameplayAbilitySystem(InitializeDataAssetPtr);
		InitAnimation();
		OldInitializeDataAssetPtr = InitializeDataAssetPtr;
	}
}

void ACharacterWithGAS::InitGameplayAbilitySystem(
	const TSoftObjectPtr<UDA_GAS_ActorInitializeInfo>& InInitializeDataAssetPtr)
{
	FActorAbilityBasic::InitGameplayAbilitySystem(InInitializeDataAssetPtr);
	
	DefaultAbilities = InInitializeDataAssetPtr->DefaultAbilities;
	DefaultInitEffectList = InInitializeDataAssetPtr->DefaultInitEffectList;
}

// Called when the game starts or when spawned
void ACharacterWithGAS::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterWithGAS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterWithGAS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

