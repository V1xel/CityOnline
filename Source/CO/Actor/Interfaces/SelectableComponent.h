﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectableComponent.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class USelectableComponent : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CO_API ISelectableComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UPARAM(DisplayName = "SelectComponent") void SelectComponent();
	virtual void SelectComponent_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UPARAM(DisplayName = "DeselectComponent") void DeselectComponent();
	virtual void DeselectComponent_Implementation();
public:
};
