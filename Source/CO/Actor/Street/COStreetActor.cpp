// Fill out your copyright notice in the Description page of Project Settings.


#include "COStreetActor.h"

#include "CO/Actor/Building/COBuildingActor.h"

ACOStreetActor::ACOStreetActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetMobility(EComponentMobility::Static);
	SetRootComponent(SceneComponent);
}

void ACOStreetActor::SelectActor_Implementation()
{
	ICOSelectableActor::SelectActor_Implementation();
}

void ACOStreetActor::DeselectActor_Implementation()
{
	ICOSelectableActor::DeselectActor_Implementation();
}
