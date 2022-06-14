// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildingActorBase.h"

// Sets default values
ACOBuildingActorBase::ACOBuildingActorBase()
{
}

void ACOBuildingActorBase::Select()
{
	IsSelected = true;
}

void ACOBuildingActorBase::Deselect()
{
	IsSelected = false;
}
