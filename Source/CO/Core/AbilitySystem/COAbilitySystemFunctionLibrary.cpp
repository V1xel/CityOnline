// Fill out your copyright notice in the Description page of Project Settings.


#include "COAbilitySystemFunctionLibrary.h"
#include "COAbilitySystemComponent.h"
#include "COGameplayEffectContext.h"
#include <AbilitySystemBlueprintLibrary.h>
#include "COGameplayAbilityBase.h"
#include "CO/Database/Assets/COBuildingAsset.h"
#include "CO/Database/Assets/CORootAsset.h"
#include "CO/Actor/Player/Abilities/Build/TargetData/COBuildConfigurationTD.h"
#include "CO/Actor/Player/Abilities/Build/TargetData/COBuildAllocationTD.h"
#include "CO/Actor/Player/Abilities/Build/TargetData/COBuildRequirementsTD.h"
#include "CO/Actor/Player/COPlayerController.h"

FGameplayEffectContextHandle UCOAbilitySystemFunctionLibrary::GetEffectContextFromActiveGEHandle(UAbilitySystemComponent* AbilitySystem, FActiveGameplayEffectHandle Handle)
{
	return AbilitySystem->GetEffectContextFromActiveGEHandle(Handle);
}

FGameplayAbilityTargetDataHandle UCOAbilitySystemFunctionLibrary::GetTargetDataHandleFromActiveEffect(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag EffectTag)
{
	return UCOGameplayAbilityBase::GetTargetDataFromAbilitySystemActiveEffect(AbilitySystemComponent,
		FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(EffectTag.GetSingleTagContainer()));
}

TArray<AActor*> UCOAbilitySystemFunctionLibrary::GetEffectContextTargetActors(UAbilitySystemComponent* AbilitySystem, FActiveGameplayEffectHandle Effect)
{
	auto GEHandle = UCOAbilitySystemFunctionLibrary::GetEffectContextFromActiveGEHandle(AbilitySystem, Effect);
	auto Context = static_cast<FCOGameplayEffectContext*>(GEHandle.Get());

	return UAbilitySystemBlueprintLibrary::GetAllActorsFromTargetData(Context->TargetData);
}

AActor* UCOAbilitySystemFunctionLibrary::GetTargetActorFromEffectByTag(UAbilitySystemComponent* AbilitySystem, FGameplayTag Tag)
{
	auto Effects = AbilitySystem->GetActiveEffects(FGameplayEffectQuery::MakeQuery_MatchAllEffectTags(Tag.GetSingleTagContainer()));
	if (Effects.Num() == 0)
		return nullptr;

	auto Targets = UCOAbilitySystemFunctionLibrary::GetEffectContextTargetActors(AbilitySystem, Effects[0]);
	if (Targets.Num() == 0)
		return nullptr;

	return Targets[0];
}

UCOBuildingAsset* UCOAbilitySystemFunctionLibrary::BreakCueEffectContextTargetDataAsBuildConfiguration(FGameplayCueParameters Parameters, FVector& Center, FVector& Direction, int32& Floors)
{
	auto EffectContext = static_cast<FCOGameplayEffectContext*>(Parameters.EffectContext.Get());
	auto BuildTargetData = static_cast<const FCOBuildRequirementsTD*>(EffectContext->TargetData.Get(0));
	auto ConfigurationTargetData = static_cast<const FCOBuildConfigurationTD*>(EffectContext->TargetData.Get(1));
	auto SelectionTargetData = static_cast<const FCOBuildAllocationTD*>(EffectContext->TargetData.Get(2));

	Floors = ConfigurationTargetData->Floors;
	Center = SelectionTargetData->Center;
	Direction = SelectionTargetData->Direction;

	auto InstigatorController = EffectContext->GetInstigator()->GetInstigatorController();
	auto RootAsset = Cast<ACOPlayerController>(InstigatorController)->RootAsset;

	return RootAsset->FindBestAsset(SelectionTargetData, BuildTargetData);
}

FGameplayAbilityTargetDataHandle UCOAbilitySystemFunctionLibrary::MakeBuildConfigurationTargetDataHandle(FName BuildingName, int32 Floors)
{
	auto TargetData = new FCOBuildConfigurationTD();
	TargetData->BuildingName = BuildingName;
	TargetData->Floors = Floors;

	return FGameplayAbilityTargetDataHandle(TargetData);
}

void UCOAbilitySystemFunctionLibrary::BreakSelectionTD(FGameplayAbilityTargetDataHandle InSelectionTargetData, int32& Length, int32& Width)
{
	auto SelectionTargetData = static_cast<const FCOBuildAllocationTD*>(InSelectionTargetData.Get(0));

	Length = SelectionTargetData->Length;
	Width = SelectionTargetData->Width;
}