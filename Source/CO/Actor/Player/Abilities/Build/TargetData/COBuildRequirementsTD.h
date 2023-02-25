// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "COBuildRequirementsTD.generated.h"

USTRUCT(BlueprintType)
struct CO_API FCOBuildRequirementsTD : public FGameplayAbilityTargetData
{
	GENERATED_USTRUCT_BODY()

	FString Name;

	int32 MinWidth;

	int32 MaxWidth;

	int32 MinLength;

	int32 MaxLength;

	int32 MinFloors;

	int32 MaxFloors;

	virtual FString ToString() const override
	{
		return TEXT("FCOBuildRequirementsTD");
	}

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};

template <>
struct TStructOpsTypeTraits<FCOBuildRequirementsTD> : public TStructOpsTypeTraitsBase2<FCOBuildRequirementsTD>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true // Necessary so that TSharedPtr<FHitResult> Data is copied around
	};
};
