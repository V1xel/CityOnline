// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Core/AbilitySystem/COGameplayAbilityBase.h"
#include "GameplayTagContainer.h"
#include "COAllocateAbility.generated.h"

class UCOSelectCellsAbilityTask;
class UCOSelectionDTO;

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CO_API UCOAllocateAbility : public UCOGameplayAbilityBase
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	void AbilityTaskTick();

	void AllocationCancel(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData);

public:
	UPROPERTY(EditAnywhere)
	bool DebugAllocation;

	UPROPERTY(EditAnywhere)
	FGameplayTag BroadcastedEventOnAllocationUpdated;

	UPROPERTY(EditAnywhere)
	FGameplayTag BroadcastedEventOnAllocationFinished;

	UPROPERTY(EditAnywhere)
	FGameplayTag FilterAllocatePermissionTag;

	UPROPERTY(EditAnywhere)
	FGameplayTag ListenCancelAllocateTag;

private:
	UPROPERTY()
	const AActor* _Target;

	UPROPERTY()
	UCOSelectCellsAbilityTask* _AllocationTask;

	FDelegateHandle _CancelDelegateHandle;
};
