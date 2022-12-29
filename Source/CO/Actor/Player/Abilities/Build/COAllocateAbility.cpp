// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Actor/Player/Abilities/Build/COAllocateAbility.h"
#include "CO/Actor/Player/Abilities/AbilityTasks/COSelectCellsAbilityTask.h"
#include "CO/Extensions/GameplayTagExtension.h"
#include "CO/Game/COConstants.h"
#include "AbilitySystemComponent.h"
#include "COBuildAbility.h"

void UCOAllocateAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	_Handle = Handle;
	_ActorInfo = ActorInfo;
	_ActivationInfo = ActivationInfo;

	auto context = GetGrantedByEffectContext();
	auto dto = Cast<UCOBuildDTO>(context.GetSourceObject());
	const auto PlayerController = GetController(ActorInfo);
	SelectCellsAbilityTask = UCOSelectCellsAbilityTask::HandleSelectionTillSelectionEnded(this, "SelectCellsTask", PlayerController, dto);
	SelectCellsAbilityTask->SetDrawDebugSelection(DebugAllocation);
	SelectCellsAbilityTask->SetMousePositionAsFirstPoint();
	SelectCellsAbilityTask->ReadyForActivation();

	FGameplayEventTagMulticastDelegate::FDelegate AllocationCanceledDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UCOAllocateAbility::OnAllocationCanceled);
	ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(UCOGameplayTags::AllocateCancel().GetSingleTagContainer(), AllocationCanceledDelegate);
	AllocateCanceledHandle = AllocationCanceledDelegate.GetHandle();
}

void UCOAllocateAbility::OnAllocationCanceled(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	UCOSelectionDTO* SelectionDTO = SelectCellsAbilityTask->GetSelectionResult();
	if (SelectionDTO->IsValid) {
		auto Data = FGameplayEventData();
		Data.OptionalObject = SelectionDTO;
		SendGameplayEvent(UCOGameplayTags::AllocateFinished(), Data);
	}

	SelectCellsAbilityTask->ExternalConfirm(true);
	EndAbility(_Handle, _ActorInfo, _ActivationInfo, false, false);
}

void UCOAllocateAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(UCOGameplayTags::AllocateCancel().GetSingleTagContainer(), AllocateCanceledHandle);
}
