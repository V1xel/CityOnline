// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/DefaultPawn.h"
#include "COPlayerCamera.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CO_API ACOPlayerCamera : public ADefaultPawn
{
	GENERATED_BODY()

public:
	ACOPlayerCamera();

	void AddForwardMovementInput(float Value);
	
	void AddRightMovementInput(float Value);
	
	void AddCameraYawInput(float Value);

	UFUNCTION(BlueprintCallable)
	void NavigateOnObject(AActor* object, float zoom);

	void EnableRotateCamera();
	
	void ZoomCamera(float Value);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera;
	
private:
	bool EnableCameraRotation;
};
