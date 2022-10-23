// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "COConstants.generated.h"

struct FGameplayTag;

/**
 * 
 */
UCLASS()
class CO_API UCOGameplayTags : public UObject
{
	GENERATED_BODY()
	

public:

	static FGameplayTag GetAllocate();

	static FGameplayTag GetAllocateCancel();

	static FGameplayTag GetAllocateFinished();

	static FGameplayTag GetConstruct();

	static FGameplayTag GetConstructCancel();

	static FGameplayTag GetConstructFinished();
};
