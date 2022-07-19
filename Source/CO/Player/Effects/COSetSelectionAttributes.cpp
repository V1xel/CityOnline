// Fill out your copyright notice in the Description page of Project Settings.


#include "COSetSelectionAttributes.h"

UCOSetSelectionAttributes::UCOSetSelectionAttributes()
{
	RelevantAttributesToCapture.Add(mCapture.SelectedCellsCountDef);
}

void UCOSetSelectionAttributes::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecParams,
                                                       FGameplayEffectCustomExecutionOutput& ExecOutputs) const
{
	Super::Execute_Implementation(ExecParams, ExecOutputs);

	float selectedCellsCount{};

	if(!ExecParams.AttemptCalculateCapturedAttributeMagnitude(
		mCapture.SelectedCellsCountDef, FAggregatorEvaluateParameters{}, selectedCellsCount))
	{
		UE_LOG(LogTemp, Error,
			TEXT("Failed to get selected cells count")
		);
	}

	ExecOutputs.AddOutputModifier(FGameplayModifierEvaluatedData(
			mCapture.SelectedCellsCountProperty, EGameplayModOp::Additive, selectedCellsCount));
}
