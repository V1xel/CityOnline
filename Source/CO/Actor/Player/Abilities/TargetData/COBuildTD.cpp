#include "COBuildTD.h"

bool FCOBuildTD::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Name;
	Ar << MinWidth;
	Ar << MaxWidth;
	Ar << MinLength;
	Ar << MaxLength;
	Ar << MinFloors;
	Ar << MaxFloors;

	bOutSuccess = true;
    return true;
}
