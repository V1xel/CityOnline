// Fill out your copyright notice in the Description page of Project Settings.


#include "COCitizenCharacter.h"
#include "CO/Actor/Building/COBuildingActor.h"

// Sets default values
ACOCitizenCharacter::ACOCitizenCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACOCitizenCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACOCitizenCharacter::AddBuildingVisited(ACOBuildingActor* Building)
{
	VisitedBuildings.Add(Building);
}

void ACOCitizenCharacter::ClearVisitedBuildings()
{
	VisitedBuildings.Empty();
}

bool ACOCitizenCharacter::CheckBuildingVisited(ACOBuildingActor* Building)
{
	return VisitedBuildings.Contains(Building);
}

ACOBuildingActor* ACOCitizenCharacter::GetCheapestShop()
{
	ACOBuildingActor* Target = nullptr;
	float lowestCost = 0;
	for (auto Building : VisitedBuildings)
	{
		if (lowestCost > Building->GetProvisionUnitCost())
		{
			lowestCost = Building->GetProvisionUnitCost();
			Target = Building;
			continue;
		}
		if (!Target)
		{
			lowestCost = Building->GetProvisionUnitCost();
			Target = Building;
		}
	}

	return Target;
}

// Called every frame
void ACOCitizenCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACOCitizenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}


