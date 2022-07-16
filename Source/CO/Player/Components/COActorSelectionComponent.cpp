// Fill out your copyright notice in the Description page of Project Settings.


#include "COActorSelectionComponent.h"

#include "CO/Actor/Interfaces/SelectableActor.h"

void UCOActorSelectionComponent::TrySelectUnderCursor()
{
	const ACOPlayerController* PlayerController = GetOwnerController();
	
	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
	HandleActorSelection(HitResult);
}

void UCOActorSelectionComponent::HandleActorSelection(FHitResult HitResult)
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
