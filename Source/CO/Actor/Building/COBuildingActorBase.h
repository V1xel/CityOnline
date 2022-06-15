// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/Interfaces/SelectableActor.h"
#include "GameFramework/Actor.h"
#include "COBuildingActorBase.generated.h"

UENUM()
enum BuildingType
{
	Retail     UMETA(DisplayName = "Retail"),
	Living     UMETA(DisplayName = "Living"),
};

UCLASS(Blueprintable)
class CO_API ACOBuildingActorBase : public AActor, public ISelectableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACOBuildingActorBase();

	virtual void Select() override;

	virtual void Deselect() override;

	void GetInformation();
	
	void Sell();

	void Buy();
	
	void Refurbish();
	
	void Demolish();
private:
	bool IsSelected;

	BuildingType BuildingType;
};
