// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Core/AbilitySystem/COGameplayAbilityBase.h"
#include "CO/Database/Tables/COBuildingTable.h"
#include "COBuildAbility.generated.h"

class UCORootAsset;
class UCOBuildingAsset;
class ACOBuildingActor;
class UCOSelectCellsAbilityTask;

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

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
		bool bWasCancelled) override;

	void OnAllocationFinished(FGameplayTag Tag, const FGameplayEventData* EventData);

	void OnConfigurationUpdated(FGameplayTag Tag, const FGameplayEventData* EventData);

	void OnAllocateCancelOrConfirm(FGameplayTag Tag, const FGameplayEventData* EventData);

	void AddBuildPreviewEffect();

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> TargetBuildPreviewEffect;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> PlayerAllocatePermissionEffect;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> PlayerPerformingBuildEffect;

	UPROPERTY(EditAnywhere)
	UDataTable* BuildingsTable;

	UPROPERTY(EditAnywhere)
	FGameplayTag FilterBuildingTag;
	UPROPERTY(EditAnywhere)
	FGameplayTag ListenEventOnAllocationFinished;
	UPROPERTY(EditAnywhere)
	FGameplayTag ListenEventOnConfigurationUpdated;
	UPROPERTY(EditAnywhere)
	FGameplayTag ListenEventOnBuildCanceled;
	UPROPERTY(EditAnywhere)
	FGameplayTag ListenEventOnBuildConfirmed;
	UPROPERTY(EditAnywhere)
	FGameplayTag BroadcastDeployEventOnBuildProcessFinished;
	UPROPERTY(EditAnywhere)
	FGameplayTag BroadcastSelectActorEventOnBuildCanceled;
private:
	FGameplayAbilityTargetDataHandle _SelectionDTOTargetDataHandle;

	FGameplayAbilityTargetDataHandle _ConfigurationDTOTargetDataHandle;

	FDelegateHandle _OnAllocationFinishedDH;

	FDelegateHandle _OnConfigurationUpdatedDH;

	FDelegateHandle _OnBuildConfirmedDH;

	FDelegateHandle _OnBuildCanceledDH;

	FActiveGameplayEffectHandle _PlayerPerformingBuildEffectHandle;

	FActiveGameplayEffectHandle _AllocationEffectHandle;

	FActiveGameplayEffectHandle _BuildInProgressEffectHandle;
};
