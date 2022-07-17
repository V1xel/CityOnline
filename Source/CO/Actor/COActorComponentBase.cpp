// Fill out your copyright notice in the Description page of Project Settings.


#include "COActorComponentBase.h"
#include "CO/Player/COPlayerController.h"

ACOPlayerController* UCOActorComponentBase::GetOwnerController() const
{
	return Cast<ACOPlayerController>(GetOwner());
}
