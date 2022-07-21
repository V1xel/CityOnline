// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/COActorComponentBase.h"
#include "COActorSelectionComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CO_API UCOActorSelectionComponent : public UCOActorComponentBase
{
	GENERATED_BODY()

public:
	void TrySelectUnderCursor();
	
	void HandleActorSelection(FHitResult HitResult);

	template <typename T>
	T* GetSelectedActor() const
	{
		return Cast<T>(SelectedActor);
	}
	
protected:
	UPROPERTY()
	AActor* SelectedActor;
};
