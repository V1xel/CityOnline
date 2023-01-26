#include "COBuildDTO.h"

bool FCOBuildDTOContext::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << MinWidth;
	Ar << MaxWidth;
	Ar << MinLength;
	Ar << MaxLength;
	Ar << MinFlours;
	Ar << MaxFlours;

    return true;
}
