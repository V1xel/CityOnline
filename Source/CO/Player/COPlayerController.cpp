// Fill out your copyright notice in the Description page of Project Settings.


#include "COPlayerController.h"
#include "CO/Actor/Interfaces/SelectableActor.h"

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
	HitStartedLocation = HitResult.Location;
	IsSelecting = true;
}

void ACOPlayerController::StopSelection()
{
	IsSelecting = false;
}

void ACOPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsSelecting)
	{
		FHitResult HitResult;
		GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
		auto Size = (HitResult.Location - HitStartedLocation)/2;
		auto Extent = FVector( FMath::Sqrt(Size.X * Size.X),  FMath::Sqrt(Size.Y * Size.Y),  FMath::Sqrt(Size.Z * Size.Z));
		FCollisionShape MyColSphere = FCollisionShape::MakeBox(Extent);

		TArray<FHitResult> OutHits;
		bool isHit = GetWorld()->SweepMultiByChannel(OutHits, (HitResult.Location + HitStartedLocation) /2, (HitResult.Location + HitStartedLocation) /2, FQuat::Identity, ECC_WorldStatic, MyColSphere);
		if(isHit)
		{
			for (auto OutHit : OutHits)
			{
				auto hitA = OutHit.GetActor();
				if(hitA && hitA->Implements<USelectableActor>())
				{
					ISelectableActor::Execute_Select(hitA);
					Selected.Add(hitA);
				}
			}
		}
	}else if(Selected.Num() > 0)
	{
		for (auto hitActor : Selected)
		{
			ISelectableActor::Execute_Deselect(hitActor);
		}
		
		Selected.Empty();
	}
}

void ACOPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Select", EInputEvent::IE_Pressed, this, &ACOPlayerController::StartSelection);
	InputComponent->BindAction("Select", EInputEvent::IE_Released, this, &ACOPlayerController::StopSelection);
}
