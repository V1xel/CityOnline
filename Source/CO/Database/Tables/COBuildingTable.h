#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CO/Extensions/GameplayTagExtension.h"
#include "CO/Actor/Player/Abilities/DTO/COSelectionDTO.h"
#include "COBuildingTable.generated.h"

USTRUCT()
struct CO_API FCOBuildingTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FString GetName() 
	{
		return UGameplayTagExtension::GetTagThirdElement(Tag);
	}

	bool Validate(UCOSelectionDTO* SelectionDTO)
	{
		auto HasValidWidth = SelectionDTO->Width <= MaxWidth && SelectionDTO->Width >= MinWidth;
		auto HasValidLength = SelectionDTO->Length <= MaxLength && SelectionDTO->Length >= MinLength;
		auto HasValidFlour = SelectionDTO->Flours <= MaxFlours && SelectionDTO->Flours >= MinFlours;

		return HasValidWidth && HasValidLength && HasValidFlour;
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
