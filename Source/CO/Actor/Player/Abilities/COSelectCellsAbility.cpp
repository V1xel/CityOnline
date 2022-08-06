﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "COSelectCellsAbility.h"
#include "AbilityTasks/COSelectCellsAbilityTask.h"
#include "CO/Actor/Player/COPlayerController.h"

void UCOSelectCellsAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	const auto PlayerController = GetController(ActorInfo);
	
	SelectCellsAbilityTask = UCOSelectCellsAbilityTask::HandleSelectionTillSelectionEnded(this, "SelectCellsTask", PlayerController, SelectionDTO);
	SelectCellsAbilityTask->SetDrawDebugSelection(DrawDebugSelection);
	SelectCellsAbilityTask->ReadyForActivation();
}

void UCOSelectCellsAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
	SelectCellsAbilityTask->ExternalConfirm(true);
	OnSelectionEnded.Broadcast(SelectionDTO,SelectCellsAbilityTask->GetSelectedCells());
	EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
}

void UCOSelectCellsAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	OnSelectionEnded.RemoveAll(this);
}
