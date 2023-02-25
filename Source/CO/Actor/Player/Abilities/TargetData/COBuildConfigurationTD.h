// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "COBuildConfigurationTD.generated.h"

USTRUCT(BlueprintType)
struct CO_API FCOBuildConfigurationTD : public FGameplayAbilityTargetData
{
	GENERATED_USTRUCT_BODY()

	int32 Floors;

	FName BuildingName;

	virtual FString ToString() const override
	{
		return TEXT("FCOBuildConfigurationTD");
	}

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	static FName GetBuildingName(FGameplayAbilityTargetDataHandle Handle);
};

template <>
struct TStructOpsTypeTraits<FCOBuildConfigurationTD> : public TStructOpsTypeTraitsBase2<FCOBuildConfigurationTD>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true // Necessary so that TSharedPtr<FHitResult> Data is copied around
	};
};
