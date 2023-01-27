#include "COSelectionDTO.h"

bool FCOSelectionDTOTargetData::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << Length;
	Ar << Width;
	Ar << HasCorner;
	Ar << HasExtreme;
	Ar << Center;
	Ar << Direction;

    bOutSuccess = true;
    return true;
}

UCOSelectionDTO* FCOSelectionDTOTargetData::ToDTO()
{
	auto DTO = NewObject<UCOSelectionDTO>();
	DTO->Length = Length;
	DTO->Width = Width;
	DTO->HasCorner = HasCorner;
	DTO->HasExtreme = HasExtreme;
	DTO->Center = Center;
	DTO->Direction = Direction;

    return DTO;
}

FCOSelectionDTOTargetData* UCOSelectionDTO::ToTargetData()
{
	auto TargetData = new FCOSelectionDTOTargetData();
	TargetData->Length = Length;
	TargetData->Width = Width;
	TargetData->HasCorner = HasCorner;
	TargetData->HasExtreme = HasExtreme;
	TargetData->Center = Center;
	TargetData->Direction = Direction;

	return TargetData;
}
