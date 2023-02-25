// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Actor/Player/Abilities/Calculation/COBuildCostCalculation.h"
#include "CO/Actor/Player/Attributes/COPlayerAttributeSet.h"
#include "CO/Core/AbilitySystem/COGameplayEffectContext.h"
#include "CO/Actor/Player/Abilities/Build/TargetData/COBuildAllocationTD.h"
#include "CO/Actor/Player/Abilities/Build/TargetData/COBuildConfigurationTD.h"
#include "CO/Actor/Player/Abilities/Build/TargetData/COBuildRequirementsTD.h"
#include <CO/Actor/Player/Abilities/Build/COBuildAbility.h>
#include <CO/Core/AbilitySystem/COAbilitySystemFunctionLibrary.h>
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"

void UCOBuildCostCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	auto Spec = ExecutionParams.GetOwningSpec();
	auto EffectContext = Spec.GetEffectContext();
	auto Ability = Cast<UCOBuildAbility>(EffectContext.GetAbility());
	FGameplayTagContainer TagContainer;
	Ability->TargetBuildPreviewEffect.GetDefaultObject()->GetOwnedGameplayTags(TagContainer);
	auto Target = UCOAbilitySystemFunctionLibrary::GetTargetActorFromEffectByTag(ExecutionParams.GetSourceAbilitySystemComponent(), Ability->StreetSelectedTag);
	auto TargetASC = Cast<IAbilitySystemInterface>(Target)->GetAbilitySystemComponent();

	auto Effect = TargetASC->GetActiveEffects(FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(TagContainer)).Last();
	auto TrueEffectContext = TargetASC->GetEffectContextFromActiveGEHandle(Effect);

	auto TargetData = static_cast<FCOGameplayEffectContext*>(TrueEffectContext.Get())->TargetData;
	auto BuildRequirements = static_cast<const FCOBuildRequirementsTD*>(TargetData.Get(0));
	auto BuildConfiguration = static_cast<const FCOBuildConfigurationTD*>(TargetData.Get(1));
	auto BuildAllocation = static_cast<const FCOBuildAllocationTD*>(TargetData.Get(2));
	auto CellsCount = BuildAllocation->Cells.Num();

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UCOPlayerAttributeSet::GetMoneyAttribute(), EGameplayModOp::Additive, BuildConfiguration->Floors * CellsCount * -BuildRequirements->CostMultiplier));
}
