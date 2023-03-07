// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagExtension.generated.h"

struct FGameplayTag;
struct FGameplayTagContainer;

/**
 * 
 */
UCLASS()
class CO_API UGameplayTagExtension : public UObject
{
	GENERATED_BODY()

public:

	static FString GetTagFirstElement(FGameplayTag Tag);

	static FString GetTagSecondElement(FGameplayTag Tag);

	static FString GetTagThirdElement(FGameplayTag Tag);

	static bool MatchesTag(FGameplayTag Tag, FString Element);

	static bool MatchesTagExact(FGameplayTag Tag, FString Element);

	static FGameplayTagContainer CreateContainer(FString Tag);

	UFUNCTION(BlueprintPure)
	static FGameplayTagContainer CreateContainer(FName Tag);
};
