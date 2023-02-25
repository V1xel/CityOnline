// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "COGameplayAbilityBase.generated.h"

class ACOPlayerController;
class ACOPlayerCharacter;
struct FGameplayEffectSpecHandle;

using FGEDelegate = FGameplayEventTagMulticastDelegate::FDelegate;

/**
 * 
 */
UCLASS(abstract)
class CO_API UCOGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility, bool bWasCancelled) override;

	FDelegateHandle AddGETagDelegate(FGameplayTag Tag, FGEDelegate Delegate);

	FActiveGameplayEffectHandle ApplyGESpecToOwner(const FGameplayEffectSpecHandle SpecHandle);

	TArray<FActiveGameplayEffectHandle> ApplyGESpecToTarget(const FGameplayEffectSpecHandle SpecHandle, const FGameplayAbilityTargetDataHandle& TargetData);

	UAbilitySystemComponent* GetASC(AActor* Actor);

	void RemoveActiveGameplayEffect(FActiveGameplayEffectHandle Handle);

	void RemoveGETagDelegate(const FGameplayTag Tag, FDelegateHandle DelegateHandle);

	void SendServerGEToTarget(AActor* Target, FGameplayTag Tag, FGameplayEventData Payload);

	void EndAbilityArgsless();

	FGameplayAbilityTargetDataHandle GetTargetDataFromActiveEffect(const FGameplayEffectQuery& Query);
	static FGameplayAbilityTargetDataHandle GetTargetDataFromAbilitySystemActiveEffect(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectQuery& Query);
};
