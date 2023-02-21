// Fill out your copyright notice in the Description page of Project Settings.


#include "COSelectActorAbility.h"

#include "CO/Actor/Player/COPlayerCharacter.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Core/AbilitySystem/COAbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "Templates/SharedPointer.h"
#include <CO/Core/AbilitySystem/COGameplayEffectContext.h>

bool UCOSelectActorAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return !TargetTags->HasAny(TargetBlockedTags) &&
		TargetTags->HasAny(TargetRequiredTags) &&
		TargetTags->Filter(FilterSelectionTags).IsValidIndex(0) &&
		!SourceTags->HasAny(SourceBlockedTags);
}

void UCOSelectActorAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	auto FilteredTags = TriggerEventData->TargetTags.Filter(FilterSelectionTags);
	auto PawnEffect = ActorSelectionMapping.Find(FilteredTags.GetByIndex(0));

	auto Context = new FCOGameplayEffectContext(ActorInfo->OwnerActor.Get(), ActorInfo->OwnerActor.Get());
	Context->SetTargetData(TriggerEventData->TargetData);
	auto EffectSpec = new FGameplayEffectSpec(PawnEffect->GetDefaultObject(), FGameplayEffectContextHandle(Context));

	_Target = TriggerEventData->Target.Get();
	_AppliedEffect = ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, FGameplayEffectSpecHandle(EffectSpec));
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

	ActorInfo->AbilitySystemComponent.Get()->RemoveActiveGameplayEffect(_AppliedEffect);

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UCOSelectActorAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
