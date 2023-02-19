// Fill out your copyright notice in the Description page of Project Settings.


#include "COAbilitySystemFunctionLibrary.h"
#include "COAbilitySystemComponent.h"

FGameplayEffectContextHandle UCOAbilitySystemFunctionLibrary::GetEffectContextFromActiveGEHandle(UAbilitySystemComponent* AbilitySystem, FActiveGameplayEffectHandle Handle)
{
	return AbilitySystem->GetEffectContextFromActiveGEHandle(Handle);
}