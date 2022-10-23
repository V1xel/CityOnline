﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/AbilitySystem/COGameplayAbilityBase.h"
#include "CO/Database/Tables/COBuildingTable.h"
#include "AbilityTasks/COSelectCellsAbilityTask.h"
#include "COBuildAbility.generated.h"

class UCOSelectionDTO;

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CO_API UCOBuildAbility : public UCOGameplayAbilityBase
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							const FGameplayAbilityActivationInfo ActivationInfo,
							const FGameplayEventData* TriggerEventData) override;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
		OUT FGameplayTagContainer* OptionalRelevantTags) const;


	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
							bool bWasCancelled) override;

	void OnAllocationFinished(FGameplayTag Tag, const FGameplayEventData* EventData);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* BuildingsTable{};

	UPROPERTY()
	UCOSelectCellsAbilityTask* SelectCellsAbilityTask;

	UPROPERTY()
	UCOSelectionDTO* SelectionDTO;

	UPROPERTY()
	FCOBuildingTable BuildingSpecialization;

	UPROPERTY(EditDefaultsOnly)
	bool DrawDebugSelection;

	UPROPERTY()
	bool BuildSpecializationProvided;

private:
	FGameplayAbilitySpecHandle _Handle;

	const FGameplayAbilityActorInfo* _ActorInfo;

	FGameplayAbilityActivationInfo _ActivationInfo;
};
