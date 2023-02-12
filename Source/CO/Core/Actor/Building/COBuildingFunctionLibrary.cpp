// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildingFunctionLibrary.h"
#include "CO/Actor/Building/Components/COBuildingPartComponent.h"
#include "CO/Database/Assets/COBuildingAsset.h"

void UCOBuildingFunctionLibrary::ComposeBuilding(AActor* Owner, int32 Floors, TSubclassOf<UCOBuildingPartComponent> BuildingPartComponentClass, UCOBuildingAsset* BuildingAsset, TArray<UCOBuildingPartComponent*>& OutParts)
{
	for (size_t i = 0; i <= Floors; i++)
	{
		auto Mesh = Cast<UCOBuildingPartComponent>(Owner->AddComponentByClass(BuildingPartComponentClass, false, FTransform::Identity, false));
		Mesh->SetStaticMesh(BuildingAsset->ExtensionFloor);
		Mesh->SetRelativeLocation(FVector(0, 0, BuildingAsset->FloorHeight * i));
		OutParts.Add(Mesh);
	}

	auto MainFloor = Cast<UCOBuildingPartComponent>(Owner->AddComponentByClass(BuildingPartComponentClass, false, FTransform::Identity, false));
	MainFloor->SetStaticMesh(BuildingAsset->MainFloor);
	OutParts.Add(MainFloor);

	auto Roof = Cast<UCOBuildingPartComponent>(Owner->AddComponentByClass(BuildingPartComponentClass, false, FTransform::Identity, false));
	Roof->SetStaticMesh(BuildingAsset->Roof);
	Roof->SetRelativeLocation(FVector(0, 0, BuildingAsset->FloorHeight * Floors));
	OutParts.Add(Roof);
}
