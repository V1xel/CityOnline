// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COStreetCellComponent.h"
#include "COStreetCellManagementComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCellSelected);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CO_API UCOStreetCellManagementComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UCOStreetCellManagementComponent();
	
public:
	UFUNCTION(BlueprintCallable)
	void ConstructCells();

	void SetCellsSelectable(bool Value);

	void GetSelectedCells(const TArray<UCOStreetCellComponent*> _Cells);

    void AllocateCells(const TArray<UCOStreetCellComponent*> _Cells);
	
	bool ValidateCells(const TArray<UCOStreetCellComponent*> _Cells);

	void OccupyCells(const TArray<UCOStreetCellComponent*> _Cells);

protected:
	
	bool IsSelectionValid;

	FOnCellSelected OnCellSelected;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int Horizontal = 6; 
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int Vertical = 6;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float Coverage = 0.83;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float Size = 0.17f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<UCOStreetCellComponent*> Cells{};
};
