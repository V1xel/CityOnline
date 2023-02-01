// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "AbilitySystemInterface.h"
#include "CO/Actor/Player/Attributes/COPlayerAttributeSet.h"
#include "COPlayerCharacterBase.generated.h"

class UBehaviorTree;
class AAIController;
class UCOAbilitySystemComponent;
class UCOActorSelectionComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CO_API ACOPlayerCharacterBase : public ADefaultPawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACOPlayerCharacterBase();

	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void Tick(float DeltaTime) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
		void AddForwardMovementInput(float Value);

	UFUNCTION(BlueprintCallable)
		void AddRightMovementInput(float Value);

	UFUNCTION(BlueprintCallable)
		void AddCameraYawInput(float Value);

	UFUNCTION(BlueprintCallable)
		void NavigateOnObject(AActor* object, float zoom);

	UFUNCTION(BlueprintCallable)
	void NavigateOnPosition(FVector position, float zoom);

	UFUNCTION(BlueprintCallable)
		void ZoomCamera(float Value);

	UFUNCTION(BlueprintCallable)
		void EnableRotateCamera();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UCOAbilitySystemComponent* AbilitySystemComponent {};

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UCOPlayerAttributeSet* AttributeSetBase {};

private:
	bool EnableCameraRotation;
	float DesiredTargetArmLength;

	float ArmLengthScalingSpeed = 10;
};
