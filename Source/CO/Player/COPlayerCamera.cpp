// Fill out your copyright notice in the Description page of Project Settings.


#include "COPlayerCamera.h"


// Sets default values
ACOPlayerCamera::ACOPlayerCamera()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACOPlayerCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACOPlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACOPlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

