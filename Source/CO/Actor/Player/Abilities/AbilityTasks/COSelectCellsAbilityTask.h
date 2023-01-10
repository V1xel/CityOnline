// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/Player/Abilities/DTO/COSelectionDTO.h"
#include "CO/Core/AbilitySystem/COAbilityTaskBase.h"
#include "COSelectCellsAbilityTask.generated.h"

class UCOStreetCellComponent;
class UCOBuildingDetails;
class UCOSelectionDTO;
class UCOBuildDTO;

/**
 * 
 */
UCLASS()
class CO_API UCOSelectCellsAbilityTask : public UCOAbilityTaskBase
{
	GENERATED_BODY()

public:
	virtual void ExternalConfirm(bool bEndTask) override;
protected:
	virtual void TickTask(float DeltaTime) override;

	virtual void OnDestroy(bool AbilityIsEnding) override;

	bool RaycastWithRectangle(FVector RectangleStart, FVector RectangleEnd,	TArray<FHitResult>& OutHits) const;

	void UpdateCellsState(TArray<FHitResult>& HitResults);

	void CollectSelectionData();

	void ValidateSelectionData();

public:
	UPROPERTY()
		UCOSelectionDTO* SelectionDTO{};

private:
	UPROPERTY()
		FVector _SelectionStartedLocation{};
	UPROPERTY()
		TArray<UCOStreetCellComponent*> _SelectedCells{};
	UPROPERTY()
		UCOBuildDTO* _BuildDTO {};
};
