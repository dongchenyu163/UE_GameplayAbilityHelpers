// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UI_BuffStatusIndicatorBase.h"

#include "Blueprint/WidgetTree.h"
#include "Base/AbilityHelperLog.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

// UUI_BuffStatusIndicatorBase::UUI_BuffStatusIndicatorBase(): BuffMaterial()
// {
// 	// BuffMaterial->parameter
// }

#if WITH_EDITOR


void UUI_BuffStatusIndicatorBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!MonitorEffectViewData.BuffIcon.IsValid())
	{
		MonitorEffectViewData.BuffIcon.LoadSynchronous();
	}
	if (!MonitorEffectViewData.BuffMaterial.IsValid())
	{
		MonitorEffectViewData.BuffMaterial.LoadSynchronous();
	}

	RefreshTimeInterval = 1 / MonitorEffectViewData.RefreshFrequency;

	// 扫描所有Material参数，存储在TMap中
	// GetAllParameterInfoOfType GetAllParametersOfType
	// GetAllParametersOfType
	TMap<FMaterialParameterInfo, FMaterialParameterMetadata> OutParameters;
	TArray<FMaterialParameterInfo> OutParameterInfo;
	TArray<FGuid> OutParameterIds;
	MonitorEffectViewData.BuffMaterial->GetAllParameterInfoOfType(EMaterialParameterType::Scalar, OutParameterInfo, OutParameterIds);
	// MonitorEffectViewData.BuffMaterial->GetAllParametersOfType(EMaterialParameterType::Scalar, OutParameters);
	// FHashedMaterialParameterInfo()
	// MonitorEffectViewData.BuffMaterial->GetScalarParameterValue()
	// OutParameters[0];
	// OutParameterInfo[0].Name
}

void UUI_BuffStatusIndicatorBase::NativeConstruct()
{
	Super::NativeConstruct();

	UImage* ImageWidget_SkillImage = WidgetTree->FindWidget<UImage>(Name_ImageWidget_SkillImage);
	UTextBlock* TextWidget_CDTime = WidgetTree->FindWidget<UTextBlock>(Name_TextWidget_CDTime);
	UTextBlock* TextWidget_StackTime = WidgetTree->FindWidget<UTextBlock>(Name_TextWidget_StackTime);
	if (!IsValid(ImageWidget_SkillImage) || !IsValid(TextWidget_CDTime) || !IsValid(TextWidget_StackTime))
	{
		ULOG_ABILITYHELPERLOG_ERR("Invalid widget pointer: SkillImage:[%p] CDTime:[%p] StackTime:[%p]");
		ULOG_ABILITYHELPERLOG_ERR("Check the name property is right?");
		return;
	}

	ImageWidget_SkillImage->SetBrushFromSoftMaterial(MonitorEffectViewData.BuffMaterial);
	BuffDynamicMaterial = ImageWidget_SkillImage->GetDynamicMaterial();
	// BuffDynamicMaterial->Setvec
	// BuffDynamicMaterial->param
		
	FTimerManager& TimeManager = GetWorld()->GetTimerManager(); // Uncomment if need.
	TimeManager.SetTimer(Timer_RefreshBuffDisplay,
						 FTimerDelegate::CreateUObject(this, &UUI_BuffStatusIndicatorBase::HandleTimer_OnRefreshBuffDisplay),
						 RefreshTimeInterval, true, 0);
}

void UUI_BuffStatusIndicatorBase::HandleTimer_OnRefreshBuffDisplay()
{
	OnRefreshBuffDisplay();
}

void UUI_BuffStatusIndicatorBase::PostCDOCompiled(const FPostCDOCompiledContext& Context)
{
	Super::PostCDOCompiled(Context);
	// Scalar
	// Vector,
	// DoubleVector,
	// Texture,
	// Font,
	// RuntimeVirtualTexture,
	// BuffMaterial->GetAllParameterInfoOfType(EMaterialParameterType::Num);
}
#endif
