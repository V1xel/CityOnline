// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COStreetCellComponent.h"
#include "Components/ActorComponent.h"
#include "COStreetCellManagementComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCellSelected);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CO_API UCOStreetCellManagementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCOStreetCellManagementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;
public:
	void ConstructCells();

	void SetCellsSelectable(bool Value);

	void GetSelectedCells(const TArray<UCOStreetCellComponent*> Cells);

    void AllocateCells(const TArray<UCOStreetCellComponent*> Cells);
	
	bool ValidateCells(const TArray<UCOStreetCellComponent*> Cells);

	void OccupyCells(const TArray<UCOStreetCellComponent*> Cells);
protected:
	int HorizontalCells;

	int VerticalCells;

	float CellSize;

	float Coverage;

	bool IsSelectionValid;

	FOnCellSelected OnCellSelected;
};
