﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "COCharacterBase.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CO/Core/AbilitySystem/COAbilitySystemComponent.h"

ACOCharacterBase::ACOCharacterBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCOAbilitySystemComponent>("AbilitySystem");
	AttributeSetBase = CreateDefaultSubobject<UCOPlayerAttributeSet>(TEXT("AttributeSetBase"));
}

void ACOCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACOCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

}

UAbilitySystemComponent* ACOCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
