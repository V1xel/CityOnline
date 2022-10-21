// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildAbility.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Actor/Street/COStreetActor.h"
#include "CO/Actor/Player/COPlayerState.h"
#include "CO/Extensions/GameplayTagContainerExtension.h"

void UCOBuildAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	FString Left, Right;
	auto SourceTags = TriggerEventData->InstigatorTags;
	auto BuildingName = UGameplayTagContainerExtension::GetTagSecondElement(SourceTags.First());
	auto Table = *BuildingsTable->FindRow<FCOBuildingTable>(FName(BuildingName), "");
	BuildingSpecialization = Table;

	if (CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		//	Build
	}
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

FCOBuildingTable UCOBuildAbility::GetBuildingSpecialization() const
{
	return BuildingSpecialization;
}
