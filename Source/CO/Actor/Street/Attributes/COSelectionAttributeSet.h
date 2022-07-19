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
	GENERATE_ATTRIBUTE_ACCESSORS(UCOSelectionAttributeSet, SelectedCellsCount);

protected:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData SelectedCellsCount{};

	friend class UCOSetSelectionAttributes;
};
