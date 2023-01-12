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

	auto BuildingTag = TriggerEventData->InstigatorTags.Filter(FGameplayTagContainer(FilterBuildingTag)).First();
	auto BuildingName = UGameplayTagExtension::GetTagSecondElement(BuildingTag);
	auto BuildingSpecialization = BuildingsTable->FindRow<FCOBuildingTable>(FName(BuildingName), "");
	_BuildDTO = BuildingSpecialization->ToDTO();

	FGameplayEventTagMulticastDelegate::FDelegate AllocationFinishedDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UCOBuildAbility::OnAllocationFinished);
	ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenEventOnAllocationFinished.GetSingleTagContainer(), AllocationFinishedDelegate);

	auto EffectContext = FGameplayEffectContextHandle(new FGameplayEffectContext());
	EffectContext.AddSourceObject(_BuildDTO);

	_AllocationEffectHandle = ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, FGameplayEffectSpecHandle(new FGameplayEffectSpec(EnableCellAllocationEffect.GetDefaultObject(), EffectContext)));
}

void UCOBuildAbility::OnAllocationFinished(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	GetActorInfo().AbilitySystemComponent->RemoveActiveGameplayEffect(_AllocationEffectHandle);

	_DeployBuilding = NewObject<UCODeployBuildingDTO>();

	auto SelectionDTO = Cast<UCOSelectionDTO>(EventData->OptionalObject);
	auto Asset = RootAsset->FindBestAsset(SelectionDTO, _BuildDTO);
	_BuildingPreview = GetWorld()->SpawnActorDeferred<ACOBuildingActor>(BuildingActorClass, FTransform(SelectionDTO->Rotation, SelectionDTO->Center));
	_BuildingPreview->BuildingAsset = Asset;
	_BuildingPreview->ComposeBuilding();
	_BuildingPreview->FinishSpawning(FTransform());
	_BuildingPreview->SetActorLocationAndRotation(SelectionDTO->Center, SelectionDTO->Rotation + Asset->RotationOffset);
}

void UCOBuildAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	auto EffectContext = FGameplayEffectContextHandle(new FGameplayEffectContext());
	EffectContext.AddSourceObject(_DeployBuilding);
	ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, FGameplayEffectSpecHandle(new FGameplayEffectSpec(PendingDeployEffect.GetDefaultObject(), EffectContext)));

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UCOBuildAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

