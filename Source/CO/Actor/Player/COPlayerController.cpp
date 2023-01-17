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

void ACOPlayerController::SendServerGameplayEventToPawn_Implementation(FGameplayTag Tag, FGameplayEventData Payload)
{
	Cast<IAbilitySystemInterface>(GetPawn())->GetAbilitySystemComponent()->HandleGameplayEvent(Tag, &Payload);
}

void ACOPlayerController::SendServerGameplayEventToListener_Implementation(AActor* Listener, FGameplayTag Tag, FGameplayEventData Payload)
{
	Cast<IAbilitySystemInterface>(Listener)->GetAbilitySystemComponent()->HandleGameplayEvent(Tag, &Payload);
}
