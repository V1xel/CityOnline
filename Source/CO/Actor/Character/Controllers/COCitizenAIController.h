// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionListenerInterface.h"
#include "COCitizenAIController.generated.h"

/**
 * 
 */
UCLASS()
class CO_API ACOCitizenAIController : public AAIController
{
	GENERATED_BODY()
	


public:
	ACOCitizenAIController();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UAIPerceptionComponent* AIPerceptionComponent;

	virtual UAIPerceptionComponent* GetPerceptionComponent() override { return AIPerceptionComponent; }
};
