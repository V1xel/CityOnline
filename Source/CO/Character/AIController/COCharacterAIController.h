// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "COCharacterAIController.generated.h"

class UAISenseConfig_Sight;
class UAISense;

UCLASS()
class CO_API ACOCharacterAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACOCharacterAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UBehaviorTree* BehaviourTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Test)
	UAIPerceptionComponent* AIPerception;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Test)
	UAISenseConfig_Sight* SightSense;

	TArray<AActor*> GetPerceivedActors(TSubclassOf<UAISense> SenseToUse);
};
