// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UFuncLib_GameplayAbilityHelper.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYABILITYHELPERS_API UUFuncLib_GameplayAbilityHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category="Asset List", meta=(ToolTip="创建DataTable资产，用于Gameplay Effect资产的UI显示（显示Buff状态时需要Buff的图标等）。自动扫描所有GameplayEffect资产，并以资产名称作为RowName存储在DataTable中。"))
	static void CreateDataTableAsset_ForBuffIndicatorData(FGameplayTagQuery GameplayEffectAssetTagsQuery);
};
