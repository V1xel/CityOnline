// Fill out your copyright notice in the Description page of Project Settings.


#include "COStreetActor.h"

#include "CO/Actor/Building/COBuildingActor.h"
#include "Components/COStreetBuildingComponent.h"

ACOStreetActor::ACOStreetActor()
{
	PrimaryActorTick.bCanEverTick = true;
	BuildingComponent = CreateDefaultSubobject<UCOStreetBuildingComponent>(TEXT("BuildingComponent"));
}

ACOBuildingActor* ACOStreetActor::CreateBuilding(FCOBuildingConfiguration Configuration, const TArray<UCOStreetCellComponent*>& SelectedCells)
{
	return nullptr;
}

ACOBuildingActor* ACOStreetActor::UpdateBuilding(FCOBuildingConfiguration Configuration)
{
	return nullptr;
}