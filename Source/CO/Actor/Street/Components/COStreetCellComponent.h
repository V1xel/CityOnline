// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/Interfaces/SelectableComponent.h"
#include "Components/ActorComponent.h"
#include "COStreetCellComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CO_API UCOStreetCellComponent : public UActorComponent, public ISelectableComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCOStreetCellComponent();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SelectComponent_Implementation() override;

	virtual void DeselectComponent_Implementation() override;
protected:
	bool IsOccupied;

	bool IsSelected;

	bool IsExtreme;

	bool IsCorner;
};
