// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Net/UnrealNetwork.h>
#include "COStreetCellComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CO_API UCOStreetCellComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override
	{
		Super::GetLifetimeReplicatedProps(OutLifetimeProps);
		DOREPLIFETIME(UCOStreetCellComponent, IsOccupied);
		DOREPLIFETIME(UCOStreetCellComponent, IsSelected);
		DOREPLIFETIME(UCOStreetCellComponent, IsExtreme);
		DOREPLIFETIME(UCOStreetCellComponent, IsCorner);
		DOREPLIFETIME(UCOStreetCellComponent, Horizontal);
		DOREPLIFETIME(UCOStreetCellComponent, Vertical);
	}

public:
	void SetOccupied(bool Value);

	void SetSelected(bool Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetValid(bool Value);
	void SetValid_Implementation(bool Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetVisible(bool Value);
	void SetVisible_Implementation(bool Value);

public:
	UPROPERTY(BlueprintReadOnly, Replicated)
	bool IsOccupied;
	
	UPROPERTY(BlueprintReadOnly, Replicated)
	bool IsSelected;
	
	UPROPERTY(BlueprintReadOnly, Replicated)
	bool IsExtreme;
	
	UPROPERTY(BlueprintReadOnly, Replicated)
	bool IsCorner;
	
	UPROPERTY(BlueprintReadOnly, Replicated)
	int Horizontal;
	
	UPROPERTY(BlueprintReadOnly, Replicated)
	int Vertical;
};
