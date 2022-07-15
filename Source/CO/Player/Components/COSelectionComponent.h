// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COSelectionComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CO_API UCOSelectionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCOSelectionComponent();

	void StartSelection();
	
	void SetComponentSelectionEnabled(bool Value);

	void StopSelection();
	
	void HandleActorSelection(FHitResult HitResult);
	
	void HandleActorComponentSelection(TArray<FHitResult>& HitResults);

	bool RaycastWithRectangle(FVector RectangleStart, FVector RectangleEnd, TArray<FHitResult>& OutHits);
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	bool IsSelectionWithRectangleEnabled = true;

	bool IsSelectingWithRectangle;

	FVector SelectionStartedLocation;

	UPROPERTY()
	AActor* SelectedActor;

public:
	UPROPERTY()
	TArray<UPrimitiveComponent*> SelectedComponents{};
};
