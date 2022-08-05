// Fill out your copyright notice in the Description page of Project Settings.


#include "COSelectActorAbility.h"

#include "CO/Actor/Interfaces/COSelectableActor.h"
#include "CO/Actor/Player/COPlayerCharacter.h"
#include "CO/Actor/Player/COPlayerController.h"

void UCOSelectActorAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	const ACOPlayerController* PlayerController = GetController(ActorInfo);
	const auto Player = GetOwnerActor(ActorInfo);
	const auto SelectedActor = Player->GetSelectedActor();
	
	FHitResult HitResult;
	PlayerController->GetHitResultUnderCursor(ECC_WorldStatic, false, HitResult);
	AActor* HitActor = HitResult.GetActor();
	if(HitActor && HitActor != SelectedActor && HitActor->Implements<UCOSelectableActor>())
	{
		ICOSelectableActor::Execute_SelectActor(HitActor);
		if(SelectedActor)
		{
			ICOSelectableActor::Execute_DeselectActor(SelectedActor);
		}

		Player->SetSelectedActor(HitActor);
	}
	
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UCOSelectActorAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
