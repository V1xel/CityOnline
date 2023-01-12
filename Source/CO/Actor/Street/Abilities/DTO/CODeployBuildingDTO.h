// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CODeployBuildingDTO.generated.h"

class UCOBuildingAsset;

/**
 * 
 */
UCLASS(Blueprintable)
class CO_API UCODeployBuildingDTO : public UObject
{
	GENERATED_BODY()
	
public:
	int Floors;

	int Style;

	int Quality;

	TArray<UCOStreetCellComponent*> _SelectedCells{};
};
