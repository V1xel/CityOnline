﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CORootAsset.generated.h"

class UCOBuildingAsset;

/**
 * 
 */
UCLASS()
class CO_API UCORootAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UDataTable* Buildings;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UCOBuildingAsset*> BuildingsAssets;
};