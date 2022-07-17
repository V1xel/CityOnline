// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COPlayerControllerBase.h"
#include "CO/Actor/Building/COBuildingConfiguration.h"
#include "COPlayerController.generated.h"

class UCOPlayerBuildingHandler;
class UCOStreetCellComponent;

UCLASS()
class CO_API ACOPlayerController : public ACOPlayerControllerBase
{
	GENERATED_BODY()

public:
	ACOPlayerController();

	void StartBuildingProcess(FCOBuildingConfiguration Configuration);

	void UpdateBuildingConfiguration(FCOBuildingConfiguration Configuration);

	void EndBuildingProcess(const TArray<UCOStreetCellComponent*>& SelectedCells);

	void CancelBuildingProcess();

protected:
	UPROPERTY()
	UCOPlayerBuildingHandler* BuildingHandler;
};
