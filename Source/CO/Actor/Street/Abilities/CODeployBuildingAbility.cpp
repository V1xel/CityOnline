// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Actor/Street/Abilities/CODeployBuildingAbility.h"
#include "AbilitySystemComponent.h"

void UCODeployBuildingAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	auto DeployBuildingActiveEffects = ActorInfo->AbilitySystemComponent->GetActiveEffects(FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(FilterDeployBuildingTag.GetSingleTagContainer()));
	if (DeployBuildingActiveEffects.Num() > 0) {
		FGameplayEffectContextHandle DeployBuildingEffectContext = ActorInfo->AbilitySystemComponent->GetEffectContextFromActiveGEHandle(DeployBuildingActiveEffects[0]);
		DeployBuildingEffectContext.GetSourceObject();
	}
}

void UCODeployBuildingAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
