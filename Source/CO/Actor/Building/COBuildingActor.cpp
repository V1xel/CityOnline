// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildingActor.h"

#include "CO/AbilitySystem/COAbilitySystemComponent.h"

// Sets default values
ACOBuildingActor::ACOBuildingActor()
{
}

void ACOBuildingActor::UpdateConfiguration(UCOBuildingDetails* Configuration)
{
	_Configuration = Configuration;
}

void ACOBuildingActor::ApplyChanges()
{
	AbilitySystemComponent->OnGameplayEffectAppliedDelegateToTarget.AddLambda([&](
		UAbilitySystemComponent* Target,
		const FGameplayEffectSpec& SpecApplied,
		FActiveGameplayEffectHandle ActiveHandle)
	{
		for (auto Attribute : SpecApplied.ModifiedAttributes)
		{
			auto value = Attribute.Attribute.GetNumericValue(BuildingAttributeSet);
		}
		
	});
}

void ACOBuildingActor::RemoveActor()
{
}

void ACOBuildingActor::SelectActor_Implementation()
{
	ICOSelectableActor::SelectActor_Implementation();
}

void ACOBuildingActor::DeselectActor_Implementation()
{
	ICOSelectableActor::DeselectActor_Implementation();
}


