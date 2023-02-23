// Fill out your copyright notice in the Description page of Project Settings.

#include "COBuildingActor.h"
#include "CO/Core/AbilitySystem/COAbilitySystemComponent.h"
#include <CO/Core/Actor/Building/COBuildingFunctionLibrary.h>

ACOBuildingActor::ACOBuildingActor()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCOAbilitySystemComponent>("AbilitySystem");
}

void ACOBuildingActor::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ACOBuildingActor::ComposeBuilding(int32 Floors, UCOBuildingAsset* BuildingAsset, FVector Direction)
{
	UCOBuildingFunctionLibrary::ComposeBuilding(this, Floors, BuildingPartComponentClass, BuildingAsset, Direction, Meshes);
}
