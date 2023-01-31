// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildAbility.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Actor/Street/COStreetActor.h"
#include "CO/Actor/Player/COPlayerState.h"
#include "CO/Extensions/GameplayTagExtension.h"
#include "CO/Database/Assets/COBuildingAsset.h"
#include "CO/Database/Assets/CORootAsset.h"
#include "CO/Actor/Building/COBuildingActor.h"
#include "CO/Actor/Player/Abilities/TargetData/COBuildConfigurationTD.h"
#include "CO/Actor/Player/Abilities/Helpers/COAllocateHelper.h"
#include "CO/Core/AbilitySystem/COGameplayEffectContext.h"

void UCOBuildAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	FGameplayEventTagMulticastDelegate::FDelegate BuildConfirmedDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateLambda([this, Handle, ActorInfo, ActivationInfo]
	(FGameplayTag Tag, const FGameplayEventData* EventData) { OnAllocateCancelOrConfirm(Handle, ActorInfo, ActivationInfo, EventData, true); });
	_OnBuildConfirmedDelegateHandle = ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenEventOnBuildConfirmed.GetSingleTagContainer(), BuildConfirmedDelegate);

	FGameplayEventTagMulticastDelegate::FDelegate BuildCanceledDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateLambda([this, Handle, ActorInfo, ActivationInfo]
	(FGameplayTag Tag, const FGameplayEventData* EventData) { OnAllocateCancelOrConfirm(Handle, ActorInfo, ActivationInfo, EventData, false); });
	_OnBuildCanceledDelegateHandle = ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenEventOnBuildCanceled.GetSingleTagContainer(), BuildCanceledDelegate);

	FGameplayEventTagMulticastDelegate::FDelegate AllocationFinishedDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateLambda([this, Handle, ActorInfo, ActivationInfo]
	(FGameplayTag Tag, const FGameplayEventData* EventData) { OnAllocationFinished(Handle, ActorInfo, ActivationInfo, EventData); });
	_OnAllocationFinishedDelegateHandle = ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenEventOnAllocationFinished.GetSingleTagContainer(), AllocationFinishedDelegate);

	FGameplayEventTagMulticastDelegate::FDelegate ConfigurationUpdatedDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateLambda([this, Handle, ActorInfo, ActivationInfo]
	(FGameplayTag Tag, const FGameplayEventData* EventData) { OnConfigurationUpdated(Handle, ActorInfo, ActivationInfo, EventData); });
	_OnConfigurationUpdatedDelegateHandle = ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenEventOnConfigurationUpdated.GetSingleTagContainer(), ConfigurationUpdatedDelegate);

	auto EffectContext = new FCOGameplayEffectContext(ActorInfo->OwnerActor.Get(), ActorInfo->OwnerActor.Get());
	auto ConfigurationTargetData = static_cast<const FCOBuildConfigurationTD*>(TriggerEventData->TargetData.Get(0));
	auto BuildingSpecialization = BuildingsTable->FindRow<FCOBuildingTable>(ConfigurationTargetData->BuildingName, "");
	EffectContext->SetTargetData(BuildingSpecialization->ToTargetDataHandle());

	_ConfigurationDTOTargetDataHandle = TriggerEventData->TargetData;
	_AllocationEffectHandle = ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, FGameplayEffectSpecHandle(new FGameplayEffectSpec(EnableCellAllocationEffect.GetDefaultObject(), FGameplayEffectContextHandle(EffectContext))));
}

void UCOBuildAbility::OnAllocationFinished(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* EventData)
{
	GetActorInfo().AbilitySystemComponent->RemoveActiveGameplayEffect(_AllocationEffectHandle);
	_SelectionDTOTargetDataHandle = EventData->TargetData;
	_AllocationEffectHandle.Invalidate();

	AddBuildInProgressEffect(Handle, ActorInfo, ActivationInfo);
}

void UCOBuildAbility::AddBuildInProgressEffect(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	auto EffectContext = new FCOGameplayEffectContext(ActorInfo->OwnerActor.Get(), ActorInfo->OwnerActor.Get());
	auto ConfigurationTargetData = static_cast<const FCOBuildConfigurationTD*>(_ConfigurationDTOTargetDataHandle.Get(0));
	auto BuildingSpecialization = BuildingsTable->FindRow<FCOBuildingTable>(ConfigurationTargetData->BuildingName, "");

	FGameplayAbilityTargetDataHandle TargetData;
	TargetData.Append(BuildingSpecialization->ToTargetDataHandle());
	TargetData.Append(_ConfigurationDTOTargetDataHandle);
	TargetData.Append(_SelectionDTOTargetDataHandle);
	EffectContext->SetTargetData(TargetData);

	_BuildInProgressEffectHandle = ApplyGameplayEffectSpecToTarget(Handle, ActorInfo, ActivationInfo, 
		FGameplayEffectSpecHandle(new FGameplayEffectSpec(BuildInProgressEffect.GetDefaultObject(), FGameplayEffectContextHandle(EffectContext))), _SelectionDTOTargetDataHandle);
}

void UCOBuildAbility::OnConfigurationUpdated(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* EventData)
{
	_ConfigurationDTOTargetDataHandle = EventData->TargetData;

	auto SelectionTargetData = static_cast<FCOSelectionTD*>(_SelectionDTOTargetDataHandle.Get(0));
	auto TargetAbilitySystem = Cast<IAbilitySystemInterface>(SelectionTargetData->Target)->GetAbilitySystemComponent();

	for (auto EffectHandle : _BuildInProgressEffectHandle)
	{
		TargetAbilitySystem->RemoveActiveGameplayEffect(EffectHandle);
	}
	AddBuildInProgressEffect(Handle, ActorInfo, ActivationInfo);
}

void UCOBuildAbility::OnAllocateCancelOrConfirm(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* EventData, bool Confirm)
{
	if (Confirm) {
		FGameplayEventData DeployEventData;
		DeployEventData.TargetData.Append(_ConfigurationDTOTargetDataHandle);
		DeployEventData.TargetData.Append(_SelectionDTOTargetDataHandle);

		SendGameplayEvent(BroadcastDeployEventOnBuildProcessFinished, DeployEventData);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

FGameplayAbilityTargetDataHandle UCOBuildAbility::MakeBuildConfigurationTargetDataHandle(FName BuildingName, int32 Floors)
{
	auto TargetData = new FCOBuildConfigurationTD();
	TargetData->BuildingName = BuildingName;
	TargetData->Floors = Floors;

	return FGameplayAbilityTargetDataHandle(TargetData);
}

UCOBuildingAsset* UCOBuildAbility::BreakCueEffectContextTargetDataAsBuildConfiguration(FGameplayCueParameters Parameters, FVector& Center, FVector& Direction, int32& Floors)
{
	auto EffectContext = static_cast<FCOGameplayEffectContext*>(Parameters.EffectContext.Get());
	auto BuildTargetData = static_cast<const FCOBuildTD*>(EffectContext->TargetData.Get(0));
	auto SelectionTargetData = static_cast<const FCOSelectionTD*>(EffectContext->TargetData.Get(1));
	auto ConfigurationTargetData = static_cast<const FCOBuildConfigurationTD*>(EffectContext->TargetData.Get(2));

	Floors = ConfigurationTargetData->Floors;
	Center = SelectionTargetData->Center;
	Direction = SelectionTargetData->Direction;

	return UCORootAsset::Instance->FindBestAsset(SelectionTargetData, BuildTargetData);
}

void UCOBuildAbility::BreakSelectionTD(FGameplayAbilityTargetDataHandle InSelectionTargetData, int32& Length, int32& Width)
{
	auto SelectionTargetData = static_cast<const FCOSelectionTD*>(InSelectionTargetData.Get(0));

	Length = SelectionTargetData->Length;
	Width = SelectionTargetData->Width;
}

void UCOBuildAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenEventOnBuildConfirmed.GetSingleTagContainer(), _OnBuildConfirmedDelegateHandle);
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenEventOnBuildCanceled.GetSingleTagContainer(), _OnBuildCanceledDelegateHandle);
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenEventOnAllocationFinished.GetSingleTagContainer(), _OnAllocationFinishedDelegateHandle);
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenEventOnConfigurationUpdated.GetSingleTagContainer(), _OnConfigurationUpdatedDelegateHandle);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

