// Fill out your copyright notice in the Description page of Project Settings.


#include "COCitizenAIController.h"
#include "Perception/AIPerceptionComponent.h"

ACOCitizenAIController::ACOCitizenAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComponent");
}
