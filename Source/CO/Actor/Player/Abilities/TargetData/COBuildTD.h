﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "COBuildTD.generated.h"

USTRUCT(BlueprintType)
struct CO_API FCOBuildTD : public FGameplayAbilityTargetData
{
	GENERATED_USTRUCT_BODY()

	FString Name;

	int32 MinWidth;

	int32 MaxWidth;

	int32 MinLength;

	int32 MaxLength;

	int32 MinFloors;

	int32 MaxFloors;

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};