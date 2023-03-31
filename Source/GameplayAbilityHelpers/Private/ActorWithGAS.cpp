// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorWithGAS.h"

#include "Initialize/DA_GAS_ActorInitializeInfo.h"

// Sets default values
AActorWithGAS::AActorWithGAS()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	ActorTagsPtr = &ActorTags;
	AbilitySystemComponentImpl = AbilitySystemComponent;
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AActorWithGAS::InitGameplayAbilitySystem(const TSoftObjectPtr<UDA_GAS_ActorInitializeInfo>& InInitializeDataAssetPtr)
{
	FActorAbilityBasic::InitGameplayAbilitySystem(InInitializeDataAssetPtr);

	DefaultAbilities = InInitializeDataAssetPtr->DefaultAbilities;
	DefaultInitEffectList = InInitializeDataAssetPtr->DefaultInitEffectList;
}

// Called when the game starts or when spawned
void AActorWithGAS::BeginPlay()
{
	Super::BeginPlay();
	
}

void AActorWithGAS::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	const bool bIsInitializeDataAssetChanged = OldInitializeDataAssetPtr != InitializeDataAssetPtr;
	if (bIsInitializeDataAssetChanged)
	{
		InitGameplayAbilitySystem(InitializeDataAssetPtr);
		OldInitializeDataAssetPtr = InitializeDataAssetPtr;
	}
}

// Called every frame
void AActorWithGAS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

