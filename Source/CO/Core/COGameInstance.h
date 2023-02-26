// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "COGameInstance.generated.h"

class UCORootAsset;

/**
 * 
 */
UCLASS()
class CO_API UCOGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
};
