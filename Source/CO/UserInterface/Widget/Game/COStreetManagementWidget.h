// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "COStreetManagementWidget.generated.h"

/**
 * 
 */
UCLASS()
class CO_API UCOStreetManagementWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
};
