// Fill out your copyright notice in the Description page of Project Settings.


#include "COCharacterBase.h"

#include "AIController.h"
#include "AIController/COCharacterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

ACOCharacterBase::ACOCharacterBase()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCOAbilitySystemComponent>(TEXT("AbilitySystem"));
}

void ACOCharacterBase::MoveTo(FVector DestinationPoint)
{
	auto AIController = Cast<ACOCharacterAIController>(GetController());
	if(AIController)
	{
		auto Blackboard = AIController->GetBlackboardComponent();
		if(Blackboard)
		{
			AIController->GetBlackboardComponent()->SetValueAsVector("DestinationPoint", DestinationPoint);
		}
	}
}

void ACOCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
