// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Core/AbilitySystem/COGameplayAbilityBase.h"
#include "CODeployBuildingAbility.generated.h"

class ACOBuildingActor;
class UCOBuildingPartComponent;

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class CO_API UCODeployBuildingAbility : public UCOGameplayAbilityBase
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
			const FGameplayAbilityActivationInfo ActivationInfo,
			const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACOBuildingActor> BuildingActorClass;

	UPROPERTY(EditAnywhere)
	UDataTable* BuildingsTable {};
};
