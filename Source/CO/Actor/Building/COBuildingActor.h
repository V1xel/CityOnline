// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Attributes/COBuildingAttributeSet.h"
#include "GameFramework/Actor.h"
#include "COBuildingActor.generated.h"

class UCOBuildingPartComponent;
class UCOConstructionDTO;
class UCOBuildingAsset;

UCLASS(Blueprintable)
class CO_API ACOBuildingActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACOBuildingActor();

	virtual void BeginPlay() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override 
	{
		return AbilitySystemComponent;
	}

	void ComposeBuilding(int32 Floors, UCOBuildingAsset* BuildingAsset, FVector Direction);
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<UCOBuildingPartComponent> BuildingPartComponentClass;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UAbilitySystemComponent* AbilitySystemComponent {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCOBuildingAttributeSet* BuildingAttributeSet{};

	UPROPERTY()
	TArray<UCOBuildingPartComponent*> Meshes;

};
