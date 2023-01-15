// Fill out your copyright notice in the Description page of Project Settings.


#include "COGameInstance.h"
#include <AbilitySystemGlobals.h>

void UCOGameInstance::Init()
{
	UAbilitySystemGlobals::Get().InitGlobalData();
}
