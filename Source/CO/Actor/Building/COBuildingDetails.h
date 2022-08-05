// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "COBuildingDetails.generated.h"

UENUM(BlueprintType)
enum class EBuildingType : uint8 
{
	Retail     UMETA(DisplayName = "Retail"),
	Living     UMETA(DisplayName = "Living"),
};

UENUM(BlueprintType)
enum class EBuildingPrestige : uint8 
{
	Low			UMETA(DisplayName = "Low"),
	Medium		UMETA(DisplayName = "Medium"),
	High		UMETA(DisplayName = "High"),
};

UCLASS()
class CO_API UCOBuildingDetails : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EBuildingType Type;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MinWidth;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxWidth;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MinLength;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxLength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxFloors;
};
