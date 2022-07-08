// Fill out your copyright notice in the Description page of Project Settings.


#include "COStreetBuildingComponent.h"


// Sets default values for this component's properties
UCOStreetBuildingComponent::UCOStreetBuildingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UCOStreetBuildingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCOStreetBuildingComponent::StartBuildingTransaction()
{
}

void UCOStreetBuildingComponent::TryReserveCells()
{
}

void UCOStreetBuildingComponent::SetBuildingParameters()
{
}

void UCOStreetBuildingComponent::CalculatePotentialOutput()
{
}

bool UCOStreetBuildingComponent::CheckBuildingRequirements()
{
	return false;
}

void UCOStreetBuildingComponent::CancelBuildingTransaction()
{
}

void UCOStreetBuildingComponent::CommitBuildingTransaction()
{
}
