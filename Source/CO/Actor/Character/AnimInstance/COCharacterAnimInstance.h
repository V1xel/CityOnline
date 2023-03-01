// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "COCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CO_API UCOCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsMoving;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsRunning;
};
