#include "CORootAsset.h"
#include "COBuildingAsset.h"
#include "CO/Actor/Player/Abilities/Build/TargetData/COBuildAllocationTD.h"
#include "CO/Actor/Player/Abilities/Build/TargetData/COBuildRequirementsTD.h"

UCOBuildingAsset* UCORootAsset::FindBestAsset(const FCOBuildAllocationTD* SelectionDTO, const FCOBuildRequirementsTD* BuildDTO)
{
	int matchCount = -1;
	UCOBuildingAsset* BestAsset = nullptr;
	for (UCOBuildingAsset* Asset : BuildingsAssets)
	{
		int currentCount = 0;
        if ((Asset->Width == SelectionDTO->Width && Asset->Length == SelectionDTO->Length) ||
            (Asset->Width == SelectionDTO->Length && Asset->Length == SelectionDTO->Width)) {
			currentCount += 2;
        }

        if (Asset->ExtremeCount == SelectionDTO->ExtremeCount) {
			currentCount++;
        }
		if (currentCount > matchCount)
		{
			matchCount = currentCount;
			BestAsset = Asset;
		}
	}

	return BestAsset;

}



//if (Asset->Width == SelectionDTO->Width || Asset->Width == SelectionDTO->Length)
//{
//	currentCount++;
//}
//if (Asset->Length == SelectionDTO->Length || Asset->Length == SelectionDTO->Width)
//{
//	currentCount++;
//}
//if (Asset->Length == Asset->Width && Asset->Width == SelectionDTO->Length && SelectionDTO->Length == SelectionDTO->Width)
//{
//	currentCount++;
//}
//
//if (Asset->ExtremeCount == SelectionDTO->ExtremeCount)
//{
//	currentCount++;
//}
//if (currentCount > matchCount)
//{
//	matchCount = currentCount;
//	BestAsset = Asset;
//}