﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "COSelectionDTO.generated.h"

USTRUCT(BlueprintType)
struct CO_API FCOSelectionDTOTargetData : public FGameplayAbilityTargetData
{
	GENERATED_USTRUCT_BODY()

	int32 Length;

	int32 Width;

	bool HasCorner;

	bool HasExtreme;

	FVector Center;

	FVector Direction;

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	UCOSelectionDTO* ToDTO();
};

/**
 * 
 */
UCLASS(Blueprintable)
class CO_API UCOSelectionDTO : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int32 Length;

	UPROPERTY(BlueprintReadOnly)
	int32 Width;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool HasCorner;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool HasExtreme;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Center;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Direction;

	FGameplayAbilityTargetDataHandle ToTargetDataHandle();
};
