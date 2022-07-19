// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/Building/COBuildingConfiguration.h"
#include "UObject/Object.h"
#include "COSetBuildingAttributes.generated.h"

/**
 * 
 */
UCLASS()
class CO_API UCOSetBuildingAttributes : public UObject
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
