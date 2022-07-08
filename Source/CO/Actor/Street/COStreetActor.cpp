// Fill out your copyright notice in the Description page of Project Settings.


#include "COStreetActor.h"

#include "Components/COStreetBuildingComponent.h"

ACOStreetActor::ACOStreetActor()
{
	PrimaryActorTick.bCanEverTick = true;
	BuildingComponent = CreateDefaultSubobject<UCOStreetBuildingComponent>(TEXT("BuildingComponent"));
}

void ACOStreetActor::StartBuildingTransaction()
{
	//BuildingComponent->StartBuildingTransaction();
}

void ACOStreetActor::TryReserveCells()
{
	//BuildingComponent->TryReserveCells();
}

void ACOStreetActor::SetBuildingParameters()
{
	//BuildingComponent->SetBuildingParameters();
}

void ACOStreetActor::CalculatePotentialOutput()
{
	//BuildingComponent->CalculatePotentialOutput();
}

bool ACOStreetActor::CheckBuildingRequirements()
{
	//BuildingComponent->CheckBuildingRequirements();
	return false;
}

void ACOStreetActor::CancelBuildingTransaction()
{
	//BuildingComponent->CancelBuildingTransaction();
}

void ACOStreetActor::FailBuildingTransaction()
{
}

void ACOStreetActor::CommitBuildingTransaction()
{
//	BuildingComponent->CommitBuildingTransaction();
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
