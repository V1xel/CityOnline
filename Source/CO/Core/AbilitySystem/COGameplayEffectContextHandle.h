// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "COGameplayEffectContext.h"
#include "COGameplayEffectContextHandle.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CO_API FCOGameplayEffectContextHandle : public FGameplayEffectContextHandle
{
	GENERATED_USTRUCT_BODY()

	FCOGameplayEffectContextHandle() : FGameplayEffectContextHandle()
	{
	}

	virtual ~FCOGameplayEffectContextHandle()
	{
	}
	/** Constructs from an existing context, should be allocated by new */
	explicit FCOGameplayEffectContextHandle(AActor* Instigator) : FGameplayEffectContextHandle(new FCOGameplayEffectContext(Instigator))
	{
	}

	/** Constructs from an existing context, should be allocated by new */
	explicit FCOGameplayEffectContextHandle(AActor* Instigator, FGameplayAbilityTargetDataHandle Handle) : FGameplayEffectContextHandle(new FCOGameplayEffectContext(Instigator))
	{
		SetTargetData(Handle);
	}

	FGameplayEffectSpecHandle MakeGESpec(TSubclassOf<UGameplayEffect> Effect);

	void SetTargetData(FGameplayAbilityTargetDataHandle Handle);
};
