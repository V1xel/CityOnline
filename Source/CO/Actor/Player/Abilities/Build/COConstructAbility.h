// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Core/AbilitySystem/COGameplayAbilityBase.h"
#include "COConstructAbility.generated.h"

class ACOBuildingActor;
class UCORootAsset;
class UCOBuildingAsset;
class UCOSelectionDTO;
class UCOBuildDTO;
class UCOConstructionDTO;

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CO_API UCOConstructAbility : public UCOGameplayAbilityBase
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
		bool bWasCancelled) override;

	void OnConstructConfigurate(FGameplayTag Tag, const FGameplayEventData* EventData);

	void OnConstructFinalize(FGameplayTag Tag, const FGameplayEventData* EventData);

	UCOBuildingAsset* FindBestAsset();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCORootAsset* RootAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACOBuildingActor> BuildingActorClass;

	UPROPERTY()
	FGameplayTag ListenBuildingConfigurationUpdatedTag;

	UPROPERTY()
	FGameplayTag ListenBuildingConfigurationFinalizedTag;

	UPROPERTY()
	FGameplayTag SelectBuildingAfterItIsConstructedTag;

	UPROPERTY()
	FGameplayTag OccupyStreetCellsTag;

private:
	UPROPERTY()
	UCOSelectionDTO* _SelectionDTO;

	UPROPERTY()
	UCOBuildDTO* _BuildDTO;

	UPROPERTY()
	UCOBuildingAsset* _Asset;

	UPROPERTY()
	ACOBuildingActor* _BuildingActor;
};
