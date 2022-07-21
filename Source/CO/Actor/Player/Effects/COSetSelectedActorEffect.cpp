// Fill out your copyright notice in the Description page of Project Settings.


#include "COSetSelectedActorEffect.h"

void UCOSetSelectedActorEffect::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecParams,
	FGameplayEffectCustomExecutionOutput& ExecOutputs) const
{
	Super::Execute_Implementation(ExecParams, ExecOutputs);
	/*AActor* selectedCellsCount;

	if(!ExecParams.(
		mCapture.SelectedActorDef, FAggregatorEvaluateParameters{}, selectedCellsCount))
	{
		UE_LOG(LogTemp, Error,
			TEXT("Failed to get selected cells count")
		);
	}

	ExecOutputs.GetOutputModifiers(FGameplayModifierEvaluatedData(
			mCapture.SelectedActorProperty, EGameplayModOp::Additive, selectedCellsCount));*/
}
