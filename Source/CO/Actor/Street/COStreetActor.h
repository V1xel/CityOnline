// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "COStreetActor.generated.h"

class UCOStreetBuildingComponent;
class UCOStreetInformationComponent;
class UCOStreetLeasingComponent;

UCLASS()
class CO_API ACOStreetActor : public AActor
{
	GENERATED_BODY()

public:
	ACOStreetActor();

	//Building
	void StartBuildingTransaction();
	
	void TryReserveCells();

	void SetBuildingParameters();

	void CalculatePotentionalOutput();

	bool CheckBuildingRequirements();

	void CancelBuildingTransaction();
	
	void CommitBuildingTransaction();
	
	//Information
	void GetBuildings();

	void GetRentListingByPlayer();

	//Leasing
	void RequestStreetLeasing(float Price);

	void GetPriceRange();

	void GetOwner();

	void GetLeaseOverDate();
protected:
	UCOStreetBuildingComponent* BuildingComponent;

	UCOStreetInformationComponent* InformationComponent;

	UCOStreetLeasingComponent* LeasingComponent;
};
