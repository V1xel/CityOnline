// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/COBuildingAttributeSet.h"
#include "GameFramework/Actor.h"
#include "COBuildingActor.generated.h"

class UCOAbilitySystemComponent;
class UCOConstructionDTO;
class UCOBuildingAsset;

UCLASS(Blueprintable)
class CO_API ACOBuildingActor : public AActor
{
	GENERATED_BODY()

public:
	ACOBuildingActor();

	void ApplyChanges();

	void RemoveActor();

	UFUNCTION()
	void ComposeBuilding();
	
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

	int Floor;
private:

	TArray<UStaticMeshComponent*> Meshes{};
	bool IsSelected;

	bool IsEdited;
};
