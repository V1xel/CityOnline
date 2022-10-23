// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "COSelectionDTO.generated.h"

/**
 * 
 */
UCLASS()
class CO_API UCOSelectionDTO : public UObject
{
	GENERATED_BODY()

public:
	int Length;

	int Width;

	int Flours;

	bool HasCorner;

	bool HasExtreme;
};
