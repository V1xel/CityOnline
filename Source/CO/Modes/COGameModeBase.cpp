// Copyright Epic Games, Inc. All Rights Reserved.

#include "COGameModeBase.h"
#include "CO/Player/COPlayerCamera.h"
#include "CO/Player/COPlayerControllerBase.h"
#include "CO/UserInterface/COHUD.h"

ACOGameModeBase::ACOGameModeBase()
{
	DefaultPawnClass = ACOPlayerCamera::StaticClass();
	PlayerControllerClass = ACOPlayerControllerBase::StaticClass();
	HUDClass = ACOHUD::StaticClass();
}
