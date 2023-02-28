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
		bool ExtremeBest = false;
		int currentCount = 0;
		int currentExtremeCount = 0;
        if ((Asset->Width == SelectionDTO->Width && Asset->Length == SelectionDTO->Length) ||
            (Asset->Width == SelectionDTO->Length && Asset->Length == SelectionDTO->Width)) {
			currentCount += 2;
        }

        if (Asset->ExtremeCount == SelectionDTO->ExtremeCount) {
			currentCount++;
			ExtremeBest = true;
		}
		else if (!ExtremeBest && BestAsset != nullptr && BestAsset->ExtremeCount < Asset->ExtremeCount) {
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
