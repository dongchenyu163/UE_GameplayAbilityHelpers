// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PawnWithGAS.h"


// Sets default values
APawnWithGAS::APawnWithGAS()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	ActorTagsPtr = &ActorTags;
	AbilitySystemComponentImpl = AbilitySystemComponent;
	
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APawnWithGAS::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	const bool bIsInitializeDataAssetChanged = OldInitializeDataAssetPtr != InitializeDataAssetPtr;
	if (bIsInitializeDataAssetChanged)
	{
		InitGameplayAbilitySystem(InitializeDataAssetPtr);
		OldInitializeDataAssetPtr = InitializeDataAssetPtr;
	}
}

void APawnWithGAS::InitGameplayAbilitySystem(
	const TSoftObjectPtr<UDA_GAS_ActorInitializeInfo>& InInitializeDataAssetPtr)
{
	FActorAbilityBasic::InitGameplayAbilitySystem(InInitializeDataAssetPtr);
	
	DefaultAbilities = InInitializeDataAssetPtr->DefaultAbilities;
	DefaultInitEffectList = InInitializeDataAssetPtr->DefaultInitEffectList;
}

// Called when the game starts or when spawned
void APawnWithGAS::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnWithGAS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APawnWithGAS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

