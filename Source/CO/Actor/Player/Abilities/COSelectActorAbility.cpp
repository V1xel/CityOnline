// Fill out your copyright notice in the Description page of Project Settings.


#include "COSelectActorAbility.h"

#include "CO/Actor/Player/COPlayerCharacter.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Core/AbilitySystem/COAbilitySystemComponent.h"
#include "Templates/SharedPointer.h"

bool UCOSelectActorAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return !TargetTags->HasAny(TargetBlockedTags) && TargetTags->HasAll(TargetRequiredTags);
}

void UCOSelectActorAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	_Target = TriggerEventData->Target.Get();
	_AppliedEffects = ApplyGameplayEffectToTarget(Handle, ActorInfo, ActivationInfo, TriggerEventData->TargetData, ActorSelectedEffect, 0);
}

void UCOSelectActorAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	for (auto Effect : _AppliedEffects)
	{
		auto SelectedActorAbilityInterface = Cast<IAbilitySystemInterface>(_Target);
		SelectedActorAbilityInterface->GetAbilitySystemComponent()->RemoveActiveGameplayEffect(Effect);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UCOSelectActorAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
