// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/Interfaces/SelectableActor.h"
#include "GameFramework/Character.h"
#include "COCharacterBase.generated.h"

class UBehaviorTree;
class AAIController;

UCLASS()
class CO_API ACOCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACOCharacterBase();

	virtual void MoveTo(FVector DestinationPoint);
public:
	bool IsSelected;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBehaviorTree* BehaviorTree;
};
