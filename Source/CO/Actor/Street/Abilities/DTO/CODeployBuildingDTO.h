// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CODeployBuildingDTO.generated.h"

class UCOSelectionDTO;
class UCOBuildDTO;

/**
 * 
 */
UCLASS(Blueprintable)
class CO_API UCODeployBuildingDTO : public UObject
{
	GENERATED_BODY()
	
public:
	int Floors;

	FString BuildingName;

	UCOSelectionDTO* SelectionDTO;
};
