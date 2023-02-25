// Fill out your copyright notice in the Description page of Project Settings.


#include "COGameplayAbilityBase.h"
#include "CO/Actor/Player/COPlayerCharacter.h"
#include "CO/Actor/Player/COPlayerController.h"
#include "COGameplayEffectContext.h"

void UCOGameplayAbilityBase::ActivateAbility(FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UCOGameplayAbilityBase::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

FGameplayAbilityTargetDataHandle UCOGameplayAbilityBase::GetTargetDataFromActiveEffect(const FGameplayEffectQuery& Query)
{
	return UCOGameplayAbilityBase::GetTargetDataFromAbilitySystemActiveEffect(GetActorInfo().AbilitySystemComponent.Get(), Query);
}

FGameplayAbilityTargetDataHandle UCOGameplayAbilityBase::GetTargetDataFromAbilitySystemActiveEffect(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectQuery& Query)
{
	auto AllocatePermissionActiveEffects = AbilitySystemComponent->GetActiveEffects(Query);
	FGameplayEffectContextHandle PermissionGrantedEffectContext = AbilitySystemComponent->GetEffectContextFromActiveGEHandle(AllocatePermissionActiveEffects[0]);
	auto AllocatePermissionEffectContext = static_cast<FCOGameplayEffectContext*>(PermissionGrantedEffectContext.Get());

	return AllocatePermissionEffectContext->TargetData;
}

FDelegateHandle UCOGameplayAbilityBase::AddGETagDelegate(FGameplayTag Tag, FGEDelegate Delegate)
{
	return GetActorInfo().AbilitySystemComponent->AddGameplayEventTagContainerDelegate(Tag.GetSingleTagContainer(), Delegate);
}

FActiveGameplayEffectHandle UCOGameplayAbilityBase::ApplyGESpecToOwner(const FGameplayEffectSpecHandle SpecHandle)
{
	return ApplyGameplayEffectSpecToOwner(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), SpecHandle);
}

TArray<FActiveGameplayEffectHandle> UCOGameplayAbilityBase::ApplyGESpecToTarget(const FGameplayEffectSpecHandle SpecHandle, const FGameplayAbilityTargetDataHandle& TargetData)
{
	return ApplyGameplayEffectSpecToTarget(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), SpecHandle, TargetData);
}

UAbilitySystemComponent* UCOGameplayAbilityBase::GetASC(AActor* Actor)
{
	return Cast<IAbilitySystemInterface>(Actor)->GetAbilitySystemComponent();
}

void UCOGameplayAbilityBase::RemoveActiveGameplayEffect(FActiveGameplayEffectHandle Handle)
{
	GetActorInfo().AbilitySystemComponent->RemoveActiveGameplayEffect(Handle);
}

void UCOGameplayAbilityBase::SendServerGEToTarget(AActor* Target, FGameplayTag Tag, FGameplayEventData Payload)
{
	auto PlayerCharacter = Cast<ACOPlayerController>(GetActorInfo().PlayerController.Get());
	PlayerCharacter->SendServerGameplayEventToListener(Target, Tag, Payload);
}

void UCOGameplayAbilityBase::EndAbilityArgsless()
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}
