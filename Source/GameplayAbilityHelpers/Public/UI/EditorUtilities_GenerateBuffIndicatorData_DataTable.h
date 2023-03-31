// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#if WITH_EDITOR

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "UObject/Object.h"
#include "EditorUtilities_GenerateBuffIndicatorData_DataTable.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GAMEPLAYABILITYHELPERS_API UEditorUtilities_GenerateBuffIndicatorData_DataTable : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Asset List")
	void GetGameplayEffectAssetNameList(FGameplayTagQuery GameplayEffectAssetTagsQuery, TArray<FString>& OutEffectAssetNameList);
};

#endif
