// Fill out your copyright notice in the Description page of Project Settings.


#include "COStreetActor.h"

#include "CO/Actor/Building/COBuildingActor.h"

ACOStreetActor::ACOStreetActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetMobility(EComponentMobility::Static);
	SetRootComponent(SceneComponent);
	CellManagementComponent = CreateDefaultSubobject<UCOStreetCellManagementComponent>(TEXT("CellManagementComponent"));
	CellManagementComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

ACOBuildingActor* ACOStreetActor::CreateBuilding(UCOBuildingDetails* Configuration, const TArray<UCOStreetCellComponent*>& SelectedCells)
{
	return nullptr;
}

void ACOStreetActor::SelectActor_Implementation()
{
	ICOSelectableActor::SelectActor_Implementation();
}

void ACOStreetActor::DeselectActor_Implementation()
{
	ICOSelectableActor::DeselectActor_Implementation();
}

void ACOStreetActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	CellManagementComponent->ConstructCells();
}
