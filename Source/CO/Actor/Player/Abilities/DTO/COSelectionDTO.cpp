#include "COSelectionDTO.h"

bool FCOSelectionDTOTargetData::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Length;
	Ar << Width;
	Ar << HasCorner;
	Ar << HasExtreme;
	Center.NetSerialize(Ar, Map, bOutSuccess);
	Rotation.NetSerialize(Ar, Map, bOutSuccess);

    bOutSuccess = true;
    return true;
}

UCOSelectionDTO* FCOSelectionDTOTargetData::ToDTO()
{
    return nullptr;
}

FCOSelectionDTOTargetData UCOSelectionDTO::ToTargetData()
{
	return FCOSelectionDTOTargetData();
}
