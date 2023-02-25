// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildAbility.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Actor/Player/Abilities/TargetData/COBuildConfigurationTD.h"
#include "CO/Actor/Player/Abilities/Helpers/COAllocateHelper.h"
#include "CO/Core/AbilitySystem/COGameplayEffectContext.h"
#include <CO/Core/AbilitySystem/COGameplayEffectContextHandle.h>

void UCOBuildAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	_OnBuildConfirmedDH = AddGETagDelegate(ListenEventOnBuildConfirmed, FGEDelegate::CreateUObject(this, &UCOBuildAbility::OnAllocateCancelOrConfirm));
	_OnBuildCanceledDH = AddGETagDelegate(ListenEventOnBuildCanceled, FGEDelegate::CreateUObject(this, &UCOBuildAbility::OnAllocateCancelOrConfirm));
	_OnAllocationFinishedDH = AddGETagDelegate(ListenEventOnAllocationFinished, FGEDelegate::CreateUObject(this, &UCOBuildAbility::OnAllocationFinished));
	_OnConfigurationUpdatedDH = AddGETagDelegate(ListenEventOnConfigurationUpdated, FGEDelegate::CreateUObject(this, &UCOBuildAbility::OnConfigurationUpdated));

	auto BuildingTableData = BuildingsTable->FindRow<FCOBuildingTable>(FCOBuildConfigurationTD::GetBuildingName(TriggerEventData->TargetData), "");

	auto BuildPerformingEffectContext = FCOGameplayEffectContextHandle(ActorInfo->OwnerActor.Get());
	BuildPerformingEffectContext.SetTargetData(UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(const_cast<AActor*>(TriggerEventData->Target.Get())));
	_PlayerPerformingBuildEffectHandle = ApplyGESpecToOwner(BuildPerformingEffectContext.MakeGESpec(PlayerPerformingBuildEffect));

	auto EffectContext = FCOGameplayEffectContextHandle(ActorInfo->OwnerActor.Get(), BuildingTableData->ToBuildTargetDataHandle());
	_AllocationEffectHandle = ApplyGESpecToOwner(EffectContext.MakeGESpec(EnableCellAllocationEffect));

	_ConfigurationDTOTargetDataHandle = TriggerEventData->TargetData;
}

void UCOBuildAbility::OnAllocationFinished(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	_SelectionDTOTargetDataHandle = EventData->TargetData;

	GetActorInfo().AbilitySystemComponent->RemoveActiveGameplayEffect(_AllocationEffectHandle);
	_AllocationEffectHandle.Invalidate();

	AddBuildInProgressEffect();
}

void UCOBuildAbility::OnConfigurationUpdated(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	_ConfigurationDTOTargetDataHandle = EventData->TargetData;

	auto TargetASC = GetASC(FCOSelectionTD::GetTarget(_SelectionDTOTargetDataHandle));
	TargetASC->RemoveActiveGameplayEffect(_BuildInProgressEffectHandle);

	AddBuildInProgressEffect();
}

void UCOBuildAbility::AddBuildInProgressEffect()
{
	auto EffectContext = FCOGameplayEffectContextHandle(GetActorInfo().OwnerActor.Get());
	auto BuildingTableData = BuildingsTable->FindRow<FCOBuildingTable>(FCOBuildConfigurationTD::GetBuildingName(_ConfigurationDTOTargetDataHandle), "");

	FGameplayAbilityTargetDataHandle TargetData;
	TargetData.Append(BuildingTableData->ToBuildTargetDataHandle());
	TargetData.Append(_ConfigurationDTOTargetDataHandle);
	TargetData.Append(_SelectionDTOTargetDataHandle);
	EffectContext.SetTargetData(TargetData);

	_BuildInProgressEffectHandle = ApplyGESpecToTarget(EffectContext.MakeGESpec(BuildInProgressEffect), _SelectionDTOTargetDataHandle).Last();
}

void UCOBuildAbility::OnAllocateCancelOrConfirm(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	auto Target = FCOSelectionTD::GetTarget(_SelectionDTOTargetDataHandle);
	GetASC(Target)->RemoveActiveGameplayEffect(_BuildInProgressEffectHandle);

	if (Tag.MatchesTag(ListenEventOnBuildConfirmed)) 
	{
		FGameplayEventData DeployEventData;
		DeployEventData.TargetData.Append(_ConfigurationDTOTargetDataHandle);
		DeployEventData.TargetData.Append(_SelectionDTOTargetDataHandle);
		DeployEventData.Instigator = GetActorInfo().OwnerActor.Get();

		SendServerGEToTarget(Target, BroadcastDeployEventOnBuildProcessFinished, DeployEventData);
	}

	RemoveActiveGameplayEffect(_PlayerPerformingBuildEffectHandle);
	EndAbilityArgsless();
}

void UCOBuildAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenEventOnBuildConfirmed.GetSingleTagContainer(), _OnBuildConfirmedDH);
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenEventOnBuildCanceled.GetSingleTagContainer(), _OnBuildCanceledDH);
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenEventOnAllocationFinished.GetSingleTagContainer(), _OnAllocationFinishedDH);
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenEventOnConfigurationUpdated.GetSingleTagContainer(), _OnConfigurationUpdatedDH);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
