﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/AbilitySystem/COGameplayAbilityBase.h"
#include "COSelectActorAbility.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CO_API UCOSelectActorAbility : public UCOGameplayAbilityBase
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							 const FGameplayAbilityActivationInfo ActivationInfo,
							 const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
							bool bWasCancelled) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameplayEffect> ActorSelectedEffect{};

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UGameplayEffect> ActorDeselectedEffect{};
};