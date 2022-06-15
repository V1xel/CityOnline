// Fill out your copyright notice in the Description page of Project Settings.


#include "COCharacterBase.h"

#include "AIController.h"
#include "AIController/COCharacterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ACOCharacterBase::ACOCharacterBase()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ACOCharacterBase::Select()
{
	IsSelected = true;
}

void ACOCharacterBase::Deselect()
{
	IsSelected = false;
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
