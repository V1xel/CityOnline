// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/Interfaces/SelectableActor.h"
#include "GameFramework/Character.h"
#include "COCharacterBase.generated.h"

UCLASS()
class CO_API ACOCharacterBase : public ACharacter, public ISelectableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACOCharacterBase();
	
	virtual void Select() override;

	virtual void Deselect() override;

private:
	bool IsSelected;
};
