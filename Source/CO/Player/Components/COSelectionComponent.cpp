// Fill out your copyright notice in the Description page of Project Settings.


#include "COSelectionComponent.h"

#include "CO/Actor/Interfaces/SelectableActor.h"
#include "CO/Actor/Interfaces/SelectableComponent.h"
#include "CO/Player/COPlayerController.h"


UCOSelectionComponent::UCOSelectionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCOSelectionComponent::StartSelection()
{
	FHitResult HitResult;
	const ACOPlayerController* PlayerController = Cast<ACOPlayerController>(GetOwner());
	PlayerController->GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
	HandleActorSelection(HitResult);

	if(IsSelectionWithRectangleEnabled)
	{
		IsSelectingWithRectangle = true;
		SelectionStartedLocation = HitResult.Location;
	}
}

void UCOSelectionComponent::SetComponentSelectionEnabled(bool Value)
{
	IsSelectionWithRectangleEnabled = Value;
}

void UCOSelectionComponent::StopSelection()
{
	IsSelectingWithRectangle = false;
	for (const auto SelectedComponent : SelectedComponents)
	{
		ISelectableComponent::Execute_DeselectComponent(SelectedComponent);
	}

	SelectedComponents.Empty();
}

void UCOSelectionComponent::HandleActorSelection(FHitResult HitResult)
{
	AActor* HitActor = HitResult.GetActor();
	if(HitActor && HitActor != SelectedActor && HitActor->Implements<USelectableActor>())
	{
		ISelectableActor::Execute_SelectActor(HitActor);
		if(SelectedActor)
		{
			ISelectableActor::Execute_DeselectActor(SelectedActor);
		}
		
		SelectedActor = HitActor;
	}
}

void UCOSelectionComponent::HandleActorComponentSelection(TArray<FHitResult>& HitResults)
{
	TArray<UPrimitiveComponent*> DesiredSelectedComponents;

	for (auto HitResult : HitResults)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		if(HitComponent && HitComponent->Implements<USelectableComponent>())
		{
			bool PendingSelect = true;
			for (const auto SelectedComponent : SelectedComponents)
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

	for (const auto SelectedComponent : SelectedComponents)
	{
		bool PendingDeselect = true;
		for (auto HitResult : HitResults)
		{
			UPrimitiveComponent* HitComponent = HitResult.GetComponent();
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

	SelectedComponents.Empty();
	SelectedComponents = DesiredSelectedComponents;
}

bool UCOSelectionComponent::RaycastWithRectangle(FVector RectangleStart, FVector RectangleEnd,
	TArray<FHitResult>& OutHits)
{
	const FVector Size = (RectangleEnd - RectangleStart) / 2;
	const FVector Extent = FVector( FMath::Sqrt(Size.X * Size.X),  FMath::Sqrt(Size.Y * Size.Y),  1);
	const FVector Center = (RectangleEnd + RectangleStart) / 2;
	const FCollisionShape CollisionBox = FCollisionShape::MakeBox(Extent);

	return GetWorld()->SweepMultiByChannel(OutHits, Center, Center, FQuat::Identity, ECC_WorldStatic, CollisionBox);
}


// Called every frame
void UCOSelectionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(IsSelectingWithRectangle)
	{
		FHitResult CurrentMousePositionHitResult;
		const ACOPlayerController* PlayerController = Cast<ACOPlayerController>(GetOwner());
		PlayerController->GetHitResultUnderCursor(ECC_WorldStatic, false, CurrentMousePositionHitResult);
		
		TArray<FHitResult> OutHits;
		RaycastWithRectangle(SelectionStartedLocation,CurrentMousePositionHitResult.Location, OutHits);
		HandleActorComponentSelection(OutHits);
	}
}

