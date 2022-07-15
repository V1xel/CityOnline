// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "COPlayerController.generated.h"

class UCOSelectionComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectionFinishedDelegate, const TArray<UPrimitiveComponent*>&, AllocatedComponents);
/**
 * 
 */
UCLASS()
class CO_API ACOPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	ACOPlayerController();
	
	void StartSelection();

	void StopSelection();
	
	void SetComponentSelectionEnabled(bool Value);
	
	virtual void SetupInputComponent() override;

protected:
	UPROPERTY()
	UCOSelectionComponent* SelectionComponent;

	UPROPERTY(BlueprintAssignable)
	FOnSelectionFinishedDelegate OnSelectionFinished;
};
