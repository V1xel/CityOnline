// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "CO/Actor/Street/Attributes/COSelectionAttributeSet.h"
#include "COSetSelectionAttributes.generated.h"

/**
 * 
 */
UCLASS()
class CO_API UCOSetSelectionAttributes : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	struct FSelectionAttributesCapture
	{
		//we must capture all ammo attributes from UAmmoAttributeSet
		DECLARE_ATTRIBUTE_CAPTUREDEF(SelectedCellsCount);

		FSelectionAttributesCapture()
		{
			DEFINE_ATTRIBUTE_CAPTUREDEF(UCOSelectionAttributeSet, SelectedCellsCount, Source, true);
		}
	};

public:
	UCOSetSelectionAttributes();
	
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecParams,
										FGameplayEffectCustomExecutionOutput& ExecOutputs) const override;

protected:
	FSelectionAttributesCapture mCapture{};
};
