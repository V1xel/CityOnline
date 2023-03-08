// Fill out your copyright notice in the Description page of Project Settings.

#include "CODeployBuildingAbility.h"
#include "AbilitySystemComponent.h"
#include "CO/Actor/Building/COBuildingActor.h"
#include "CO/Actor/Player/Abilities/Build/TargetData/COBuildConfigurationTD.h"
#include "CO/Actor/Player/Abilities/Build/TargetData/COBuildRequirementsTD.h"
#include "CO/Actor/Player/Abilities/Build/TargetData/COBuildAllocationTD.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Database/Assets/CORootAsset.h"
#include "CO/Database/Tables/COBuildingTable.h"
#include "CO/Database/Assets/COBuildingAsset.h"
#include "CO/Core/Actor/Building/COBuildingFunctionLibrary.h"
#include <CO/Actor/Street/COStreetActor.h>
#include <AbilitySystemBlueprintLibrary.h>
#include <CO/Core/AbilitySystem/COGameplayEffectContextHandle.h>

void UCODeployBuildingAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	auto ConfigurationTD = static_cast<const FCOBuildConfigurationTD*>(TriggerEventData->TargetData.Get(0));
	auto AllocationTD = static_cast<const FCOBuildAllocationTD*>(TriggerEventData->TargetData.Get(1));
	auto BuildingRotation = AllocationTD->Direction.ToOrientationRotator();

	auto BuildingSpecialization = BuildingsTable->FindRow<FCOBuildingTable>(ConfigurationTD->BuildingName, "");
	auto BuildTargetDataHandle = BuildingSpecialization->ToBuildTargetDataHandle();
	auto BuildTargetData = static_cast<const FCOBuildRequirementsTD*>(BuildTargetDataHandle.Get(0));

	auto InstigatorController = TriggerEventData->Instigator.Get()->GetInstigatorController();
	auto RootAsset = Cast<ACOPlayerController>(InstigatorController)->RootAsset;

	auto BuildingAsset = RootAsset->FindBestAsset(AllocationTD, BuildTargetData);

	auto Street = Cast<ACOStreetActor>(ActorInfo->OwnerActor);
	Street->OccupyCells(AllocationTD);

	auto Building = GetWorld()->SpawnActorDeferred<ACOBuildingActor>(BuildingActorClass, FTransform(AllocationTD->Center));
	Building->ComposeBuilding(ConfigurationTD->Floors, BuildingAsset, AllocationTD->Direction);
	Building->UnitCost = ConfigurationTD->Floors * AllocationTD->Cells.Num() * BuildTargetData->CostMultiplier;
	Building->FinishSpawning(FTransform());
	Building->SetActorLocation(AllocationTD->Center);

	auto InitialEffectContext = FCOGameplayEffectContextHandle(ActorInfo->OwnerActor.Get());

	auto BuildingActorInitialEffect = NewObject<UGameplayEffect>(Building, "BuildingActorInitial", RF_NoFlags, BuildingActorInitialEffectClass.GetDefaultObject());
	BuildingActorInitialEffect->InheritableOwnedTagsContainer.AddTag(BuildTargetData->Type);

	ApplyGameplayEffectSpecToTarget(Handle, ActorInfo, ActivationInfo, InitialEffectContext.MakeGESpec(BuildingActorInitialEffect), UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(Building));
}

void UCODeployBuildingAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
