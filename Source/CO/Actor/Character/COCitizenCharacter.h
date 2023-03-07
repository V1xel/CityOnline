// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Core/Actor/Player/COPlayerCharacterBase.h"
#include "GameFramework/Character.h"
#include "COCitizenCharacter.generated.h"

class ACOBuildingActor;

UCLASS()
class CO_API ACOCitizenCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACOCitizenCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void AddBuildingVisited(ACOBuildingActor* Building);

	UFUNCTION(BlueprintCallable)
	void ClearVisitedBuildings();

	UFUNCTION(BlueprintCallable)
	bool CheckBuildingVisited(ACOBuildingActor* Building);

	UFUNCTION(BlueprintCallable)
	ACOBuildingActor* GetCheapestShop();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RegenerateShoppingList();
public:
	UPROPERTY(BlueprintReadOnly)
	TSet<ACOBuildingActor*> VisitedBuildings;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTagContainer ShoppingList;
};
