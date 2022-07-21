// Copyright Epic Games, Inc. All Rights Reserved.

#include "COGameModeBase.h"
#include "CO/Actor/Player/COPlayerCharacter.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/UserInterface/COHUD.h"

ACOGameModeBase::ACOGameModeBase()
{
	DefaultPawnClass = ACOPlayerCharacter::StaticClass();
	PlayerControllerClass = ACOPlayerController::StaticClass();
	HUDClass = ACOHUD::StaticClass();
}
