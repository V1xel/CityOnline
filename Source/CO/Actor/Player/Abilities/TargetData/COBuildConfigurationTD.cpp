// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildConfigurationTD.h"

bool FCOBuildConfigurationTD::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	Ar << BuildingName;
	Ar << Floors;

	bOutSuccess = true;
	return true;
}
