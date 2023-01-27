// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Core/AbilitySystem/COGameplayAbilityBase.h"
#include "CO/Database/Tables/COBuildingTable.h"
#include "COBuildAbility.generated.h"

class UCOBuildDTO;
class UCORootAsset;
class UCOSelectionDTO;
class UCOBuildingAsset;
class ACOBuildingActor;
class UCOBuildConfigurationDTO;
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

	void OnConfigurationUpdated(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* EventData);

	void OnAllocateCancelOrConfirm(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* EventData, bool Confirm);

	UFUNCTION(BlueprintPure)
	static FGameplayAbilityTargetDataHandle MakeBuildConfigurationTargetDataHandle(FName BuildingName, int32 Floors);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCORootAsset* RootAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ACOBuildingActor> BuildingActorClass;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> EnableCellAllocationEffect{};

	UPROPERTY(EditAnywhere)
		TSubclassOf<UGameplayEffect> PendingDeployEffect{};

	UPROPERTY(EditAnywhere)
		UDataTable* BuildingsTable {};
	UPROPERTY(EditAnywhere)
		FGameplayTag ListenEventOnAllocationFinished;

	UPROPERTY(EditAnywhere)
		FGameplayTag ListenEventOnConfigurationUpdated;

	UPROPERTY(EditAnywhere)
		FGameplayTag ListenEventOnBuildConfirmed;

	UPROPERTY(EditAnywhere)
		FGameplayTag ListenEventOnBuildCanceled;

	UPROPERTY(EditAnywhere)
		FGameplayTag FilterBuildingTag;

private:
	UPROPERTY()
		ACOBuildingActor* _BuildingPreview;

	FGameplayAbilityTargetDataHandle _SelectionDTOTargetDataHandle;

	FGameplayAbilityTargetDataHandle _ConfigurationDTOTargetDataHandle;

	FDelegateHandle _OnAllocationFinishedDelegateHandle;

	FDelegateHandle _OnConfigurationUpdatedDelegateHandle;

	FDelegateHandle _OnBuildConfirmedDelegateHandle;

	FDelegateHandle _OnBuildCanceledDelegateHandle;

	FActiveGameplayEffectHandle _AllocationEffectHandle;
};
