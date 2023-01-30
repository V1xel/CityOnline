#include "CORootAsset.h"
#include "COBuildingAsset.h"
#include "CO/Actor/Player/Abilities/TargetData/COSelectionTD.h"
#include "CO/Actor/Player/Abilities/TargetData/COBuildTD.h"

UCORootAsset* UCORootAsset::Instance = nullptr;

void UCORootAsset::PostLoad()
{
	Super::PostLoad();
	UCORootAsset::Instance = this;
}

UCOBuildingAsset* UCORootAsset::FindBestAsset(const FCOSelectionTD* SelectionDTO, const FCOBuildTD* BuildDTO)
{
	int matchCount = -1;
	UCOBuildingAsset* BestAsset = nullptr;
	for (UCOBuildingAsset* Asset : BuildingsAssets)
	{
		int currentCount = 0;
		if (Asset->HasCorner == SelectionDTO->HasCorner)
		{
			currentCount++;
		}
	//	if (Asset->IsLiving == BuildDTO->IsLiving ||
	//		Asset->IsStore == BuildDTO->IsStore)
	//	{
	//		currentCount++;
	//	}
		if (Asset->Width == SelectionDTO->Width || Asset->Width == SelectionDTO->Length)
		{
			currentCount++;
		}
		if (Asset->Length == SelectionDTO->Length || Asset->Length == SelectionDTO->Width)
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
