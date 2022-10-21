// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "Attributes/COPlayerAttributeSet.h"
#include "COPlayerState.generated.h"

class UCOAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class CO_API ACOPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()


public:
	ACOPlayerState();

	class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	class UCOPlayerAttributeSet* GetAttributeSetBase() const;
	
public:
	UFUNCTION(BlueprintCallable)
	int32 GetMoney() const;

protected:
	UPROPERTY()
	class UCOAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class UCOPlayerAttributeSet* AttributeSetBase;

};
