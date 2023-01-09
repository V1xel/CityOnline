// Fill out your copyright notice in the Description page of Project Settings.


#include "COGameplayAbilityBase.h"
#include "CO/Actor/Player/COPlayerCharacter.h"
#include "CO/Actor/Player/COPlayerController.h"

void UCOGameplayAbilityBase::ActivateAbility(FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	_Handle = Handle;
	_ActorInfo = ActorInfo;
	_ActivationInfo = ActivationInfo;
}

ACOPlayerController* UCOGameplayAbilityBase::GetPlayerController() const
{
	return Cast<ACOPlayerController>(_ActorInfo->PlayerController);
}

ACOPlayerCharacter* UCOGameplayAbilityBase::GetOwnerCharacter() const
{
	return Cast<ACOPlayerCharacter>(_ActorInfo->OwnerActor);
}

ACOPlayerCharacter* UCOGameplayAbilityBase::GetOwnerActor(const FGameplayAbilityActorInfo* ActorInfo) const
{
	return Cast<ACOPlayerCharacter>(ActorInfo->OwnerActor);
}

void UCOGameplayAbilityBase::SendGameplayEvents(FGameplayTagContainer TagContainer, FGameplayEventData Payload)
{
	for (auto Tag : TagContainer)
	{
		SendGameplayEvent(Tag, Payload);
	}
}
