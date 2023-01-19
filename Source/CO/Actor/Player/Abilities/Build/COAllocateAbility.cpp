// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Actor/Player/Abilities/Build/COAllocateAbility.h"
#include "CO/Actor/Player/Abilities/Helpers/COAllocateHelper.h"
#include "CO/Core/AbilitySystem/COAbilityTaskBase.h"
#include "CO/Extensions/GameplayTagExtension.h"
#include "AbilitySystemComponent.h"
#include <AbilitySystemInterface.h>
#include "COBuildAbility.h"

void UCOAllocateAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	_Target = TriggerEventData->Target.Get();
	auto AllocationCancelDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateLambda([this, Handle, ActorInfo, ActivationInfo, TriggerEventData]
	(FGameplayTag Tag, const FGameplayEventData* EventData) { AllocationCancel(Handle, ActorInfo, ActivationInfo, TriggerEventData, EventData); });
	_CancelDelegateHandle = ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenCancelAllocateTag.GetSingleTagContainer(), AllocationCancelDelegate);

	auto AllocatePermissionActiveEffects = ActorInfo->AbilitySystemComponent->GetActiveEffects(FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(FilterAllocatePermissionTag.GetSingleTagContainer()));
	FGameplayEffectContextHandle PermissionGrantedEffectContext = ActorInfo->AbilitySystemComponent->GetEffectContextFromActiveGEHandle(AllocatePermissionActiveEffects[0]);
	auto BuildDTO = Cast<UCOBuildDTO>(PermissionGrantedEffectContext.GetSourceObject());

	auto EffectContext = FGameplayEffectContextHandle(new FGameplayEffectContext(ActorInfo->OwnerActor.Get(), ActorInfo->OwnerActor.Get()));
	EffectContext.AddSourceObject(BuildDTO);
	auto EffectSpec = FGameplayEffectSpecHandle(new FGameplayEffectSpec(AllocateInProgressEffect.GetDefaultObject(), EffectContext));

	_EffectHadles = ApplyGameplayEffectSpecToTarget(Handle, ActorInfo, ActivationInfo, EffectSpec, TriggerEventData->TargetData);
}

void UCOAllocateAbility::AllocationCancel(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* ActivateEventData, const FGameplayEventData* CancelEventData)
{
	auto TargetAbilitySystem = Cast<IAbilitySystemInterface>(_Target)->GetAbilitySystemComponent();
	for (auto EffectHandle : _EffectHadles)
	{
		TargetAbilitySystem->RemoveActiveGameplayEffect(EffectHandle);
	}

	auto AllocatePermissionActiveEffects = ActorInfo->AbilitySystemComponent->GetActiveEffects(FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(FilterAllocatePermissionTag.GetSingleTagContainer()));
	FGameplayEffectContextHandle PermissionGrantedEffectContext = ActorInfo->AbilitySystemComponent->GetEffectContextFromActiveGEHandle(AllocatePermissionActiveEffects[0]);
	auto BuildDTO = Cast<UCOBuildDTO>(PermissionGrantedEffectContext.GetSourceObject());

	if (ActivateEventData->TargetData.IsValid(0) && CancelEventData->TargetData.IsValid(0)) 
	{
		auto StartLocation = ActivateEventData->TargetData.Get(0)->GetHitResult()->Location;
		auto EndLocation = CancelEventData->TargetData.Get(0)->GetHitResult()->Location;
		UCOSelectionDTO* SelectionDTO = UCOAllocateAbilityHelper::CalculateSelectionData(ActivateEventData->Target.Get(), StartLocation, EndLocation);

		if (UCOAllocateAbilityHelper::ValidateSelectionData(SelectionDTO, BuildDTO)) {
			auto Data = FGameplayEventData();
			Data.Target = _Target;
			Data.OptionalObject = SelectionDTO;
			SendGameplayEvent(BroadcastedEventOnAllocationFinished, Data);
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UCOAllocateAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenCancelAllocateTag.GetSingleTagContainer(), _CancelDelegateHandle);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
