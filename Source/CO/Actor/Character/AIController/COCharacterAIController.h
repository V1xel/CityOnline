﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "COCharacterAIController.generated.h"

class UAISenseConfig_Sight;
class UAISense;

UCLASS()
class CO_API ACOCharacterAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACOCharacterAIController();

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

protected:
	TArray<AActor*> GetPerceivedActors(TSubclassOf<UAISense> SenseToUse);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBehaviorTree* BehaviourTree;
};
