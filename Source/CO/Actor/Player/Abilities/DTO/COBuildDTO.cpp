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

UCOBuildDTO* FCOBuildDTOTargetData::ToObject()
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
