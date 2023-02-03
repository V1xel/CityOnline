// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/HitResult.h"
#include "CO/Core/AbilitySystem/COGameplayAbilityBase.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "COPlayerController.generated.h"

class UCORootAsset;

UCLASS()
class CO_API ACOPlayerController : public APlayerController
{
	GENERATED_BODY()

	ACOPlayerController();

public:
	UPROPERTY(EditAnywhere)
	UCORootAsset* RootAsset;

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SendServerGameplayEventToPawn(FGameplayTag Tag, FGameplayEventData Payload);

	void SendServerGameplayEventToPawn_Implementation(FGameplayTag Tag, FGameplayEventData Payload);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SendServerGameplayEventToListener(AActor* Listener, FGameplayTag Tag, FGameplayEventData Payload);

	void SendServerGameplayEventToListener_Implementation(AActor* Listener, FGameplayTag Tag, FGameplayEventData Payload);
};
