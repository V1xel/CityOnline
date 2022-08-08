// Fill out your copyright notice in the Description page of Project Settings.


#include "COCharacterBase.h"

#include "AIController.h"
#include "CO/Actor/AI/COAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CO/AbilitySystem/COAbilitySystemComponent.h"

ACOCharacterBase::ACOCharacterBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCOAbilitySystemComponent>("AbilitySystem");
}

void ACOCharacterBase::MoveTo(FVector DestinationPoint)
{
	auto AIController = Cast<ACOAIController>(GetController());
	if(AIController)
	{
		auto Blackboard = AIController->GetBlackboardComponent();
		if(Blackboard)
		{
			AIController->GetBlackboardComponent()->SetValueAsVector("DestinationPoint", DestinationPoint);
		}
	}
}

void ACOCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ACOCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->RefreshAbilityActorInfo();
}

UAbilitySystemComponent* ACOCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
