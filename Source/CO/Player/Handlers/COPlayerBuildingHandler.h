// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/COActorComponentBase.h"
#include "CO/Actor/Building/COBuildingConfiguration.h"
#include "COPlayerBuildingHandler.generated.h"

class ACOBuildingActor;
class UCOStreetCellComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CO_API UCOPlayerBuildingHandler : public UCOActorComponentBase
{
	GENERATED_BODY()

public:
	void StartBuildingProcess(FCOBuildingConfiguration _Configuration);

	void UpdateBuildingConfiguration(FCOBuildingConfiguration _Configuration);

	void EndBuildingProcess(const TArray<UCOStreetCellComponent*>& SelectedCells);

	void CancelBuildingProcess();
protected:
	void PreviewBuildingProcess(const TArray<UCOStreetCellComponent*>& SelectedCells);

protected:
	UPROPERTY()
	FCOBuildingConfiguration Configuration {};
	
	UPROPERTY()
	ACOBuildingActor* BuildingActor{};
};
