#include "COBuildRequirementsTD.h"

bool FCOBuildRequirementsTD::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Type.NetSerialize(Ar, Map, bOutSuccess);
	Ar << Name;
	Ar << MinWidth;
	Ar << MaxWidth;
	Ar << MinLength;
	Ar << MaxLength;
	Ar << MinFloors;
	Ar << MaxFloors;
	Ar << CostMultiplier;
	Ar << CapacityMultiplier;

	bOutSuccess = true;
    return true;
}
