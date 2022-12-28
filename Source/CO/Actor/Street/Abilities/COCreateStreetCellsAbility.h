// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/AbilitySystem/COGameplayAbilityBase.h"
#include "COCreateStreetCellsAbility.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CO_API UCOCreateStreetCellsAbility : public UCOGameplayAbilityBase
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
			const FGameplayAbilityActivationInfo ActivationInfo,
			const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FVector Scale;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		FVector Extent;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		int Horizontal = 6;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		int Vertical = 6;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		float Coverage = 0.83;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		float Size = 0.17f;
};
