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

void UCOAbilitySystemFunctionLibrary::BreakBuildRequirementsTargetData(FGameplayAbilityTargetDataHandle Handle, int32 HandleIndex, FString& Name, int32& MinWidth, int32& MaxWidth, int32& MinLength, int32& MaxLength, int32& MinFloors, int32& MaxFloors, float& CostMultiplier, float& CapacityMultiplier)
{
	if (Handle.IsValid(HandleIndex)) 
	{
		auto BuildRequirementsTD = static_cast<FCOBuildRequirementsTD*>(Handle.Get(HandleIndex));

		Name = BuildRequirementsTD->Name;
		MinWidth = BuildRequirementsTD->MinWidth;
		MaxWidth = BuildRequirementsTD->MaxWidth;
		MinLength = BuildRequirementsTD->MinLength;
		MaxLength = BuildRequirementsTD->MaxLength;
		MinFloors = BuildRequirementsTD->MinFloors;
		MaxFloors = BuildRequirementsTD->MaxFloors;
		CostMultiplier = BuildRequirementsTD->CostMultiplier;
		CapacityMultiplier = BuildRequirementsTD->CapacityMultiplier;
	}
}

void UCOAbilitySystemFunctionLibrary::BreakBuildAllocationTargetData(FGameplayAbilityTargetDataHandle Handle, int32 HandleIndex, AActor*& Target, int32& Length, int32& Width, int32& ExtremeCount, FVector& Center, FVector& Direction, bool& HasOccupiedCells)
{
	if (Handle.IsValid(HandleIndex)) 
	{
		auto BuildRequirementsTD = static_cast<FCOBuildAllocationTD*>(Handle.Get(HandleIndex));

		Target = BuildRequirementsTD->Target;
		Length = BuildRequirementsTD->Length;
		Width = BuildRequirementsTD->Width;
		ExtremeCount = BuildRequirementsTD->ExtremeCount;
		Center = BuildRequirementsTD->Center;
		Direction = BuildRequirementsTD->Direction;
		HasOccupiedCells = BuildRequirementsTD->HasOccupiedCells;
	}
}

void UCOAbilitySystemFunctionLibrary::BreakBuildConfigurationTD(FGameplayAbilityTargetDataHandle Handle, int32 HandleIndex, int32& Floors, FName& BuildingName)
{
	if (Handle.IsValid(HandleIndex))
	{
		auto BuildRequirementsTD = static_cast<FCOBuildConfigurationTD*>(Handle.Get(HandleIndex));

		Floors = BuildRequirementsTD->Floors;
		BuildingName = BuildRequirementsTD->BuildingName;
	}
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