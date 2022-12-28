// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COBuildingAsset.generated.h"

/**
 * 
 */
UCLASS()
class CO_API UCOBuildingAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator RotationOffset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Width;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Length;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsLiving;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsStore;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool HasCorner;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FloorHeight = 410;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* FirstFloor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* MiddleFloor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* Roof;
};
