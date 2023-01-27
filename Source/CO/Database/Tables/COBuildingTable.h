#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CO/Extensions/GameplayTagExtension.h"
#include "CO/Actor/Player/Abilities/DTO/COSelectionDTO.h"
#include "CO/Actor/Player/Abilities/DTO/COBuildDTO.h"
#include "GameplayTagContainer.h"
#include "COBuildingTable.generated.h"

USTRUCT()
struct CO_API FCOBuildingTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FString GetName() 
	{
		return UGameplayTagExtension::GetTagSecondElement(Tag);
	}

	FCOBuildDTOTargetData* ToTargetData() {
		auto Struct = new FCOBuildDTOTargetData();
		Struct->Name = GetName();
		Struct->MinWidth = MinWidth;
		Struct->MaxWidth = MaxWidth;
		Struct->MinLength = MinLength;
		Struct->MaxLength = MaxLength;
		Struct->MinFlours = MinFlours;
		Struct->MaxFlours = MaxFlours;
		
		return Struct;
	}

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag Tag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MinWidth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxWidth;
  
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MinLength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxLength;
  
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MinFlours;
  
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int MaxFlours;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CostMultiplier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float GoodsMultiplier;
};
