// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildAbility.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Actor/Street/COStreetActor.h"
#include "CO/Actor/Player/COPlayerState.h"
#include "CO/Extensions/GameplayTagExtension.h"
#include "CO/Database/Assets/COBuildingAsset.h"
#include "CO/Database/Assets/CORootAsset.h"
#include "CO/Actor/Building/COBuildingActor.h"
#include "CO/Actor/Player/Abilities/TargetData/COBuildConfigurationTD.h"
#include "CO/Actor/Player/Abilities/Helpers/COAllocateHelper.h"
#include "CO/Core/AbilitySystem/COGameplayEffectContext.h"

void UCOBuildAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	FGameplayEventTagMulticastDelegate::FDelegate BuildConfirmedDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateLambda([this, Handle, ActorInfo, ActivationInfo]
	(FGameplayTag Tag, const FGameplayEventData* EventData) { OnAllocateCancelOrConfirm(Handle, ActorInfo, ActivationInfo, EventData, true); });
	_OnBuildConfirmedDelegateHandle = ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenEventOnBuildConfirmed.GetSingleTagContainer(), BuildConfirmedDelegate);

	FGameplayEventTagMulticastDelegate::FDelegate BuildCanceledDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateLambda([this, Handle, ActorInfo, ActivationInfo]
	(FGameplayTag Tag, const FGameplayEventData* EventData) { OnAllocateCancelOrConfirm(Handle, ActorInfo, ActivationInfo, EventData, false); });
	_OnBuildCanceledDelegateHandle = ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenEventOnBuildCanceled.GetSingleTagContainer(), BuildCanceledDelegate);

	FGameplayEventTagMulticastDelegate::FDelegate AllocationFinishedDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UCOBuildAbility::OnAllocationFinished);
	_OnAllocationFinishedDelegateHandle = ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenEventOnAllocationFinished.GetSingleTagContainer(), AllocationFinishedDelegate);

	FGameplayEventTagMulticastDelegate::FDelegate ConfigurationUpdatedDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UCOBuildAbility::OnConfigurationUpdated);
	_OnConfigurationUpdatedDelegateHandle = ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenEventOnConfigurationUpdated.GetSingleTagContainer(), ConfigurationUpdatedDelegate);

	auto ConfigurationTargetData = static_cast<const FCOBuildConfigurationTD*>(TriggerEventData->TargetData.Get(0));
	auto BuildingSpecialization = BuildingsTable->FindRow<FCOBuildingTable>(ConfigurationTargetData->BuildingName, "");
	
	FGameplayEventData EventData;
	EventData.TargetData.Append(TriggerEventData->TargetData);
	EventData.TargetData.Append(BuildingSpecialization->ToTargetDataHandle());
	SendGameplayEvent(BroadcastBuildDTOUpdated, EventData);

	_AllocationEffectHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, EnableCellAllocationEffect.GetDefaultObject(), 0);
}

void UCOBuildAbility::OnAllocationFinished(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	GetActorInfo().AbilitySystemComponent->RemoveActiveGameplayEffect(_AllocationEffectHandle);
	_SelectionDTOTargetDataHandle = EventData->TargetData;
}

void UCOBuildAbility::OnConfigurationUpdated(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	_ConfigurationDTOTargetDataHandle = EventData->TargetData;
}

void UCOBuildAbility::OnAllocateCancelOrConfirm(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* EventData, bool Confirm)
{
	if (Confirm) {
		FGameplayAbilityTargetDataHandle TagetData;
		TagetData.Append(_SelectionDTOTargetDataHandle);
		TagetData.Append(_ConfigurationDTOTargetDataHandle);

		ApplyGameplayEffectToTarget(Handle, ActorInfo, ActivationInfo, TagetData, PendingDeployEffect, 0);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UCOBuildAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenEventOnBuildConfirmed.GetSingleTagContainer(), _OnBuildConfirmedDelegateHandle);
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenEventOnBuildCanceled.GetSingleTagContainer(), _OnBuildCanceledDelegateHandle);
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenEventOnAllocationFinished.GetSingleTagContainer(), _OnAllocationFinishedDelegateHandle);
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenEventOnConfigurationUpdated.GetSingleTagContainer(), _OnConfigurationUpdatedDelegateHandle);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

