// Fill out your copyright notice in the Description page of Project Settings.


#include "COVehicleCharacter.h"

#include "Components/BoxComponent.h"

// Sets default values
ACOVehicleCharacter::ACOVehicleCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void ACOVehicleCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACOVehicleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACOVehicleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

