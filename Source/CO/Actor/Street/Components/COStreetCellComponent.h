// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/COSelectableComponent.h"
#include "COStreetCellComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CO_API UCOStreetCellComponent : public UStaticMeshComponent, public ICOSelectableComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCOStreetCellComponent();

public:
	virtual void SelectComponent_Implementation() override;

	virtual void DeselectComponent_Implementation() override;

	void SetValid(bool Value);

	void SetVisible(bool Value);

public:
	UPROPERTY(BlueprintReadOnly)
	bool IsOccupied;
	
	UPROPERTY(BlueprintReadOnly)
	bool IsSelected;
	
	UPROPERTY(BlueprintReadOnly)
	bool IsExtreme;
	
	UPROPERTY(BlueprintReadOnly)
	bool IsCorner;
	
	UPROPERTY(BlueprintReadOnly)
	int Horizontal;
	
	UPROPERTY(BlueprintReadOnly)
	int Vertical;

	UPROPERTY(BlueprintReadWrite)
	UMaterialInstanceDynamic* DynamicMaterial;
};
