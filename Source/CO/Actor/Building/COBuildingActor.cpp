// Fill out your copyright notice in the Description page of Project Settings.

#include "COBuildingActor.h"
#include "CO/Core/AbilitySystem/COAbilitySystemComponent.h"

ACOBuildingActor::ACOBuildingActor()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCOAbilitySystemComponent>("AbilitySystem");
}

void ACOBuildingActor::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}