﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Attributes/COBuildingAttributeSet.h"
#include "GameFramework/Actor.h"
#include "COBuildingActor.generated.h"

class UCOAbilitySystemComponent;
class UCOBuildingPartComponent;
class UCOConstructionDTO;
class UCOBuildingAsset;

UCLASS(Blueprintable)
class CO_API ACOBuildingActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	void ComposeBuilding();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCOAbilitySystemComponent* AbilitySystemComponent{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCOBuildingAttributeSet* BuildingAttributeSet{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCOBuildingAsset* BuildingAsset {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCOConstructionDTO> OverrideConfiguration {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	const UCOConstructionDTO* Configuration{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCOBuildingPartComponent> BuildingPartComponentClass;

	int Floor;
private:

	TArray<UCOBuildingPartComponent*> Meshes{};
	bool IsSelected;

	bool IsEdited;
};
