﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "COGameplayAbilityBase.generated.h"

class ACOPlayerController;
class ACOPlayerCharacter;

/**
 * 
 */
UCLASS(abstract)
class CO_API UCOGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	ACOPlayerController* GetController(const FGameplayAbilityActorInfo* ActorInfo);
	
	ACOPlayerCharacter* GetOwnerActor(const FGameplayAbilityActorInfo* ActorInfo);
	
	template <typename T>
	T* GetOptionalParameter(const FGameplayEventData* TriggerEventData)
	{
		return Cast<T>(TriggerEventData->OptionalObject);
	}

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag TriggerTag;
};
