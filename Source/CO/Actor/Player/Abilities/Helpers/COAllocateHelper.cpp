// Fill out your copyright notice in the Description page of Project Settings.


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

void UCOAllocateAbilityHelper::CollectSelectionData(FCOSelectionDTOTargetData* SelectionDTO, TArray<UCOStreetCellComponent*>& SelectedCells)
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
	FVector SelectionAverageNormal;
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
				
			SelectionAverageNormal = SelectionAverageNormal - Cell->GetComponentLocation();
			HasExtreme = true;
		}
		if (Cell->IsCorner)
		{
			HasCorner = true;
		}
		
		SelectionCenter = SelectionCenter + Cell->GetComponentLocation();
	}

	const FVector SelectionAverageCenter = SelectionCenter / SelectedCells.Num();
	const FVector SelectionNormalizedNormal = SelectionAverageNormal.GetSafeNormal2D();
	const FVector SelectionNormalCorrect = (SelectionAverageCenter - SelectionNormalizedNormal).GetSafeNormal2D(); // just inverting normal ? what is the point ?

	FVector SelectionDirection;
	if (ExtremeCount == 3) {
		SelectionDirection = -SelectionNormalCorrect;
	}
	else {
		const double dot = FVector::DotProduct(SelectionNormalCorrect, FVector::ForwardVector);
		const FVector FinalNormal = dot * dot > 0.5 ? FVector::ForwardVector : FVector::RightVector;
		const double dot2 = FVector::DotProduct(SelectionNormalCorrect, FinalNormal);
		SelectionDirection = dot2 < 0 ? FVector(FinalNormal) : FVector(FinalNormal * -1);
	}

	SelectionDTO->Direction = SelectionDirection;
	SelectionDTO->Center = SelectionAverageCenter;
	SelectionDTO->Length = MaximumHorizontal - MinimumHorizontal + 1;
	SelectionDTO->Width = MaximumVertical - MinimumVertical + 1;
	SelectionDTO->HasExtreme = HasExtreme;
	SelectionDTO->HasCorner = HasCorner;
}

bool UCOAllocateAbilityHelper::ValidateSelectionData(FGameplayAbilityTargetDataHandle SelectionDTOHandle, FGameplayAbilityTargetDataHandle BuildDTOHandle)
{
	if (!SelectionDTOHandle.IsValid(0) || !BuildDTOHandle.IsValid(0)) {
		return false;
	}

	auto SelectionDTO = static_cast<FCOSelectionDTOTargetData*>(SelectionDTOHandle.Get(0));
	auto BuildDTO = static_cast<FCOBuildDTOTargetData*>(BuildDTOHandle.Get(0));

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

FGameplayAbilityTargetDataHandle UCOAllocateAbilityHelper::CalculateSelectionData(const AActor* Target, FVector Start, FVector End)
{
	auto TargetData = new FCOSelectionDTOTargetData();
	UWorld* World = Target->GetWorld();

	TArray<FHitResult> OutHits;
	RaycastWithRectangle(World, Start, End, OutHits);
	auto Cells = GetSelectedCells(Target, OutHits);
	CollectSelectionData(TargetData, Cells);

	return FGameplayAbilityTargetDataHandle(TargetData);
}

FGameplayAbilityTargetDataHandle UCOAllocateAbilityHelper::CalculateSelectionDataWithCells(const AActor* Target, FVector Start, FVector End, TArray<UCOStreetCellComponent*>& OutSelectedCells)
{
	auto TargetData = new FCOSelectionDTOTargetData();
	UWorld* World = Target->GetWorld();

	TArray<FHitResult> OutHits;
	RaycastWithRectangle(World, Start, End, OutHits);
	auto Cells = GetSelectedCells(Target, OutHits);
	CollectSelectionData(TargetData, Cells);
	OutSelectedCells = Cells;

	return FGameplayAbilityTargetDataHandle(TargetData);
}

