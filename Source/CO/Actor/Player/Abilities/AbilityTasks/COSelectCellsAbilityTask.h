﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "CO/Actor/Building/COBuildingConfiguration.h"
#include "COSelectCellsAbilityTask.generated.h"

class UCOStreetCellComponent;
class ACOPlayerController;
class UCOBuildingDetails;

/**
 * 
 */
UCLASS()
class CO_API UCOSelectCellsAbilityTask : public UAbilityTask
{
	GENERATED_BODY()

	UCOSelectCellsAbilityTask();
public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UCOSelectCellsAbilityTask* HandleSelectionTillSelectionEnded(UGameplayAbility* OwningAbility, FName TaskInstanceName, ACOPlayerController* PlayerController,
	UCOBuildingDetails* BuildingDetails);
	
	virtual void ExternalConfirm(bool bEndTask) override;

	TArray<UCOStreetCellComponent*> GetSelectedCells() const { return TArray(_SelectedCells); }

	void SetDrawDebugSelection(bool Value) { _DrawDebugSelection = Value; }
protected:
	virtual void Activate() override;

	virtual void TickTask(float DeltaTime) override;

	virtual void OnDestroy(bool AbilityIsEnding) override;

	bool RaycastWithRectangle(FVector RectangleStart, FVector RectangleEnd,	TArray<FHitResult>& OutHits) const;

	void HandleActorComponentSelection(TArray<FHitResult>& HitResults);

protected:
	UPROPERTY()
	UCOBuildingDetails* _BuildingDetails{};

	UPROPERTY()
	FVector SelectionStartedLocation{};
	
	UPROPERTY()
	ACOPlayerController* _PlayerController{};
	
	UPROPERTY()
	TArray<UCOStreetCellComponent*> _SelectedCells{};

	UPROPERTY()
	bool _DrawDebugSelection;
};
