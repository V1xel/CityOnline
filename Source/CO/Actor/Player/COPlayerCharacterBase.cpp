// Fill out your copyright notice in the Description page of Project Settings.


#include "COPlayerCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ACOPlayerCharacterBase::ACOPlayerCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	bAddDefaultMovementBindings  = false;
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

void ACOPlayerCharacterBase::AddForwardMovementInput(float Value)
{
	if(Value != 0)
	{
		AddMovementInput(GetActorForwardVector() * Value);
	}
}

void ACOPlayerCharacterBase::AddRightMovementInput(float Value)
{
	if(Value != 0)
	{
		AddMovementInput(GetActorRightVector() * Value);
	}
}

void ACOPlayerCharacterBase::AddCameraYawInput(float Value)
{
	if(Value != 0 && EnableCameraRotation)
	{
		AddControllerYawInput(Value);
	}
}

void ACOPlayerCharacterBase::NavigateOnObject(AActor* object, float zoom)
{
	DesiredTargetArmLength = zoom;
	const FVector NavigatedObjectLocation = object->GetActorLocation();
	SetActorLocation(NavigatedObjectLocation);
}

void ACOPlayerCharacterBase::ZoomCamera(float Value)
{
	if(Value != 0)
	{
		DesiredTargetArmLength = DesiredTargetArmLength - Value;
	}
} 

void ACOPlayerCharacterBase::EnableRotateCamera()
{
	EnableCameraRotation = !EnableCameraRotation;
}

void ACOPlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArm->TargetArmLength = FMath::Lerp(SpringArm->TargetArmLength, DesiredTargetArmLength, DeltaTime);
}

