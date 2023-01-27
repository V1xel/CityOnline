// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "COBuildDTO.generated.h"

USTRUCT(BlueprintType)
struct CO_API FCOBuildDTOTargetData : public FGameplayAbilityTargetData
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

	UCOBuildDTO* ToDTO();
};


UCLASS(Blueprintable)
class CO_API UCOBuildDTO : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MinWidth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MaxWidth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MinLength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MaxLength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MinFloors;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MaxFloors;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsLiving;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool IsStore;

	FGameplayAbilityTargetDataHandle ToTargetDataHandle();
};
