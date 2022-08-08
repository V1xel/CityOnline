// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/Interfaces/COSelectableActor.h"
#include "CO/Actor/Player/COPlayerCharacter.h"
#include "CO/Database/Enums/COStreetPrestige.h"
#include "Components/COStreetCellManagementComponent.h"
#include "GameFramework/Actor.h"
#include "COStreetActor.generated.h"

class UCOStreetBuildingComponent;
class UCOStreetInformationComponent;
class UCOStreetLeasingComponent;
class ACOBuildingActor;

UCLASS()
class CO_API ACOStreetActor : public AActor, public ICOSelectableActor
{
	GENERATED_BODY()

public:
	ACOStreetActor();

	ACOBuildingActor* CreateBuilding(const TArray<UCOStreetCellComponent*>& SelectedCells);

	void CalculatePotentialOutput();

	bool CheckBuildingRequirements();

	void CancelBuildingTransaction();

	void FailBuildingTransaction();
	
	void CommitBuildingTransaction();

	virtual void SelectActor_Implementation() override;

	virtual void DeselectActor_Implementation() override;

	virtual void OnConstruction(const FTransform& Transform) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCOStreetCellManagementComponent* CellManagementComponent{};
	
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
