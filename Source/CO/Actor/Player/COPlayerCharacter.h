// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COPlayerCharacterBase.h"
#include "GameFramework/Character.h"
#include "COPlayerCharacter.generated.h"

class UCOSelectActorAbility;
class UCOSelectCellsAbility;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CO_API ACOPlayerCharacter : public ACOPlayerCharacterBase
{
	GENERATED_BODY()

public:
	AActor* GetSelectedActor() const { return SelectedActor; }

	void SetSelectedActor(AActor* Value){ SelectedActor = Value; };
	
	void StartSelection();

	void EndSelection();
	
	void StartBuildingProcess();

	void UpdateBuildingConfiguration();

	void EndBuildingProcess();

	void CancelBuildingProcess();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditDefaultsOnly, Category="Character Abilities", meta=(BlueprintBaseOnly))
	TSubclassOf<UCOSelectActorAbility> SelectActorAbility{};

	UPROPERTY(EditDefaultsOnly, Category="Character Abilities", meta=(BlueprintBaseOnly))
	TSubclassOf<UCOSelectCellsAbility> SelectCellsAbility{};
private:
	UPROPERTY()
	AActor* SelectedActor;
	
};
