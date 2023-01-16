// Fill out your copyright notice in the Description page of Project Settings.


#include "COPlayerController.h"
#include "CO/Actor/Street/COStreetActor.h"
#include "CO/Actor/Building/COBuildingActor.h"
#include "CO/Actor/Street/Abilities/DTO/CODeployBuildingDTO.h"

ACOPlayerController::ACOPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void ACOPlayerController::SendGameplayEventToPawn(FGameplayTag Tag, FGameplayEventData Payload, bool SendToServer)
{
	if (SendToServer) {
		SendServerGameplayEventToPawn(Tag, Payload);
	}
	else {
		Cast<IAbilitySystemInterface>(GetPawn())->GetAbilitySystemComponent()->HandleGameplayEvent(Tag, &Payload);
	}
}

void ACOPlayerController::SendGameplayEventToListener(AActor* Listener, FGameplayTag Tag, FGameplayEventData Payload, bool SendToServer)
{
	if (SendToServer) {
		SendServerGameplayEventToListener(Listener, Tag, Payload);
	}
	else {
		Cast<IAbilitySystemInterface>(Listener)->GetAbilitySystemComponent()->HandleGameplayEvent(Tag, &Payload);
	}
}

void ACOPlayerController::SendServerGameplayEventToPawn_Implementation(FGameplayTag Tag, FGameplayEventData Payload)
{
	Cast<IAbilitySystemInterface>(GetPawn())->GetAbilitySystemComponent()->HandleGameplayEvent(Tag, &Payload);
}

void ACOPlayerController::SendServerGameplayEventToListener_Implementation(AActor* Listener, FGameplayTag Tag, FGameplayEventData Payload)
{
	Cast<IAbilitySystemInterface>(Listener)->GetAbilitySystemComponent()->HandleGameplayEvent(Tag, &Payload);
}
