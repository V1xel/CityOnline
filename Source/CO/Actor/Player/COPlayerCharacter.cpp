// Fill out your copyright notice in the Description page of Project Settings.

#include "COPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACOPlayerCharacter::ACOPlayerCharacter() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	bAddDefaultMovementBindings = false;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-60, 0, 0));
	SpringArm->TargetArmLength = 8000;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 0.5f;
	DesiredTargetArmLength = SpringArm->TargetArmLength;

	bUseControllerRotationYaw = true;
	SetActorEnableCollision(false);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ACOPlayerCharacter::AddForwardMovementInput(float Value)
{
	if (Value != 0)
	{
		AddMovementInput(GetActorForwardVector() * Value);
	}
}

void ACOPlayerCharacter::AddRightMovementInput(float Value)
{
	if (Value != 0)
	{
		AddMovementInput(GetActorRightVector() * Value);
	}
}

void ACOPlayerCharacter::AddCameraYawInput(float Value)
{
	if (Value != 0 && EnableCameraRotation)
	{
		AddControllerYawInput(Value);
	}
}

void ACOPlayerCharacter::NavigateOnObject(AActor* object, float zoom)
{
	DesiredTargetArmLength = zoom;
	const FVector NavigatedObjectLocation = object->GetActorLocation();
	SetActorLocation(NavigatedObjectLocation);
}

void ACOPlayerCharacter::ZoomCamera(float Value)
{
	if (Value != 0)
	{
		DesiredTargetArmLength = DesiredTargetArmLength - Value;
	}
}

void ACOPlayerCharacter::EnableRotateCamera()
{
	EnableCameraRotation = !EnableCameraRotation;
}

void ACOPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArm->TargetArmLength = FMath::Lerp(SpringArm->TargetArmLength, DesiredTargetArmLength, DeltaTime);
}