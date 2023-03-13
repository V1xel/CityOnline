// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NavModifierComponent.h"
#include "CONavModifierComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Navigation), meta = (BlueprintSpawnableComponent), hidecategories = (Activation))
class CO_API UCONavModifierComponent : public UNavModifierComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		FVector NavExtent;

	virtual void GetNavigationData(FNavigationRelevantData& Data) const override;
};
