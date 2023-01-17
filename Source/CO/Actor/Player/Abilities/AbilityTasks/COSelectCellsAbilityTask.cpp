// Fill out your copyright notice in the Description page of Project Settings.


#include "COSelectCellsAbilityTask.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Actor/Street/Components/COStreetCellComponent.h"
#include "CO/Actor/Player/Abilities/Build/COBuildAbility.h"
#include "CO/Actor/Player/Abilities/Build/COAllocateAbility.h"

void UCOSelectCellsAbilityTask::Initialize()
{
	_SelectionDTO = NewObject<UCOSelectionDTO>();
	_BuildDTO = Cast<UCOBuildDTO>(_PermissionGrantedEffectContext.GetSourceObject());
	_SelectionStartedLocation = _TargetData.Get(0)->GetHitResult()->Location;
}

bool UCOSelectCellsAbilityTask::RaycastWithRectangle(FVector RectangleStart, FVector RectangleEnd,
	TArray<FHitResult>& OutHits) const
{
	const FVector Size = (RectangleEnd - RectangleStart) / 2;
	const FVector Extent = FVector(FMath::Sqrt(Size.X * Size.X), FMath::Sqrt(Size.Y * Size.Y), 10);
	const FCollisionShape CollisionBox = FCollisionShape::MakeBox(Extent);
	const FVector Center = (RectangleEnd + RectangleStart) / 2;

	return GetWorld()->SweepMultiByChannel(OutHits, Center, Center, FQuat::Identity, ECC_WorldStatic, CollisionBox);
}

TArray<UCOStreetCellComponent*> UCOSelectCellsAbilityTask::GetSelectedCells(TArray<FHitResult>& HitResults)
{
	TArray<UCOStreetCellComponent*> SelectedCells;
	
	for (auto HitResult : HitResults)
	{
		UCOStreetCellComponent* SelectedCell = Cast<UCOStreetCellComponent>(HitResult.GetComponent());
		if(SelectedCell)
		{
			SelectedCells.Add(SelectedCell);
		}
	}

	return SelectedCells;
}

void UCOSelectCellsAbilityTask::CollectSelectionData(UCOSelectionDTO* SelectionDTO, TArray<UCOStreetCellComponent*>& SelectedCells)
{
	auto MinimumHorizontal = SelectedCells[0]->Horizontal;
	auto MaximumHorizontal = SelectedCells[0]->Horizontal;
	auto MinimumVertical = SelectedCells[0]->Vertical;
	auto MaximumVertical = SelectedCells[0]->Vertical;
	bool HasExtreme = false;
	bool HasCorner = false;
	int ExtremeCount = 0;

	FVector SelectionCenter;
	FVector SelectionNormal;
	for (auto Cell : SelectedCells)
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

	const FVector SelectionCenterCorrect = SelectionCenter / SelectedCells.Num();
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

void UCOSelectCellsAbilityTask::VisualizeSelection() 
{
	FHitResult CurrentMousePositionHitResult;
	Ability->GetActorInfo().PlayerController->GetHitResultUnderCursor(ECC_WorldStatic, false, CurrentMousePositionHitResult);

	for (auto Cell : _SelectedCells)
	{
		Cell->SetVisible(false);
		Cell->SetSelected(false);
	}
	_SelectedCells.Empty();

	TArray<FHitResult> OutHits;
	RaycastWithRectangle(_SelectionStartedLocation, CurrentMousePositionHitResult.Location, OutHits);
	auto Cells = GetSelectedCells(OutHits);
	if (Cells.Num() == 0) 
		return;
	
	CollectSelectionData(_SelectionDTO, Cells);
	ValidateSelectionData(_SelectionDTO, _BuildDTO);

	for (auto Cell : Cells)
	{
		Cell->SetVisible(true);
		if (Cell->IsOccupied) {
			Cell->SetValid(false);
		}
		else {
			Cell->SetValid(_SelectionDTO->IsValid);
		}
	}

	_SelectedCells = Cells;
}

void UCOSelectCellsAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	VisualizeSelection();

	auto AllocateAbility = Cast<UCOAllocateAbility>(Ability);
	AllocateAbility->AbilityTaskTick();
}

void UCOSelectCellsAbilityTask::ValidateSelectionData(UCOSelectionDTO* SelectionDTO, UCOBuildDTO* BuildDTO) 
{
	bool valid = true;
	if (!SelectionDTO->HasExtreme) {
		valid = false;
	}
	if (SelectionDTO->Length > BuildDTO->MaxLength ||
		SelectionDTO->Width > BuildDTO->MaxWidth)
	{
		if (SelectionDTO->Width > BuildDTO->MaxLength ||
			SelectionDTO->Length > BuildDTO->MaxWidth)
		{
			valid = false;
		}
	}
	if (SelectionDTO->Length < BuildDTO->MinLength ||
		SelectionDTO->Width < BuildDTO->MinWidth)
	{
		if (SelectionDTO->Width < BuildDTO->MinLength ||
			SelectionDTO->Length < BuildDTO->MinWidth)
		{
			valid = false;
		}
	}

	SelectionDTO->IsValid = valid;
}

void UCOSelectCellsAbilityTask::ExternalConfirm(bool bEndTask)
{
	if (bTickingTask) {
		for (const auto SelectedComponent : _SelectedCells)
		{
			SelectedComponent->SetSelected(false);
			SelectedComponent->SetVisible(false);
		}
	}

	Super::ExternalConfirm(bEndTask);
}

UCOSelectionDTO* UCOSelectCellsAbilityTask::GetVisualisationResult()
{
	return _SelectionDTO;
}

UCOSelectionDTO* UCOSelectCellsAbilityTask::CalculateSelectionData(FGameplayAbilityTargetDataHandle TargetData)
{
	TArray<FHitResult> OutHits;
	RaycastWithRectangle(_SelectionStartedLocation, TargetData.Get(0)->GetHitResult()->Location, OutHits);
	auto Cells = GetSelectedCells(OutHits);
	CollectSelectionData(_SelectionDTO, Cells);
	ValidateSelectionData(_SelectionDTO, _BuildDTO);

	return _SelectionDTO;
}

void UCOSelectCellsAbilityTask::OnDestroy(bool AbilityIsEnding)
{
	Super::OnDestroy(AbilityIsEnding);
}
