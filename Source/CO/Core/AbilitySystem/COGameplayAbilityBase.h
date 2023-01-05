// Fill out your copyright notice in the Description page of Project Settings.

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
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	ACOPlayerController* GetPlayerController() const;
	
	ACOPlayerCharacter* GetOwnerActor(const FGameplayAbilityActorInfo* ActorInfo) const;
	
	template <typename T>
	T* GetOptionalParameter(const FGameplayEventData* TriggerEventData)
	{
		return Cast<T>(TriggerEventData->OptionalObject);
	}

protected:
	FGameplayAbilitySpecHandle _Handle;
	const FGameplayAbilityActorInfo* _ActorInfo;
	FGameplayAbilityActivationInfo _ActivationInfo;
};
