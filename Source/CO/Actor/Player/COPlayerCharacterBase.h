// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CO/Actor/Character/COCharacterBase.h"
#include "COPlayerCharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CO_API ACOPlayerCharacterBase : public ACOCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACOPlayerCharacterBase();
	void AddForwardMovementInput(float Value);
	void AddRightMovementInput(float Value);
	void AddCameraYawInput(float Value);

	UFUNCTION(BlueprintCallable)
	void NavigateOnObject(AActor* object, float zoom);
	
	void ZoomCamera(float Value);
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
