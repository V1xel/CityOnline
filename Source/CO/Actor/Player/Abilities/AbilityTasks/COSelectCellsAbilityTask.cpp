// Fill out your copyright notice in the Description page of Project Settings.


#include "COSelectCellsAbilityTask.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Actor/Street/Components/COStreetCellComponent.h"
#include "CO/Actor/Player/Abilities/Build/COBuildAbility.h"
#include "CO/Actor/Player/Abilities/Build/COAllocateAbility.h"
#include "CO/Core/COConstants.h"

bool UCOSelectCellsAbilityTask::RaycastWithRectangle(FVector RectangleStart, FVector RectangleEnd,
	TArray<FHitResult>& OutHits) const
{
	const FVector Size = (RectangleEnd - RectangleStart) / 2;
	const FVector Extent = FVector(FMath::Sqrt(Size.X * Size.X), FMath::Sqrt(Size.Y * Size.Y), 10);
	const FCollisionShape CollisionBox = FCollisionShape::MakeBox(Extent);
	const FVector Center = (RectangleEnd + RectangleStart) / 2;

	return GetWorld()->SweepMultiByChannel(OutHits, Center, Center, FQuat::Identity, ECC_WorldStatic, CollisionBox);
}

void UCOSelectCellsAbilityTask::UpdateCellsState(TArray<FHitResult>& HitResults)
{
	TArray<UCOStreetCellComponent*> DesiredSelectedComponents;
	
	for (auto HitResult : HitResults)
	{
		UCOStreetCellComponent* HitComponent = Cast<UCOStreetCellComponent>(HitResult.GetComponent());
		if(HitComponent)
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
				HitComponent->SetSelected(true);
			}
			
			DesiredSelectedComponents.Add(HitComponent);
		}
	}

	for (const auto CellComponent : _SelectedCells)
	{
		bool PendingDeselect = true;
		for (auto HitResult : HitResults)
		{
			UCOStreetCellComponent* HitComponent = Cast<UCOStreetCellComponent>(HitResult.GetComponent());
			if(HitComponent && CellComponent == HitComponent)
			{
				PendingDeselect = false;
			}
		}

		if(PendingDeselect)
		{
			CellComponent->SetSelected(false);
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
	int ExtremeCount = 0;

	FVector SelectionCenter;
	FVector SelectionNormal;
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
			ExtremeCount++;
				
			SelectionNormal = SelectionNormal - Cell->GetComponentLocation();
			HasExtreme = true;
		}
		if (Cell->IsCorner)
		{
			HasCorner = true;
		}
		
		SelectionCenter = SelectionCenter + Cell->GetComponentLocation();
	}

	const FVector SelectionCenterCorrect = SelectionCenter / _SelectedCells.Num();
	const FVector SelectionNormalSafe = SelectionNormal.GetSafeNormal2D();
	const FVector SelectionNormalCorrect = (SelectionCenterCorrect - SelectionNormalSafe).GetSafeNormal2D();

	FVector FinalFinalNormal;
	if (ExtremeCount == 3) {
		FinalFinalNormal = -SelectionNormalCorrect;
	}
	else {
		const double dot = FVector::DotProduct(SelectionNormalCorrect, FVector::ForwardVector);
		const FVector FinalNormal = dot * dot > 0.5 ? FVector::ForwardVector : FVector::RightVector;
		const double dot2 = FVector::DotProduct(SelectionNormalCorrect, FinalNormal);
		FinalFinalNormal = dot2 < 0 ? FVector(FinalNormal) : FVector(FinalNormal * -1);
	}

	SelectionDTO->Rotation = FinalFinalNormal.ToOrientationRotator();
	SelectionDTO->Center = SelectionCenterCorrect;
	SelectionDTO->Length = MaximumHorizontal - MinimumHorizontal + 1;
	SelectionDTO->Width = MaximumVertical - MinimumVertical + 1;
	SelectionDTO->HasExtreme = HasExtreme;
	SelectionDTO->HasCorner = HasCorner;
}

void UCOSelectCellsAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	FHitResult CurrentMousePositionHitResult;
	Ability->GetActorInfo().PlayerController->GetHitResultUnderCursor(ECC_WorldStatic, false, CurrentMousePositionHitResult);

	TArray<FHitResult> OutHits;
	RaycastWithRectangle(_SelectionStartedLocation, CurrentMousePositionHitResult.Location, OutHits);
	UpdateCellsState(OutHits);

	CollectSelectionData();
	ValidateSelectionData();
	
	auto AllocateAbility = Cast<UCOAllocateAbility>(Ability);
	AllocateAbility->AbilityTaskTick();
}

void UCOSelectCellsAbilityTask::ValidateSelectionData() 
{
	bool valid = true;

	if (!SelectionDTO->HasExtreme) {
		valid = false;
	}

	if (SelectionDTO->Length > _BuildDTO->MaxLength ||
		SelectionDTO->Width > _BuildDTO->MaxWidth)
	{
		if (SelectionDTO->Width > _BuildDTO->MaxLength ||
			SelectionDTO->Length > _BuildDTO->MaxWidth)
		{
			valid = false;
		}
	}

	if (SelectionDTO->Length < _BuildDTO->MinLength ||
		SelectionDTO->Width < _BuildDTO->MinWidth)
	{
		if (SelectionDTO->Width < _BuildDTO->MinLength ||
			SelectionDTO->Length < _BuildDTO->MinWidth)
		{
			valid = false;
		}
	}

	for (auto Cell :  _SelectedCells)
	{
		if (Cell->IsOccupied) {
			Cell->SetValid(false);
		}
		else {
			Cell->SetValid(valid);
		}
	}

	SelectionDTO->IsValid = valid;
}

void UCOSelectCellsAbilityTask::ExternalConfirm(bool bEndTask)
{
	for (const auto SelectedComponent : _SelectedCells)
	{
		SelectedComponent->SetSelected(false);
	}

	Super::ExternalConfirm(bEndTask);
}

void UCOSelectCellsAbilityTask::OnDestroy(bool AbilityIsEnding)
{
	Super::OnDestroy(AbilityIsEnding);
}
