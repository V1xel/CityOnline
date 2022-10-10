// Fill out your copyright notice in the Description page of Project Settings.


#include "COSelectActorAbility.h"

#include "CO/Actor/Interfaces/COSelectableActor.h"
#include "CO/Actor/Player/COPlayerCharacter.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/AbilitySystem/COAbilitySystemComponent.h"

void UCOSelectActorAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	ACOPlayerController* PlayerController = GetController(ActorInfo);
	const auto SelectedActor = PlayerController->GetSelectedActor();
	
	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
	AActor* HitActor = HitResult.GetActor();
	if(HitActor && HitActor != SelectedActor && HitActor->Implements<UCOSelectableActor>())
	{
		auto AbilitySystem = Cast<UAbilitySystemComponent>(HitActor->GetComponentByClass(UAbilitySystemComponent::StaticClass()));
		for (auto Tag : TargetBlockedTags)
		{
			if (AbilitySystem->HasMatchingGameplayTag(Tag)) 
			{
				return;
			}
		}

		ICOSelectableActor::Execute_SelectActor(HitActor);
		if(SelectedActor)
		{
			ICOSelectableActor::Execute_DeselectActor(SelectedActor);
		}

		PlayerController->SetSelectedActor(HitActor);
	}
	
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UCOSelectActorAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
