// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "CO/Actor/Player/Abilities/DTO/COSelectionDTO.h"
#include "COSelectCellsAbilityTask.generated.h"

class UCOStreetCellComponent;
class ACOPlayerController;
class UCOBuildingDetails;
class UCOSelectionDTO;

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
	static UCOSelectCellsAbilityTask* HandleSelectionTillSelectionEnded(UGameplayAbility* OwningAbility, FName TaskInstanceName, ACOPlayerController* PlayerController, UCOBuildDTO* BuildDTO);
	
	virtual void ExternalConfirm(bool bEndTask) override;

	UCOSelectionDTO* GetSelectionResult() const { return _SelectionDTO; }

	void SetDrawDebugSelection(bool Value) { _DrawDebugSelection = Value; }

	void SetMousePositionAsFirstPoint();
protected:
	virtual void TickTask(float DeltaTime) override;

	virtual void OnDestroy(bool AbilityIsEnding) override;

	bool RaycastWithRectangle(FVector RectangleStart, FVector RectangleEnd,	TArray<FHitResult>& OutHits) const;

	void HandleActorComponentSelection(TArray<FHitResult>& HitResults);

	void CollectSelectionData();

	void ValidateSelectionData();

protected:
	UPROPERTY()
	FVector SelectionStartedLocation{};
	
	UPROPERTY()
	ACOPlayerController* _PlayerController{};
	
	UPROPERTY()
	TArray<UCOStreetCellComponent*> _SelectedCells{};

	UPROPERTY()
	UCOSelectionDTO* _SelectionDTO;

	UPROPERTY()
	UCOBuildDTO* _BuildDTO;

	UPROPERTY()
	bool _DrawDebugSelection;

	UPROPERTY()
	bool _TurnOffValidation;
};
