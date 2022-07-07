// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectableActor.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class USelectableActor : public UInterface
{
	GENERATED_BODY()
};

class CO_API ISelectableActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UPARAM(DisplayName = "Select") void Select();
	virtual void Select_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UPARAM(DisplayName = "Deselect") void Deselect();
	virtual void Deselect_Implementation();
};
