// Fill out your copyright notice in the Description page of Project Settings.


#include "COActorSelectionComponent.h"
#include "CO/Actor/Interfaces/SelectableActor.h"
#include "CO/Player/COPlayerController.h"

void UCOActorSelectionComponent::TrySelectUnderCursor()
{
	const ACOPlayerController* PlayerController = GetOwnerController();
	
	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
	HandleActorSelection(HitResult);
}

void UCOActorSelectionComponent::HandleActorSelection(FHitResult HitResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("HandleActorSelection"));	
	AActor* HitActor = HitResult.GetActor();
	if(HitActor && HitActor != SelectedActor && HitActor->Implements<USelectableActor>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Execute_SelectActor"));	
		ISelectableActor::Execute_SelectActor(HitActor);
		if(SelectedActor)
		{
			ISelectableActor::Execute_DeselectActor(SelectedActor);
		}
		
		SelectedActor = HitActor;
	}
}
