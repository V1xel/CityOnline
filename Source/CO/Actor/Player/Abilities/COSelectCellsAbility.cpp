// Fill out your copyright notice in the Description page of Project Settings.


#include "COSelectCellsAbility.h"
#include "CO/Actor/Player/Effects/COActorSelectedEffect.h"

void UCOSelectCellsAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	auto OwnerActor = GetOwnerActor(ActorInfo);
	

	auto Effect = Cast<UCOActorSelectedEffect>(UCOActorSelectedEffect::StaticClass()->GetDefaultObject());
	ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, Effect, 1);

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UCOSelectCellsAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
}

void UCOSelectCellsAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
