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
#include <AbilitySystemBlueprintLibrary.h>

void UCOBuildAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	_OnBuildConfirmedDelegateHandle = AddGETagDelegate(ListenEventOnBuildConfirmed, FGEDelegate::CreateUObject(this, &UCOBuildAbility::OnAllocateCancelOrConfirm));
	_OnBuildCanceledDelegateHandle = AddGETagDelegate(ListenEventOnBuildCanceled, FGEDelegate::CreateUObject(this, &UCOBuildAbility::OnAllocateCancelOrConfirm));
	_OnAllocationFinishedDelegateHandle = AddGETagDelegate(ListenEventOnAllocationFinished, FGEDelegate::CreateUObject(this, &UCOBuildAbility::OnAllocationFinished));
	_OnConfigurationUpdatedDelegateHandle = AddGETagDelegate(ListenEventOnConfigurationUpdated, FGEDelegate::CreateUObject(this, &UCOBuildAbility::OnConfigurationUpdated));

	auto EffectContext = new FCOGameplayEffectContext(ActorInfo->OwnerActor.Get(), ActorInfo->OwnerActor.Get());
	auto ConfigurationTargetData = static_cast<const FCOBuildConfigurationTD*>(TriggerEventData->TargetData.Get(0));
	auto BuildingSpecialization = BuildingsTable->FindRow<FCOBuildingTable>(ConfigurationTargetData->BuildingName, "");
	EffectContext->SetTargetData(BuildingSpecialization->ToBuildTargetDataHandle());

	auto BuildPerformingEffectContext = new FCOGameplayEffectContext(ActorInfo->OwnerActor.Get(), ActorInfo->OwnerActor.Get());
	BuildPerformingEffectContext->SetTargetData(UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(const_cast<AActor*>(TriggerEventData->Target.Get())));

	_ConfigurationDTOTargetDataHandle = TriggerEventData->TargetData;
	_PlayerPerformingBuildEffectHandle = ApplyGESpecToOwner(FGameplayEffectSpecHandle(new FGameplayEffectSpec(PlayerPerformingBuildEffect.GetDefaultObject(), FGameplayEffectContextHandle(BuildPerformingEffectContext))));
	_AllocationEffectHandle = ApplyGESpecToOwner(FGameplayEffectSpecHandle(new FGameplayEffectSpec(EnableCellAllocationEffect.GetDefaultObject(), FGameplayEffectContextHandle(EffectContext))));
}

void UCOBuildAbility::OnAllocationFinished(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	GetActorInfo().AbilitySystemComponent->RemoveActiveGameplayEffect(_AllocationEffectHandle);
	_SelectionDTOTargetDataHandle = EventData->TargetData;
	_AllocationEffectHandle.Invalidate();
	SelectionForPreviewBuildingOverridden = true;

	AddBuildInProgressEffect();
}

void UCOBuildAbility::OnConfigurationUpdated(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	_ConfigurationDTOTargetDataHandle = EventData->TargetData;
	if (!SelectionForPreviewBuildingOverridden)
		return;

	auto SelectionTargetData = static_cast<FCOSelectionTD*>(_SelectionDTOTargetDataHandle.Get(0));
	auto TargetAbilitySystem = Cast<IAbilitySystemInterface>(SelectionTargetData->Target)->GetAbilitySystemComponent();

	for (auto EffectHandle : _BuildInProgressEffectHandle)
	{
		TargetAbilitySystem->RemoveActiveGameplayEffect(EffectHandle);
	}

	AddBuildInProgressEffect();
}

void UCOBuildAbility::AddBuildInProgressEffect()
{
	auto EffectContext = new FCOGameplayEffectContext(GetActorInfo().OwnerActor.Get());
	auto ConfigurationTargetData = static_cast<const FCOBuildConfigurationTD*>(_ConfigurationDTOTargetDataHandle.Get(0));
	auto BuildingSpecialization = BuildingsTable->FindRow<FCOBuildingTable>(ConfigurationTargetData->BuildingName, "");

	FGameplayAbilityTargetDataHandle TargetData;
	TargetData.Append(BuildingSpecialization->ToBuildTargetDataHandle());
	TargetData.Append(_ConfigurationDTOTargetDataHandle);
	TargetData.Append(_SelectionDTOTargetDataHandle);
	EffectContext->SetTargetData(TargetData);

	_BuildInProgressEffectHandle = ApplyGESpecToTarget(
		FGameplayEffectSpecHandle(new FGameplayEffectSpec(BuildInProgressEffect.GetDefaultObject(), FGameplayEffectContextHandle(EffectContext))), _SelectionDTOTargetDataHandle);
}

void UCOBuildAbility::OnAllocateCancelOrConfirm(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	AActor* Target = nullptr;
	if (SelectionForPreviewBuildingOverridden) {
		FGameplayEventData SelectEventData;
		Target = _SelectionDTOTargetDataHandle.Get(0)->GetActors()[0].Get();
		SelectEventData.Target = Target;
		SelectEventData.TargetData = _SelectionDTOTargetDataHandle;

		SendGameplayEvent(BroadcastSelectActorEventOnBuildCanceled, SelectEventData);

		auto SelectionTargetData = static_cast<FCOSelectionTD*>(_SelectionDTOTargetDataHandle.Get(0));
		auto TargetAbilitySystem = Cast<IAbilitySystemInterface>(SelectionTargetData->Target)->GetAbilitySystemComponent();
		for (auto EffectHandle : _BuildInProgressEffectHandle)
		{
			TargetAbilitySystem->RemoveActiveGameplayEffect(EffectHandle);
		}
	}

	if (SelectionForPreviewBuildingOverridden) { // && Confirm
		FGameplayEventData DeployEventData;
		DeployEventData.TargetData.Append(_ConfigurationDTOTargetDataHandle);
		DeployEventData.TargetData.Append(_SelectionDTOTargetDataHandle);
		DeployEventData.Instigator = GetActorInfo().OwnerActor.Get();

		SendGameplayEvent(BroadcastDeployEventOnBuildProcessFinished, DeployEventData);

		auto PlayerCharacter = Cast<ACOPlayerController>(GetActorInfo().PlayerController.Get());
		PlayerCharacter->SendServerGameplayEventToListener(Target, BroadcastDeployEventOnBuildProcessFinished, DeployEventData);
	}

	GetActorInfo().AbilitySystemComponent->RemoveActiveGameplayEffect(_PlayerPerformingBuildEffectHandle);

	TerminateAbility();
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
	auto ConfigurationTargetData = static_cast<const FCOBuildConfigurationTD*>(EffectContext->TargetData.Get(1));
	auto SelectionTargetData = static_cast<const FCOSelectionTD*>(EffectContext->TargetData.Get(2));

	Floors = ConfigurationTargetData->Floors;
	Center = SelectionTargetData->Center;
	Direction = SelectionTargetData->Direction;

	auto InstigatorController = EffectContext->GetInstigator()->GetInstigatorController();
	auto RootAsset = Cast<ACOPlayerController>(InstigatorController)->RootAsset;

	return RootAsset->FindBestAsset(SelectionTargetData, BuildTargetData);
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

