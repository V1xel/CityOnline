// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COBuildingConfiguration.h"
#include "CO/Actor/Interfaces/SelectableActor.h"
#include "GameFramework/Actor.h"
#include "COBuildingActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfigurationUpdatedDelegate, FCOBuildingConfiguration, Configuration);

UCLASS(Blueprintable)
class CO_API ACOBuildingActor : public AActor, public ISelectableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACOBuildingActor();

	void UpdateConfiguration(FCOBuildingConfiguration _Configuration);

	void ApplyChanges();

	void RemoveActor();

	virtual void SelectActor_Implementation() override;

	virtual void DeselectActor_Implementation() override;
private:
	bool IsSelected;

	bool IsEdited;

	FCOBuildingConfiguration Configuration;

	UPROPERTY()
	FOnConfigurationUpdatedDelegate OnConfigurationUpdatedDelegate;
};
