#include "CORootAsset.h"
#include "COBuildingAsset.h"
#include "CO/Actor/Player/Abilities/TargetData/COSelectionTD.h"
#include "CO/Actor/Player/Abilities/TargetData/COBuildTD.h"

UCOBuildingAsset* UCORootAsset::FindBestAsset(const FCOSelectionTD* SelectionDTO, const FCOBuildTD* BuildDTO)
{
	int matchCount = -1;
	UCOBuildingAsset* BestAsset = nullptr;
	for (UCOBuildingAsset* Asset : BuildingsAssets)
	{
		int currentCount = 0;
		if (Asset->Width == SelectionDTO->Width || Asset->Width == SelectionDTO->Length)
		{
			currentCount++;
		}
		if (Asset->Length == SelectionDTO->Length || Asset->Length == SelectionDTO->Width)
		{
			currentCount++;
		}
		if (Asset->ExtremeCount == SelectionDTO->ExtremeCount)
		{
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
