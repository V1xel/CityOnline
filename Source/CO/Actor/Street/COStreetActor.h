// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/Building/COBuildingConfiguration.h"
#include "Components/COStreetCellManagementComponent.h"
#include "GameFramework/Actor.h"
#include "COStreetActor.generated.h"

class UCOStreetBuildingComponent;
class UCOStreetInformationComponent;
class UCOStreetLeasingComponent;
class ACOBuildingActor;

UCLASS()
class CO_API ACOStreetActor : public AActor
{
	GENERATED_BODY()

public:
	ACOStreetActor();

	ACOBuildingActor* CreateBuilding(FCOBuildingConfiguration Configuration, const TArray<UCOStreetCellComponent*>& SelectedCells);

	void CalculatePotentialOutput();

	bool CheckBuildingRequirements();

	void CancelBuildingTransaction();

	void FailBuildingTransaction();
	
	void CommitBuildingTransaction();
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCOStreetBuildingComponent* BuildingComponent;
	
	UPROPERTY()
	UCOStreetInformationComponent* InformationComponent;
	
	UPROPERTY()
	UCOStreetLeasingComponent* LeasingComponent;
	
	UPROPERTY()
	UCOStreetCellManagementComponent* CellManagementComponent;
};
