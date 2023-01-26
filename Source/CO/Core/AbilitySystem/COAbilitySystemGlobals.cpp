// Fill out your copyright notice in the Description page of Project Settings.


#include "COAbilitySystemGlobals.h"
#include "COGameplayEffectContext.h"

FGameplayEffectContext* UCOAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FCOGameplayEffectContext();
}
