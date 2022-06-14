// Fill out your copyright notice in the Description page of Project Settings.

#include "COCharacterAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
ACOCharacterAIController::ACOCharacterAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	/*AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SetPerceptionComponent(*AIPerception);

	SightSense = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightSense"));
	SightSense->DetectionByAffiliation.bDetectEnemies = true;
	SightSense->DetectionByAffiliation.bDetectNeutrals = true;
	SightSense->DetectionByAffiliation.bDetectFriendlies = true;
	SightSense->SightRadius = 4000;
	SightSense->LoseSightRadius = 4500;
	SightSense->PeripheralVisionAngleDegrees = 360.0f;
	SightSense->AutoSuccessRangeFromLastSeenLocation = -1;
	SightSense->SetMaxAge(0);
	AIPerception->SetSenseEnabled(UAISenseConfig_Sight::StaticClass(), true);
	AIPerception->ConfigureSense(*SightSense);*/
}

// Called when the game starts or when spawned
void ACOCharacterAIController::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority() && BehaviourTree)
	{
		RunBehaviorTree(BehaviourTree);
	}
}

// Called every frame
void ACOCharacterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<AActor*> ACOCharacterAIController::GetPerceivedActors(TSubclassOf<UAISense> SenseToUse)
{
	TArray<AActor*> ActorsSensed;
	//AIPerception->GetPerceivedActors(SenseToUse, ActorsSensed);
	return ActorsSensed;
}
