// Fill out your copyright notice in the Description page of Project Settings.


#include "COSelectActorAbility.h"

#include "CO/Actor/Interfaces/SelectableActor.h"
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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Try select"));	
	if(HitActor && HitActor != SelectedActor && HitActor->Implements<USelectableActor>())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Execute_SelectActor"));	
		ISelectableActor::Execute_SelectActor(HitActor);
		if(SelectedActor)
		{
			ISelectableActor::Execute_DeselectActor(SelectedActor);
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
