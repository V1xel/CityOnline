// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildAbility.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "CO/Actor/Street/COStreetActor.h"
#include "CO/Actor/Player/COPlayerState.h"
#include "CO/Extensions/GameplayTagExtension.h"
#include "CO/Actor/Player/Abilities/AbilityTasks/COSelectCellsAbilityTask.h"
#include "CO/Core/COConstants.h"
#include "CO/Extensions/GameplayTagExtension.h"

void UCOBuildAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	auto BuildingTag = TriggerEventData->InstigatorTags.First();
	auto BuildingName = UGameplayTagExtension::GetTagSecondElement(BuildingTag);
	auto BuildingSpecialization = *BuildingsTable->FindRow<FCOBuildingTable>(FName(BuildingName), "");
	_BuildDTO = BuildingSpecialization.ToDTO();

	FGameplayEventTagMulticastDelegate::FDelegate AllocationCanceledDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UCOBuildAbility::OnAllocationFinished);
	ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(UCOGameplayTags::AllocateFinished().GetSingleTagContainer(), AllocationCanceledDelegate);

	UAbilitySystemComponent* const AbilitySystemComponent = ActorInfo->AbilitySystemComponent.Get();

	ApplyPlease();
}

void UCOBuildAbility::OnAllocationFinished(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	FGameplayEventData BuildEventData = FGameplayEventData();
	BuildEventData.OptionalObject = EventData->OptionalObject;

	_ActorInfo->AbilitySystemComponent->RemoveActiveGameplayEffect(_AllocationEffectHandle);
	BuildEventData.OptionalObject2 = _BuildDTO;
	
	SendGameplayEvent(UCOGameplayTags::Construct(), BuildEventData);

	EndAbility(_Handle, _ActorInfo, _ActivationInfo, false, false);
}

void UCOBuildAbility::ApplyPlease_Implementation()
{
	auto Effect = EnableCellAllocationEffect.GetDefaultObject();
	auto EffectContext = FGameplayEffectContextHandle(new FGameplayEffectContext());
	EffectContext.AddSourceObject(_BuildDTO);
	auto SpecHandle = FGameplayEffectSpecHandle(new FGameplayEffectSpec(Effect, EffectContext));

	auto effects = _ActorInfo->AbilitySystemComponent->GetActiveGameplayEffects();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::FromInt(effects.GetActiveEffectCount(FGameplayEffectQuery())));
	_ActorInfo->AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	auto effects2 = _ActorInfo->AbilitySystemComponent->GetActiveGameplayEffects();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::FromInt(effects2.GetActiveEffectCount(FGameplayEffectQuery())));
}

bool UCOBuildAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return true;
}

void UCOBuildAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

void UCOBuildAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
