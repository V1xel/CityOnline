// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "COBuildDTO.generated.h"

USTRUCT(BlueprintType)
struct CO_API FCOBuildDTOContext
{
	GENERATED_BODY()

	int32 MinWidth;

	int32 MaxWidth;

	int32 MinLength;

	int32 MaxLength;

	int32 MinFlours;

	int32 MaxFlours;

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
};


UCLASS(Blueprintable)
class CO_API UCOBuildDTO : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MinWidth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxWidth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MinLength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxLength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MinFlours;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxFlours;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsLiving;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsStore;

	FCOBuildDTOContext ToStruct() {
		auto Struct = FCOBuildDTOContext();
		Struct.MinWidth = MinWidth;
		Struct.MaxWidth = MaxWidth;
		Struct.MinLength = MinLength;
		Struct.MaxLength = MaxLength;
		Struct.MinFlours = MinFlours;
		Struct.MaxFlours = MaxFlours;

		return Struct;
	}
};
