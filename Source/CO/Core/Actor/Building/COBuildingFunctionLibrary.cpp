// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildingFunctionLibrary.h"
#include "CO/Actor/Building/Components/COBuildingPartComponent.h"
#include "CO/Database/Assets/COBuildingAsset.h"

void UCOBuildingFunctionLibrary::ComposeBuilding(AActor* Owner, int32 Floors, TSubclassOf<UCOBuildingPartComponent> BuildingPartComponentClass, UCOBuildingAsset* BuildingAsset, FVector Direction, TArray<UCOBuildingPartComponent*>& OutParts)
{
	for (size_t i = 0; i < Floors - 1; i++)
	{
		auto Mesh = Cast<UCOBuildingPartComponent>(Owner->AddComponentByClass(BuildingPartComponentClass, false, FTransform::Identity, false));
		Mesh->SetStaticMesh(BuildingAsset->ExtensionFloor);
		Mesh->SetRelativeLocation(FVector(0, 0, BuildingAsset->FloorHeight * i));
		Mesh->SetWorldRotation(BuildingAsset->RotationOffset + Direction.ToOrientationRotator());
		OutParts.Add(Mesh);
	}

	auto MainFloor = Cast<UCOBuildingPartComponent>(Owner->AddComponentByClass(BuildingPartComponentClass, false, FTransform::Identity, false));
	MainFloor->SetStaticMesh(BuildingAsset->MainFloor);
	MainFloor->SetWorldRotation(BuildingAsset->RotationOffset + Direction.ToOrientationRotator());
	OutParts.Add(MainFloor);

	auto Roof = Cast<UCOBuildingPartComponent>(Owner->AddComponentByClass(BuildingPartComponentClass, false, FTransform::Identity, false));
	Roof->SetStaticMesh(BuildingAsset->Roof);
	Roof->SetRelativeLocation(FVector(0, 0, BuildingAsset->FloorHeight * (Floors - 2)));
	Roof->SetWorldRotation(BuildingAsset->RotationOffset + Direction.ToOrientationRotator());
	OutParts.Add(Roof);
}
