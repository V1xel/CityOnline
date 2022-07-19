// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CO/Utilities/COComponentHelper.h"
#include "COGameplayAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class CO_API UCOGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	template <typename T>
	T* GetOwnerComponent(const TSubclassOf<UActorComponent> Class) const
	{
		T* Component = Cast<T>(OwnerActor->GetComponentByClass(Class));

		return COAssertionChecker::CheckReferenceNotNull(Component, FString::Printf(TEXT("Null reference: %s"), *Class->ClassConfigName.ToString()));
	}

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
											const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
											const FGameplayEventData* TriggerEventData) override;

protected:
	TWeakObjectPtr<AActor> OwnerActor;
};
