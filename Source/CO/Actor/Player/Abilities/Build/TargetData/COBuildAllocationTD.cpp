#include "COBuildAllocationTD.h"

bool FCOBuildAllocationTD::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Target;
	Ar << Length;
	Ar << Width;
	Ar << ExtremeCount;
	Ar << Center;
	Ar << Direction;
	Ar << HasOccupiedCells;
	Ar << Cells;

    bOutSuccess = true;
    return true;
}

AActor* FCOBuildAllocationTD::GetTarget(FGameplayAbilityTargetDataHandle Handle)
{
	return static_cast<FCOBuildAllocationTD*>(Handle.Get(0))->Target;
}
