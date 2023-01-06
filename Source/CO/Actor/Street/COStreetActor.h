// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/Player/COPlayerCharacter.h"
#include "CO/Database/Enums/COStreetPrestige.h"
#include "GameFramework/Actor.h"
#include "COStreetActor.generated.h"

class UCOAbilitySystemComponent;
class ACOBuildingActor;
class UCOStreetCellComponent;

UCLASS()
class CO_API ACOStreetActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACOStreetActor();

	virtual void BeginPlay() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void CalculatePotentialOutput();

	bool CheckBuildingRequirements();

	void CancelBuildingTransaction();

	void FailBuildingTransaction();
	
	void CommitBuildingTransaction();

public:
	UPROPERTY()
	TArray<UCOStreetCellComponent*> Cells{};


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UCOAbilitySystemComponent* AbilitySystemComponent {};
	
protected:
	bool IsConstructed;
	
	UPROPERTY()
	USceneComponent* SceneComponent;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	FString _Name;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	ECOStreetPrestige _Prestige;
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	ACOPlayerCharacter* _Tenant;
};
