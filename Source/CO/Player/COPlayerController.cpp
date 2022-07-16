// Fill out your copyright notice in the Description page of Project Settings.


#include "COPlayerController.h"

#include "Components/COActorSelectionComponent.h"
#include "Components/COCellSelectionComponent.h"

ACOPlayerController::ACOPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	PrimaryActorTick.bCanEverTick = true;
	
	ActorSelection = CreateDefaultSubobject<UCOActorSelectionComponent>(TEXT("ActorSelection"));
	CellSelection = CreateDefaultSubobject<UCOCellSelectionComponent>(TEXT("CellSelection"));
}

void ACOPlayerController::StartSelection()
{
	ActorSelection->TrySelectUnderCursor();
	CellSelection->StartSelection();
}

void ACOPlayerController::StopSelection()
{
	CellSelection->EndSelection();
}

void ACOPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Select", EInputEvent::IE_Pressed, this, &ACOPlayerController::StartSelection);
	InputComponent->BindAction("Select", EInputEvent::IE_Released, this, &ACOPlayerController::StopSelection);
}
