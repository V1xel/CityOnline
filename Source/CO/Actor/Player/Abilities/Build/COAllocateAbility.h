// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Core/AbilitySystem/COGameplayAbilityBase.h"
#include "GameplayTagContainer.h"
#include "COAllocateAbility.generated.h"

class UCOSelectCellsAbilityTask;
class UCOSelectionDTO;
class UCOBuildDTO;

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

	void AllocationCancel(FGameplayTag Tag, const FGameplayEventData* EventData);
public:
	UPROPERTY(EditAnywhere)
	FGameplayTag BroadcastedEventOnAllocationFinished;
	UPROPERTY(EditAnywhere)
	FGameplayTag FilterAllocatePermissionTag;
	UPROPERTY(EditAnywhere)
	FGameplayTag ListenCancelAllocateTag;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> TargetAllocateInProgressEffect;
private:
	FGameplayAbilityTargetDataHandle _AllocateActivatedTargetData;

	FGameplayAbilityTargetDataHandle _BuildRequirementsTargetData;

	FActiveGameplayEffectHandle _AllocateEffectHandle;

	FDelegateHandle _CancelDelegateHandle;
};
