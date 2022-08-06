// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "COActorComponentBase.generated.h"

class ACOPlayerController;

UCLASS()
class CO_API UCOActorComponentBase : public UActorComponent
{
	GENERATED_BODY()

protected:
	template <typename T>
	T* GetOwnerComponent(const TSubclassOf<UActorComponent> Class) const
	{
		T* Component = CastChecked<T>(GetOwner()->GetComponentByClass(Class), ECastCheckedType::NullChecked);

		return Component;
	}

	ACOPlayerController* GetOwnerController() const;
};
