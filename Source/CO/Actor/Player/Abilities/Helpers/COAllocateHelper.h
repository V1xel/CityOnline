﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "COAllocateHelper.generated.h"

class UCOStreetCellComponent;

struct FCOBuildAllocationTD;
/**
 * 
 */
UCLASS()
class CO_API UCOAllocateAbilityHelper : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject"))
		static FGameplayAbilityTargetDataHandle CalculateSelectionData(const AActor* Target, FVector Start, FVector End);

	UFUNCTION(BlueprintPure, meta = (bIgnoreSelf = "true", WorldContext = "WorldContextObject"))
		static FGameplayAbilityTargetDataHandle CalculateSelectionDataWithCells(const AActor* Target, FVector Start, FVector End, TArray<UCOStreetCellComponent*>& OutSelectedCells);

	UFUNCTION(BlueprintPure)
		static bool ValidateSelectionData(FGameplayAbilityTargetDataHandle SelectionDTOHandle, FGameplayAbilityTargetDataHandle BuildDTOHandle);
private:
	static bool RaycastWithRectangle(UWorld* World, FVector RectangleStart, FVector RectangleEnd, TArray<FHitResult>& OutHits);

	static TArray<UCOStreetCellComponent*> GetSelectedCells(const AActor* Target, TArray<FHitResult>& HitResults);

	static void CollectSelectionData(FCOBuildAllocationTD* SelectionDTO, TArray<UCOStreetCellComponent*>& SelectedCells);
};
