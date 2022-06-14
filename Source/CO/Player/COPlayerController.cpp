// Fill out your copyright notice in the Description page of Project Settings.


#include "COPlayerController.h"
#include "CO/Actor/Interfaces/SelectableActor.h"

ACOPlayerController::ACOPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
}

void ACOPlayerController::Select()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Selecting"));	
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Pawn, false, HitResult);
	AActor* hitActor = HitResult.GetActor();
	if (hitActor->Implements<USelectableActor>()) {
		ISelectableActor* Selectable = Cast<ISelectableActor>(hitActor);
		if (Selectable)
		{
			Selectable->Select();
			Selected = Selectable;
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Selected"));	
		}
		else if(Selected != nullptr) {
			Selected->Deselect();
			Selected = nullptr;
		}
	}
}

void ACOPlayerController::SetMoveDestination()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Moving"));	
	FHitResult HitResult;
	auto hit = GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
	if(hit && Selected)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Moving 2"));	
		Selected->MoveTo(HitResult.ImpactPoint);
	}
}

void ACOPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Select", EInputEvent::IE_Released, this, &ACOPlayerController::Select);
	InputComponent->BindAction("SetMoveDestination", EInputEvent::IE_Released, this, &ACOPlayerController::SetMoveDestination);
}
