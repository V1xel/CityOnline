// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainerExtension.generated.h"

struct FGameplayTagContainer;
struct FGameplayTag;

/**
 * 
 */
UCLASS()
class CO_API UGameplayTagContainerExtension : public UObject
{
	GENERATED_BODY()

public:

	static FString GetTagFirstElement(FGameplayTag Tag);

	static FString GetTagSecondElement(FGameplayTag Tag);

	static FString GetTagThirdElement(FGameplayTag Tag);
};
