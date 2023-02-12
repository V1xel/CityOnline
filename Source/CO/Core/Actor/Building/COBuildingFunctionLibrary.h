// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "COBuildingFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CO_API UCOBuildingFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable)
	static void ComposeBuilding(AActor* Owner, int32 Floors, TSubclassOf<UCOBuildingPartComponent> BuildingPartComponentClass, UCOBuildingAsset* BuildingAsset, FVector Direction, TArray<UCOBuildingPartComponent*>& OutParts);
};
