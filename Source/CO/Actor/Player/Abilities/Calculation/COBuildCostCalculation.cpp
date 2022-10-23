// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Actor/Player/Abilities/Calculation/COBuildCostCalculation.h"
#include "CO/Database/Tables/COBuildingTable.h"
#include "CO/Actor/Player/Attributes/COPlayerAttributeSet.h"
#include "CO/Actor/Player/Abilities/COBuildAbility.h"

void UCOBuildCostCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	auto Spec = ExecutionParams.GetOwningSpec();

	const UCOBuildAbility* Ability = Cast<UCOBuildAbility>(Spec.GetContext().GetAbilityInstance_NotReplicated());

	//auto Specialization = Ability->GetBuildingSpecialization();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Specialization.GetName());

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UCOPlayerAttributeSet::GetMoneyAttribute(), EGameplayModOp::Additive, 1));
}
