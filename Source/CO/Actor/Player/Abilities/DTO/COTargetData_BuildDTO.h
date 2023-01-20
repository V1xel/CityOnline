// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "COTargetData_BuildDTO.generated.h"

class UCOBuildDTO;

USTRUCT(BlueprintType)
struct CO_API FCOEffectContext_BuildDTO : public FGameplayEffectContext
{
	GENERATED_BODY()
public:

	FCOEffectContext_BuildDTO()
		: FGameplayEffectContext()
	{
	}

	FCOEffectContext_BuildDTO(AActor* InInstigator, AActor* InEffectCauser, UCOBuildDTO* BuildDTO);

	virtual ~FCOEffectContext_BuildDTO()
	{
	}

	FString Name;

	int MinWidth;

	int MaxWidth;

	int MinLength;

	int MaxLength;

	int MinFlours;

	int MaxFlours;

	bool IsLiving;

	bool IsStore;

	virtual FString ToString() const override;

	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	UCOBuildDTO* ToObject();

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FCOEffectContext_BuildDTO::StaticStruct();
	}
};

template<> struct TIsPODType<FCOEffectContext_BuildDTO> { enum { Value = true }; };

template<>
struct TStructOpsTypeTraits<FCOEffectContext_BuildDTO> : public TStructOpsTypeTraitsBase2<FCOEffectContext_BuildDTO>
{
	enum
	{
		WithNetSerializer = true	// For now this is REQUIRED for FGameplayAbilityTargetDataHandle net serialization to work
	};
};
