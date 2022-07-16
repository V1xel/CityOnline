// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/COActorComponentBase.h"
#include "CO/Actor/Building/COBuildingConfiguration.h"
#include "COPlayerBuildingHandler.generated.h"

class ACOBuildingActor;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CO_API UCOPlayerBuildingHandler : public UCOActorComponentBase
{
	GENERATED_BODY()

public:
	void StartBuildingProcess(FCOBuildingConfiguration Configuration);

	void PreviewBuildingProcess(const TArray<UCOStreetCellComponent*>& SelectedCells);

	void UpdateBuildingConfiguration(FCOBuildingConfiguration Configuration);

	void EndBuildingProcess(const TArray<UCOStreetCellComponent*>& SelectedCells);

	void CancelBuildingProcess();

	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	FCOBuildingConfiguration Configuration {};
	
	UPROPERTY()
	ACOBuildingActor* BuildingActor{};
};
