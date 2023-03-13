// Fill out your copyright notice in the Description page of Project Settings.

#include "COBuildingActor.h"
#include "CO/Core/AI/CONavModifierComponent.h"
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

void ACOBuildingActor::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	AbilitySystemComponent->GetOwnedGameplayTags(TagContainer);
}

bool ACOBuildingActor::HasMatchingGameplayTag(FGameplayTag TagToCheck) const
{
	return AbilitySystemComponent->HasMatchingGameplayTag(TagToCheck);
}

bool ACOBuildingActor::HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return AbilitySystemComponent->HasAllMatchingGameplayTags(TagContainer);
}

bool ACOBuildingActor::HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const
{
	return AbilitySystemComponent->HasAnyMatchingGameplayTags(TagContainer);
}

void ACOBuildingActor::ComposeBuilding(int32 Floors, UCOBuildingAsset* BuildingAsset, FVector Direction)
{
	UCOBuildingFunctionLibrary::ComposeBuilding(this, Floors, BuildingPartComponentClass, BuildingAsset, Direction, Meshes);

	NavModifierComponent = Cast<UCONavModifierComponent>(AddComponentByClass(UCONavModifierComponent::StaticClass(), false, FTransform::Identity, true));
	NavModifierComponent->AreaClass = AreaClass;
	NavModifierComponent->NavExtent = FVector(100, 100, 100);
	NavModifierComponent->CalcAndCacheBounds();
	FinishAddComponent(NavModifierComponent, false, FTransform());
}

float ACOBuildingActor::GetProvisionUnitCost()
{
	return UnitCost;
}