// Fill out your copyright notice in the Description page of Project Settings.


#include "COSelectCellsAbilityTask.h"
#include "CO/Actor/Street/Components/Interfaces/COSelectableComponent.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Actor/Street/Components/COStreetCellComponent.h"

UCOSelectCellsAbilityTask::UCOSelectCellsAbilityTask()
{
	bTickingTask = true;
	_SelectionDTO = NewObject<UCOSelectionDTO>();
	_DrawDebugSelection = true;
}

UCOSelectCellsAbilityTask* UCOSelectCellsAbilityTask::HandleSelectionTillSelectionEnded(UGameplayAbility* OwningAbility, FName TaskInstanceName, ACOPlayerController* PlayerController)
{
	UCOSelectCellsAbilityTask* Task = NewAbilityTask<UCOSelectCellsAbilityTask>(OwningAbility, TaskInstanceName);
	Task->_PlayerController = PlayerController;
	
	return Task;
}

void UCOSelectCellsAbilityTask::SetMousePositionAsFirstPoint() 
{
	FHitResult HitResult;
	_PlayerController->GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
	SelectionStartedLocation = HitResult.Location;
}

bool UCOSelectCellsAbilityTask::RaycastWithRectangle(FVector RectangleStart, FVector RectangleEnd,
	TArray<FHitResult>& OutHits) const
{
	const FVector Size = (RectangleEnd - RectangleStart) / 2;
	const FVector Extent = FVector(FMath::Sqrt(Size.X * Size.X), FMath::Sqrt(Size.Y * Size.Y), 10);
	const FCollisionShape CollisionBox = FCollisionShape::MakeBox(Extent);
	const FVector Center = (RectangleEnd + RectangleStart) / 2;


	DrawDebugBox(GetWorld(), Center, Extent, FColor::Red, false, -1, 0, 10);


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

	FVector SelectionCenter;
	FVector SelectionNormal;
	for (auto Cell : _SelectedCells)
	{
		DrawDebugBox(GetWorld(), Cell->GetComponentLocation(), FVector::OneVector * 20, FColor::Yellow, false, -1, 0, 20);
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
			DrawDebugBox(GetWorld(), Cell->GetComponentLocation(), FVector::OneVector * 40, FColor::Blue, false, -1, 0, 20);
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

	DrawDebugDirectionalArrow(GetWorld(), SelectionNormalSafe, SelectionCenterCorrect, 2000, FColor::Green, false, -1, 0, 50);

	const double dot = FVector::DotProduct(SelectionNormalCorrect, FVector::ForwardVector);
	const FVector FinalNormal = dot * dot > 0.5 ? FVector::ForwardVector : FVector::RightVector;
	const double dot2 = FVector::DotProduct(SelectionNormalCorrect, FinalNormal);
	const FVector FinalFinalNormal = dot2 < 0 ? FinalNormal : FinalNormal * -1;

	DrawDebugDirectionalArrow(GetWorld(), FinalFinalNormal, FinalFinalNormal * 1000, 2000, FColor::Red, false, -1, 0, 50);

	_SelectionDTO->Rotation = FinalFinalNormal.ToOrientationRotator();
	_SelectionDTO->Center = SelectionCenterCorrect;
	_SelectionDTO->Length = MaximumHorizontal - MinimumHorizontal + 1;
	_SelectionDTO->Width = MaximumVertical - MinimumVertical + 1;
	_SelectionDTO->HasExtreme = HasExtreme;
	_SelectionDTO->HasCorner = HasCorner;
}

void UCOSelectCellsAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	FHitResult CurrentMousePositionHitResult;
	_PlayerController->GetHitResultUnderCursor(ECC_WorldStatic, false, CurrentMousePositionHitResult);

	TArray<FHitResult> OutHits;
	RaycastWithRectangle(SelectionStartedLocation, CurrentMousePositionHitResult.Location, OutHits);
	HandleActorComponentSelection(OutHits);
	CollectSelectionData();
}

void UCOSelectCellsAbilityTask::ExternalConfirm(bool bEndTask)
{
	Super::ExternalConfirm(bEndTask);

	for (const auto SelectedComponent : _SelectedCells)
	{
		ICOSelectableComponent::Execute_DeselectComponent(SelectedComponent);
	}
}

void UCOSelectCellsAbilityTask::OnDestroy(bool AbilityIsEnding)
{
	Super::OnDestroy(AbilityIsEnding);
}
