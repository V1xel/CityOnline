// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildAbility.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Actor/Player/Abilities/TargetData/COBuildAllocationTD.h"
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

	auto BuildPerformingEffectContext = FCOGameplayEffectContextHandle(ActorInfo->OwnerActor.Get());
	BuildPerformingEffectContext.SetTargetData(UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(const_cast<AActor*>(TriggerEventData->Target.Get())));
	//Adding player effect to track build ability is in progress, block other abilities
	_PlayerPerformingBuildEffectHandle = ApplyGESpecToOwner(BuildPerformingEffectContext.MakeGESpec(PlayerPerformingBuildEffect));

	auto BuildingTableData = BuildingsTable->FindRow<FCOBuildingTable>(FCOBuildConfigurationTD::GetBuildingName(TriggerEventData->TargetData), "");
	auto EffectContext = FCOGameplayEffectContextHandle(ActorInfo->OwnerActor.Get(), BuildingTableData->ToBuildTargetDataHandle());
	//Adding player effect to allow allocating the cells for building placing
	_AllocationEffectHandle = ApplyGESpecToOwner(EffectContext.MakeGESpec(PlayerAllocatePermissionEffect));

	_ConfigurationDTOTargetDataHandle = TriggerEventData->TargetData;
}

void UCOBuildAbility::OnAllocationFinished(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	_SelectionDTOTargetDataHandle = EventData->TargetData;

	RemoveActiveGameplayEffect(_AllocationEffectHandle);
	_AllocationEffectHandle.Invalidate();

	AddBuildPreviewEffect();
}

void UCOBuildAbility::OnConfigurationUpdated(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	_ConfigurationDTOTargetDataHandle = EventData->TargetData;

	auto TargetASC = GetASC(FCOBuildAllocationTD::GetTarget(_SelectionDTOTargetDataHandle));
	//Removing target effect to stop previewing the old build configuration
	TargetASC->RemoveActiveGameplayEffect(_BuildInProgressEffectHandle);

	AddBuildPreviewEffect();
}

void UCOBuildAbility::AddBuildPreviewEffect()
{
	auto BuildingTableData = BuildingsTable->FindRow<FCOBuildingTable>(FCOBuildConfigurationTD::GetBuildingName(_ConfigurationDTOTargetDataHandle), "");

	FGameplayAbilityTargetDataHandle TargetData;
	TargetData.Append(BuildingTableData->ToBuildTargetDataHandle());
	TargetData.Append(_ConfigurationDTOTargetDataHandle);
	TargetData.Append(_SelectionDTOTargetDataHandle);

	auto EffectContext = FCOGameplayEffectContextHandle(GetActorInfo().OwnerActor.Get());
	EffectContext.SetTargetData(TargetData);
	//Adding target effect to preview the build process
	_BuildInProgressEffectHandle = ApplyGESpecToTarget(EffectContext.MakeGESpec(TargetBuildPreviewEffect), _SelectionDTOTargetDataHandle).Last();
}

void UCOBuildAbility::OnAllocateCancelOrConfirm(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	auto Target = FCOBuildAllocationTD::GetTarget(_SelectionDTOTargetDataHandle);
	//Removing target effect to stop previewing the build process
	GetASC(Target)->RemoveActiveGameplayEffect(_BuildInProgressEffectHandle);

	if (Tag.MatchesTag(ListenEventOnBuildConfirmed)) 
	{
		FGameplayEventData DeployEventData;
		DeployEventData.TargetData.Append(_ConfigurationDTOTargetDataHandle);
		DeployEventData.TargetData.Append(_SelectionDTOTargetDataHandle);
		DeployEventData.Instigator = GetActorInfo().OwnerActor.Get();

		//Sending event to Target, to request the deploy of building
		SendServerGEToTarget(Target, BroadcastDeployEventOnBuildProcessFinished, DeployEventData);
	}

	//Removing palyer effect to indicate build is no more in progress
	RemoveActiveGameplayEffect(_PlayerPerformingBuildEffectHandle);
	EndAbilityArgsless();
}

void UCOBuildAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	RemoveGETagDelegate(ListenEventOnBuildConfirmed, _OnBuildConfirmedDH);
	RemoveGETagDelegate(ListenEventOnBuildCanceled, _OnBuildCanceledDH);
	RemoveGETagDelegate(ListenEventOnAllocationFinished, _OnAllocationFinishedDH);
	RemoveGETagDelegate(ListenEventOnConfigurationUpdated, _OnConfigurationUpdatedDH);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
