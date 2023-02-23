// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Actor/Street/Abilities/CODeployBuildingAbility.h"
#include "CO/Actor/Building/COBuildingActor.h"
#include "AbilitySystemComponent.h"
#include "CO/Database/Assets/CORootAsset.h"
#include "CO/Actor/Player/Abilities/TargetData/COBuildConfigurationTD.h"
#include "CO/Actor/Player/Abilities/TargetData/COSelectionTD.h"
#include "CO/Database/Tables/COBuildingTable.h"
#include "CO/Database/Assets/COBuildingAsset.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Core/Actor/Building/COBuildingFunctionLibrary.h"

void UCODeployBuildingAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	auto ConfigurationTD = static_cast<const FCOBuildConfigurationTD*>(TriggerEventData->TargetData.Get(0));
	auto SelectionTD = static_cast<const FCOSelectionTD*>(TriggerEventData->TargetData.Get(1));
	auto BuildingRotation = SelectionTD->Direction.ToOrientationRotator();

	auto BuildingSpecialization = BuildingsTable->FindRow<FCOBuildingTable>(ConfigurationTD->BuildingName, "");
	auto BuildTargetDataHandle = BuildingSpecialization->ToBuildTargetDataHandle();
	auto BuildTargetData = static_cast<const FCOBuildTD*>(BuildTargetDataHandle.Get(0));

	auto InstigatorController = TriggerEventData->Instigator.Get()->GetInstigatorController();
	auto RootAsset = Cast<ACOPlayerController>(InstigatorController)->RootAsset;
	auto BuildingAsset = RootAsset->FindBestAsset(SelectionTD, BuildTargetData);

	auto Building = GetWorld()->SpawnActorDeferred<ACOBuildingActor>(BuildingActorClass, FTransform(SelectionTD->Center));
	Building->ComposeBuilding(ConfigurationTD->Floors, BuildingAsset, SelectionTD->Direction);
	Building->FinishSpawning(FTransform());
	Building->SetActorLocation(SelectionTD->Center);
}

void UCODeployBuildingAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
