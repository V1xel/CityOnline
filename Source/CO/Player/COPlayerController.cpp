// Fill out your copyright notice in the Description page of Project Settings.


#include "COPlayerController.h"
#include "Components/COSelectionComponent.h"

ACOPlayerController::ACOPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	PrimaryActorTick.bCanEverTick = true;
	
	SelectionComponent = CreateDefaultSubobject<UCOSelectionComponent>(TEXT("SelectionComponent"));
}

void ACOPlayerController::StartSelection()
{
	SelectionComponent->StartSelection();
}

void ACOPlayerController::StopSelection()
{
	OnSelectionFinished.Broadcast(TArray(SelectionComponent->SelectedComponents));
	SelectionComponent->StopSelection();
}

void ACOPlayerController::SetComponentSelectionEnabled(bool Value)
{
	SelectionComponent->SetComponentSelectionEnabled(Value);
}

void ACOPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Select", EInputEvent::IE_Pressed, this, &ACOPlayerController::StartSelection);
	InputComponent->BindAction("Select", EInputEvent::IE_Released, this, &ACOPlayerController::StopSelection);
}
