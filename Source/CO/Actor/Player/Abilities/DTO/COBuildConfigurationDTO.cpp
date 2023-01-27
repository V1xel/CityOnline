// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildConfigurationDTO.h"

bool FCOBuildConfigurationDTOTargetData::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << BuildingName;
	Ar << Floors;

	bOutSuccess = true;
	return true;
}

UCOBuildConfigurationDTO* FCOBuildConfigurationDTOTargetData::ToDTO() const
{
	auto DTO = NewObject<UCOBuildConfigurationDTO>();
	DTO->BuildingName = BuildingName;
	DTO->Floors = Floors;

	return nullptr;
}

FGameplayAbilityTargetDataHandle UCOBuildConfigurationDTO::ToTargetDataHandle()
{
	auto TargetData = new FCOBuildConfigurationDTOTargetData();
	TargetData->BuildingName = BuildingName;
	TargetData->Floors = Floors;

	return FGameplayAbilityTargetDataHandle(TargetData);
}

FGameplayAbilityTargetDataHandle UCOBuildConfigurationDTO::MakeBuildConfigurationTargetDataHandle(FName InBuildingName, int32 InFloors)
{
	auto TargetData = new FCOBuildConfigurationDTOTargetData();
	TargetData->BuildingName = InBuildingName;
	TargetData->Floors = InFloors;

	return FGameplayAbilityTargetDataHandle(TargetData);
}
