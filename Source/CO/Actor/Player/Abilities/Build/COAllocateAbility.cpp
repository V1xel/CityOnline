// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Actor/Player/Abilities/Build/COAllocateAbility.h"
#include "CO/Actor/Player/Abilities/AbilityTasks/COSelectCellsAbilityTask.h"
#include "CO/Core/AbilitySystem/COAbilityTaskBase.h"
#include "CO/Extensions/GameplayTagExtension.h"
#include "CO/Core/COConstants.h"
#include "AbilitySystemComponent.h"
#include "COBuildAbility.h"

void UCOAllocateAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	auto Context = GetGrantedByEffectContext();
	auto DTO = Cast<UCOBuildDTO>(Context.GetSourceObject());
	_AllocationTask = UCOAbilityTaskBase::CreateAllocationTask<UCOSelectCellsAbilityTask>(this, TriggerEventData->TargetData);
}

void UCOAllocateAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	UCOSelectionDTO* SelectionDTO = _AllocationTask->SelectionDTO;
	if (SelectionDTO && SelectionDTO->IsValid) {
		auto Data = FGameplayEventData();
		Data.OptionalObject = SelectionDTO;
		SendGameplayEvent(BroadcastedEventOnAllocationFinished, Data);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UCOAllocateAbility::AbilityTaskTick()
{
	auto Data = FGameplayEventData();
	Data.OptionalObject = _AllocationTask->SelectionDTO;

	SendGameplayEvent(BroadcastedEventOnAllocationUpdated, Data);
}

void UCOAllocateAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	_AllocationTask->ExternalConfirm(true);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
