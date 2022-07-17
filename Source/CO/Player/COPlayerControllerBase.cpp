// Fill out your copyright notice in the Description page of Project Settings.


#include "COPlayerControllerBase.h"

#include "Components/COActorSelectionComponent.h"
#include "Components/COCellSelectionComponent.h"

ACOPlayerControllerBase::ACOPlayerControllerBase()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	PrimaryActorTick.bCanEverTick = true;
	
	ActorSelection = CreateDefaultSubobject<UCOActorSelectionComponent>(TEXT("ActorSelection"));
	CellSelection = CreateDefaultSubobject<UCOCellSelectionComponent>(TEXT("CellSelection"));
}

void ACOPlayerControllerBase::StartSelection()
{
	ActorSelection->TrySelectUnderCursor();
	CellSelection->StartSelection();
}

void ACOPlayerControllerBase::StopSelection()
{
	CellSelection->EndSelection();
}

void ACOPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Select", IE_Pressed, this, &ACOPlayerControllerBase::StartSelection);
	InputComponent->BindAction("Select", IE_Released, this, &ACOPlayerControllerBase::StopSelection);
}
