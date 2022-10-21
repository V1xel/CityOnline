// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/AbilitySystem/COAttributeSetBase.h"
#include "COPlayerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class CO_API UCOPlayerAttributeSet : public UCOAttributeSetBase
{
	GENERATED_BODY()

public:
	GENERATE_ATTRIBUTE_ACCESSORS(UCOPlayerAttributeSet, Money);

protected:
	UPROPERTY(BlueprintReadOnly)
		FGameplayAttributeData Money;
	
};
