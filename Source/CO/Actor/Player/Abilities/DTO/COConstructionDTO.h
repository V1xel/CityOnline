#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "COConstructionDTO.generated.h"

UCLASS(Blueprintable)
class CO_API UCOConstructionDTO : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsLivingAndNotShop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Floors = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Quality;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Style = 2;
};
