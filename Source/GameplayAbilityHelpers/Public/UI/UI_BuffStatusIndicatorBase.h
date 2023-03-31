// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "UObject/Object.h"
#include "UI_BuffStatusIndicatorBase.generated.h"


USTRUCT(BlueprintType)
struct FBuffIndicatorDataTableRow : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="View")
	TSoftObjectPtr<UTexture2D> BuffIcon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="View")
	FVector2D ShowingSize = FVector2d(64, 64);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="View")
	float DarkenCoefficient = 0.2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="View")
	float RefreshFrequency = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Text")
	bool bIsShowCDTime = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Text", meta=(EditCondition="bIsShowCDTime==true"))
	FSlateFontInfo Font_CDTime = FSlateFontInfo("Roboto", 56);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Text", meta=(EditCondition="bIsShowCDTime==true"))
	FLinearColor TextColor_CDTime = FLinearColor::White;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Text")
	bool bIsShowStackCount = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Text", meta=(EditCondition="bIsShowStackCount==true"))
	FSlateFontInfo Font_StackCount = FSlateFontInfo("Roboto", 56);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Text", meta=(EditCondition="bIsShowStackCount==true"))
	FLinearColor TextColor_StackCount = FLinearColor::White;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Advanced")
	TSoftObjectPtr<UMaterial> BuffMaterial = TSoftObjectPtr<UMaterial>(FSoftObjectPath("/Script/Engine.Material'/GameplayAbilityHelpers/UI/MAT_RotateProgressBar.MAT_RotateProgressBar'"));
};


/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
// UCLASS()
class GAMEPLAYABILITYHELPERS_API UUI_BuffStatusIndicatorBase : public UUserWidget
{
	GENERATED_BODY()

public:
	// UUI_BuffStatusIndicatorBase();
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

#if WITH_EDITOR
	virtual void PostCDOCompiled(const FPostCDOCompiledContext& Context) override;
#endif
protected:
	void HandleTimer_OnRefreshBuffDisplay();

	/**
	 * @brief 蓝图覆盖专用，每回刷新显示的时候调用。
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="Update")
	void OnRefreshBuffDisplay();
	
public:
	// UPROPERTY(meta=(ExposeOnSpawn))
	// TSoftObjectPtr<UMaterial> BuffMaterial;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="", meta=(ExposeOnSpawn))
	// FName MonitorEffectAssetName;
	//
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="", meta=(ExposeOnSpawn))
	// UDataTable* DT_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Design Param", meta=(ExposeOnSpawn))
	FBuffIndicatorDataTableRow MonitorEffectViewData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Design Param")
	FName Name_ImageWidget_SkillImage = FName("Img_SkillImage");
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Design Param")
	FName Name_TextWidget_CDTime = FName("Text_CDTime");
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Design Param")
	FName Name_TextWidget_StackTime = FName("Text_StackCount");

	UPROPERTY(BlueprintReadWrite, Category="Runtime")
	UAbilitySystemComponent* AbilityComp = nullptr;
	
	UPROPERTY(BlueprintReadWrite, Category="Runtime")
	float RefreshTimeInterval = 0.0;
	
	UPROPERTY(BlueprintReadWrite, Category="Runtime")
	UMaterialInstanceDynamic* BuffDynamicMaterial = nullptr;


	UPROPERTY(EditAnywhere, Category="Design Param|Material Param(Auto generated)")
	TMap<FName, float> MaterialParamDict_Scalar;
	UPROPERTY(EditAnywhere, Category="Design Param|Material Param(Auto generated)")
	TMap<FName, FVector> MaterialParamDict_Vector;
	UPROPERTY(EditAnywhere, Category="Design Param|Material Param(Auto generated)")
	TMap<FName, FVector4> MaterialParamDict_DoubleVector;
	UPROPERTY(EditAnywhere, Category="Design Param|Material Param(Auto generated)")
	TMap<FName, UTexture2D*> MaterialParamDict_Texture;

	FTimerHandle Timer_RefreshBuffDisplay; // Copy to property

};
