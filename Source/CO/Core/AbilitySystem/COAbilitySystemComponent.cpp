// Fill out your copyright notice in the Description page of Project Settings.


#include "COAbilitySystemComponent.h"

void UCOAbilitySystemComponent::GiveAbility(UClass* Class)
{
	if(Class)
	{
		const FGameplayAbilitySpec AbilitySpec{Class, 1};

		Super::GiveAbility(AbilitySpec);
	}
}
