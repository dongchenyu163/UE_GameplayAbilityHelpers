// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshActorWithGAS.h"
#include "Base/AbilityHelperLog.h"
#include "Initialize/DA_GAS_MeshActorInitializeInfo.h"


// Sets default values
AStaticMeshActorWithGAS::AStaticMeshActorWithGAS()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	ActorTagsPtr = &ActorTags;
	AbilitySystemComponentImpl = AbilitySystemComponent;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AStaticMeshActorWithGAS::SetupStaticMesh()
{
	if (!InitializeDataAssetPtr)
	{
		return;
	}
	if (!InitializeDataAssetPtr->StaticMeshAsset)
	{
		ULOG_ABILITYHELPERLOG_ERR("StaticMeshAsset MUST be set in data asset [%s]", *(InitializeDataAssetPtr.ToString()));
		return;
	}

	GetStaticMeshComponent()->SetStaticMesh(InitializeDataAssetPtr->StaticMeshAsset.LoadSynchronous());
}

void AStaticMeshActorWithGAS::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	const bool bIsInitializeDataAssetChanged = OldInitializeDataAssetPtr != InitializeDataAssetPtr;
	if (bIsInitializeDataAssetChanged)
	{
		InitGameplayAbilitySystem(InitializeDataAssetPtr.Get());  // 因为TSoftObjectPtr无法直接进行类型转换，只能先转换成裸指针。
		SetupStaticMesh();
		OldInitializeDataAssetPtr = InitializeDataAssetPtr;
	}
}

void AStaticMeshActorWithGAS::InitGameplayAbilitySystem(
	const TSoftObjectPtr<UDA_GAS_ActorInitializeInfo>& InInitializeDataAssetPtr)
{
	if (!InitializeDataAssetPtr)
	{
		return;
	}
	FActorAbilityBasic::InitGameplayAbilitySystem(InInitializeDataAssetPtr);
}

// Called when the game starts or when spawned
void AStaticMeshActorWithGAS::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStaticMeshActorWithGAS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

