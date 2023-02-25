// Fill out your copyright notice in the Description page of Project Settings.


#include "COGameplayEffectContextHandle.h"
#include "GameplayEffect.h"

FGameplayEffectSpecHandle FCOGameplayEffectContextHandle::MakeGESpec(TSubclassOf<UGameplayEffect> Effect)
{
	return FGameplayEffectSpecHandle(new FGameplayEffectSpec(Effect.GetDefaultObject(), *this));
}

void FCOGameplayEffectContextHandle::SetTargetData(FGameplayAbilityTargetDataHandle Handle)
{
	auto Context = static_cast<FCOGameplayEffectContext*>(Get());

	Context->SetTargetData(Handle);
}
