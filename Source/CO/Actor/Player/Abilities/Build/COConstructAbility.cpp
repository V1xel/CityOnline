// Fill out your copyright notice in the Description page of Project Settings.

#include "CO/Actor/Player/Abilities/Build/COConstructAbility.h"
#include "CO/Actor/Player/Abilities/DTO/COSelectionDTO.h"
#include "CO/Actor/Player/Abilities/DTO/COBuildDTO.h"
#include "CO/Actor/Player/Abilities/DTO/COConstructionDTO.h"
#include "CO/Actor/Building/COBuildingActor.h"
#include "CO/Database/Assets/COBuildingAsset.h"
#include "CO/Database/Assets/CORootAsset.h"
#include "CO/Core/COConstants.h"
#include "COConstructAbility.h"
#include "Kismet/GameplayStatics.h"

void UCOConstructAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	FGameplayEventTagMulticastDelegate::FDelegate ConstructConfigurateDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UCOConstructAbility::OnConstructConfigurate);
	ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(UCOGameplayTags::UpdatedConfiguration().GetSingleTagContainer(), ConstructConfigurateDelegate);

	FGameplayEventTagMulticastDelegate::FDelegate ConstructFinalizeDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UCOConstructAbility::OnConstructFinalize);
	ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(UCOGameplayTags::UpdatedConfiguration().GetSingleTagContainer(), ConstructFinalizeDelegate);

	_SelectionDTO = Cast<UCOSelectionDTO>(TriggerEventData->OptionalObject);
	_BuildDTO = Cast<UCOBuildDTO>(TriggerEventData->OptionalObject2);

	if (_SelectionDTO && _BuildDTO) {
		_Asset = FindBestAsset();
		_BuildingActor = GetWorld()->SpawnActorDeferred<ACOBuildingActor>(BuildingActorClass, FTransform(_SelectionDTO->Rotation, _SelectionDTO->Center));
		_BuildingActor->BuildingAsset = _Asset;
		_BuildingActor->ComposeBuilding();
		_BuildingActor->FinishSpawning(FTransform());
		_BuildingActor->SetActorLocationAndRotation(_SelectionDTO->Center, _SelectionDTO->Rotation + _Asset->RotationOffset);

		auto Data = FGameplayEventData();
		Data.Target = _BuildingActor;
		SendGameplayEvent(SelectBuildingAfterItIsConstructedTag, Data);
	}
}

UCOBuildingAsset* UCOConstructAbility::FindBestAsset()
{
	int matchCount = -1;
	UCOBuildingAsset* BestAsset = nullptr;
	for (UCOBuildingAsset* Asset : RootAsset->BuildingsAssets)
	{
		int currentCount = 0;
		if (Asset->HasCorner == _SelectionDTO->HasCorner)
		{
			currentCount++;
		}
		if (Asset->IsLiving == _BuildDTO->IsLiving ||
			Asset->IsStore == _BuildDTO->IsStore)
		{
			currentCount++;
		}
		if (Asset->Width == _SelectionDTO->Width || Asset->Width == _SelectionDTO->Length)
		{
			currentCount++;
		}
		if (Asset->Length == _SelectionDTO->Length || Asset->Length == _SelectionDTO->Width)
		{
			currentCount++;
		}
		if (currentCount > matchCount)
		{
			matchCount = currentCount;
			BestAsset = Asset;
		}
	}

	return BestAsset;
}

void UCOConstructAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UCOConstructAbility::OnConstructConfigurate(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	if (_BuildingActor && EventData && EventData->Target) {
		_BuildingActor->Configuration = Cast<UCOConstructionDTO>(EventData->Target);
		_BuildingActor->ApplyChanges();
		_BuildingActor->SetActorLocationAndRotation(_SelectionDTO->Center, _SelectionDTO->Rotation + _Asset->RotationOffset);
	}
}

void UCOConstructAbility::OnConstructFinalize(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	if (_BuildingActor && EventData && EventData->Target) {
		auto Data = FGameplayEventData();
		Data.Target = _BuildingActor;
		SendGameplayEvent(UCOGameplayTags::Select(), Data);
	}
}
