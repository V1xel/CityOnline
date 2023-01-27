// Fill out your copyright notice in the Description page of Project Settings.

#include "COPlayerCharacter.h"
#include "CO/Core/AbilitySystem/COAbilitySystemComponent.h"
#include "GameplayTagContainer.h"

ACOPlayerCharacter::ACOPlayerCharacter() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACOPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}
