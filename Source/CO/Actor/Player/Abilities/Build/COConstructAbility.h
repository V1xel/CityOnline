// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/AbilitySystem/COGameplayAbilityBase.h"
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

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
		bool bWasCancelled) override;

	void OnConstructConfigurate(FGameplayTag Tag, const FGameplayEventData* EventData);

	UCOBuildingAsset* FindBestAsset(const UCOSelectionDTO* SelectionDTO,const UCOBuildDTO* BuildDTO);
public:
	ACOBuildingActor* Construction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCORootAsset* RootAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACOBuildingActor> BuildingActor;
};
