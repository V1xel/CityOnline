// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include <GameplayTags.h>
#include "COEQT_GameplayTags.generated.h"


USTRUCT()
struct CO_API FAIDataProviderFNameValue : public FAIDataProviderTypedValue
{
	GENERATED_USTRUCT_BODY()

	FAIDataProviderFNameValue();

	UPROPERTY(EditAnywhere, Category = Value)
		FName DefaultValue;

	FName GetValue() const;
	virtual FString ValueToString() const override;

	bool Serialize(FArchive& Ar);
};

/**
 * 
 */
UCLASS()
class CO_API UCOEQT_GameplayTags : public UEnvQueryTest
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = Generator)
	FAIDataProviderFNameValue FilterByTag;

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

	virtual FText GetDescriptionTitle() const override;
	virtual FText GetDescriptionDetails() const override;
};
