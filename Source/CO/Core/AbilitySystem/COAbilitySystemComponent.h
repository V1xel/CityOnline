// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "COAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class CO_API UCOAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void CancelAbility(const UClass* Class);
	
	void GiveAbility(UClass* Class);
};
