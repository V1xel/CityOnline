// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Actor/Player/Abilities/Calculation/COBuildCostCalculation.h"
#include "CO/Database/Tables/COBuildingTable.h"
#include "CO/Actor/Player/Attributes/COPlayerAttributeSet.h"
#include "CO/Actor/Player/Abilities/Build/COBuildAbility.h"
#include <CO/Core/AbilitySystem/COGameplayEffectContext.h>
#include "CO/Actor/Player/Abilities/TargetData/COBuildConfigurationTD.h"

void UCOBuildCostCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UCOPlayerAttributeSet::GetMoneyAttribute(), EGameplayModOp::Additive, 25.0f));
}
