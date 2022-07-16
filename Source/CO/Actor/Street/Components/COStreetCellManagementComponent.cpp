// Fill out your copyright notice in the Description page of Project Settings.


#include "COStreetCellManagementComponent.h"


// Sets default values for this component's properties
UCOStreetCellManagementComponent::UCOStreetCellManagementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCOStreetCellManagementComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCOStreetCellManagementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                  FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCOStreetCellManagementComponent::ConstructCells()
{
}

void UCOStreetCellManagementComponent::SetCellsSelectable(bool Value)
{
}

void UCOStreetCellManagementComponent::GetSelectedCells(const TArray<UCOStreetCellComponent*> Cells)
{
}

bool UCOStreetCellManagementComponent::ValidateCells(const TArray<UCOStreetCellComponent*> Cells)
{
	return false;
}

void UCOStreetCellManagementComponent::AllocateCells(const TArray<UCOStreetCellComponent*> Cells)
{
}

void UCOStreetCellManagementComponent::OccupyCells(const TArray<UCOStreetCellComponent*> Cells)
{
}

