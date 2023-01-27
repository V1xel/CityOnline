// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Actor/Street/Abilities/DTO/CODeployBuildingDTO.h"

bool FCODeployDTOTargetData::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
    Ar << Floors;
    Ar << BuildingName;
    SelectionDTO.NetSerialize(Ar, Map, bOutSuccess);

    bOutSuccess = true;
    return true;
}

UCODeployBuildingDTO* FCODeployDTOTargetData::ToDTO()
{
    auto DTO = NewObject<UCODeployBuildingDTO>();
    DTO->Floors = Floors;
    DTO->BuildingName = BuildingName;
    DTO->SelectionDTO = SelectionDTO.ToDTO();

    return nullptr;
}

FGameplayAbilityTargetData* UCODeployBuildingDTO::ToTargetData()
{
    FCODeployDTOTargetData* TargetData = new FCODeployDTOTargetData();
    TargetData->Floors = Floors;
    TargetData->BuildingName = BuildingName;
    TargetData->SelectionDTO = SelectionDTO->ToTargetData();

    return TargetData;
}
