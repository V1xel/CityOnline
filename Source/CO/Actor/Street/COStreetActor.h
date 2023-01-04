﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/Player/COPlayerCharacter.h"
#include "CO/Database/Enums/COStreetPrestige.h"
#include "GameFramework/Actor.h"
#include "COStreetActor.generated.h"


class UCOStreetBuildingComponent;
class UCOStreetInformationComponent;
class UCOStreetLeasingComponent;
class ACOBuildingActor;
class UCOStreetCellComponent;

UCLASS()
class CO_API ACOStreetActor : public AActor
{
	GENERATED_BODY()

public:
	ACOStreetActor();

	void CalculatePotentialOutput();

	bool CheckBuildingRequirements();

	void CancelBuildingTransaction();

	void FailBuildingTransaction();
	
	void CommitBuildingTransaction();

public:
	UPROPERTY()
	TArray<UCOStreetCellComponent*> Cells{};
	
protected:
	bool IsConstructed;
	
	UPROPERTY()
	UCOStreetInformationComponent* InformationComponent;
	
	UPROPERTY()
	UCOStreetLeasingComponent* LeasingComponent;

	UPROPERTY()
	USceneComponent* SceneComponent;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	FString _Name;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	ECOStreetPrestige _Prestige;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	ACOPlayerCharacter* _Tenant;
};
