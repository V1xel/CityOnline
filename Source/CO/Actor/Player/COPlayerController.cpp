// Fill out your copyright notice in the Description page of Project Settings.


#include "COPlayerController.h"
#include "CO/Actor/Street/COStreetActor.h"
#include "CO/Actor/Building/COBuildingActor.h"

ACOPlayerController::ACOPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void ACOPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	auto delegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &ACOPlayerController::OnActorSelected);
	auto pawn = Cast<IAbilitySystemInterface>(aPawn);
	auto asc = pawn->GetAbilitySystemComponent();
	_actorSelectedHandle = asc->AddGameplayEventTagContainerDelegate(ListenActorSelectedTag.GetSingleTagContainer(), delegate);
}

void ACOPlayerController::OnUnPossess()
{
	auto pawn = Cast<IAbilitySystemInterface>(GetPawn());
	auto asc = pawn->GetAbilitySystemComponent();
	asc->RemoveGameplayEventTagContainerDelegate(ListenActorSelectedTag.GetSingleTagContainer(), _actorSelectedHandle);

	Super::OnUnPossess();
}

void ACOPlayerController::OnActorSelected(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	SelectedActor = EventData->Target.Get();
}
