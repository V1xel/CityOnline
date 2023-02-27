// Fill out your copyright notice in the Description page of Project Settings.

#include "COPlayerCharacter.h"

void ACOPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		// Attribute change callbacks
		MoneyChangedDelegateHandle = GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMoneyAttribute()).AddUObject(this, &ACOPlayerCharacter::MoneyChanged);
	}
}

void ACOPlayerCharacter::MoneyChanged(const FOnAttributeChangeData& Data)
{
	auto Payload = FGameplayEventData();
	Payload.EventMagnitude = Data.NewValue;
	GetAbilitySystemComponent()->HandleGameplayEvent(PlayerStateUpdated, &Payload);
}