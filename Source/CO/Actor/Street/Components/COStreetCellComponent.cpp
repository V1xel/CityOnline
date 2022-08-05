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
		DynamicMaterial = UMaterialInstanceDynamic::Create(CellMaterialAsset.Object, this, "CellMaterial");
		UMeshComponent::SetMaterial(0, DynamicMaterial);
	}
	
	USceneComponent::SetMobility(EComponentMobility::Static);
}

void UCOStreetCellComponent::SelectComponent_Implementation()
{
	ICOSelectableComponent::SelectComponent_Implementation();
	IsSelected = true;
}

void UCOStreetCellComponent::DeselectComponent_Implementation()
{
	ICOSelectableComponent::DeselectComponent_Implementation();
	IsSelected = false;
}

