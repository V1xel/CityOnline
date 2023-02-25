#include "COSelectionTD.h"

bool FCOSelectionTD::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Target;
	Ar << Length;
	Ar << Width;
	Ar << HasCorner;
	Ar << HasExtreme;
	Ar << ExtremeCount;
	Ar << Center;
	Ar << Direction;

    bOutSuccess = true;
    return true;
}

AActor* FCOSelectionTD::GetTarget(FGameplayAbilityTargetDataHandle Handle)
{
	return static_cast<FCOSelectionTD*>(Handle.Get(0))->Target;
}
