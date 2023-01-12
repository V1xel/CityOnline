// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildingActor.h"
#include "CO/Database/Assets/COBuildingAsset.h"
#include "CO/Core/AbilitySystem/COAbilitySystemComponent.h"
#include "CO/Actor/Building/Components/COBuildingPartComponent.h"
#include "CO/Actor/Player/Abilities/DTO/COConstructionDTO.h"

UAbilitySystemComponent* ACOBuildingActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACOBuildingActor::ComposeBuilding()
{
	int floors = 2;
	if (Configuration) {
		floors = Configuration->Floors;
	}
	
	Meshes.Empty();
	for (size_t i = 0; i <= floors; i++)
	{
		auto Mesh = Cast<UCOBuildingPartComponent>(AddComponentByClass(BuildingPartComponentClass, false, FTransform::Identity, false));
		if (Mesh)
		{
			Meshes.Add(Mesh);
			if (i == 0) {
				Mesh->SetStaticMesh(BuildingAsset->FirstFloor);
			}
			else if (i <= floors) {
				Mesh->SetStaticMesh(BuildingAsset->MiddleFloor);
				Mesh->SetRelativeLocation(FVector(0, 0, BuildingAsset->FloorHeight * (i - 1)));
			}
		}
	}

	auto Roof = Cast<UCOBuildingPartComponent>(AddComponentByClass(BuildingPartComponentClass, false, FTransform::Identity, false));
	Roof->SetStaticMesh(BuildingAsset->Roof);
	Roof->SetRelativeLocation(FVector(0, 0, BuildingAsset->FloorHeight * (floors - 1)));
	Meshes.Add(Roof);
}
