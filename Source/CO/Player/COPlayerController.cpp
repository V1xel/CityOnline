// Fill out your copyright notice in the Description page of Project Settings.


#include "COPlayerController.h"
#include "Components/COSelectionComponent.h"

ACOPlayerController::ACOPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	PrimaryActorTick.bCanEverTick = true;
	
	SelectionComponent = CreateDefaultSubobject<UCOSelectionComponent>(TEXT("CameraSpringArm"));
}

void ACOPlayerController::StartSelection()
{
	SelectionComponent->StartSelection();
}

void ACOPlayerController::StopSelection()
{
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
