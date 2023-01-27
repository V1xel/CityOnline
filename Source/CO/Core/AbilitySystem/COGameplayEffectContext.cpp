// Fill out your copyright notice in the Description page of Project Settings.


#include "COGameplayEffectContext.h"

void FCOGameplayEffectContext::SetTargetData(FGameplayAbilityTargetDataHandle InTargetData)
{
    TargetData.Clear();
    TargetData = InTargetData;
}

bool FCOGameplayEffectContext::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Super::NetSerialize(Ar, Map, bOutSuccess);
    TargetData.NetSerialize(Ar, Map, bOutSuccess);
    bOutSuccess = true;
    return true;
}
