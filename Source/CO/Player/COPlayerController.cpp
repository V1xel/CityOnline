// Fill out your copyright notice in the Description page of Project Settings.


#include "COPlayerController.h"
#include "CO/Actor/Interfaces/SelectableActor.h"
#include "CO/Actor/Interfaces/SelectableComponent.h"

ACOPlayerController::ACOPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ACOPlayerController::StartSelection()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
	HandleActorSelection(HitResult);

	SelectionStartedLocation = HitResult.Location;
	IsSelectingWithRectangle = true;
}

void ACOPlayerController::StopSelection()
{
	IsSelectingWithRectangle = false;
}

void ACOPlayerController::HandleActorSelection(FHitResult HitResult)
{
	AActor* HitActor = HitResult.GetActor();
	if(HitActor && HitActor != SelectedActor && HitActor->Implements<USelectableActor>())
	{
		ISelectableActor::Execute_SelectActor(HitActor);
		ISelectableActor::Execute_DeselectActor(SelectedActor);
		SelectedActor = HitActor;
	}
}

void ACOPlayerController::HandleActorComponentSelection(TArray<FHitResult>& HitResults)
{
	for (auto HitResult : HitResults)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		if(HitComponent && HitComponent->Implements<USelectableComponent>())
		{
			ISelectableComponent::Execute_SelectComponent(HitComponent);
			ISelectableComponent::Execute_DeselectComponent(HitComponent);
			SelectedActor = HitActor;
		}
	}
}

bool ACOPlayerController::RaycastWithRectangle(FVector RectangleStart, FVector RectangleEnd, TArray<struct FHitResult>& OutHits)
{
	const FVector Size = (RectangleEnd - RectangleStart) / 2;
	const FVector Extent = FVector( FMath::Sqrt(Size.X * Size.X),  FMath::Sqrt(Size.Y * Size.Y),  1);
	const FVector Center = (RectangleEnd + RectangleStart) / 2;
	const FCollisionShape CollisionBox = FCollisionShape::MakeBox(Extent);

	return GetWorld()->SweepMultiByChannel(OutHits, Center, Center, FQuat::Identity, ECC_WorldStatic, CollisionBox);
}

void ACOPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsSelectingWithRectangle)
	{
		FHitResult CurrentMousePositionHitResult;
		GetHitResultUnderCursor(ECC_WorldStatic, false, CurrentMousePositionHitResult);
		
		TArray<FHitResult> OutHits;
		RaycastWithRectangle(SelectionStartedLocation,CurrentMousePositionHitResult.Location, OutHits);
		HandleActorComponentSelection(OutHits);
	}
}

void ACOPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Select", EInputEvent::IE_Pressed, this, &ACOPlayerController::StartSelection);
	InputComponent->BindAction("Select", EInputEvent::IE_Released, this, &ACOPlayerController::StopSelection);
}
