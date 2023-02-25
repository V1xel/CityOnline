#include "COBuildRequirementsTD.h"

bool FCOBuildRequirementsTD::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
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
