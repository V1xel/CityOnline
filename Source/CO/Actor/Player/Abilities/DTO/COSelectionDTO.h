// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "COSelectionDTO.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CO_API UCOSelectionDTO : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int Length;

	UPROPERTY(BlueprintReadOnly)
	int Width;

	bool HasCorner = false;

	bool HasExtreme = false;

	FVector Center;

	FRotator Rotation;
};
