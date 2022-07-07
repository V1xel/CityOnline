// Fill out your copyright notice in the Description page of Project Settings.

#include "COPlayerCamera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACOPlayerCamera::ACOPlayerCamera()
{
	bAddDefaultMovementBindings  = false;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-60, 0, 0));
	SpringArm->TargetArmLength = 400;
	SpringArm->bDoCollisionTest = false;
	bUseControllerRotationYaw = true;
	SetActorEnableCollision(false);
	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ACOPlayerCamera::AddForwardMovementInput(float Value)
{
	if(Value != 0)
	{
		AddMovementInput(GetActorForwardVector() * Value);
	}
}

void ACOPlayerCamera::AddRightMovementInput(float Value)
{
	if(Value != 0)
	{
		AddMovementInput(GetActorRightVector() * Value);
	}
}

void ACOPlayerCamera::AddCameraYawInput(float Value)
{
	if(Value != 0 && EnableCameraRotation)
	{
		AddControllerYawInput(Value);
	}
}

void ACOPlayerCamera::ZoomCamera(float Value)
{
	if(Value != 0)
	{
		SpringArm->TargetArmLength = SpringArm->TargetArmLength - Value;
	}
} 

void ACOPlayerCamera::EnableRotateCamera()
{
	EnableCameraRotation = !EnableCameraRotation;
}

void ACOPlayerCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &ACOPlayerCamera::AddForwardMovementInput);
	InputComponent->BindAxis("MoveRight", this, &ACOPlayerCamera::AddRightMovementInput);
	InputComponent->BindAxis("RotateCamera", this, &ACOPlayerCamera::AddCameraYawInput);
	InputComponent->BindAxis("ZoomCamera", this, &ACOPlayerCamera::ZoomCamera);
	InputComponent->BindAction("EnableRotateCamera", IE_Pressed, this, &ACOPlayerCamera::EnableRotateCamera);
	InputComponent->BindAction("EnableRotateCamera", IE_Released, this, &ACOPlayerCamera::EnableRotateCamera);
}
