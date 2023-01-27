// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildAbility.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Actor/Street/COStreetActor.h"
#include "CO/Actor/Player/COPlayerState.h"
#include "CO/Extensions/GameplayTagExtension.h"
#include "CO/Database/Assets/COBuildingAsset.h"
#include "CO/Database/Assets/CORootAsset.h"
#include "CO/Actor/Building/COBuildingActor.h"
#include "CO/Actor/Player/Abilities/Helpers/COAllocateHelper.h"
#include "CO/Actor/Street/Abilities/DTO/CODeployBuildingDTO.h"
#include "CO/Core/AbilitySystem/COGameplayEffectContext.h"

void UCOBuildAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	FGameplayEventTagMulticastDelegate::FDelegate BuildConfirmedDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateLambda([this, Handle, ActorInfo, ActivationInfo]
	(FGameplayTag Tag, const FGameplayEventData* EventData) { OnAllocateCancelOrConfirm(Handle, ActorInfo, ActivationInfo, EventData, true); });
	ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenEventOnBuildConfirmed.GetSingleTagContainer(), BuildConfirmedDelegate);

	FGameplayEventTagMulticastDelegate::FDelegate BuildCanceledDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateLambda([this, Handle, ActorInfo, ActivationInfo]
	(FGameplayTag Tag, const FGameplayEventData* EventData) { OnAllocateCancelOrConfirm(Handle, ActorInfo, ActivationInfo, EventData, false); });
	ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenEventOnBuildCanceled.GetSingleTagContainer(), BuildCanceledDelegate);

	FGameplayEventTagMulticastDelegate::FDelegate AllocationFinishedDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UCOBuildAbility::OnAllocationFinished);
	ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenEventOnAllocationFinished.GetSingleTagContainer(), AllocationFinishedDelegate);


	auto BuildingTag = TriggerEventData->InstigatorTags.Filter(FGameplayTagContainer(FilterBuildingTag)).First();
	auto BuildingName = UGameplayTagExtension::GetTagSecondElement(BuildingTag);
	auto BuildingSpecialization = BuildingsTable->FindRow<FCOBuildingTable>(FName(BuildingName), "");

	FGameplayEventData EventData;
	EventData.TargetData = FGameplayAbilityTargetDataHandle(BuildingSpecialization->ToTargetData());
	SendGameplayEvent(BroadcastBuildDTOUpdated, EventData);


	_BuildingName = BuildingName;
	_AllocationEffectHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, EnableCellAllocationEffect.GetDefaultObject(), 0);
}

void UCOBuildAbility::OnAllocationFinished(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	GetActorInfo().AbilitySystemComponent->RemoveActiveGameplayEffect(_AllocationEffectHandle);

	_Target = EventData->Target.Get();
	_SelectionDTO = Cast<UCOSelectionDTO>(EventData->OptionalObject);
}

void UCOBuildAbility::OnAllocateCancelOrConfirm(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* EventData, bool Confirm)
{
	if (Confirm) {
		auto DeployBuilding = NewObject<UCODeployBuildingDTO>();
		DeployBuilding->SelectionDTO = _SelectionDTO;
		DeployBuilding->BuildingName = _BuildingName;
		DeployBuilding->Floors = EventData->EventMagnitude;

		ApplyGameplayEffectToTarget(Handle, ActorInfo, ActivationInfo, FGameplayAbilityTargetDataHandle(DeployBuilding->ToTargetData()), PendingDeployEffect, 0);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UCOBuildAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

