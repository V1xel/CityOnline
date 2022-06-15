// Copyright Epic Games, Inc. All Rights Reserved.

#include "COGameModeBase.h"
#include "CO/Player/COPlayerCamera.h"
#include "CO/Player/COPlayerController.h"
#include "CO/UserInterface/COHUD.h"

ACOGameModeBase::ACOGameModeBase()
{
	DefaultPawnClass = ACOPlayerCamera::StaticClass();
	PlayerControllerClass = ACOPlayerController::StaticClass();
	HUDClass = ACOHUD::StaticClass();
}
