// Fill out your copyright notice in the Description page of Project Settings.


#include "COPlayerBuildingHandler.h"
#include "CO/Actor/Building/COBuildingActor.h"
#include "CO/Actor/Street/COStreetActor.h"
#include "CO/Player/Components/COActorSelectionComponent.h"
#include "CO/Player/Components/COCellSelectionComponent.h"

void UCOPlayerBuildingHandler::StartBuildingProcess(FCOBuildingConfiguration _Configuration)
{
	this->Configuration = Configuration;
	const auto CellSelection = GetOwnerComponent<UCOCellSelectionComponent>(UCOCellSelectionComponent::StaticClass());
	CellSelection->EnableSelection();
	CellSelection->OnSelectionEnded.AddDynamic(this, &UCOPlayerBuildingHandler::PreviewBuildingProcess);
}

void UCOPlayerBuildingHandler::PreviewBuildingProcess(const TArray<UCOStreetCellComponent*>& SelectedCells)
{
	const auto CellSelection = GetOwnerComponent<UCOCellSelectionComponent>(UCOCellSelectionComponent::StaticClass());
	CellSelection->OnSelectionEnded.RemoveAll(this);
	
	const auto ActorSelection = GetOwnerComponent<UCOActorSelectionComponent>(UCOCellSelectionComponent::StaticClass());
	const auto SelectedStreet = ActorSelection->GetSelectedActor<ACOStreetActor>();
	BuildingActor = SelectedStreet->CreateBuilding(Configuration, SelectedCells);
}

void UCOPlayerBuildingHandler::UpdateBuildingConfiguration(FCOBuildingConfiguration _Configuration)
{
	BuildingActor->UpdateConfiguration(_Configuration);
}

void UCOPlayerBuildingHandler::EndBuildingProcess(const TArray<UCOStreetCellComponent*>& SelectedCells)
{
	BuildingActor->ApplyChanges();
	BuildingActor = nullptr;
}

void UCOPlayerBuildingHandler::CancelBuildingProcess()
{
	BuildingActor->RemoveActor();
	this->Configuration = {};
}
