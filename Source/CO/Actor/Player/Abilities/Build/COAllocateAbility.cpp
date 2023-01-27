// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Actor/Player/Abilities/Build/COAllocateAbility.h"
#include "CO/Actor/Player/Abilities/Helpers/COAllocateHelper.h"
#include "CO/Core/AbilitySystem/COAbilityTaskBase.h"
#include "CO/Extensions/GameplayTagExtension.h"
#include "AbilitySystemComponent.h"
#include <AbilitySystemInterface.h>
#include "COBuildAbility.h"
#include "CO/Actor/Player/Abilities/DTO/COBuildDTO.h"
#include <CO/Core/AbilitySystem/COGameplayEffectContext.h>

void UCOAllocateAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	auto AllocationCancelDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateLambda([this, Handle, ActorInfo, ActivationInfo]
	(FGameplayTag Tag, const FGameplayEventData* EventData) { AllocationCancel(Handle, ActorInfo, ActivationInfo, EventData); });
	_CancelDelegateHandle = ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenCancelAllocateTag.GetSingleTagContainer(), AllocationCancelDelegate);

	auto BuildDTOUpdatedDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UCOAllocateAbility::UpdateBuildDTO);
	_UpdateBuildDTODelegateHandle = ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenBuildDTOUpdated.GetSingleTagContainer(), BuildDTOUpdatedDelegate);


	_Target = TriggerEventData->Target.Get();
	_AllocateStartLocation = TriggerEventData->TargetData.Get(0)->GetHitResult()->Location;
	_EffectHadles = ApplyGameplayEffectToTarget(Handle, ActorInfo, ActivationInfo, TriggerEventData->TargetData, AllocateInProgressEffect, 0);
}

void UCOAllocateAbility::UpdateBuildDTO(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	auto TargetData = EventData->TargetData.Get(0);
	auto BuildDTOTargetData = static_cast<FCOBuildDTOTargetData*>(const_cast<FGameplayAbilityTargetData*>(TargetData));
	_BuildDTO = BuildDTOTargetData->ToDTO();
}

void UCOAllocateAbility::AllocationCancel(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* CancelEventData)
{
	auto EndLocation = CancelEventData->TargetData.Get(0)->GetHitResult()->Location;
	UCOSelectionDTO* SelectionDTO = UCOAllocateAbilityHelper::CalculateSelectionData(_Target, _AllocateStartLocation, EndLocation);
	if (UCOAllocateAbilityHelper::ValidateSelectionData(SelectionDTO, _BuildDTO)) {
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
	auto TargetAbilitySystem = Cast<IAbilitySystemInterface>(_Target)->GetAbilitySystemComponent();
	for (auto EffectHandle : _EffectHadles)
	{
		TargetAbilitySystem->RemoveActiveGameplayEffect(EffectHandle);
	}

	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenCancelAllocateTag.GetSingleTagContainer(), _CancelDelegateHandle);
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenCancelAllocateTag.GetSingleTagContainer(), _UpdateBuildDTODelegateHandle);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
