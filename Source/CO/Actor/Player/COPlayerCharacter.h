// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Core/Actor/Player/COPlayerCharacterBase.h"
#include "COPlayerCharacter.generated.h"

UCLASS()
class CO_API ACOPlayerCharacter : public ACOPlayerCharacterBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	void MoneyChanged(const FOnAttributeChangeData& Data);

	UPROPERTY(EditAnywhere)
	FGameplayTag PlayerStateUpdated;

	FDelegateHandle MoneyChangedDelegateHandle;
};