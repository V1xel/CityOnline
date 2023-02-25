// Fill out your copyright notice in the Description page of Project Settings.


#include "COStreetActor.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayEffectApplied.h"
#include "CO/Core/AbilitySystem/COAbilitySystemComponent.h"
#include "CO/Actor/Building/COBuildingActor.h"
#include "CO/Actor/Player/Abilities/Build/TargetData/COBuildAllocationTD.h"
#include "Components/COStreetCellComponent.h"

ACOStreetActor::ACOStreetActor()
{
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

void ACOStreetActor::OccupyCells(const FCOBuildAllocationTD* AllocationTD)
{
	for (auto Cell : AllocationTD->Cells)
	{
		for (auto CellComponent : Cells)
		{
			if (Cell.Key == CellComponent->Horizontal && Cell.Value == CellComponent->Vertical) 
			{
				CellComponent->SetOccupied(true);
				break;
			}
		}
	}
}

void ACOStreetActor::ReleaseCells(const FCOBuildAllocationTD* AllocationTD)
{
	for (auto Cell : AllocationTD->Cells)
	{
		for (auto CellComponent : Cells)
		{
			if (Cell.Key == CellComponent->Horizontal && Cell.Value == CellComponent->Vertical)
			{
				CellComponent->SetOccupied(false);
				break;
			}
		}
	}
}
