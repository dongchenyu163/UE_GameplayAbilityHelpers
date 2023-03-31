// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DA_GAS_ActorInitializeInfo.h"
#include "UObject/Object.h"
#include "DA_GAS_MeshActorInitializeInfo.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYABILITYHELPERS_API UDA_GAS_MeshActorInitializeInfo : public UDA_GAS_ActorInitializeInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="StaticMesh", meta=(EditCondition="SkeletalMeshAsset == nullptr"))
	TSoftObjectPtr<UStaticMesh> StaticMeshAsset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SkeletalMesh", meta=(EditCondition="StaticMeshAsset == nullptr"))
	TSoftObjectPtr<USkeletalMesh> SkeletalMeshAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SkeletalMesh", meta=(EditCondition="StaticMeshAsset == nullptr"))
	TSubclassOf<UAnimInstance> SkeletalMeshAnimationClass;

};
