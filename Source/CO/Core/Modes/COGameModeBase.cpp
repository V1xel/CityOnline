// Copyright Epic Games, Inc. All Rights Reserved.

#include "COGameModeBase.h"
#include "CO/Actor/Player/COPlayerCharacter.h"
#include "CO/Actor/Player/COPlayerController.h"

ACOGameModeBase::ACOGameModeBase()
{
	DefaultPawnClass = ACOPlayerCharacter::StaticClass();
	PlayerControllerClass = ACOPlayerController::StaticClass();
}
