// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "COAbilityTaskBase.generated.h"

/**
 * 
 */
UCLASS()
class CO_API UCOAbilityTaskBase : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	template <class TAbilityTask>
	static FORCEINLINE TAbilityTask* CreateAllocationTask(UGameplayAbility* OwningAbility, FGameplayAbilityTargetDataHandle TargetData, bool bTickingTask = true)
	{
		TAbilityTask* Task = NewAbilityTask<TAbilityTask>(OwningAbility);
		Task->_TargetData = TargetData;
		Task->bTickingTask = bTickingTask;
		Task->ReadyForActivation();

		return Task;
	}

protected:
	FGameplayAbilityTargetDataHandle _TargetData;
};
