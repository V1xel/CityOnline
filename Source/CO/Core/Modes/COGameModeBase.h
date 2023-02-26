// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "COGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CO_API ACOGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	ACOGameModeBase();

public: 
	//UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = Classes)
	//TSubclassOf<APlayerState> PlayerStateClass;
};
