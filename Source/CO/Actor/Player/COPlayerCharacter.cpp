// Fill out your copyright notice in the Description page of Project Settings.

#include "COPlayerCharacter.h"
#include "Abilities/COSelectActorAbility.h"
#include "Abilities/COSelectCellsAbility.h"
#include "CO/AbilitySystem/COAbilitySystemComponent.h"
#include "CO/Actor/Building/Attributes/COBuildingAttributeSet.h"

void ACOPlayerCharacter::StartSelection()
{
	AbilitySystemComponent->TryActivateAbilityByClass(SelectActorAbility);
	AbilitySystemComponent->TryActivateAbilityByClass(SelectCellsAbility);
}

void ACOPlayerCharacter::EndSelection()
{
	AbilitySystemComponent->CancelAbility(SelectCellsAbility);
}

void ACOPlayerCharacter::StartBuildingProcess()
{
}

void ACOPlayerCharacter::UpdateBuildingConfiguration()
{
}

void ACOPlayerCharacter::EndBuildingProcess()
{
}

void ACOPlayerCharacter::CancelBuildingProcess()
{
}

void ACOPlayerCharacter::BeginPlay()
{
	if (HasAuthority())
	{
		AbilitySystemComponent->GiveAbility(SelectActorAbility);
		AbilitySystemComponent->GiveAbility(SelectCellsAbility);
	}
	
	Super::BeginPlay();
}

void ACOPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &ACOPlayerCharacter::AddForwardMovementInput);
	InputComponent->BindAxis("MoveForward", this, &ACOPlayerCharacter::AddForwardMovementInput);
	InputComponent->BindAxis("MoveRight", this, &ACOPlayerCharacter::AddRightMovementInput);
	InputComponent->BindAxis("RotateCamera", this, &ACOPlayerCharacter::AddCameraYawInput);
	InputComponent->BindAxis("ZoomCamera", this, &ACOPlayerCharacter::ZoomCamera);
	InputComponent->BindAction("Select", IE_Pressed, this, &ACOPlayerCharacter::StartSelection);
	InputComponent->BindAction("Select", IE_Released, this, &ACOPlayerCharacter::EndSelection);
	InputComponent->BindAction("EnableRotateCamera", IE_Pressed, this, &ACOPlayerCharacter::EnableRotateCamera);
	InputComponent->BindAction("EnableRotateCamera", IE_Released, this, &ACOPlayerCharacter::EnableRotateCamera);
}
