// Fill out your copyright notice in the Description page of Project Settings.


#include "COSelectActorAbility.h"

#include "CO/Actor/Player/COPlayerCharacter.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Core/AbilitySystem/COAbilitySystemComponent.h"

bool UCOSelectActorAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return !TargetTags->HasAny(TargetBlockedTags);
}

void UCOSelectActorAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	auto TargetAbilitySystem = Cast<IAbilitySystemInterface>(TriggerEventData->Target);
	if (!TargetAbilitySystem) {
		return;
	}

	FGameplayTagContainer AbilityGrantedTags;
	ActorSelectedEffect.GetDefaultObject()->GetOwnedGameplayTags(AbilityGrantedTags);

	auto PreviousTarget = Cast<IAbilitySystemInterface>(GetPlayerController()->SelectedActor);
	if (PreviousTarget) {
		auto AbilitySystem = PreviousTarget->GetAbilitySystemComponent();
		AbilitySystem->RemoveActiveEffectsWithGrantedTags(AbilityGrantedTags);
	}

	ApplyGameplayEffectToTarget(Handle, ActorInfo, ActivationInfo, TriggerEventData->TargetData, ActorSelectedEffect, 0);
	SendGameplayEvents(AbilityGrantedTags, *TriggerEventData);

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UCOSelectActorAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
