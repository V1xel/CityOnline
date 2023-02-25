// Fill out your copyright notice in the Description page of Project Settings.


#include "COAllocateHelper.h"
#include "CO/Actor/Player/Abilities/Build/TargetData/COBuildRequirementsTD.h"
#include "CO/Actor/Player/Abilities/Build/TargetData/COBuildAllocationTD.h"
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

void UCOAllocateAbilityHelper::CollectSelectionData(FCOBuildAllocationTD* SelectionTD, TArray<UCOStreetCellComponent*>& SelectedCells)
{
	if (SelectedCells.Num() == 0) {
		return;
	}

	auto MinimumHorizontal = SelectedCells[0]->Horizontal;
	auto MaximumHorizontal = SelectedCells[0]->Horizontal;
	auto MinimumVertical = SelectedCells[0]->Vertical;
	auto MaximumVertical = SelectedCells[0]->Vertical;
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

	SelectionTD->Direction = SelectionDirection;
	SelectionTD->Center = SelectionAverageCenter;
	SelectionTD->Length = MaximumHorizontal - MinimumHorizontal + 1;
	SelectionTD->Width = MaximumVertical - MinimumVertical + 1;
	SelectionTD->ExtremeCount = ExtremeCount;
}

bool UCOAllocateAbilityHelper::ValidateSelectionData(FGameplayAbilityTargetDataHandle SelectionDTOHandle, FGameplayAbilityTargetDataHandle BuildDTOHandle)
{
	auto SelectionDTO = static_cast<FCOBuildAllocationTD*>(SelectionDTOHandle.Get(0));
	auto BuildDTO = static_cast<FCOBuildRequirementsTD*>(BuildDTOHandle.Get(0));

	bool valid = true;
	if (SelectionDTO->ExtremeCount == 0) {
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
	auto TargetData = new FCOBuildAllocationTD();
	TargetData->Target = const_cast<AActor*>(Target);
	UWorld* World = Target->GetWorld();

	TArray<FHitResult> OutHits;
	RaycastWithRectangle(World, Start, End, OutHits);
	auto Cells = GetSelectedCells(Target, OutHits);
	CollectSelectionData(TargetData, Cells);

	return FGameplayAbilityTargetDataHandle(TargetData);
}

FGameplayAbilityTargetDataHandle UCOAllocateAbilityHelper::CalculateSelectionDataWithCells(const AActor* Target, FVector Start, FVector End, TArray<UCOStreetCellComponent*>& OutSelectedCells)
{
	auto TargetData = new FCOBuildAllocationTD();
	TargetData->Target = const_cast<AActor*>(Target);
	UWorld* World = Target->GetWorld();

	TArray<FHitResult> OutHits;
	RaycastWithRectangle(World, Start, End, OutHits);
	auto Cells = GetSelectedCells(Target, OutHits);
	CollectSelectionData(TargetData, Cells);
	OutSelectedCells = Cells;

	return FGameplayAbilityTargetDataHandle(TargetData);
}

