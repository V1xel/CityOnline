// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "COGameplayAbilityBase.h"
#include "COAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class CO_API UCOAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<UCOGameplayAbilityBase>> Abilities{};

	void GiveAbility(UClass* Class);

	void CancelAbility(UClass* Class);
	
};
