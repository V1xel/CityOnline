// Fill out your copyright notice in the Description page of Project Settings.


#include "COAbilitySystemComponent.h"

#include "CO/Actor/Player/Abilities/COSelectCellsAbility.h"

void UCOAbilitySystemComponent::GiveAbility(UClass* Class)
{
	const FGameplayAbilitySpec AbilitySpec{Class, 1};
	
	Super::GiveAbility(AbilitySpec);
}

void UCOAbilitySystemComponent::CancelAbility(UClass* Class)
{
	const auto Ability = Cast<UCOSelectCellsAbility>(Class->GetDefaultObject());

	Super::CancelAbility(Ability);
}
