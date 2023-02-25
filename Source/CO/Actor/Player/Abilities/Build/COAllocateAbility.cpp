// Fill out your copyright notice in the Description page of Project Settings.


#include "COAllocateAbility.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "TargetData/COBuildRequirementsTD.h"
#include "CO/Actor/Player/Abilities/Build/COAllocateAbility.h"
#include "CO/Actor/Player/Abilities/Helpers/COAllocateHelper.h"
#include "CO/Core/AbilitySystem/COAbilityTaskBase.h"
#include "CO/Core/AbilitySystem/COGameplayEffectContext.h"
#include "CO/Core/AbilitySystem/COAbilitySystemFunctionLibrary.h"
#include "CO/Core/AbilitySystem/COGameplayEffectContextHandle.h"
#include "CO/Extensions/GameplayTagExtension.h"

void UCOAllocateAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	_CancelDelegateHandle = AddGETagDelegate(ListenCancelAllocateTag, FGEDelegate::CreateUObject(this, &UCOAllocateAbility::AllocationCancel));

	_AllocateActivatedTargetData = TriggerEventData->TargetData;

	auto BuildTargetDataHandle = GetTargetDataFromActiveEffect(FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(FilterAllocatePermissionTag.GetSingleTagContainer()));
	_BuildRequirementsTargetData = BuildTargetDataHandle;

	auto SelectionContext = new FCOGameplayEffectContextHandle(ActorInfo->OwnerActor.Get(), BuildTargetDataHandle);
	SelectionContext->AddHitResult(*TriggerEventData->TargetData.Get(0)->GetHitResult());
	//Adding target effect to preview the allocation
	_AllocateEffectHandle = ApplyGESpecToTarget(SelectionContext->MakeGESpec(TargetAllocateInProgressEffect), TriggerEventData->TargetData).Last();
}

void UCOAllocateAbility::AllocationCancel(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	auto StartHit = _AllocateActivatedTargetData.Get(0)->GetHitResult();
	auto EndHit = EventData->TargetData.Get(0)->GetHitResult();
	auto SelectionDTO = UCOAllocateAbilityHelper::CalculateSelectionData(StartHit->GetActor(), StartHit->Location, EndHit->Location);
	if (UCOAllocateAbilityHelper::ValidateSelectionData(SelectionDTO, _BuildRequirementsTargetData) && StartHit->GetActor() == EndHit->GetActor())
	{
		auto AllocateEventData = FGameplayEventData();
		AllocateEventData.TargetData.Append(SelectionDTO);

		SendGameplayEvent(BroadcastedEventOnAllocationFinished, AllocateEventData);
	}

	EndAbilityArgsless();
}

void UCOAllocateAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	RemoveGETagDelegate(ListenCancelAllocateTag, _CancelDelegateHandle);

	auto TargetAbilitySystem = GetASC(_AllocateActivatedTargetData.Get(0)->GetActors()[0].Get());
	//Removing target effect to stop previewing the allocation
	TargetAbilitySystem->RemoveActiveGameplayEffect(_AllocateEffectHandle);

	_AllocateActivatedTargetData.Clear();
}
