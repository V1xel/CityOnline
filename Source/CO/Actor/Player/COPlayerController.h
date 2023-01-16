// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/HitResult.h"
#include "CO/Core/AbilitySystem/COGameplayAbilityBase.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "COPlayerController.generated.h"

UCLASS()
class CO_API ACOPlayerController : public APlayerController
{
	GENERATED_BODY()

	ACOPlayerController();

public:
	UFUNCTION(BlueprintCallable)
	void SendGameplayEventToPawn(FGameplayTag Tag, FGameplayEventData Payload, bool SendToServer);

	UFUNCTION(BlueprintCallable)
	void SendGameplayEventToListener(AActor* Listener, FGameplayTag Tag, FGameplayEventData Payload, bool SendToServer);

	UFUNCTION(Server, Reliable)
	void SendServerGameplayEventToPawn(FGameplayTag Tag, FGameplayEventData Payload);

	void SendServerGameplayEventToPawn_Implementation(FGameplayTag Tag, FGameplayEventData Payload);

	UFUNCTION(Server, Reliable)
	void SendServerGameplayEventToListener(AActor* Listener, FGameplayTag Tag, FGameplayEventData Payload);

	void SendServerGameplayEventToListener_Implementation(AActor* Listener, FGameplayTag Tag, FGameplayEventData Payload);
};
