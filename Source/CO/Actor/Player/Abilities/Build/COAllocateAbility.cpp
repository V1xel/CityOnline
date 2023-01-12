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

	auto AllocationCancelDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateLambda([this, Handle, ActorInfo, ActivationInfo]
	(FGameplayTag Tag, const FGameplayEventData* EventData) { CancelAbility(Handle, ActorInfo, ActivationInfo, false); });
	_CancelDelegateHandle = ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenCancelAllocateTag.GetSingleTagContainer(), AllocationCancelDelegate);

	auto AllocatePermissionActiveEffects = ActorInfo->AbilitySystemComponent->GetActiveEffects(FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(FilterAllocatePermissionTag.GetSingleTagContainer()));
	if (AllocatePermissionActiveEffects.Num() > 0) {
		FGameplayEffectContextHandle PermissionGrantedEffectContext = ActorInfo->AbilitySystemComponent->GetEffectContextFromActiveGEHandle(AllocatePermissionActiveEffects[0]);
		_AllocationTask = UCOAbilityTaskBase::CreateAllocationTask<UCOSelectCellsAbilityTask>(this, TriggerEventData->TargetData, PermissionGrantedEffectContext);
	}
}

void UCOAllocateAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	if (!_AllocationTask) {
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	UCOSelectionDTO* SelectionDTO = _AllocationTask->GetResult();
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
	Data.OptionalObject = _AllocationTask->GetResult();

	SendGameplayEvent(BroadcastedEventOnAllocationUpdated, Data);
}

void UCOAllocateAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (_AllocationTask) {
		_AllocationTask->ExternalConfirm(true);
	}

	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenCancelAllocateTag.GetSingleTagContainer(), _CancelDelegateHandle);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
