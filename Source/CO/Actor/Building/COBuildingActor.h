// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Attributes/COBuildingAttributeSet.h"
#include "GameFramework/Actor.h"
#include "GameplayTagAssetInterface.h"
#include "COBuildingActor.generated.h"

class UCOBuildingPartComponent;
class UCOConstructionDTO;
class UCOBuildingAsset;

UCLASS(Abstract, Blueprintable)
class CO_API ACOBuildingActor : public AActor, public IAbilitySystemInterface, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	ACOBuildingActor();

	virtual void BeginPlay() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override 
	{
		return AbilitySystemComponent;
	}

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	virtual bool HasMatchingGameplayTag(FGameplayTag TagToCheck) const override;

	virtual bool HasAllMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;

	virtual bool HasAnyMatchingGameplayTags(const FGameplayTagContainer& TagContainer) const override;

	void ComposeBuilding(int32 Floors, UCOBuildingAsset* BuildingAsset, FVector Direction);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetProvisionUnitCost();
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<UCOBuildingPartComponent> BuildingPartComponentClass;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UAbilitySystemComponent* AbilitySystemComponent {};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCOBuildingAttributeSet* BuildingAttributeSet{};

	UPROPERTY()
	TArray<UCOBuildingPartComponent*> Meshes;

};
