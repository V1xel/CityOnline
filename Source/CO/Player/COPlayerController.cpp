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
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Pawn, false, HitResult);
	AActor* hitActor = HitResult.GetActor();
	if (hitActor->Implements<USelectableActor>()) {
		ISelectableActor* Selectable = Cast<ISelectableActor>(hitActor);
		if (Selectable)
		{
			Selectable->Select();
			Selected = Selectable;
		}
		else if(Selected != nullptr) {
			Selected->Deselect();
			Selected = nullptr;
		}
	}
}

void ACOPlayerController::SetMoveDestination()
{
	FHitResult HitResult;
	auto hit = GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
	if(hit && Selected)
	{
		//Do action
	}
}

void ACOPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Select", EInputEvent::IE_Released, this, &ACOPlayerController::Select);
}
