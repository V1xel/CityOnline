// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Core/AbilitySystem/COGameplayAbilityBase.h"
#include "COPlayerController.generated.h"

UCLASS()
class CO_API ACOPlayerController : public APlayerController
{
	GENERATED_BODY()

	ACOPlayerController();

public:
	const AActor* GetSelectedActor() { return _selectedActor; }

	virtual void OnPossess(APawn* aPawn) override;

	virtual void OnUnPossess() override;

	void OnActorSelected(FGameplayTag Tag, const FGameplayEventData* EventData);

public:
	UPROPERTY(EditAnywhere)
	FGameplayTag ListenActorSelectedTag;

private:
	UPROPERTY()
	const AActor* _selectedActor;

	FDelegateHandle _actorSelectedHandle;
};
