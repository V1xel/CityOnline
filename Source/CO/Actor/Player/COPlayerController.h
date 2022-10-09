// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COPlayerController.generated.h"

class ACOStreetActor;
class ACOBuildingActor;
struct FGameplayTag;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStreetSelectedDelegate, const ACOStreetActor*, Street);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingSelectedDelegate, const ACOBuildingActor*, Building);

UCLASS()
class CO_API ACOPlayerController : public APlayerController
{
	GENERATED_BODY()

	ACOPlayerController();

public:
	AActor* GetSelectedActor() { return SelectedActor; }

	UFUNCTION(BlueprintCallable)
	ACOStreetActor* TryGetSelectedStreet();

	UFUNCTION(BlueprintCallable)
	ACOBuildingActor* TryGetSelectedBuilding();

	void SetSelectedActor(AActor* Value);;

public:
	UPROPERTY(BlueprintAssignable)
		FOnStreetSelectedDelegate OnStreetSelected {};

	UPROPERTY(BlueprintAssignable)
		FOnBuildingSelectedDelegate OnBuildingSelected {};

	UFUNCTION(BlueprintPure, BlueprintCallable)
	static FGameplayTag GetTagFromString(FString TagName);

private:
	UPROPERTY()
		AActor* SelectedActor;


};
