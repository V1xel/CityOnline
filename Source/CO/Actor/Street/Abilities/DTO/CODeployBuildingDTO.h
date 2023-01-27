// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "CO/Actor/Player/Abilities/DTO/COSelectionDTO.h"
#include "CODeployBuildingDTO.generated.h"

USTRUCT(BlueprintType)
struct CO_API FCODeployDTOTargetData : public FGameplayAbilityTargetData
{
	GENERATED_USTRUCT_BODY()

	int Floors;

	FString BuildingName;

	FCOSelectionDTOTargetData SelectionDTO;

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	UCODeployBuildingDTO* ToDTO();
};

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

	FGameplayAbilityTargetData* ToTargetData();
};
