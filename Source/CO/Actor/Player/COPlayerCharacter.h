// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COPlayerCharacterBase.h"
#include "GameFramework/Character.h"
#include "COPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CO_API ACOPlayerCharacter : public ACOPlayerCharacterBase
{
	GENERATED_BODY()

public:
	ACOPlayerCharacter();

	AActor* GetSelectedActor() const { return SelectedActor; }

	void SetSelectedActor(AActor* Value){ SelectedActor = Value; };
	
	void StartSelection();

	void EndSelection();
	
	void StartBuildingProcess();

	void UpdateBuildingConfiguration();

	void EndBuildingProcess();

	void CancelBuildingProcess();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY()
	AActor* SelectedActor;
};
