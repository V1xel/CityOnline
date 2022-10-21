// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Actor/Player/COPlayerState.h"
#include "CO/AbilitySystem/COAbilitySystemComponent.h"

ACOPlayerState::ACOPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCOAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSetBase = CreateDefaultSubobject<UCOPlayerAttributeSet>(TEXT("AttributeSetBase"));
}

UAbilitySystemComponent* ACOPlayerState::GetAbilitySystemComponent() const
{
    return Cast<UAbilitySystemComponent>(AbilitySystemComponent);
}

UCOPlayerAttributeSet* ACOPlayerState::GetAttributeSetBase() const
{
    return AttributeSetBase;
}

int32 ACOPlayerState::GetMoney() const
{
    return AttributeSetBase->GetMoney();
}
