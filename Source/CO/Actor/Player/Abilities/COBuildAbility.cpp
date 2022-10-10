// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildAbility.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Actor/Street/COStreetActor.h"
#include <CO/Actor/Player/COPlayerState.h>

void UCOBuildAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "ActivateAbility");
}

bool UCOBuildAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "CanActivateAbility");
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags))
	{
		return false;
	}

	auto Controller = GetController(ActorInfo);
	auto Street = Controller->TryGetSelectedStreet();
	if (!Street) 
	{
		return false;
	}

	FString Left, Right;
	TargetTags->First().GetTagName().ToString().Split(FString("."), nullptr, &Right);
	FCOBuildingTable* Building = BuildingsTable->FindRow<FCOBuildingTable>(FName(Right), "");

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Right);
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
