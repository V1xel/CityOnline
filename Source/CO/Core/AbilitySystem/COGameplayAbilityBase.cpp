// Fill out your copyright notice in the Description page of Project Settings.


#include "COGameplayAbilityBase.h"
#include "CO/Actor/Player/COPlayerCharacter.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "COGameplayEffectContext.h"

void UCOGameplayAbilityBase::ActivateAbility(FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UCOGameplayAbilityBase::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

FGameplayAbilityTargetDataHandle UCOGameplayAbilityBase::GetTargetDataFromActiveEffect(const FGameplayEffectQuery& Query)
{
	auto ActorInfo = GetActorInfo();
	auto AllocatePermissionActiveEffects = ActorInfo.AbilitySystemComponent->GetActiveEffects(Query);
	FGameplayEffectContextHandle PermissionGrantedEffectContext = ActorInfo.AbilitySystemComponent->GetEffectContextFromActiveGEHandle(AllocatePermissionActiveEffects[0]);
	auto AllocatePermissionEffectContext = static_cast<FCOGameplayEffectContext*>(PermissionGrantedEffectContext.Get());

	return AllocatePermissionEffectContext->TargetData;
}
