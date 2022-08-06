// Fill out your copyright notice in the Description page of Project Settings.


#include "COSelectCellsAbilityTask.h"
#include "CO/Actor/Street/Components/Interfaces/COSelectableComponent.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Actor/Street/Components/COStreetCellComponent.h"

UCOSelectCellsAbilityTask::UCOSelectCellsAbilityTask()
{
	bTickingTask = true;
}

UCOSelectCellsAbilityTask* UCOSelectCellsAbilityTask::HandleSelectionTillSelectionEnded(UGameplayAbility* OwningAbility, FName TaskInstanceName, ACOPlayerController* PlayerController, UCOSelectionDTO* SelectionDTO)
{
	UCOSelectCellsAbilityTask* Task = NewAbilityTask<UCOSelectCellsAbilityTask>(OwningAbility, TaskInstanceName);
	Task->_PlayerController = PlayerController;
	Task->_SelectionDTO = SelectionDTO;
	
	return Task;
}

void UCOSelectCellsAbilityTask::Activate()
{
	Super::Activate();
	FHitResult HitResult;
	_PlayerController->GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
	SelectionStartedLocation = HitResult.Location;
}

void UCOSelectCellsAbilityTask::ExternalConfirm(bool bEndTask)
{
	Super::ExternalConfirm(bEndTask);

	for (const auto SelectedComponent : _SelectedCells)
	{
		ICOSelectableComponent::Execute_DeselectComponent(SelectedComponent);
	}
}

bool UCOSelectCellsAbilityTask::RaycastWithRectangle(FVector RectangleStart, FVector RectangleEnd,
                                                     TArray<FHitResult>& OutHits) const
{
	const FVector Size = (RectangleEnd - RectangleStart) / 2;
	const FVector Extent = FVector( FMath::Sqrt(Size.X * Size.X),  FMath::Sqrt(Size.Y * Size.Y),  1);
	const FCollisionShape CollisionBox = FCollisionShape::MakeBox(Extent);
	const FVector Center = (RectangleEnd + RectangleStart) / 2;

	if(_DrawDebugSelection)
	{
		DrawDebugBox(GetWorld(), Center, Extent, FColor::Red, false, -1, 0, 100);
	}

	return GetWorld()->SweepMultiByChannel(OutHits, Center, Center, FQuat::Identity, ECC_WorldStatic, CollisionBox);
}

void UCOSelectCellsAbilityTask::HandleActorComponentSelection(TArray<FHitResult>& HitResults)
{
	TArray<UCOStreetCellComponent*> DesiredSelectedComponents;
	
	for (auto HitResult : HitResults)
	{
		UCOStreetCellComponent* HitComponent = Cast<UCOStreetCellComponent>(HitResult.GetComponent());
		if(HitComponent && HitComponent->Implements<UCOSelectableComponent>())
		{
			bool PendingSelect = true;
			for (const auto SelectedComponent : _SelectedCells)
			{
				if(SelectedComponent == HitComponent)
				{
					PendingSelect = false;
					break;
				}
			}
			if(PendingSelect)
			{
				ICOSelectableComponent::Execute_SelectComponent(HitComponent);
			}
			
			DesiredSelectedComponents.Add(HitComponent);
		}
	}

	for (const auto SelectedComponent : _SelectedCells)
	{
		bool PendingDeselect = true;
		for (auto HitResult : HitResults)
		{
			UCOStreetCellComponent* HitComponent = Cast<UCOStreetCellComponent>(HitResult.GetComponent());
			if(HitComponent && HitComponent->Implements<UCOSelectableComponent>())
			{
				if(SelectedComponent == HitComponent)
				{
					PendingDeselect = false;
				}
			}
		}

		if(PendingDeselect)
		{
			ICOSelectableComponent::Execute_DeselectComponent(SelectedComponent);
		}
	}

	_SelectedCells.Empty();
	_SelectedCells = DesiredSelectedComponents;
}

void UCOSelectCellsAbilityTask::CollectSelectionData()
{
	if(_SelectedCells.Num() == 0)
		return;
	
	auto MinimumHorizontal = _SelectedCells[0]->Horizontal;
	auto MaximumHorizontal = _SelectedCells[0]->Horizontal;
	auto MinimumVertical = _SelectedCells[0]->Vertical;
	auto MaximumVertical = _SelectedCells[0]->Vertical;
	bool HasExtreme = false;
	bool HasCorner = false;
	for (auto Cell : _SelectedCells)
	{
		if(MinimumHorizontal > Cell->Horizontal)
		{
			MinimumHorizontal = Cell->Horizontal;
		}
		if(MaximumHorizontal < Cell->Horizontal)
		{
			MaximumHorizontal = Cell->Horizontal;
		}
		if(MinimumVertical > Cell->Vertical)
		{
			MinimumVertical = Cell->Vertical;
		}
		if(MaximumVertical < Cell->Vertical)
		{
			MaximumVertical = Cell->Vertical;
		}
		if (Cell->IsExtreme)
		{
			HasExtreme = true;
		}
		if (Cell->IsCorner)
		{
			HasCorner = true;
		}
	}

	_SelectionDTO->Length = MaximumHorizontal - MinimumHorizontal;
	_SelectionDTO->Width = MaximumVertical - MinimumVertical;
	_SelectionDTO->HasExtreme = HasExtreme;
	_SelectionDTO->HasCorner = HasCorner;
}

void UCOSelectCellsAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	FHitResult CurrentMousePositionHitResult;
	_PlayerController->GetHitResultUnderCursor(ECC_WorldStatic, false, CurrentMousePositionHitResult);
		
	TArray<FHitResult> OutHits;
	RaycastWithRectangle(SelectionStartedLocation,CurrentMousePositionHitResult.Location, OutHits);
	HandleActorComponentSelection(OutHits);
	CollectSelectionData();
}

void UCOSelectCellsAbilityTask::OnDestroy(bool AbilityIsEnding)
{
	Super::OnDestroy(AbilityIsEnding);
}
