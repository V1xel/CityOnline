// Fill out your copyright notice in the Description page of Project Settings.


#include "COCellSelectionComponent.h"
#include "CO/Actor/Interfaces/SelectableComponent.h"
#include "CO/Actor/Street/Components/COStreetCellComponent.h"
#include "CO/Player/COPlayerController.h"

UCOCellSelectionComponent::UCOCellSelectionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCOCellSelectionComponent::EnableSelection(bool Value)
{
	IsEnabled = Value;
	if(!IsEnabled)
	{
		EndSelection();
	}
}

void UCOCellSelectionComponent::StartSelection()
{
	if(IsEnabled && IsSelecting)
	{
		FHitResult HitResult;
		const ACOPlayerController* PlayerController = GetOwnerController();
		PlayerController->GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);

		SelectionStartedLocation = HitResult.Location;
	}
}

void UCOCellSelectionComponent::EndSelection()
{
	IsSelecting = false;
	for (const auto SelectedComponent : SelectedCells)
	{
		ISelectableComponent::Execute_DeselectComponent(SelectedComponent);
	}

	OnSelectionEnded.Broadcast(TArray(SelectedCells));
	SelectedCells.Empty();
}

bool UCOCellSelectionComponent::RaycastWithRectangle(FVector RectangleStart, FVector RectangleEnd,
                                                     TArray<FHitResult>& OutHits) const
{
	const FVector Size = (RectangleEnd - RectangleStart) / 2;
	const FVector Extent = FVector( FMath::Sqrt(Size.X * Size.X),  FMath::Sqrt(Size.Y * Size.Y),  1);
	const FCollisionShape CollisionBox = FCollisionShape::MakeBox(Extent);
	
	const FVector Center = (RectangleEnd + RectangleStart) / 2;
	return GetWorld()->SweepMultiByChannel(OutHits, Center, Center, FQuat::Identity, ECC_WorldStatic, CollisionBox);
}

void UCOCellSelectionComponent::HandleActorComponentSelection(TArray<FHitResult>& HitResults)
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

void UCOCellSelectionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(IsEnabled & IsSelecting)
	{
		FHitResult CurrentMousePositionHitResult;
		const ACOPlayerControllerBase* PlayerController = Cast<ACOPlayerControllerBase>(GetOwner());
		PlayerController->GetHitResultUnderCursor(ECC_WorldStatic, false, CurrentMousePositionHitResult);
		
		TArray<FHitResult> OutHits;
		RaycastWithRectangle(SelectionStartedLocation,CurrentMousePositionHitResult.Location, OutHits);
		HandleActorComponentSelection(OutHits);
	}
}
