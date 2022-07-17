// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildingActor.h"

// Sets default values
ACOBuildingActor::ACOBuildingActor()
{
}

void ACOBuildingActor::UpdateConfiguration(FCOBuildingConfiguration _Configuration)
{
	Configuration = _Configuration;
}

void ACOBuildingActor::ApplyChanges()
{
}

void ACOBuildingActor::RemoveActor()
{
}

void ACOBuildingActor::SelectActor_Implementation()
{
	ISelectableActor::SelectActor_Implementation();
}

void ACOBuildingActor::DeselectActor_Implementation()
{
	ISelectableActor::DeselectActor_Implementation();
}


