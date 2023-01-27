// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "COSelectionTD.generated.h"

USTRUCT(BlueprintType)
struct CO_API FCOSelectionTD : public FGameplayAbilityTargetData
{
	GENERATED_USTRUCT_BODY()

	int32 Length;

	int32 Width;

	bool HasCorner;

	bool HasExtreme;

	FVector Center;

	FVector Direction;

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};
