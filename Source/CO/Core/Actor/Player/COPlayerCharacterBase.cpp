// Fill out your copyright notice in the Description page of Project Settings.


#include "COPlayerCharacterBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CO/Core/AbilitySystem/COAbilitySystemComponent.h"

ACOPlayerCharacterBase::ACOPlayerCharacterBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCOAbilitySystemComponent>("AbilitySystem");
	AttributeSetBase = CreateDefaultSubobject<UCOPlayerAttributeSet>(TEXT("AttributeSetBase"));
}

void ACOPlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ACOPlayerCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->RefreshAbilityActorInfo();
}

UAbilitySystemComponent* ACOPlayerCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
