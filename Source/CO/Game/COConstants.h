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

	static FGameplayTag Allocate();

	static FGameplayTag AllocateCancel();

	static FGameplayTag AllocateFinished();

	static FGameplayTag Construct();

	static FGameplayTag ConstructCancel();

	static FGameplayTag ConstructFinished();
};
