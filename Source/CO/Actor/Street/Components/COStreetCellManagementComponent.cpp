// Fill out your copyright notice in the Description page of Project Settings.


#include "COStreetCellManagementComponent.h"


// Sets default values for this component's properties
UCOStreetCellManagementComponent::UCOStreetCellManagementComponent()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneAsset(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	if (PlaneAsset.Succeeded()) {
		UStaticMeshComponent::SetStaticMesh(PlaneAsset.Object);
	}

	USceneComponent::SetMobility(EComponentMobility::Static);
}

void UCOStreetCellManagementComponent::ConstructCells()
{
	const auto Scale = GetRelativeScale3D();
	const auto HorizontalOffset = Coverage * 100 * Scale.X / (Horizontal -1);
	const auto VerticalOffset = Coverage * 100 * Scale.Y/ (Vertical-1);
	
	const auto Origin = GetComponentLocation();
	const auto Extent = Bounds.BoxExtent;
	const auto WorldOffset = Origin - Coverage * Extent;
	
	Cells.Empty();
	for (int iHorizontal = 0; iHorizontal <= Horizontal-1; ++iHorizontal)
	{
		for (int iVertical = 0; iVertical <= Vertical-1; ++iVertical)
		{
			auto CellOffset = FVector(HorizontalOffset * iHorizontal, VerticalOffset * iVertical, 1);
			const FVector Position = CellOffset + WorldOffset;

			auto Cell = NewObject<UCOStreetCellComponent>(this, UCOStreetCellComponent::StaticClass(), *FString::Printf(TEXT("Cell-%d::%d"), iHorizontal, iVertical));
			Cell->RegisterComponent();
			Cell->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
			Cell->SetWorldScale3D(FVector(Size,Size,1));
			Cell->SetWorldLocation(Position);
			Cell->Horizontal = iHorizontal;
			Cell->Vertical = iVertical;
			Cell->IsExtreme = iHorizontal == 0 || iVertical == 0 || iHorizontal == Horizontal || iVertical == Vertical;
			Cell->IsCorner = (iHorizontal == iVertical && iHorizontal == 0) || (iHorizontal == iVertical && iHorizontal == HorizontalOffset);
			
			Cells.Add(Cell);
		}
	}
}

void UCOStreetCellManagementComponent::SetCellsSelectable(bool Value)
{
}

void UCOStreetCellManagementComponent::GetSelectedCells(const TArray<UCOStreetCellComponent*> _Cells)
{
}

bool UCOStreetCellManagementComponent::ValidateCells(const TArray<UCOStreetCellComponent*> _Cells)
{
	return false;
}

void UCOStreetCellManagementComponent::AllocateCells(const TArray<UCOStreetCellComponent*> _Cells)
{
}

void UCOStreetCellManagementComponent::OccupyCells(const TArray<UCOStreetCellComponent*> _Cells)
{
}
