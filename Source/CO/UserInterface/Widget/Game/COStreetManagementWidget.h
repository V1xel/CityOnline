// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "COStreetManagementWidget.generated.h"

class ACOStreetActor;

/**
 * 
 */
UCLASS()
class CO_API UCOStreetManagementWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void GetStreetInformation(ACOStreetActor* Street);
	
	UFUNCTION(BlueprintCallable)
	void Build();
	
protected:
	virtual void NativeConstruct() override;
};
