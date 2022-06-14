// Fill out your copyright notice in the Description page of Project Settings.

#include "COCharacterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
ACOCharacterAIController::ACOCharacterAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTFinder(TEXT("BehaviorTree'/Game/CityOnline/AI/CitizenBehaviour.CitizenBehaviour'"));
	//BehaviourTree = BTFinder.Object;

	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
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
	AIPerception->ConfigureSense(*SightSense);
}

// Called when the game starts or when spawned
void ACOCharacterAIController::BeginPlay()
{
	Super::BeginPlay();
	
	//RunBehaviorTree(BehaviourTree);
}

// Called every frame
void ACOCharacterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TArray<AActor*> ACOCharacterAIController::GetPerceivedActors(TSubclassOf<UAISense> SenseToUse)
{
	TArray<AActor*> ActorsSensed;
	AIPerception->GetPerceivedActors(SenseToUse, ActorsSensed);
	return ActorsSensed;
}
