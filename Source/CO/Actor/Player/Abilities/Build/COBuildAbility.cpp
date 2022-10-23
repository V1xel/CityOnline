// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildAbility.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Actor/Street/COStreetActor.h"
#include "CO/Actor/Player/COPlayerState.h"
#include "CO/Extensions/GameplayTagExtension.h"
#include "CO/Actor/Player/Abilities/AbilityTasks/COSelectCellsAbilityTask.h"
#include "CO/Game/COConstants.h"
#include "CO/Extensions/GameplayTagExtension.h"

void UCOBuildAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	_Handle = Handle;
	_ActorInfo = ActorInfo;
	_ActivationInfo = ActivationInfo;
	BuildingTag = TriggerEventData->InstigatorTags.First();

	FGameplayEventTagMulticastDelegate::FDelegate AllocationCanceledDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UCOBuildAbility::OnAllocationFinished);
	ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(UCOGameplayTags::AllocateFinished().GetSingleTagContainer(), AllocationCanceledDelegate);
}

void UCOBuildAbility::OnAllocationFinished(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	FGameplayEventData BuildEventData = FGameplayEventData();
	BuildEventData.OptionalObject = EventData->OptionalObject;

	auto BuildingName = UGameplayTagExtension::GetTagSecondElement(BuildingTag);
	auto BuildingSpecialization = *BuildingsTable->FindRow<FCOBuildingTable>(FName(BuildingName), "");
	BuildEventData.OptionalObject2 = BuildingSpecialization.ToDTO();
	
	SendGameplayEvent(UCOGameplayTags::Construct(), BuildEventData);
}

bool UCOBuildAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Build can not be activated. Seems to be Tag validation.");
		return false;
	}

	auto Controller = GetController(ActorInfo);
	auto Street = Controller->TryGetSelectedStreet();
	if (!Street) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Build can not be activated. There is no street target.");
		return false;
	}

	return true;
}

void UCOBuildAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

}

void UCOBuildAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
