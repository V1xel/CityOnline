// Fill out your copyright notice in the Description page of Project Settings.


#include "COTargetData_BuildDTO.h"
#include "CO/Actor/Player/Abilities/DTO/COBuildDTO.h"

FCOEffectContext_BuildDTO::FCOEffectContext_BuildDTO(AActor* InInstigator, AActor* InEffectCauser, UCOBuildDTO* BuildDTO)
	: FGameplayEffectContext(InInstigator, InEffectCauser)
{
	MinFlours = BuildDTO->MinFlours;
	MaxFlours = BuildDTO->MaxFlours;
	Name = BuildDTO->Name;
	MinWidth = BuildDTO->MinWidth;
	MaxWidth = BuildDTO->MaxWidth;
	MinLength = BuildDTO->MinLength;
	MaxLength = BuildDTO->MaxLength;
	IsLiving = BuildDTO->IsLiving;
	IsStore = BuildDTO->IsStore;
}

FString FCOEffectContext_BuildDTO::ToString() const
{
	return TEXT("FCOTargetData_BuildDTO");
}

bool FCOEffectContext_BuildDTO::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	bOutSuccess = true;
	return true;
}

UCOBuildDTO* FCOEffectContext_BuildDTO::ToObject()
{
	auto BuildDTO = NewObject<UCOBuildDTO>();
	BuildDTO->MinFlours = MinFlours;
	BuildDTO->MaxFlours = MaxFlours;
	BuildDTO->Name = Name;
	BuildDTO->MinWidth = MinWidth;
	BuildDTO->MaxWidth = MaxWidth;
	BuildDTO->MinLength = MinLength;
	BuildDTO->MaxLength = MaxLength;
	BuildDTO->IsLiving = IsLiving;
	BuildDTO->IsStore = IsStore;

	return BuildDTO;
}
