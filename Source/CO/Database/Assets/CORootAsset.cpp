#include "CORootAsset.h"
#include "COBuildingAsset.h"
#include "CO/Actor/Player/Abilities/TargetData/COSelectionTD.h"
#include "CO/Actor/Player/Abilities/TargetData/COBuildTD.h"

UCOBuildingAsset* UCORootAsset::FindBestAsset(FGameplayAbilityTargetDataHandle SelectionDTOHandle, FGameplayAbilityTargetDataHandle BuildDTOHandle)
{
	if (!SelectionDTOHandle.IsValid(0) || !BuildDTOHandle.IsValid(0)) {
		return false;
	}

	auto SelectionDTO = static_cast<FCOSelectionTD*>(SelectionDTOHandle.Get(0));
	auto BuildDTO = static_cast<FCOBuildTD*>(BuildDTOHandle.Get(0));

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
