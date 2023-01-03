// Fill out your copyright notice in the Description page of Project Settings.


#include "COSelectActorAbility.h"

#include "CO/Core/Actor/Interfaces/COSelectableActor.h"
#include "CO/Actor/Player/COPlayerCharacter.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Core/AbilitySystem/COAbilitySystemComponent.h"

void UCOSelectActorAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	ACOPlayerController* PlayerController = GetController(ActorInfo);
	const auto SelectedActor = PlayerController->GetSelectedActor();
	
	AActor* HitActor = Cast<AActor>(TriggerEventData->OptionalObject);
	if(HitActor && HitActor != SelectedActor && HitActor->Implements<UCOSelectableActor>())
	{
		auto AbilitySystem = Cast<UAbilitySystemComponent>(HitActor->GetComponentByClass(UAbilitySystemComponent::StaticClass()));
		static FGameplayTagContainer TargetTags;
		TargetTags.Reset();
		AbilitySystem->GetOwnedGameplayTags(TargetTags);
		if (TargetTags.HasAny(TargetBlockedTags))
			return;

		ICOSelectableActor::Execute_SelectActor(HitActor);
		if(SelectedActor)
		{
			ICOSelectableActor::Execute_DeselectActor(SelectedActor);
		}

		PlayerController->SetSelectedActor(HitActor);
	}
	
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

bool UCOSelectActorAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return true;
}

void UCOSelectActorAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
