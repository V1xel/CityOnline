// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "COAbilitySystemFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CO_API UCOAbilitySystemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable)
	static FGameplayEffectContextHandle GetEffectContextFromActiveGEHandle(UAbilitySystemComponent* AbilitySystem, FActiveGameplayEffectHandle Handle);

	UFUNCTION(BlueprintPure)
	static TArray<AActor*> GetEffectContextTargetActors(UAbilitySystemComponent* AbilitySystem, FActiveGameplayEffectHandle Effect);

	UFUNCTION(BlueprintPure)
	static AActor* GetTargetActorFromEffectByTag(UAbilitySystemComponent* AbilitySystem, FGameplayTag Tag);

	UFUNCTION(BlueprintPure)
	static TArray<AActor*> GetAllActorsFromEffectContext(FGameplayEffectContextHandle EffectHandle);
};
