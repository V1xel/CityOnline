// Fill out your copyright notice in the Description page of Project Settings.


#include "COPlayerController.h"
#include "Abilities/COEndBuildingAbility.h"
#include "Abilities/COStartBuildingAbility.h"

void ACOPlayerController::StartBuildingProcess()
{
	AbilitySystemComponent->TryActivateAbilityByClass(UCOStartBuildingAbility::StaticClass());
}

void ACOPlayerController::UpdateBuildingConfiguration()
{
//	AbilitySystemComponent->TryActivateAbilityByClass(UCOEditBuildingAbility::StaticClass());
}

void ACOPlayerController::EndBuildingProcess(const TArray<UCOStreetCellComponent*>& SelectedCells)
{
	AbilitySystemComponent->TryActivateAbilityByClass(UCOEndBuildingAbility::StaticClass());
}

void ACOPlayerController::CancelBuildingProcess()
{
	AbilitySystemComponent->TryActivateAbilityByClass(UCOEndBuildingAbility::StaticClass());
}
