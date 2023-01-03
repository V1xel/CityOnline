// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Core/Actor/Character/COCharacterBase.h"
#include "COPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CO_API ACOPlayerCharacter : public ACOCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACOPlayerCharacter();

	UFUNCTION(BlueprintCallable)
	void AddForwardMovementInput(float Value);

	UFUNCTION(BlueprintCallable)
	void AddRightMovementInput(float Value);

	UFUNCTION(BlueprintCallable)
	void AddCameraYawInput(float Value);

	UFUNCTION(BlueprintCallable)
	void NavigateOnObject(AActor* object, float zoom);

	UFUNCTION(BlueprintCallable)
	void ZoomCamera(float Value);

	UFUNCTION(BlueprintCallable)
	void EnableRotateCamera();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* Camera;

	float DesiredTargetArmLength;

	float ArmLengthScalingSpeed = 10;

private:
	bool EnableCameraRotation;
};