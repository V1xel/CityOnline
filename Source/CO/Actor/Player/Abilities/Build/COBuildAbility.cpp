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

	auto SourceTags = TriggerEventData->InstigatorTags;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, SourceTags.First().GetTagName().ToString());

	if (UCOGameplayTags::Allocate().MatchesTagExact(TriggerEventData->EventTag)) {
		auto BuildingName = UGameplayTagExtension::GetTagSecondElement(SourceTags.First());
		BuildingSpecialization = *BuildingsTable->FindRow<FCOBuildingTable>(FName(BuildingName), "");
	}
}

void UCOBuildAbility::OnAllocationFinished(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "OnAllocationFinished");
	SendGameplayEvent(UCOGameplayTags::Construct(), FGameplayEventData());
	
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
