#include "COBuildDTO.h"

bool FCOBuildDTOTargetData::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Name;
	Ar << MinWidth;
	Ar << MaxWidth;
	Ar << MinLength;
	Ar << MaxLength;
	Ar << MinFloors;
	Ar << MaxFloors;

    return true;
}

UCOBuildDTO* FCOBuildDTOTargetData::ToDTO()
{
	auto DTO = NewObject<UCOBuildDTO>();
	DTO->Name = Name;
	DTO->MinWidth = MinWidth;
	DTO->MaxWidth = MaxWidth;
	DTO->MinLength = MinLength;
	DTO->MaxLength = MaxLength;
	DTO->MinFloors = MinFloors;
	DTO->MaxFloors = MaxFloors;

	return DTO;
}

FGameplayAbilityTargetDataHandle UCOBuildDTO::ToTargetDataHandle()
{
	auto TargetData = new FCOBuildDTOTargetData();
	TargetData->Name = Name;
	TargetData->MinWidth = MinWidth;
	TargetData->MaxWidth = MaxWidth;
	TargetData->MinLength = MinLength;
	TargetData->MaxLength = MaxLength;
	TargetData->MinFloors = MinFloors;
	TargetData->MaxFloors = MaxFloors;

	return FGameplayAbilityTargetDataHandle(TargetData);
}