// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "COAllocateHelper.generated.h"

class UCOStreetCellComponent;
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
		static UCOSelectionDTO* CalculateSelectionData(AActor* Target, FVector Start, FVector End);

	UFUNCTION(BlueprintPure, meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject"))
		static UCOSelectionDTO* CalculateSelectionDataWithCells(AActor* Target, FVector Start, FVector End, TArray<UCOStreetCellComponent*>& OutSelectedCells);

	UFUNCTION(BlueprintPure)
	static bool ValidateSelectionData(UCOSelectionDTO* SelectionDTO, UCOBuildDTO* BuildDTO);
private:
	static bool RaycastWithRectangle(UWorld* World, FVector RectangleStart, FVector RectangleEnd, TArray<FHitResult>& OutHits);

	static TArray<UCOStreetCellComponent*> GetSelectedCells(AActor* Target, TArray<FHitResult>& HitResults);

	static void CollectSelectionData(UCOSelectionDTO* SelectionDTO, TArray<UCOStreetCellComponent*>& SelectedCells);
};
