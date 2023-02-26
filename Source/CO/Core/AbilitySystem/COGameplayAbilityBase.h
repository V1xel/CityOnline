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
	/// <summary>
	/// Subscribes on events that are broadcasted to ability owner
	/// </summary>
	/// <param name="Tag">Event name</param>
	/// <param name="Delegate">Action that is invoked on event</param>
	/// <returns></returns>
	FDelegateHandle AddGETagDelegate(FGameplayTag Tag, FGEDelegate Delegate);

	FActiveGameplayEffectHandle ApplyGEToOwner(TSubclassOf<UGameplayEffect> Effect);

	FActiveGameplayEffectHandle ApplyGESpecToOwner(const FGameplayEffectSpecHandle SpecHandle);

	TArray<FActiveGameplayEffectHandle> ApplyGESpecToTarget(const FGameplayEffectSpecHandle SpecHandle, const FGameplayAbilityTargetDataHandle& TargetData);

	UAbilitySystemComponent* GetASC(AActor* Actor);

	void RemoveActiveGameplayEffect(FActiveGameplayEffectHandle Handle);

	void RemoveGETagDelegate(const FGameplayTag Tag, FDelegateHandle DelegateHandle);

	void SendServerGEToTarget(AActor* Target, FGameplayTag Tag, FGameplayEventData Payload);

	bool CheckCostArgsless();

	bool CommitAbilityArgsless();

	void EndAbilityArgsless();

	FGameplayAbilityTargetDataHandle GetTargetDataFromActiveEffect(const FGameplayEffectQuery& Query);
	static FGameplayAbilityTargetDataHandle GetTargetDataFromAbilitySystemActiveEffect(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectQuery& Query);
};
