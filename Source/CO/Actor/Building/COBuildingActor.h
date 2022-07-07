// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/Interfaces/SelectableActor.h"
#include "GameFramework/Actor.h"
#include "COBuildingActor.generated.h"

UENUM()
enum BuildingType
{
	Retail     UMETA(DisplayName = "Retail"),
	Living     UMETA(DisplayName = "Living"),
};

UENUM()
enum BuildingPrestige
{
	Low,
	Medium,
	High
};

UCLASS(Blueprintable)
class CO_API ACOBuildingActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACOBuildingActor();

	void GetInformation();
	
	void Sell();

	void Buy();
	
	void Refurbish();
	
	void Demolish();
private:
	bool IsSelected;

	BuildingType BuildingType;
};
