// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "AbilitySystemInterface.h"
#include "CO/Actor/Player/Attributes/COPlayerAttributeSet.h"
#include "COCharacterBase.generated.h"

class UBehaviorTree;
class AAIController;
class UCOAbilitySystemComponent;
class UCOActorSelectionComponent;

UCLASS()
class CO_API ACOCharacterBase : public ADefaultPawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACOCharacterBase();
public:
	bool IsSelected;

	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UCOAbilitySystemComponent* AbilitySystemComponent{};

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UCOPlayerAttributeSet* AttributeSetBase{};
};
