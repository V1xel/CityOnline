// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "COPlayerControllerBase.h"
#include "COPlayerController.generated.h"

class UCOPlayerBuildingHandler;
class UCOStreetCellComponent;

UCLASS()
class CO_API ACOPlayerController : public ACOPlayerControllerBase
{
	GENERATED_BODY()

public:
	void StartBuildingProcess();

	void UpdateBuildingConfiguration();

	void EndBuildingProcess(const TArray<UCOStreetCellComponent*>& SelectedCells);

	void CancelBuildingProcess();

protected:
	UPROPERTY()
	UCOPlayerBuildingHandler* BuildingHandler;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (DisplayName = "ASC"))
	UAbilitySystemComponent* AbilitySystemComponent{};
};
