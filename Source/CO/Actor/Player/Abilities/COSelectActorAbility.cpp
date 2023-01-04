﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "COSelectActorAbility.h"

#include "CO/Actor/Player/COPlayerCharacter.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Core/AbilitySystem/COAbilitySystemComponent.h"
#include <CO/Core/COConstants.h>

void UCOSelectActorAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ApplyGameplayEffectToTarget(Handle, ActorInfo, ActivationInfo, TriggerEventData->TargetData, ActorSelectedEffect, 0);
	SendGameplayEvent(UCOGameplayTags::ActorSelected(), *TriggerEventData);
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

bool UCOSelectActorAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return !TargetTags->HasAny(TargetBlockedTags);
}

void UCOSelectActorAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
