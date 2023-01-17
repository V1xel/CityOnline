// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Actor/Player/Abilities/Build/COAllocateAbility.h"
#include "CO/Actor/Player/Abilities/AbilityTasks/COSelectCellsAbilityTask.h"
#include "CO/Core/AbilitySystem/COAbilityTaskBase.h"
#include "CO/Extensions/GameplayTagExtension.h"
#include "AbilitySystemComponent.h"
#include "COBuildAbility.h"

void UCOAllocateAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	_Target = TriggerEventData->Target.Get();
	auto AllocationCancelDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateLambda([this, Handle, ActorInfo, ActivationInfo]
	(FGameplayTag Tag, const FGameplayEventData* EventData) { AllocationCancel(Handle, ActorInfo, ActivationInfo, EventData); });
	_CancelDelegateHandle = ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenCancelAllocateTag.GetSingleTagContainer(), AllocationCancelDelegate);

	auto AllocatePermissionActiveEffects = ActorInfo->AbilitySystemComponent->GetActiveEffects(FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(FilterAllocatePermissionTag.GetSingleTagContainer()));
	if (AllocatePermissionActiveEffects.Num() > 0) {
		FGameplayEffectContextHandle PermissionGrantedEffectContext = ActorInfo->AbilitySystemComponent->GetEffectContextFromActiveGEHandle(AllocatePermissionActiveEffects[0]);
		_AllocationTask = UCOAbilityTaskBase::CreateAllocationTask<UCOSelectCellsAbilityTask>(this, TriggerEventData->TargetData, PermissionGrantedEffectContext, true);
	}
}

void UCOAllocateAbility::AbilityTaskTick()
{
	auto Data = FGameplayEventData();
	Data.Target = _Target;
	Data.OptionalObject = _AllocationTask->GetVisualisationResult();

	SendGameplayEvent(BroadcastedEventOnAllocationUpdated, Data);
}

void UCOAllocateAbility::AllocationCancel(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!_AllocationTask) {
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}

	UCOSelectionDTO* SelectionDTO = _AllocationTask->CalculateSelectionData(TriggerEventData->TargetData);
	if (SelectionDTO->IsValid) {
		auto Data = FGameplayEventData();
		Data.Target = _Target;
		Data.OptionalObject = SelectionDTO;
		SendGameplayEvent(BroadcastedEventOnAllocationFinished, Data);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
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
