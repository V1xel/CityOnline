﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbilityTargetDataFilter.h"
#include "GameplayEffectTypes.h"
#include "Delegates/IDelegateInstance.h"
#include "COStreetActor.generated.h"

class ACOBuildingActor;
class UCOStreetCellComponent;
class ACOPlayerCharacter;

struct FCOBuildAllocationTD;

UCLASS()
class CO_API ACOStreetActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACOStreetActor();

	virtual void BeginPlay() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override 
	{
		return AbilitySystemComponent;
	}

	void OccupyCells(const FCOBuildAllocationTD* AllocationTD);

	void ReleaseCells(const FCOBuildAllocationTD* AllocationTD);

public:
	UPROPERTY()
	TArray<UCOStreetCellComponent*> Cells{};

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystemComponent {};
protected:
	UPROPERTY()
	USceneComponent* SceneComponent;
};
