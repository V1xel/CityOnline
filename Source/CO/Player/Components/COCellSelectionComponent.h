// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/COActorComponentBase.h"
#include "COCellSelectionComponent.generated.h"

class UCOStreetCellComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectionEndedDelegate, const TArray<UCOStreetCellComponent*>&, AllocatedComponents);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CO_API UCOCellSelectionComponent : public UCOActorComponentBase
{
	GENERATED_BODY()

public:
	UCOCellSelectionComponent();

	void EnableSelection(bool Value = true);
	
	void StartSelection();

	void EndSelection();

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool RaycastWithRectangle(FVector RectangleStart, FVector RectangleEnd,	TArray<FHitResult>& OutHits) const;

	void HandleActorComponentSelection(TArray<FHitResult>& HitResults);

public:
	UPROPERTY(BlueprintAssignable)
	FOnSelectionEndedDelegate OnSelectionEnded;
	
protected:
	bool IsEnabled{};
	
	bool IsSelecting{};
	
	FVector SelectionStartedLocation{};
	
	UPROPERTY()
	TArray<UCOStreetCellComponent*> SelectedCells{};
};
