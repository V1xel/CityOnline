// Fill out your copyright notice in the Description page of Project Settings.


#include "COAbilitySystemFunctionLibrary.h"
#include "COAbilitySystemComponent.h"
#include "COGameplayEffectContext.h"
#include <AbilitySystemBlueprintLibrary.h>
#include "COGameplayAbilityBase.h"

FGameplayEffectContextHandle UCOAbilitySystemFunctionLibrary::GetEffectContextFromActiveGEHandle(UAbilitySystemComponent* AbilitySystem, FActiveGameplayEffectHandle Handle)
{
	return AbilitySystem->GetEffectContextFromActiveGEHandle(Handle);
}

FGameplayAbilityTargetDataHandle UCOAbilitySystemFunctionLibrary::GetTargetDataHandleFromActiveEffect(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag EffectTag)
{
	return UCOGameplayAbilityBase::GetTargetDataFromAbilitySystemActiveEffect(AbilitySystemComponent,
		FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(EffectTag.GetSingleTagContainer()));
}

TArray<AActor*> UCOAbilitySystemFunctionLibrary::GetEffectContextTargetActors(UAbilitySystemComponent* AbilitySystem, FActiveGameplayEffectHandle Effect)
{
	auto GEHandle = UCOAbilitySystemFunctionLibrary::GetEffectContextFromActiveGEHandle(AbilitySystem, Effect);
	auto Context = static_cast<FCOGameplayEffectContext*>(GEHandle.Get());

	return UAbilitySystemBlueprintLibrary::GetAllActorsFromTargetData(Context->TargetData);
}

AActor* UCOAbilitySystemFunctionLibrary::GetTargetActorFromEffectByTag(UAbilitySystemComponent* AbilitySystem, FGameplayTag Tag)
{
	auto Effects = AbilitySystem->GetActiveEffects(FGameplayEffectQuery::MakeQuery_MatchAllEffectTags(Tag.GetSingleTagContainer()));
	if (Effects.Num() == 0)
		return nullptr;

	auto Targets = UCOAbilitySystemFunctionLibrary::GetEffectContextTargetActors(AbilitySystem, Effects[0]);
	if (Targets.Num() == 0)
		return nullptr;

	return Targets[0];
}
