// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/Player/Abilities/DTO/COSelectionDTO.h"
#include "CO/Core/AbilitySystem/COAbilityTaskBase.h"
#include "UObject/Object.h"
#include "COSelectCellsAbilityTask.generated.h"

class UCOStreetCellComponent;
class UCOBuildingDetails;
class UCOSelectionDTO;
class UCOBuildDTO;

/**
 * 
 */
UCLASS()
class CO_API UCOAllocateAbilityHelper : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject"))
		static UCOSelectionDTO* CalculateSelectionData(const UObject* WorldContextObject, FVector Start, FVector End);

	UFUNCTION(BlueprintPure, meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject"))
		static UCOSelectionDTO* CalculateSelectionDataWithCells(const UObject* WorldContextObject, FVector Start, FVector End, TArray<UCOStreetCellComponent*>& OutSelectedCells);

	UFUNCTION(BlueprintPure)
	static bool ValidateSelectionData(UCOSelectionDTO* SelectionDTO, UCOBuildDTO* BuildDTO);
private:
	static bool RaycastWithRectangle(UWorld* World, FVector RectangleStart, FVector RectangleEnd, TArray<FHitResult>& OutHits);

	static TArray<UCOStreetCellComponent*> GetSelectedCells(TArray<FHitResult>& HitResults);

	static void CollectSelectionData(UCOSelectionDTO* SelectionDTO, TArray<UCOStreetCellComponent*>& SelectedCells);
private:
	UPROPERTY()
		FVector _SelectionStartedLocation{};
	UPROPERTY()
		TArray<UCOStreetCellComponent*> _LastSelectedCells{};

	UPROPERTY()
		UCOSelectionDTO* _SelectionDTO;
};
