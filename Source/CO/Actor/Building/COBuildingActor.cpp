// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildingActor.h"
#include "CO/Database/Assets/COBuildingAsset.h"
#include "CO/Core/AbilitySystem/COAbilitySystemComponent.h"
#include "CO/Actor/Building/Components/COBuildingPartComponent.h"

UAbilitySystemComponent* ACOBuildingActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACOBuildingActor::ComposeBuilding()
{
	for (size_t i = 0; i <= Floors; i++)
	{
		auto Mesh = Cast<UCOBuildingPartComponent>(AddComponentByClass(BuildingPartComponentClass, false, FTransform::Identity, false));
		Mesh->SetStaticMesh(BuildingAsset->ExtensionFloor);
		Mesh->SetRelativeLocation(FVector(0, 0, BuildingAsset->FloorHeight * i));
		Meshes.Add(Mesh);
	}

	auto MainFloor = Cast<UCOBuildingPartComponent>(AddComponentByClass(BuildingPartComponentClass, false, FTransform::Identity, false));
	MainFloor->SetStaticMesh(BuildingAsset->MainFloor);
	Meshes.Add(MainFloor);

	auto Roof = Cast<UCOBuildingPartComponent>(AddComponentByClass(BuildingPartComponentClass, false, FTransform::Identity, false));
	Roof->SetStaticMesh(BuildingAsset->Roof);
	Roof->SetRelativeLocation(FVector(0, 0, BuildingAsset->FloorHeight * Floors));
	Meshes.Add(Roof);
}
