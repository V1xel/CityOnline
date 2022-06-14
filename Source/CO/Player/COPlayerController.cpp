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
		ISelectableActor* selectable = Cast<ISelectableActor>(hitActor);
		if (selectable)
		{
			selectable->Select();
			Selected = selectable;
		}
		else if(Selected != nullptr) {
			Selected->Deselect();
			Selected = nullptr;
		}
	}
}