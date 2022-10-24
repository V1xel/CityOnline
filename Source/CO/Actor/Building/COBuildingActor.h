// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/COBuildingAttributeSet.h"
#include "CO/Actor/Interfaces/COSelectableActor.h"
#include "GameFramework/Actor.h"
#include "COBuildingActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConfigurationUpdatedDelegate);

class UCOAbilitySystemComponent;
class UCOConstructionDTO;
class UCOBuildingAsset;

UCLASS(Blueprintable)
class CO_API ACOBuildingActor : public AActor, public ICOSelectableActor
{
	GENERATED_BODY()

public:
	ACOBuildingActor();

	void ApplyChanges();

	void RemoveActor();

	void ComposeBuilding();

	virtual void SelectActor_Implementation() override;

	virtual void DeselectActor_Implementation() override;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCOAbilitySystemComponent* AbilitySystemComponent{};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCOBuildingAttributeSet* BuildingAttributeSet{};

	UPROPERTY()
	UCOBuildingAsset* BuildingAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	const UCOConstructionDTO* Configuration;

	int Floor;
private:
	bool IsSelected;

	bool IsEdited;

	UPROPERTY()
	FOnConfigurationUpdatedDelegate OnConfigurationUpdatedDelegate;
};
