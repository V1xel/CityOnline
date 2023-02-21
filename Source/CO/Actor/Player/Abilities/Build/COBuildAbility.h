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

	void OnAllocationFinished(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* EventData);

	void AddBuildInProgressEffect(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo);

	void OnConfigurationUpdated(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* EventData);

	void OnAllocateCancelOrConfirm(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* EventData, bool Confirm);

	UFUNCTION(BlueprintPure)
	static FGameplayAbilityTargetDataHandle MakeBuildConfigurationTargetDataHandle(FName BuildingName, int32 Floors);

	UFUNCTION(BlueprintPure, meta = (NativeBreakFunc, AdvancedDisplay = 6))
	static UCOBuildingAsset* BreakCueEffectContextTargetDataAsBuildConfiguration(FGameplayCueParameters Parameters, FVector& Center, FVector& Direction, int32& Floors);

	UFUNCTION(BlueprintPure, meta = (NativeBreakFunc, AdvancedDisplay = 6))
	static void BreakSelectionTD(FGameplayAbilityTargetDataHandle InSelectionTargetData, int32& Length, int32& Width);

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> EnableCellAllocationEffect{};

	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> PendingDeployEffect{};

	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> BuildInProgressEffect{};

	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> PlayerPerformingBuildEffect{};

	UPROPERTY(EditAnywhere)
		UDataTable* BuildingsTable {};

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
	UPROPERTY()
		ACOBuildingActor* _BuildingPreview;

	FGameplayAbilityTargetDataHandle _SelectionDTOTargetDataHandle;

	FGameplayAbilityTargetDataHandle _ConfigurationDTOTargetDataHandle;

	FDelegateHandle _OnAllocationFinishedDelegateHandle;

	FDelegateHandle _OnConfigurationUpdatedDelegateHandle;

	FDelegateHandle _OnBuildConfirmedDelegateHandle;

	FDelegateHandle _OnBuildCanceledDelegateHandle;

	FActiveGameplayEffectHandle _PlayerPerformingBuildEffectHandle;

	FActiveGameplayEffectHandle _AllocationEffectHandle;

	TArray<FActiveGameplayEffectHandle> _BuildInProgressEffectHandle;

	bool SelectionForPreviewBuildingOverridden;
};
