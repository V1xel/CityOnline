// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "COEnvQueryTest_Visited.generated.h"

UCLASS()
class CO_API UCOEnvQueryTest_Visited : public UEnvQueryTest
{
	GENERATED_BODY()

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

	virtual FText GetDescriptionDetails() const override;

	virtual FText GetDescriptionTitle() const override;
};
