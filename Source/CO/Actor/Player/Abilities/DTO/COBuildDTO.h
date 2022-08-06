// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "COBuildDTO.generated.h"

/**
 * !TODO May replace DTO With Payload in future. UCOBuildPayload
 */
UCLASS()
class CO_API UCOBuildDTO : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Floors;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool HasCorner;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector FrontDirection;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Location;
};
