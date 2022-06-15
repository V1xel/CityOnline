// Fill out your copyright notice in the Description page of Project Settings.


#include "COStreetActor.h"

#include "Components/COStreetBuildingComponent.h"

// Sets default values
ACOStreetActor::ACOStreetActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACOStreetActor::StartBuildingTransaction()
{
	BuildingComponent->StartBuildingTransaction();
}

void ACOStreetActor::TryReserveCells()
{
	BuildingComponent->TryReserveCells();
}

void ACOStreetActor::SetBuildingParameters()
{
	BuildingComponent->SetBuildingParameters();
}

void ACOStreetActor::CalculatePotentialOutput()
{
	BuildingComponent->CalculatePotentionalOutput();
}

bool ACOStreetActor::CheckBuildingRequirements()
{
	BuildingComponent->CheckBuildingRequirements();
}

void ACOStreetActor::CancelBuildingTransaction()
{
	BuildingComponent->CancelBuildingTransaction();
}

void ACOStreetActor::CommitBuildingTransaction()
{
	BuildingComponent->CommitBuildingTransaction();
}

void ACOStreetActor::GetStreetInfo()
{
}

void ACOStreetActor::GetProfitListingByPlayer()
{
}

void ACOStreetActor::GetEfficiencyByPlayer()
{
}

void ACOStreetActor::GetSelloutValueByPlayer()
{
}

void ACOStreetActor::GetBuildings()
{
}

void ACOStreetActor::GetRentListingByPlayer()
{
}

void ACOStreetActor::RequestStreetLeasing(float Price)
{
}

void ACOStreetActor::GetPriceRange()
{
}

void ACOStreetActor::GetOwner()
{
}

void ACOStreetActor::GetLeaseOverDate()
{
}
