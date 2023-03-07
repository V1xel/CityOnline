// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include <GameplayTags.h>
#include "COEQIBlueprintWrapper.generated.h"

/**
 * 
 */
UCLASS()
class CO_API UCOEQIBlueprintWrapper : public UEnvQueryInstanceBlueprintWrapper
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure = false, Category = "AI|EQS")
	bool GetQueryResultsAsFilteredActors(TArray<AActor*>& ResultActors, FGameplayTagContainer AllTagsToFilter) const;
};
