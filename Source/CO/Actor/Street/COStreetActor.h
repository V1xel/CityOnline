// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/Interfaces/SelectableActor.h"
#include "GameFramework/Actor.h"
#include "COStreetActor.generated.h"

class UCOStreetBuildingComponent;
class UCOStreetInformationComponent;
class UCOStreetLeasingComponent;

UENUM()
enum StreetPrestige
{
	Low,
	Medium,
	High
};

UCLASS()
class CO_API ACOStreetActor : public AActor, public ISelectableActor
{
	GENERATED_BODY()

public:
	ACOStreetActor();

	//General
	void GetBuildings();

	//Layout
	void GetLayoutGrid();

	void CheckCellsFree();

	void TryReserveCells();
	
	//Building
	void StartBuildingTransaction();

	void SetBuildingParameters();

	void CalculatePotentialOutput();

	bool CheckBuildingRequirements();

	void CancelBuildingTransaction();

	void FailBuildingTransaction();
	
	void CommitBuildingTransaction();

	//Information
	void GetStreetInfo();
	
	void GetRentListingByPlayer();

	void GetProfitListingByPlayer();

	void GetEfficiencyByPlayer();

	void GetSelloutValueByPlayer();

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
