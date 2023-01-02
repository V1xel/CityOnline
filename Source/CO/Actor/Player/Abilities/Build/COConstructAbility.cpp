// Fill out your copyright notice in the Description page of Project Settings.

#include "CO/Actor/Player/Abilities/Build/COConstructAbility.h"
#include "CO/Actor/Player/Abilities/DTO/COSelectionDTO.h"
#include "CO/Actor/Player/Abilities/DTO/COBuildDTO.h"
#include "CO/Actor/Player/Abilities/DTO/COConstructionDTO.h"
#include "CO/Actor/Building/COBuildingActor.h"
#include "CO/Database/Assets/COBuildingAsset.h"
#include "CO/Database/Assets/CORootAsset.h"
#include "CO/Game/COConstants.h"
#include "COConstructAbility.h"
#include "Kismet/GameplayStatics.h"

void UCOConstructAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//FGameplayEventTagMulticastDelegate::FDelegate ConstructConfigurateDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UCOConstructAbility::OnConstructConfigurate);
	//ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(UCOGameplayTags::AllocateFinished().GetSingleTagContainer(), ConstructConfigurateDelegate);

	auto SelectionDTO = Cast<UCOSelectionDTO>(TriggerEventData->OptionalObject);
	auto BuildDTO = Cast<UCOBuildDTO>(TriggerEventData->OptionalObject2);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Construct ActivateAbility!"));

	if (SelectionDTO && BuildDTO) {
		Construction = GetWorld()->SpawnActorDeferred<ACOBuildingActor>(BuildingActor, FTransform(SelectionDTO->Rotation, SelectionDTO->Center));
		Construction->BuildingAsset = FindBestAsset(SelectionDTO, BuildDTO);
		Construction->Floor = 1;
		Construction->ComposeBuilding();
		Construction->FinishSpawning(FTransform());
		Construction->SetActorLocationAndRotation(SelectionDTO->Center, SelectionDTO->Rotation + Construction->BuildingAsset->RotationOffset);

		auto Data = FGameplayEventData();
		Data.OptionalObject = Construction;
		SendGameplayEvent(UCOGameplayTags::Select(), Data);
	}
}

UCOBuildingAsset* UCOConstructAbility::FindBestAsset(const UCOSelectionDTO* SelectionDTO, const UCOBuildDTO* BuildDTO)
{
	int matchCount = -1;
	UCOBuildingAsset* BestAsset = nullptr;
	for (UCOBuildingAsset* Asset : RootAsset->BuildingsAssets)
	{
		int currentCount = 0;
		if (Asset->HasCorner == SelectionDTO->HasCorner)
		{
			currentCount++;
		}
		if (Asset->IsLiving == BuildDTO->IsLiving ||
			Asset->IsStore == BuildDTO->IsStore)
		{
			currentCount++;
		}
		if (Asset->Width == SelectionDTO->Width || Asset->Width == SelectionDTO->Length)
		{
			currentCount++;
		}
		if (Asset->Length == SelectionDTO->Length || Asset->Length == SelectionDTO->Width)
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

void UCOConstructAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
}

void UCOConstructAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
}

void UCOConstructAbility::OnConstructConfigurate(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	if (Construction && EventData && EventData->OptionalObject) {
		Construction->Configuration = Cast<UCOConstructionDTO>(EventData->OptionalObject);
		//Construction->ApplyChanges();
	}
}
