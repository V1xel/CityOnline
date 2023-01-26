// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Actor/Player/Abilities/Build/COAllocateAbility.h"
#include "CO/Actor/Player/Abilities/Helpers/COAllocateHelper.h"
#include "CO/Core/AbilitySystem/COAbilityTaskBase.h"
#include "CO/Extensions/GameplayTagExtension.h"
#include "AbilitySystemComponent.h"
#include <AbilitySystemInterface.h>
#include "COBuildAbility.h"
#include <CO/Core/AbilitySystem/COGameplayEffectContext.h>

void UCOAllocateAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Allocate Activate"));
	_Target = TriggerEventData->Target.Get();
	AllocateStartLocation = TriggerEventData->TargetData.Get(0)->GetHitResult()->Location;
	auto AllocationCancelDelegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateLambda([this, Handle, ActorInfo, ActivationInfo]
	(FGameplayTag Tag, const FGameplayEventData* EventData) { AllocationCancel(Handle, ActorInfo, ActivationInfo, EventData); });
	_CancelDelegateHandle = ActorInfo->AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ListenCancelAllocateTag.GetSingleTagContainer(), AllocationCancelDelegate);

	auto AllocatePermissionActiveEffects = ActorInfo->AbilitySystemComponent->GetActiveEffects(FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(FilterAllocatePermissionTag.GetSingleTagContainer()));
	FGameplayEffectContextHandle PermissionGrantedEffectContext = ActorInfo->AbilitySystemComponent->GetEffectContextFromActiveGEHandle(AllocatePermissionActiveEffects[0]);

	auto EffectSpec = FGameplayEffectSpecHandle(new FGameplayEffectSpec(AllocateInProgressEffect.GetDefaultObject(), PermissionGrantedEffectContext));
	_EffectHadles = ApplyGameplayEffectSpecToTarget(Handle, ActorInfo, ActivationInfo, EffectSpec, TriggerEventData->TargetData);
	auto TestContext = PermissionGrantedEffectContext.Get();
	auto EffectContextBuildDTO = static_cast<FCOGameplayEffectContext*>(TestContext);
	
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(EffectContextBuildDTO->TestVariable));
}

void UCOAllocateAbility::AllocationCancel(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* CancelEventData)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Allocate Cancel"));
	auto AllocatePermissionActiveEffects = ActorInfo->AbilitySystemComponent->GetActiveEffects(FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(FilterAllocatePermissionTag.GetSingleTagContainer()));

	//if (CancelEventData->TargetData.IsValid(0)) 
	//{
	//	auto EndLocation = CancelEventData->TargetData.Get(0)->GetHitResult()->Location;
	//	UCOSelectionDTO* SelectionDTO = UCOAllocateAbilityHelper::CalculateSelectionData(_Target, AllocateStartLocation, EndLocation);

	//	if (UCOAllocateAbilityHelper::ValidateSelectionData(SelectionDTO, BuildDTO)) {
	//		auto Data = FGameplayEventData();
	//		Data.Target = _Target;
	//		Data.OptionalObject = SelectionDTO;
	//		SendGameplayEvent(BroadcastedEventOnAllocationFinished, Data);
	//	}
	//}

	auto TargetAbilitySystem = Cast<IAbilitySystemInterface>(_Target)->GetAbilitySystemComponent();
//	for (auto EffectHandle : _EffectHadles)
//	{
//		TargetAbilitySystem->RemoveActiveGameplayEffect(EffectHandle);
	//}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

UCOBuildDTO* UCOAllocateAbility::GetEffectContextFromActiveGEHandleTest(UAbilitySystemComponent* AS, FActiveGameplayEffectHandle Handle)
{
	FGameplayEffectContextHandle PermissionGrantedEffectContext = AS->GetEffectContextFromActiveGEHandle(Handle);
	auto TestContext = PermissionGrantedEffectContext.Get();
	auto EffectContextBuildDTO = static_cast<FCOGameplayEffectContext*>(TestContext);
	auto dto = NewObject<UCOBuildDTO>();

	dto->MaxFlours = EffectContextBuildDTO->TestVariable;

	return dto;// EffectContextBuildDTO->ToObject();
}

void UCOAllocateAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenCancelAllocateTag.GetSingleTagContainer(), _CancelDelegateHandle);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
