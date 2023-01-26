// Fill out your copyright notice in the Description page of Project Settings.


#include "COGameplayEffectContext.h"

void FCOGameplayEffectContext::AddBuildDTO(UCOBuildDTO* InBuildDTO)
{
    BuildDTO = InBuildDTO->ToStruct();
}

bool FCOGameplayEffectContext::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
    BuildDTO.NetSerialize(Ar, Map, bOutSuccess);

    bOutSuccess = true;
    return true;
}
