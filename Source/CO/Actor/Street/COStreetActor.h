// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Database/Enums/COStreetPrestige.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbilityTargetDataFilter.h"
#include "GameplayEffectTypes.h"
#include "Delegates/IDelegateInstance.h"
#include "COStreetActor.generated.h"

class ACOBuildingActor;
class UCOStreetCellComponent;
class ACOPlayerCharacter;


UCLASS()
class CO_API ACOStreetActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACOStreetActor();

	virtual void BeginPlay() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override 
	{
		return AbilitySystemComponent;
	}

	void OnEffectApplied(AActor* Source, FGameplayEffectSpecHandle SpecHandle, FActiveGameplayEffectHandle ActiveHandle);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PendingDeployEffectApplied(FGameplayEffectContextHandle EffectContextHandle);

	void PendingDeployEffectApplied_Implementation(FGameplayEffectContextHandle EffectContextHandle)
	{
	}

public:
	UPROPERTY()
	TArray<UCOStreetCellComponent*> Cells{};

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UAbilitySystemComponent* AbilitySystemComponent {};

	UPROPERTY(EditAnywhere)
	FGameplayTag ListenBuildingDeployEffectAppliedTag;
	
protected:
	UPROPERTY()
	USceneComponent* SceneComponent;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAppliedDelegate, FGameplayEffectContextHandle, EffectContextHandle);
	UPROPERTY()
	TMap<FGameplayTag, FOnAppliedDelegate> OnAppliedMap;
};
