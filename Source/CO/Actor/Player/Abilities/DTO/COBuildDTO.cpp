#include "COBuildDTO.h"

bool FCOBuildDTOTargetData::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Name;
	Ar << MinWidth;
	Ar << MaxWidth;
	Ar << MinLength;
	Ar << MaxLength;
	Ar << MinFlours;
	Ar << MaxFlours;

    return true;
}

UCOBuildDTO* FCOBuildDTOTargetData::ToDTO()
{
	auto Object = NewObject<UCOBuildDTO>();
	Object->Name = Name;
	Object->MinWidth = MinWidth;
	Object->MaxWidth = MaxWidth;
	Object->MinLength = MinLength;
	Object->MaxLength = MaxLength;
	Object->MinFlours = MinFlours;
	Object->MaxFlours = MaxFlours;

	return Object;
}

FCOBuildDTOTargetData* UCOBuildDTO::ToTargetData()
{
	auto TargetData = new FCOBuildDTOTargetData();
	TargetData->Name = Name;
	TargetData->MinWidth = MinWidth;
	TargetData->MaxWidth = MaxWidth;
	TargetData->MinLength = MinLength;
	TargetData->MaxLength = MaxLength;
	TargetData->MinFlours = MinFlours;
	TargetData->MaxFlours = MaxFlours;

	return TargetData;
}