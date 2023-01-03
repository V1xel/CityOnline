// Fill out your copyright notice in the Description page of Project Settings.


#include "COGameplayAbilityBase.h"
#include "CO/Actor/Player/COPlayerCharacter.h"
#include "CO/Actor/Player/COPlayerController.h"

ACOPlayerController* UCOGameplayAbilityBase::GetController(const FGameplayAbilityActorInfo* ActorInfo) const
{
	return Cast<ACOPlayerController>(ActorInfo->PlayerController);
}

ACOPlayerCharacter* UCOGameplayAbilityBase::GetOwnerActor(const FGameplayAbilityActorInfo* ActorInfo) const
{
	return Cast<ACOPlayerCharacter>(ActorInfo->OwnerActor);
}
