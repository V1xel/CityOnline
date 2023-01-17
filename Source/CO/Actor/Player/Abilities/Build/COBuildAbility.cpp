// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildAbility.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Actor/Street/COStreetActor.h"
#include "CO/Actor/Player/COPlayerState.h"
#include "CO/Extensions/GameplayTagExtension.h"
#include "CO/Actor/Player/Abilities/AbilityTasks/COSelectCellsAbilityTask.h"
#include "CO/Database/Assets/COBuildingAsset.h"
#include "CO/Database/Assets/CORootAsset.h"
#include "CO/Actor/Building/COBuildingActor.h"
#include "CO/Actor/Street/Abilities/DTO/CODeployBuildingDTO.h"

bool UCOBuildAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return true;
}

void UCOBuildAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	FGameplayEventTagMulticastDelegate::FDelegate BuildConfirmedDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateLambda([this, Handle, ActorInfo, ActivationInfo]
	(FGameplayTag Tag, const FGameplayEventData* EventData) { _Confirm = true; CancelAbility(Handle, ActorInfo, ActivationInfo, false); });
	ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenEventOnBuildConfirmed.GetSingleTagContainer(), BuildConfirmedDelegate);

	FGameplayEventTagMulticastDelegate::FDelegate BuildCanceledDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateLambda([this, Handle, ActorInfo, ActivationInfo]
	(FGameplayTag Tag, const FGameplayEventData* EventData) { CancelAbility(Handle, ActorInfo, ActivationInfo, false); });
	ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenEventOnBuildCanceled.GetSingleTagContainer(), BuildCanceledDelegate);

	FGameplayEventTagMulticastDelegate::FDelegate AllocationFinishedDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UCOBuildAbility::OnAllocationFinished);
	ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenEventOnAllocationFinished.GetSingleTagContainer(), AllocationFinishedDelegate);

	auto BuildingTag = TriggerEventData->InstigatorTags.Filter(FGameplayTagContainer(FilterBuildingTag)).First();
	_BuildingName = UGameplayTagExtension::GetTagSecondElement(BuildingTag);
	auto BuildingSpecialization = BuildingsTable->FindRow<FCOBuildingTable>(FName(_BuildingName), "");
	auto BuildDTO = BuildingSpecialization->ToDTO();
	auto EffectContext = FGameplayEffectContextHandle(new FGameplayEffectContext());
	EffectContext.AddSourceObject(BuildDTO);
	_AllocationEffectHandle = ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, FGameplayEffectSpecHandle(new FGameplayEffectSpec(EnableCellAllocationEffect.GetDefaultObject(), EffectContext)));
}

void UCOBuildAbility::OnAllocationFinished(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	GetActorInfo().AbilitySystemComponent->RemoveActiveGameplayEffect(_AllocationEffectHandle);

	_Target = EventData->Target.Get();
	_SelectionDTO = Cast<UCOSelectionDTO>(EventData->OptionalObject);
}

void UCOBuildAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	if (_Confirm && _Target && _SelectionDTO) {
		auto EffectContext = FGameplayEffectContextHandle(new FGameplayEffectContext());
		auto DeployBuilding = NewObject<UCODeployBuildingDTO>();
		DeployBuilding->SelectionDTO = _SelectionDTO;
		DeployBuilding->BuildingName = _BuildingName;
		DeployBuilding->Floors = 4;
		EffectContext.AddSourceObject(DeployBuilding);
		auto EffectSpecHandle = FGameplayEffectSpecHandle(new FGameplayEffectSpec(PendingDeployEffect.GetDefaultObject(), EffectContext));

		FGameplayAbilityTargetData_ActorArray* TargetData = new FGameplayAbilityTargetData_ActorArray();
		TargetData->TargetActorArray.Add(const_cast<AActor*>(_Target));
		FGameplayAbilityTargetDataHandle TargetDataHandle(TargetData);

		ApplyGameplayEffectToTarget(Handle, ActorInfo, ActivationInfo, TargetDataHandle, PendingDeployEffect, 0);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UCOBuildAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

