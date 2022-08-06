// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/AbilitySystem/COGameplayAbilityBase.h"
#include "COSelectCellsAbility.generated.h"

class UCOSelectCellsAbilityTask;
class UCOStreetCellComponent;
class UCOSelectionDTO;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSelectionEndedDelegate, const UCOSelectionDTO*, SelectionData, const TArray<UCOStreetCellComponent*>&, AllocatedComponents);

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CO_API UCOSelectCellsAbility : public UCOGameplayAbilityBase
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							 const FGameplayAbilityActivationInfo ActivationInfo,
							 const FGameplayEventData* TriggerEventData) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
							bool bWasCancelled) override;

protected:
	UPROPERTY()
	UCOSelectCellsAbilityTask* SelectCellsAbilityTask;

	UPROPERTY()
	UCOSelectionDTO* SelectionDTO;
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnSelectionEndedDelegate OnSelectionEnded;
	
	UPROPERTY(EditDefaultsOnly)
	bool DrawDebugSelection;
};
