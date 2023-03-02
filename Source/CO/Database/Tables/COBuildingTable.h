#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CO/Extensions/GameplayTagExtension.h"
#include "CO/Actor/Player/Abilities/Build/TargetData/COBuildAllocationTD.h"
#include "CO/Actor/Player/Abilities/Build/TargetData/COBuildRequirementsTD.h"
#include "GameplayTagContainer.h"
#include "COBuildingTable.generated.h"

USTRUCT()
struct CO_API FCOBuildingTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FGameplayAbilityTargetDataHandle ToBuildTargetDataHandle() {
		auto Name = UGameplayTagExtension::GetTagSecondElement(Tag);;
		auto TargetData = new FCOBuildRequirementsTD();
		TargetData->Type = Type;
		TargetData->Name = Name;
		TargetData->MinWidth = MinWidth;
		TargetData->MaxWidth = MaxWidth;
		TargetData->MinLength = MinLength;
		TargetData->MaxLength = MaxLength;
		TargetData->MinFloors = MinFloors;
		TargetData->MaxFloors = MaxFloors;
		TargetData->CostMultiplier = CostMultiplier;
		TargetData->CapacityMultiplier = CapacityMultiplier;
		
		return FGameplayAbilityTargetDataHandle(TargetData);
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag Tag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag Type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MinWidth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxWidth;
  
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MinLength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxLength;
  
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MinFloors;
  
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxFloors;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CostMultiplier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CapacityMultiplier;
};
