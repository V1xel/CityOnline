// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/Building/COBuildingConfiguration.h"
#include "Components/ActorComponent.h"
#include "COStreetBuildingComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CO_API UCOStreetBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCOStreetBuildingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void StartBuildingTransaction();
	
	void TryReserveCells();

	void SetBuildingParameters();

	void CalculatePotentialOutput();

	bool CheckBuildingRequirements();

	void CancelBuildingTransaction();
	
	void CommitBuildingTransaction();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FCOBuildingConfiguration> BuildingConfigurations {};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FCOBuildingConfiguration SelectedToBuild {};
};
