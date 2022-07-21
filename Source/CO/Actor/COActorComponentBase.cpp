// Fill out your copyright notice in the Description page of Project Settings.


#include "COActorComponentBase.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "Player/COPlayerCharacter.h"

ACOPlayerController* UCOActorComponentBase::GetOwnerController() const
{
	const auto OwnerActor = Cast<ACOCharacterBase>(GetOwner());
	return Cast<ACOPlayerController>(OwnerActor->GetController());
}
