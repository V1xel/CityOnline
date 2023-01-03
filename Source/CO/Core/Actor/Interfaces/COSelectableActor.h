// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "COSelectableActor.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UCOSelectableActor : public UInterface
{
	GENERATED_BODY()
};

class CO_API ICOSelectableActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UPARAM(DisplayName = "SelectActor") void SelectActor();
	virtual void SelectActor_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UPARAM(DisplayName = "DeselectActor") void DeselectActor();
	virtual void DeselectActor_Implementation();
};
