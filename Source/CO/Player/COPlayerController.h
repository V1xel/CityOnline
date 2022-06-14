// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/Interfaces/SelectableActor.h"
#include "GameFramework/PlayerController.h"
#include "COPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CO_API ACOPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	ACOPlayerController();

	virtual void SetupInputComponent() override;
	
	void Select();
	void SetMoveDestination();

protected:
	ISelectableActor* Selected;
	
};
