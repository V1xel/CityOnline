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

	AActor* Target;

	int32 Length;

	int32 Width;

	int32 ExtremeCount;

	bool HasCorner;

	bool HasExtreme;

	FVector Center;

	FVector Direction;

	virtual FString ToString() const override
	{
		return TEXT("FCOSelectionTD");
	}

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	virtual TArray<TWeakObjectPtr<AActor>> GetActors() const
	{
		auto Array = TArray<TWeakObjectPtr<AActor>>();
		Array.Add(Target);

		return Array;
	}

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	static AActor* GetTarget(FGameplayAbilityTargetDataHandle Handle);
};

template <>
struct TStructOpsTypeTraits<FCOSelectionTD> : public TStructOpsTypeTraitsBase2<FCOSelectionTD>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true // Necessary so that TSharedPtr<FHitResult> Data is copied around
	};
};
