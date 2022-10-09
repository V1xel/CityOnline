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

void ACOPlayerController::SetSelectedActor(AActor* Value)
{
	SelectedActor = Value;

	const auto Street = Cast<ACOStreetActor>(Value);
	if (Street)
	{
		OnStreetSelected.Broadcast(Street);
		return;
	}

	const auto Building = Cast<ACOBuildingActor>(Value);
	if (Building)
	{
		OnBuildingSelected.Broadcast(Building);
		return;
	}
}