// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/AbilitySystem/COGameplayAbilityBase.h"
#include "GameplayTagContainer.h"
#include "COAllocateAbility.generated.h"

class UCOSelectCellsAbilityTask;

/**
 * 
 */
UCLASS()
class CO_API UCOAllocateAbility : public UCOGameplayAbilityBase
{
	GENERATED_BODY()


public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	void OnAllocationCanceled(FGameplayTag Tag, const FGameplayEventData* EventData);

protected:
	UPROPERTY()
	UCOSelectCellsAbilityTask* SelectCellsAbilityTask;

	FDelegateHandle AllocateCanceledHandle;

private:
	FGameplayAbilitySpecHandle _Handle;

	const FGameplayAbilityActorInfo* _ActorInfo; 

	FGameplayAbilityActivationInfo _ActivationInfo;
};
