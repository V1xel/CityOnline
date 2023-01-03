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
	static FGameplayTag Select();

	static FGameplayTag Build();

	static FGameplayTag BuildCancel();

	static FGameplayTag BuildFinished();

	static FGameplayTag Allocate();

	static FGameplayTag AllocateCancel();

	static FGameplayTag AllocateFinished();

	static FGameplayTag UpdatedAllocation();

	static FGameplayTag UpdatedConfiguration();

	static FGameplayTag Construct();

	static FGameplayTag ConstructCancel();

	static FGameplayTag ConstructConfigurate();

	static FGameplayTag ConstructFinished();

	static FGameplayTag ActorSelected();

	static FGameplayTag ActorDeselected();
};
