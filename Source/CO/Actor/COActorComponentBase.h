// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Utilities/COComponentHelper.h"
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
		T* Component = Cast<T>(GetOwner()->GetComponentByClass(Class));

		return COAssertionChecker::CheckReferenceNotNull(Component, FString::Printf(TEXT("Null reference: %s"), *Class->ClassConfigName.ToString()));
	}

	ACOPlayerController* GetOwnerController() const;
};
