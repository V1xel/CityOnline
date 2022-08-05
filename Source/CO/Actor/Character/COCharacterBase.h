// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/AbilitySystem/COAbilitySystemComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "COCharacterBase.generated.h"

class UBehaviorTree;
class AAIController;
class UCOActorSelectionComponent;

UCLASS()
class CO_API ACOCharacterBase : public ADefaultPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACOCharacterBase();

	virtual void MoveTo(FVector DestinationPoint);
public:
	bool IsSelected;

	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBehaviorTree* BehaviorTree{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCOAbilitySystemComponent* AbilitySystemComponent{};
	
};
