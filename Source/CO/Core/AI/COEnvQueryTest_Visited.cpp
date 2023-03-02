// Fill out your copyright notice in the Description page of Project Settings.


#include "COEnvQueryTest_Visited.h"
#include <CO/Actor/Building/COBuildingActor.h>
#include <CO/Actor/Character/COCitizenCharacter.h>

void UCOEnvQueryTest_Visited::RunTest(FEnvQueryInstance& QueryInstance) const
{
	auto QueryOwner = Cast<ACOCitizenCharacter>(QueryInstance.Owner.Get());
	if (QueryOwner == nullptr)
		return;

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		ACOBuildingActor* FoundActor = Cast<ACOBuildingActor>(GetItemActor(QueryInstance, It.GetIndex()));

		It.SetScore(TestPurpose, FilterType, QueryOwner->CheckBuildingVisited(FoundActor), true);
	}
}

FText UCOEnvQueryTest_Visited::GetDescriptionDetails() const
{
	return FText::FromString("Building Visited By Citizen");
}

FText UCOEnvQueryTest_Visited::GetDescriptionTitle() const
{
	return FText::FromString("Building Visited By Citizen");
}
