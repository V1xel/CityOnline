// Fill out your copyright notice in the Description page of Project Settings.


#include "COGameplayAbilityBase.h"
#include "CO/Actor/Player/COPlayerCharacter.h"
#include "CO/Actor/Player/COPlayerController.h"

ACOPlayerController* UCOGameplayAbilityBase::GetController(const FGameplayAbilityActorInfo* ActorInfo) const
{
	if (ActorInfo->PlayerController == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("ActorInfo->PlayerController is null. Possibly InitAbilityActorInfo was not called."));
	}

	return Cast<ACOPlayerController>(ActorInfo->PlayerController);
}

ACOPlayerCharacter* UCOGameplayAbilityBase::GetOwnerActor(const FGameplayAbilityActorInfo* ActorInfo) const
{
	return Cast<ACOPlayerCharacter>(ActorInfo->OwnerActor);
}
