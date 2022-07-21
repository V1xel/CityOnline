// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "CO/Actor/Player/Attributes/COSelectionAttributeSet.h"
#include "COSetSelectedActorEffect.generated.h"

/**
 * 
 */
UCLASS()
class CO_API UCOSetSelectedActorEffect : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	struct FSelectedActorEffectCapture
	{
		//we must capture all ammo attributes from UAmmoAttributeSet
		DECLARE_ATTRIBUTE_CAPTUREDEF(SelectedActor);

		FSelectedActorEffectCapture()
		{
			DEFINE_ATTRIBUTE_CAPTUREDEF(UCOSelectionAttributeSet, SelectedActor, Source, true);
		}
	};

public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecParams,
										FGameplayEffectCustomExecutionOutput& ExecOutputs) const override;

protected:
	FSelectedActorEffectCapture mCapture{};
};
