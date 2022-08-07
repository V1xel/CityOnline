// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COPlayerCharacterBase.h"
#include "GameplayTagContainer.h"
#include "Abilities/COBuildAbility.h"
#include "GameFramework/Character.h"
#include "COPlayerCharacter.generated.h"

class UCOSelectActorAbility;
class UCOSelectCellsAbility;
class USpringArmComponent;
class UCameraComponent;
class ACOStreetActor;
class ACOBuildingActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStreetSelectedDelegate, const ACOStreetActor*, Street);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingSelectedDelegate, const ACOBuildingActor*, Building);

UCLASS()
class CO_API ACOPlayerCharacter : public ACOPlayerCharacterBase
{
	GENERATED_BODY()

public:
	AActor* GetSelectedActor() const { return SelectedActor; }

	void SetSelectedActor(AActor* Value);;
	
	void StartSelection();

	void EndSelection();
	
	void StartBuildingProcess() const;

	void UpdateBuildingConfiguration();

	void EndBuildingProcess();

	void CancelBuildingProcess();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnStreetSelectedDelegate OnStreetSelected{};

	UPROPERTY(BlueprintAssignable)
	FOnBuildingSelectedDelegate OnBuildingSelected{};
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Character Abilities")
	FGameplayTag SelectionAction;

	UPROPERTY(EditDefaultsOnly, Category="Character Abilities", meta=(BlueprintBaseOnly))
	TSubclassOf<UCOSelectActorAbility> SelectActorAbility{};

	UPROPERTY(EditDefaultsOnly, Category="Character Abilities", meta=(BlueprintBaseOnly))
	TSubclassOf<UCOSelectCellsAbility> SelectCellsAbility{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Character Abilities")
	FGameplayTag BuildingAction;

	UPROPERTY(EditDefaultsOnly, Category="Character Abilities", meta=(BlueprintBaseOnly))
	TSubclassOf<UCOBuildAbility> BuildAbility{};
private:
	UPROPERTY()
	AActor* SelectedActor;
	
};
