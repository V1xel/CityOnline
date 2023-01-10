// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Core/AbilitySystem/COGameplayAbilityBase.h"
#include "COSelectActorAbility.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CO_API UCOSelectActorAbility : public UCOGameplayAbilityBase
{
	GENERATED_BODY()

protected:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
		OUT FGameplayTagContainer* OptionalRelevantTags) const;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							 const FGameplayAbilityActivationInfo ActivationInfo,
							 const FGameplayEventData* TriggerEventData) override;

	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
							const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
							bool bWasCancelled) override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> ActorSelectedEffect;

	UPROPERTY(EditAnywhere)
	FGameplayTag BroadcastedEventOnSelect;
private:
	TArray<FActiveGameplayEffectHandle> _AppliedEffects;

	UPROPERTY()
	const AActor* _Target;
};
