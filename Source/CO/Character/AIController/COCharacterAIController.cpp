// Fill out your copyright notice in the Description page of Project Settings.


#include "COCharacterAIController.h"

// Sets default values
ACOCharacterAIController::ACOCharacterAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACOCharacterAIController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACOCharacterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

