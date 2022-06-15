// Fill out your copyright notice in the Description page of Project Settings.


#include "COVehicleCharacter.h"


// Sets default values
ACOVehicleCharacter::ACOVehicleCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

