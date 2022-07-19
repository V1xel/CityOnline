// Fill out your copyright notice in the Description page of Project Settings.


#include "COStartBuildingAbility.h"

#include "CO/Actor/Street/COStreetActor.h"
#include "CO/Player/Components/COActorSelectionComponent.h"
#include "CO/Player/Components/COCellSelectionComponent.h"

void UCOStartBuildingAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	this->Configuration = Configuration;

	const auto CellSelection = GetOwnerComponent<UCOCellSelectionComponent>(UCOCellSelectionComponent::StaticClass());
	CellSelection->EnableSelection();
	CellSelection->OnSelectionEnded.AddDynamic(this, &UCOStartBuildingAbility::PreviewBuildingProcess);
}

void UCOStartBuildingAbility::PreviewBuildingProcess(const TArray<UCOStreetCellComponent*>& SelectedCells)
{
	const auto CellSelection = GetOwnerComponent<UCOCellSelectionComponent>(UCOCellSelectionComponent::StaticClass());
	CellSelection->OnSelectionEnded.RemoveAll(this);
	
	const auto ActorSelection = GetOwnerComponent<UCOActorSelectionComponent>(UCOActorSelectionComponent::StaticClass());
	const auto SelectedStreet = ActorSelection->GetSelectedActor<ACOStreetActor>();
	BuildingActor = SelectedStreet->CreateBuilding(Configuration, SelectedCells);
	
}

void UCOStartBuildingAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
