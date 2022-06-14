// Copyright Epic Games, Inc. All Rights Reserved.


#include "COGameModeBase.h"
#include "Player/COPlayerCamera.h"
#include "Player/COPlayerController.h"

ACOGameModeBase::ACOGameModeBase()
{
	DefaultPawnClass = ACOPlayerCamera::StaticClass();
	PlayerControllerClass = ACOPlayerController::StaticClass();
}
