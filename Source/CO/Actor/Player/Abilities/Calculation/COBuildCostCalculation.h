// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "COBuildCostCalculation.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CO_API UCOBuildCostCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* BuildingsTable {};
};
