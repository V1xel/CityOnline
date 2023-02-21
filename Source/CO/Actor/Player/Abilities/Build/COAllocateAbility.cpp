// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Actor/Player/Abilities/Build/COAllocateAbility.h"
#include "CO/Actor/Player/Abilities/Helpers/COAllocateHelper.h"
#include "CO/Core/AbilitySystem/COAbilityTaskBase.h"
#include "CO/Extensions/GameplayTagExtension.h"
#include "AbilitySystemComponent.h"
#include <AbilitySystemInterface.h>
#include "COBuildAbility.h"
#include "CO/Actor/Player/Abilities/TargetData/COBuildTD.h"
#include <CO/Core/AbilitySystem/COGameplayEffectContext.h>
#include "COAllocateAbility.h"
#include <CO/Core/AbilitySystem/COAbilitySystemFunctionLibrary.h>

void UCOAllocateAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	auto AllocationCancelDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateLambda([this, Handle, ActorInfo, ActivationInfo]
	(FGameplayTag Tag, const FGameplayEventData* EventData) { AllocationCancel(Handle, ActorInfo, ActivationInfo, EventData); });
	_CancelDelegateHandle = ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenCancelAllocateTag.GetSingleTagContainer(), AllocationCancelDelegate);

	_Target = TriggerEventData->Target;
	_AllocateStartLocation = TriggerEventData->TargetData.Get(0)->GetHitResult()->Location;
	_BuildDTOTargetDataHandle = GetTargetDataFromActiveEffect(FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(FilterAllocatePermissionTag.GetSingleTagContainer()));

	auto EffectContext = new FCOGameplayEffectContext(ActorInfo->OwnerActor.Get(), ActorInfo->OwnerActor.Get());
	EffectContext->SetTargetData(_BuildDTOTargetDataHandle);
	EffectContext->AddHitResult(*TriggerEventData->TargetData.Get(0)->GetHitResult());

	_EffectHadles = ApplyGameplayEffectSpecToTarget(Handle, ActorInfo, ActivationInfo,
		FGameplayEffectSpecHandle(new FGameplayEffectSpec(AllocateInProgressEffect.GetDefaultObject(), FGameplayEffectContextHandle(EffectContext))), TriggerEventData->TargetData);
}

void UCOAllocateAbility::AllocationCancel(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* CancelEventData)
{
	auto EndLocation = CancelEventData->TargetData.Get(0)->GetHitResult()->Location;
	auto SelectionDTO = UCOAllocateAbilityHelper::CalculateSelectionData(_Target, _AllocateStartLocation, EndLocation);
	if (UCOAllocateAbilityHelper::ValidateSelectionData(SelectionDTO, _BuildDTOTargetDataHandle))
	{
		auto EventData = FGameplayEventData();
		EventData.Target = _Target;
		EventData.TargetData.Append(SelectionDTO);

		auto SelectedTarget = UCOAbilitySystemFunctionLibrary::GetTargetActorFromEffectByTag(GetActorInfo().AbilitySystemComponent.Get(), StreetSelectedTag);
		if (_Target == SelectedTarget)
		{
			SendGameplayEvent(BroadcastedEventOnAllocationFinished, EventData);
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UCOAllocateAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	_BuildDTOTargetDataHandle.Clear();

	auto TargetAbilitySystem = Cast<IAbilitySystemInterface>(_Target)->GetAbilitySystemComponent();
	for (auto EffectHandle : _EffectHadles)
	{
		TargetAbilitySystem->RemoveActiveGameplayEffect(EffectHandle);
	}

	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenCancelAllocateTag.GetSingleTagContainer(), _CancelDelegateHandle);
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenCancelAllocateTag.GetSingleTagContainer(), _UpdateBuildDTODelegateHandle);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
