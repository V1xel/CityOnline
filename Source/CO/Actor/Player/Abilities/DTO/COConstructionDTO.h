#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "COConstructionDTO.generated.h"

UCLASS()
class CO_API UCOConstructionDTO : public UObject
{
	GENERATED_BODY()

public:
	bool IsLivingAndNotShop;

};
