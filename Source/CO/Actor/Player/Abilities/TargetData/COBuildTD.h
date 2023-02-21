// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	float CapacityMultiplier;

	float CostMultiplier;

	virtual FString ToString() const override
	{
		return TEXT("FCOBuildTD");
	}

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template <>
struct TStructOpsTypeTraits<FCOBuildTD> : public TStructOpsTypeTraitsBase2<FCOBuildTD>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true // Necessary so that TSharedPtr<FHitResult> Data is copied around
	};
};
