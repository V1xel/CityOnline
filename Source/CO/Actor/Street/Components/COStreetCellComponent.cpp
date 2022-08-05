// Fill out your copyright notice in the Description page of Project Settings.


#include "COStreetCellComponent.h"

UCOStreetCellComponent::UCOStreetCellComponent()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneAsset(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	if (PlaneAsset.Succeeded()) {
		UStaticMeshComponent::SetStaticMesh(PlaneAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> CellMaterialAsset(TEXT("Material'/Game/CityOnline/Actor/Building/Material/BuildingCellValid.BuildingCellValid'"));
	if (CellMaterialAsset.Succeeded()) {
		UMeshComponent::SetMaterial(0, CellMaterialAsset.Object);
	}
	
	USceneComponent::SetMobility(EComponentMobility::Static);
}

void UCOStreetCellComponent::SelectComponent_Implementation()
{
	ISelectableComponent::SelectComponent_Implementation();
}

void UCOStreetCellComponent::DeselectComponent_Implementation()
{
	ISelectableComponent::DeselectComponent_Implementation();
}

