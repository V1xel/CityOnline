// Fill out your copyright notice in the Description page of Project Settings.


#include "COCharacterBase.h"


// Sets default values
ACOCharacterBase::ACOCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACOCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACOCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACOCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

