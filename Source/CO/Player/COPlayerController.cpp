// Fill out your copyright notice in the Description page of Project Settings.


#include "COPlayerController.h"

#include "Handlers/COPlayerBuildingHandler.h"

ACOPlayerController::ACOPlayerController()
{
	BuildingHandler = CreateDefaultSubobject<UCOPlayerBuildingHandler>(TEXT("BuildingHandler"));
}

void ACOPlayerController::StartBuildingProcess(FCOBuildingConfiguration Configuration)
{
	BuildingHandler->StartBuildingProcess(Configuration);
}

void ACOPlayerController::UpdateBuildingConfiguration(FCOBuildingConfiguration Configuration)
{
	BuildingHandler->UpdateBuildingConfiguration(Configuration);
}

void ACOPlayerController::EndBuildingProcess(const TArray<UCOStreetCellComponent*>& SelectedCells)
{
	BuildingHandler->EndBuildingProcess(SelectedCells);
}

void ACOPlayerController::CancelBuildingProcess()
{
	BuildingHandler->CancelBuildingProcess();
}
