// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/AbilitySystem/COAttributeSetBase.h"
#include "COSelectionAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class CO_API UCOSelectionAttributeSet : public UCOAttributeSetBase
{
	GENERATED_BODY()

public:
	GENERATE_ATTRIBUTE_ACCESSORS(UCOSelectionAttributeSet, SelectedActor);

protected:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData SelectedActor{};

	friend class UCOSetSelectedActorEffect;
};
