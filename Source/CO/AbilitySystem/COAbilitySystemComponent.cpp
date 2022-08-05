// Fill out your copyright notice in the Description page of Project Settings.


#include "COAbilitySystemComponent.h"

#include "CO/Actor/Player/Abilities/COSelectCellsAbility.h"

void UCOAbilitySystemComponent::GiveAbility(UClass* Class)
{
	if(Class)
	{
		const FGameplayAbilitySpec AbilitySpec{Class, 1};

		Super::GiveAbility(AbilitySpec);
	}
}

void UCOAbilitySystemComponent::CancelAbility(const UClass* Class)
{
	const auto Ability = CastChecked<UCOSelectCellsAbility>(Class->GetDefaultObject(), ECastCheckedType::NullChecked);

	Super::CancelAbility(Ability);
}
