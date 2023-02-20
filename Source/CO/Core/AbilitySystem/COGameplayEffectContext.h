// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "COGameplayEffectContext.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CO_API FCOGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()
public:

	FCOGameplayEffectContext()
		: FGameplayEffectContext()
	{
	}

	FCOGameplayEffectContext(AActor* InInstigator, AActor* InEffectCauser)
		: FGameplayEffectContext(InInstigator, InEffectCauser)
	{
	}

	virtual ~FCOGameplayEffectContext()
	{
	}

	virtual FString ToString() const override
	{
		return TEXT("FCOGameplayEffectContext");
	}

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	void SetTargetData(FGameplayAbilityTargetDataHandle InTargetData);

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FCOGameplayEffectContext* Duplicate() const override
	{
		FCOGameplayEffectContext* NewContext = new FCOGameplayEffectContext();
		*NewContext = *this;
		NewContext->AddActors(Actors);
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;

protected:
	TArray<TWeakObjectPtr<AActor>> CombinedArray{};

public:
	FGameplayAbilityTargetDataHandle TargetData;
};

template <>
struct TStructOpsTypeTraits<FCOGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FCOGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true // Necessary so that TSharedPtr<FHitResult> Data is copied around
	};
};