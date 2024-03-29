﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildAbility.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "TargetData/COBuildAllocationTD.h"
#include "TargetData/COBuildConfigurationTD.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Actor/Player/Abilities/Helpers/COAllocateHelper.h"
#include "CO/Core/AbilitySystem/COGameplayEffectContext.h"
#include <CO/Core/AbilitySystem/COGameplayEffectContextHandle.h>
#include <CO/Core/AbilitySystem/COAbilitySystemFunctionLibrary.h>
#include "GameplayEffectExecutionCalculation.h"
#include "AbilitySystemGlobals.h"
#include "CO/Actor/Player/Attributes/COPlayerAttributeSet.h"

bool UCOBuildAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return true;
}

bool UCOBuildAbility::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const
{
	auto baseCheck = Super::CheckCost(Handle, ActorInfo, OptionalRelevantTags);
	if (!baseCheck)
		return false;

	UGameplayEffect* CostGE = GetCostGameplayEffect();

	auto ASC = ActorInfo->AbilitySystemComponent.Get();
	auto Spec = FGameplayEffectSpec(CostGE, MakeEffectContext(Handle, ActorInfo));

	auto CostCalculator = CostGE->Executions.Last().CalculationClass.GetDefaultObject();
	auto CalculationInput = FGameplayEffectCustomExecutionParameters(Spec, TArray<FGameplayEffectExecutionScopedModifierInfo>(), ASC, FGameplayTagContainer(), FPredictionKey());
	auto CalculationOutput = FGameplayEffectCustomExecutionOutput();

	CostCalculator->Execute(CalculationInput, CalculationOutput);

	auto Modifiers = CalculationOutput.GetOutputModifiers();
	auto CalculatedModifier = Modifiers.Last();
	auto Value = ASC->GetNumericAttribute(UCOPlayerAttributeSet::GetMoneyAttribute());

	return Value + CalculatedModifier.Magnitude > 0;
}

void UCOBuildAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	_OnBuildConfirmedDH = AddGETagDelegate(ListenEventOnBuildConfirmed, FGEDelegate::CreateUObject(this, &UCOBuildAbility::OnAllocateCancelOrConfirm));
	_OnBuildCanceledDH = AddGETagDelegate(ListenEventOnBuildCanceled, FGEDelegate::CreateUObject(this, &UCOBuildAbility::OnAllocateCancelOrConfirm));
	_OnAllocationFinishedDH = AddGETagDelegate(ListenEventOnAllocationFinished, FGEDelegate::CreateUObject(this, &UCOBuildAbility::OnAllocationFinished));
	_OnConfigurationUpdatedDH = AddGETagDelegate(ListenEventOnConfigurationUpdated, FGEDelegate::CreateUObject(this, &UCOBuildAbility::OnConfigurationUpdated));

	auto BuildPerformingEffectContext = FCOGameplayEffectContextHandle(ActorInfo->OwnerActor.Get());
	BuildPerformingEffectContext.SetTargetData(UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(const_cast<AActor*>(TriggerEventData->Target.Get())));
	//Adding player effect to track build ability is in progress, block other abilities
	_PlayerPerformingBuildEffectHandle = ApplyGESpecToOwner(BuildPerformingEffectContext.MakeGESpec(PlayerPerformingBuildEffect));

	_BuildRequirementsDataHandle = BuildingsTable->FindRow<FCOBuildingTable>(FCOBuildConfigurationTD::GetBuildingName(TriggerEventData->TargetData), "")->ToBuildTargetDataHandle();
	auto EffectContext = FCOGameplayEffectContextHandle(ActorInfo->OwnerActor.Get(), _BuildRequirementsDataHandle);
	//Adding player effect to allow allocating the cells for building placing
	_AllocationEffectHandle = ApplyGESpecToOwner(EffectContext.MakeGESpec(PlayerAllocatePermissionEffect));

	_ConfigurationDTOTargetDataHandle = TriggerEventData->TargetData;
}

void UCOBuildAbility::OnAllocationFinished(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	_SelectionDTOTargetDataHandle = EventData->TargetData;

	RemoveActiveGameplayEffect(_AllocationEffectHandle);
	_AllocationEffectHandle.Invalidate();

	AddBuildPreviewEffect();

	if (!CheckCostArgsless()) {
		_InsufficientFundsEffectHandle = ApplyGEToOwner(PlayerInsufficientFundsEffect);
	}
}

void UCOBuildAbility::OnConfigurationUpdated(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	_ConfigurationDTOTargetDataHandle = EventData->TargetData;

	auto TargetASC = GetASC(FCOBuildAllocationTD::GetTarget(_SelectionDTOTargetDataHandle));
	//Removing target effect to stop previewing the old build configuration
	TargetASC->RemoveActiveGameplayEffect(_BuildInProgressEffectHandle);

	AddBuildPreviewEffect();

	if (!CheckCostArgsless()) {
		_InsufficientFundsEffectHandle = ApplyGEToOwner(PlayerInsufficientFundsEffect);
	}
	else {
		RemoveActiveGameplayEffect(_InsufficientFundsEffectHandle);
	}
}

void UCOBuildAbility::AddBuildPreviewEffect()
{
	_BuildRequirementsDataHandle = BuildingsTable->FindRow<FCOBuildingTable>(FCOBuildConfigurationTD::GetBuildingName(_ConfigurationDTOTargetDataHandle), "")->ToBuildTargetDataHandle();

	FGameplayAbilityTargetDataHandle TargetData;
	TargetData.Append(_BuildRequirementsDataHandle);
	TargetData.Append(_ConfigurationDTOTargetDataHandle);
	TargetData.Append(_SelectionDTOTargetDataHandle);

	auto EffectContext = FCOGameplayEffectContextHandle(GetActorInfo().OwnerActor.Get());
	EffectContext.SetTargetData(TargetData);

	//Adding target effect to preview the build process
	_BuildInProgressEffectHandle = ApplyGESpecToTarget(EffectContext.MakeGESpec(TargetBuildPreviewEffect), _SelectionDTOTargetDataHandle).Last();
}

void UCOBuildAbility::OnAllocateCancelOrConfirm(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	auto Target = UCOAbilitySystemFunctionLibrary::GetTargetActorFromEffectByTag(GetActorInfo().AbilitySystemComponent.Get(), StreetSelectedTag);

	if (Tag.MatchesTag(ListenEventOnBuildConfirmed)) 
	{
		FGameplayEventData DeployEventData;
		DeployEventData.TargetData.Append(_ConfigurationDTOTargetDataHandle);
		DeployEventData.TargetData.Append(_SelectionDTOTargetDataHandle);
		DeployEventData.TargetData.Append(_BuildRequirementsDataHandle);
		DeployEventData.Instigator = GetActorInfo().OwnerActor.Get();

		if (CommitAbilityArgsless()) 
		{
			//Sending event to Target, to request the deploy of building
			SendServerGEToTarget(Target, BroadcastDeployEventOnBuildProcessFinished, DeployEventData);
		}
	}

	//Removing target effect to stop previewing the build process
	GetASC(Target)->RemoveActiveGameplayEffect(_BuildInProgressEffectHandle);

	//Removing palyer effect to indicate build is no more in progress
	RemoveActiveGameplayEffect(_PlayerPerformingBuildEffectHandle);
	EndAbilityArgsless();
}

void UCOBuildAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	RemoveGETagDelegate(ListenEventOnBuildConfirmed, _OnBuildConfirmedDH);
	RemoveGETagDelegate(ListenEventOnBuildCanceled, _OnBuildCanceledDH);
	RemoveGETagDelegate(ListenEventOnAllocationFinished, _OnAllocationFinishedDH);
	RemoveGETagDelegate(ListenEventOnConfigurationUpdated, _OnConfigurationUpdatedDH);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
