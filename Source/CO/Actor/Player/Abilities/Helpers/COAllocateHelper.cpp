﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "COAllocateHelper.h"
#include "CO/Actor/Player/Abilities/DTO/COBuildDTO.h"
#include "CO/Actor/Player/Abilities/DTO/COSelectionDTO.h"
#include "CO/Actor/Street/Components/COStreetCellComponent.h"

bool UCOAllocateAbilityHelper::RaycastWithRectangle(UWorld* World, FVector RectangleStart, FVector RectangleEnd,
	TArray<FHitResult>& OutHits)
{
	const FVector Size = (RectangleEnd - RectangleStart) / 2;
	const FVector Extent = FVector(FMath::Sqrt(Size.X * Size.X), FMath::Sqrt(Size.Y * Size.Y), 10);
	const FCollisionShape CollisionBox = FCollisionShape::MakeBox(Extent);
	const FVector Center = (RectangleEnd + RectangleStart) / 2;

	return World->SweepMultiByChannel(OutHits, Center, Center, FQuat::Identity, ECC_WorldStatic, CollisionBox);
}

TArray<UCOStreetCellComponent*> UCOAllocateAbilityHelper::GetSelectedCells(const AActor* Target, TArray<FHitResult>& HitResults)
{
	TArray<UCOStreetCellComponent*> SelectedCells;
	AActor* Owner = nullptr;

	for (auto HitResult : HitResults)
	{
		UCOStreetCellComponent* SelectedCell = Cast<UCOStreetCellComponent>(HitResult.GetComponent());
		if(SelectedCell && SelectedCell->GetOwner() == Target)
		{
			SelectedCells.Add(SelectedCell);
		}
	}

	return SelectedCells;
}

void UCOAllocateAbilityHelper::CollectSelectionData(UCOSelectionDTO* SelectionDTO, TArray<UCOStreetCellComponent*>& SelectedCells)
{
	if (SelectedCells.Num() == 0) {
		return;
	}

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

bool UCOAllocateAbilityHelper::ValidateSelectionData(UCOSelectionDTO* SelectionDTO, UCOBuildDTO* BuildDTO)
{
	if (!BuildDTO) {
		return false;
	}

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

	return valid;
}

UCOSelectionDTO* UCOAllocateAbilityHelper::CalculateSelectionData(const AActor* Target, FVector Start, FVector End)
{
	auto SelectionDTO = NewObject<UCOSelectionDTO>();
	UWorld* World = Target->GetWorld();

	TArray<FHitResult> OutHits;
	RaycastWithRectangle(World, Start, End, OutHits);
	auto Cells = GetSelectedCells(Target, OutHits);
	CollectSelectionData(SelectionDTO, Cells);

	return SelectionDTO;
}

UCOSelectionDTO* UCOAllocateAbilityHelper::CalculateSelectionDataWithCells(const AActor* Target, FVector Start, FVector End, TArray<UCOStreetCellComponent*>& OutSelectedCells)
{
	auto SelectionDTO = NewObject<UCOSelectionDTO>();
	UWorld* World = Target->GetWorld();

	TArray<FHitResult> OutHits;
	RaycastWithRectangle(World, Start, End, OutHits);
	auto Cells = GetSelectedCells(Target, OutHits);
	CollectSelectionData(SelectionDTO, Cells);
	OutSelectedCells = Cells;

	return SelectionDTO;
}

