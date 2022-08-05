// Fill out your copyright notice in the Description page of Project Settings.


#include "COSelectCellsAbilityTask.h"

#include "CO/Actor/Interfaces/SelectableComponent.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Actor/Street/Components/COStreetCellComponent.h"

UCOSelectCellsAbilityTask::UCOSelectCellsAbilityTask()
{
	bTickingTask = true;
}

UCOSelectCellsAbilityTask* UCOSelectCellsAbilityTask::HandleSelectionTillSelectionEnded(UGameplayAbility* OwningAbility, FName TaskInstanceName, ACOPlayerController* PlayerController,
	FCOBuildingConfiguration Configuration)
{
	UCOSelectCellsAbilityTask* MyObj = NewAbilityTask<UCOSelectCellsAbilityTask>(OwningAbility, TaskInstanceName);
	MyObj->PlayerController = PlayerController;
	MyObj->Configuration = Configuration;

	return MyObj;
}

void UCOSelectCellsAbilityTask::Activate()
{
	Super::Activate();
	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
	SelectionStartedLocation = HitResult.Location;
}

void UCOSelectCellsAbilityTask::ExternalConfirm(bool bEndTask)
{
	Super::ExternalConfirm(bEndTask);

	for (const auto SelectedComponent : SelectedCells)
	{
		ISelectableComponent::Execute_DeselectComponent(SelectedComponent);
	}
}

bool UCOSelectCellsAbilityTask::RaycastWithRectangle(FVector RectangleStart, FVector RectangleEnd,
                                                     TArray<FHitResult>& OutHits) const
{
	const FVector Size = (RectangleEnd - RectangleStart) / 2;
	const FVector Extent = FVector( FMath::Sqrt(Size.X * Size.X),  FMath::Sqrt(Size.Y * Size.Y),  1);
	const FCollisionShape CollisionBox = FCollisionShape::MakeBox(Extent);
	
	const FVector Center = (RectangleEnd + RectangleStart) / 2;
	return GetWorld()->SweepMultiByChannel(OutHits, Center, Center, FQuat::Identity, ECC_WorldStatic, CollisionBox);
}

void UCOSelectCellsAbilityTask::HandleActorComponentSelection(TArray<FHitResult>& HitResults)
{
	TArray<UCOStreetCellComponent*> DesiredSelectedComponents;

	for (auto HitResult : HitResults)
	{
		UCOStreetCellComponent* HitComponent = Cast<UCOStreetCellComponent>(HitResult.GetComponent());
		if(HitComponent && HitComponent->Implements<USelectableComponent>())
		{
			bool PendingSelect = true;
			for (const auto SelectedComponent : SelectedCells)
			{
				if(SelectedComponent == HitComponent)
				{
					PendingSelect = false;
					break;
				}
			}
			if(PendingSelect)
			{
				ISelectableComponent::Execute_SelectComponent(HitComponent);
			}
			
			DesiredSelectedComponents.Add(HitComponent);
		}
	}

	for (const auto SelectedComponent : SelectedCells)
	{
		bool PendingDeselect = true;
		for (auto HitResult : HitResults)
		{
			UCOStreetCellComponent* HitComponent = Cast<UCOStreetCellComponent>(HitResult.GetComponent());
			if(HitComponent && HitComponent->Implements<USelectableComponent>())
			{
				if(SelectedComponent == HitComponent)
				{
					PendingDeselect = false;
				}
			}
		}

		if(PendingDeselect)
		{
			ISelectableComponent::Execute_DeselectComponent(SelectedComponent);
		}
	}

	SelectedCells.Empty();
	SelectedCells = DesiredSelectedComponents;
}

void UCOSelectCellsAbilityTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	FHitResult CurrentMousePositionHitResult;
	PlayerController->GetHitResultUnderCursor(ECC_WorldStatic, false, CurrentMousePositionHitResult);
		
	TArray<FHitResult> OutHits;
	RaycastWithRectangle(SelectionStartedLocation,CurrentMousePositionHitResult.Location, OutHits);
	HandleActorComponentSelection(OutHits);
}

void UCOSelectCellsAbilityTask::OnDestroy(bool AbilityIsEnding)
{
	Super::OnDestroy(AbilityIsEnding);
}
