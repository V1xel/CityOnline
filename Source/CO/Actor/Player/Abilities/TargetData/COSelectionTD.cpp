#include "COSelectionTD.h"

bool FCOSelectionTD::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Target;
	Ar << Length;
	Ar << Width;
	Ar << HasCorner;
	Ar << HasExtreme;
	Ar << Center;
	Ar << Direction;

    bOutSuccess = true;
    return true;
}
