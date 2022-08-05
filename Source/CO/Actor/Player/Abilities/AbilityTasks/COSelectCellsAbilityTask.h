// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "CO/Actor/Building/COBuildingConfiguration.h"
#include "COSelectCellsAbilityTask.generated.h"

class UCOStreetCellComponent;
class ACOPlayerController;

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
	FCOBuildingConfiguration Configuration);
	
	virtual void ExternalConfirm(bool bEndTask) override;

	TArray<UCOStreetCellComponent*> GetSelectedCells() const { return TArray(SelectedCells); }
protected:
	virtual void Activate() override;

	virtual void TickTask(float DeltaTime) override;

	virtual void OnDestroy(bool AbilityIsEnding) override;

	bool RaycastWithRectangle(FVector RectangleStart, FVector RectangleEnd,	TArray<FHitResult>& OutHits) const;

	void HandleActorComponentSelection(TArray<FHitResult>& HitResults);

protected:
	FCOBuildingConfiguration Configuration{};
	
	FVector SelectionStartedLocation{};
	
	UPROPERTY()
	ACOPlayerController* PlayerController{};
	
	UPROPERTY()
	TArray<UCOStreetCellComponent*> SelectedCells{};
};
