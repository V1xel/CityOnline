// Fill out your copyright notice in the Description page of Project Settings.


#include "COStreetActor.h"
#include "CO/Core/AbilitySystem/COAbilitySystemComponent.h"
#include "CO/Actor/Building/COBuildingActor.h"

ACOStreetActor::ACOStreetActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	AbilitySystemComponent = CreateDefaultSubobject<UCOAbilitySystemComponent>("AbilitySystem");
	SceneComponent->SetMobility(EComponentMobility::Static);
	SetRootComponent(SceneComponent);
}

void ACOStreetActor::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}


UAbilitySystemComponent* ACOStreetActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}