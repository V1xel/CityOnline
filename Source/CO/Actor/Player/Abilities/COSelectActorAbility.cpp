// Fill out your copyright notice in the Description page of Project Settings.

#include "COSelectActorAbility.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemInterface.h"
#include "CO/Core/AbilitySystem/COAbilitySystemComponent.h"
#include "CO/Core/AbilitySystem/COGameplayEffectContext.h"
#include "CO/Core/AbilitySystem/COGameplayEffectContextHandle.h"

bool UCOSelectActorAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
    return !TargetTags->HasAny(TargetBlockedTags) &&        // Target is not blocked for selection
        TargetTags->HasAny(TargetRequiredTags) &&          // Target has type that is required for selection
        TargetTags->Filter(FilterActorTypeTags).IsValidIndex(0) &&  // Target has type that is added to Mapping
        !SourceTags->HasAny(SourceBlockedTags);            // Player does not have tags that block selection
}

void UCOSelectActorAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo,
    const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    auto SelectionContextHandle = FCOGameplayEffectContextHandle(ActorInfo->OwnerActor.Get());
    SelectionContextHandle.SetTargetData(TriggerEventData->TargetData);
  
    auto TargetActorType = TriggerEventData->TargetTags.Filter(FilterActorTypeTags).First();
    auto PlayerSelectedActorEffect = TargetTypeToPlayerSelectedActorOfTypeEffectMapping.Find(TargetActorType);
    //Adding player effect to be able to track player selection
    _PlayerEffect = ApplyGameplayEffectSpecToOwner(Handle, ActorInfo, ActivationInfo, SelectionContextHandle.MakeGESpec(*PlayerSelectedActorEffect));

    //Adding target effect for each target in TargetData for selection visualization
    _TargetEffect = ApplyGameplayEffectSpecToTarget(Handle, ActorInfo, ActivationInfo, SelectionContextHandle.MakeGESpec(TargetActorSelectedEffect), TriggerEventData->TargetData).Last();

    //Storing target to remove effects later
    _TargetDataHandle = TriggerEventData->TargetData;
}

void UCOSelectActorAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
    const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

    //Removing player effect
    RemoveActiveGameplayEffect(_PlayerEffect);
 
    auto SelectedActorAbilityInterface = GetASC(_TargetDataHandle.Get(0)->GetActors()[0].Get());
    //Removing target effects
    SelectedActorAbilityInterface->RemoveActiveGameplayEffect(_TargetEffect);

    _PlayerEffect.Invalidate();
    _TargetEffect.Invalidate();
    _TargetDataHandle.Clear();
}