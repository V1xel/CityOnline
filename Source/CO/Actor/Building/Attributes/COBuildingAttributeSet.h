// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/AbilitySystem/COAttributeSetBase.h"
#include "COBuildingAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class CO_API UCOBuildingAttributeSet : public UCOAttributeSetBase
{
	GENERATED_BODY()

public:
	GENERATE_ATTRIBUTE_ACCESSORS(UCOBuildingAttributeSet, Type);
	GENERATE_ATTRIBUTE_ACCESSORS(UCOBuildingAttributeSet, MinWidth);
	GENERATE_ATTRIBUTE_ACCESSORS(UCOBuildingAttributeSet, MaxWidth);
	GENERATE_ATTRIBUTE_ACCESSORS(UCOBuildingAttributeSet, MinLength);
	GENERATE_ATTRIBUTE_ACCESSORS(UCOBuildingAttributeSet, MaxLength);
	GENERATE_ATTRIBUTE_ACCESSORS(UCOBuildingAttributeSet, MaxFloors);
	
protected:
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Type;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MinWidth;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxWidth;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MinLength;
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxLength;

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData MaxFloors;
};
