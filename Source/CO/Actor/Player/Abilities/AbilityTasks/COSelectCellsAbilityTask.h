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
	virtual void Initialize() override;

	virtual void ExternalConfirm(bool bEndTask) override;

	void VisualizeSelection();

	UCOSelectionDTO* GetVisualisationResult();

	UCOSelectionDTO* CalculateSelectionData(FGameplayAbilityTargetDataHandle TargetData);
protected:
	virtual void TickTask(float DeltaTime) override;

	virtual void OnDestroy(bool AbilityIsEnding) override;

	bool RaycastWithRectangle(FVector RectangleStart, FVector RectangleEnd,	TArray<FHitResult>& OutHits) const;

	TArray<UCOStreetCellComponent*> GetSelectedCells(TArray<FHitResult>& HitResults);

	void CollectSelectionData(UCOSelectionDTO* SelectionDTO, TArray<UCOStreetCellComponent*>& SelectedCells);

	void ValidateSelectionData(UCOSelectionDTO* SelectionDTO, UCOBuildDTO* BuildDTO);

private:
	UPROPERTY()
		FVector _SelectionStartedLocation{};
	UPROPERTY()
		TArray<UCOStreetCellComponent*> _SelectedCells{};
	UPROPERTY()
		UCOBuildDTO* _BuildDTO;

	UPROPERTY()
		UCOSelectionDTO* _SelectionDTO;
};
