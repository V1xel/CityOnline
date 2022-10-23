// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Actor/Player/Abilities/Build/COAllocateAbility.h"
#include "CO/Actor/Player/Abilities/AbilityTasks/COSelectCellsAbilityTask.h"
#include "CO/Extensions/GameplayTagExtension.h"
#include "CO/Game/COConstants.h"
#include "AbilitySystemComponent.h"

void UCOAllocateAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	_Handle = Handle;
	_ActorInfo = ActorInfo;
	_ActivationInfo = ActivationInfo;

	if (UCOGameplayTags::Allocate().MatchesTagExact(TriggerEventData->EventTag) && !SelectCellsAbilityTask)
	{
		const auto PlayerController = GetController(ActorInfo);
		SelectCellsAbilityTask = UCOSelectCellsAbilityTask::HandleSelectionTillSelectionEnded(this, "SelectCellsTask", PlayerController);
		SelectCellsAbilityTask->SetDrawDebugSelection(true); 
		SelectCellsAbilityTask->SetMousePositionAsFirstPoint();
		SelectCellsAbilityTask->ReadyForActivation();

		FGameplayEventTagMulticastDelegate::FDelegate AllocationCanceledDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UCOAllocateAbility::OnAllocationCanceled);

		ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(UCOGameplayTags::AllocateCancel().GetSingleTagContainer(), AllocationCanceledDelegate);
		AllocateCanceledHandle = AllocationCanceledDelegate.GetHandle();
	}
}

void UCOAllocateAbility::OnAllocationCanceled(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	SelectCellsAbilityTask->GetSelectionResult();
	SelectCellsAbilityTask->ExternalConfirm(true);
	SendGameplayEvent(UCOGameplayTags::AllocateFinished(), FGameplayEventData());
	EndAbility(_Handle, _ActorInfo, _ActivationInfo, false, false);
}

void UCOAllocateAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(UCOGameplayTags::AllocateCancel().GetSingleTagContainer(), AllocateCanceledHandle);
}
