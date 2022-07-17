// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "COPlayerControllerBase.generated.h"

class UCOActorSelectionComponent;
class UCOCellSelectionComponent;

UCLASS()
class CO_API ACOPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

protected:
	ACOPlayerControllerBase();
	
	void StartSelection();

	void StopSelection();

	virtual void SetupInputComponent() override;

protected:
	UPROPERTY()
	UCOActorSelectionComponent* ActorSelection;
	
	UPROPERTY()
	UCOCellSelectionComponent* CellSelection;


};
