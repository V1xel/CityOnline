// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildAbility.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Actor/Player/Abilities/TargetData/COBuildConfigurationTD.h"
#include "CO/Actor/Player/Abilities/Helpers/COAllocateHelper.h"
#include "CO/Core/AbilitySystem/COGameplayEffectContext.h"

void UCOBuildAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	_OnBuildConfirmedDH = AddGETagDelegate(ListenEventOnBuildConfirmed, FGEDelegate::CreateUObject(this, &UCOBuildAbility::OnAllocateCancelOrConfirm));
	_OnBuildCanceledDH = AddGETagDelegate(ListenEventOnBuildCanceled, FGEDelegate::CreateUObject(this, &UCOBuildAbility::OnAllocateCancelOrConfirm));
	_OnAllocationFinishedDH = AddGETagDelegate(ListenEventOnAllocationFinished, FGEDelegate::CreateUObject(this, &UCOBuildAbility::OnAllocationFinished));
	_OnConfigurationUpdatedDH = AddGETagDelegate(ListenEventOnConfigurationUpdated, FGEDelegate::CreateUObject(this, &UCOBuildAbility::OnConfigurationUpdated));

	auto EffectContext = new FCOGameplayEffectContext(ActorInfo->OwnerActor.Get());
	auto ConfigurationTargetData = static_cast<const FCOBuildConfigurationTD*>(TriggerEventData->TargetData.Get(0));
	auto BuildingSpecialization = BuildingsTable->FindRow<FCOBuildingTable>(ConfigurationTargetData->BuildingName, "");
	EffectContext->SetTargetData(BuildingSpecialization->ToBuildTargetDataHandle());

	auto BuildPerformingEffectContext = new FCOGameplayEffectContext(ActorInfo->OwnerActor.Get());
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

	AddBuildInProgressEffect();
}

void UCOBuildAbility::OnConfigurationUpdated(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	_ConfigurationDTOTargetDataHandle = EventData->TargetData;

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
	AActor* Target = _SelectionDTOTargetDataHandle.Get(0)->GetActors()[0].Get();
	FGameplayEventData SelectEventData;
	SelectEventData.Target = Target;
	SelectEventData.TargetData = _SelectionDTOTargetDataHandle;

	SendGameplayEvent(BroadcastSelectActorEventOnBuildCanceled, SelectEventData);

	auto SelectionTargetData = static_cast<FCOSelectionTD*>(_SelectionDTOTargetDataHandle.Get(0));
	auto TargetAbilitySystem = Cast<IAbilitySystemInterface>(SelectionTargetData->Target)->GetAbilitySystemComponent();
	for (auto EffectHandle : _BuildInProgressEffectHandle)
	{
		TargetAbilitySystem->RemoveActiveGameplayEffect(EffectHandle);
	}

	if (Tag.MatchesTag(ListenEventOnBuildConfirmed)) 
	{
		FGameplayEventData DeployEventData;
		DeployEventData.TargetData.Append(_ConfigurationDTOTargetDataHandle);
		DeployEventData.TargetData.Append(_SelectionDTOTargetDataHandle);
		DeployEventData.Instigator = GetActorInfo().OwnerActor.Get();

		SendGameplayEvent(BroadcastDeployEventOnBuildProcessFinished, DeployEventData);

		auto PlayerCharacter = Cast<ACOPlayerController>(GetActorInfo().PlayerController.Get());
		PlayerCharacter->SendServerGameplayEventToListener(Target, BroadcastDeployEventOnBuildProcessFinished, DeployEventData);
	}

	GetActorInfo().AbilitySystemComponent->RemoveActiveGameplayEffect(_PlayerPerformingBuildEffectHandle);
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

