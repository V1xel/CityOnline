// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "COBuildConfigurationDTO.generated.h"

USTRUCT(BlueprintType)
struct CO_API FCOBuildConfigurationDTOTargetData : public FGameplayAbilityTargetData
{
	GENERATED_USTRUCT_BODY()

	int32 Floors;

	FName BuildingName;

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	UCOBuildConfigurationDTO* ToDTO() const;
};
/**
 * 
 */
UCLASS()
class CO_API UCOBuildConfigurationDTO : public UObject
{
	GENERATED_BODY()
	
public:

	int32 Floors;

	FName BuildingName;

	FGameplayAbilityTargetDataHandle ToTargetDataHandle();

	UFUNCTION(BlueprintPure)
	static FGameplayAbilityTargetDataHandle MakeBuildConfigurationTargetDataHandle(FName InBuildingName, int32 InFloors);
};
