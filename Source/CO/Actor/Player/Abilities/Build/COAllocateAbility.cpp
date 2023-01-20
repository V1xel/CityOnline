// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Actor/Player/Abilities/Build/COAllocateAbility.h"
#include "CO/Actor/Player/Abilities/Helpers/COAllocateHelper.h"
#include "CO/Core/AbilitySystem/COAbilityTaskBase.h"
#include "CO/Extensions/GameplayTagExtension.h"
#include "AbilitySystemComponent.h"
#include <AbilitySystemInterface.h>
#include "COBuildAbility.h"
#include <CO/Actor/Player/Abilities/DTO/COTargetData_BuildDTO.h>

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
}

void UCOAllocateAbility::AllocationCancel(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, 
	const FGameplayEventData* CancelEventData)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Allocate Cancel"));

	//auto AllocatePermissionActiveEffects = ActorInfo->AbilitySystemComponent->GetActiveEffects(FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(FilterAllocatePermissionTag.GetSingleTagContainer()));
	//FGameplayEffectContextHandle PermissionGrantedEffectContext = ActorInfo->AbilitySystemComponent->GetEffectContextFromActiveGEHandle(AllocatePermissionActiveEffects[0]);
	//auto TestContext = PermissionGrantedEffectContext.Get();
	//auto EffectContextBuildDTO = static_cast<FCOEffectContext_BuildDTO*>(TestContext);
	//auto BuildDTO = EffectContextBuildDTO->ToObject();

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
	for (auto EffectHandle : _EffectHadles)
	{
		TargetAbilitySystem->RemoveActiveGameplayEffect(EffectHandle);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

UCOBuildDTO* UCOAllocateAbility::GetBuildDTO(FGameplayEffectContextHandle EffectContextHandle)
{
	auto EffectContext = EffectContextHandle.Get();
	auto Context = static_cast<FCOEffectContext_BuildDTO*>(EffectContext);

	auto BuildDTO = NewObject<UCOBuildDTO>();
	BuildDTO->MinFlours = Context->MinFlours;
	BuildDTO->MaxFlours = Context->MaxFlours;
	BuildDTO->Name = Context->Name;
	BuildDTO->MinWidth = Context->MinWidth;
	BuildDTO->MaxWidth = Context->MaxWidth;
	BuildDTO->MinLength = Context->MinLength;
	BuildDTO->MaxLength = Context->MaxLength;
	BuildDTO->IsLiving = Context->IsLiving;
	BuildDTO->IsStore = Context->IsStore;

	return BuildDTO;
}

void UCOAllocateAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ActorInfo->AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(ListenCancelAllocateTag.GetSingleTagContainer(), _CancelDelegateHandle);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
