// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "COAbilitySystemFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CO_API UCOAbilitySystemFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable)
	static FGameplayEffectContextHandle GetEffectContextFromActiveGEHandle(UAbilitySystemComponent* AbilitySystem, FActiveGameplayEffectHandle Handle);

	UFUNCTION(BlueprintPure)
	static FGameplayAbilityTargetDataHandle GetTargetDataHandleFromActiveEffect(UAbilitySystemComponent* AbilitySystemComponent, FGameplayTag EffectTag);

	UFUNCTION(BlueprintPure)
	static TArray<AActor*> GetEffectContextTargetActors(UAbilitySystemComponent* AbilitySystem, FActiveGameplayEffectHandle Effect);

	UFUNCTION(BlueprintPure)
	static AActor* GetTargetActorFromEffectByTag(UAbilitySystemComponent* AbilitySystem, FGameplayTag Tag);

	UFUNCTION(BlueprintPure, meta = (NativeBreakFunc, AdvancedDisplay = 6))
	static void BreakBuildRequirementsTargetData(FGameplayAbilityTargetDataHandle Handle, int32 HandleIndex, FString& Name, int32& MinWidth, int32& MaxWidth, int32& MinLength, int32& MaxLength, int32& MinFloors, int32& MaxFloors, float& CostMultiplier, float& CapacityMultiplier);

	UFUNCTION(BlueprintPure, meta = (NativeBreakFunc, AdvancedDisplay = 6))
	static void BreakBuildAllocationTargetData(FGameplayAbilityTargetDataHandle Handle, int32 HandleIndex, AActor*& Target, int32& Length, int32& Width, int32& ExtremeCount, FVector& Center, FVector& Direction, bool& HasOccupiedCells);
	
	UFUNCTION(BlueprintPure, meta = (NativeBreakFunc, AdvancedDisplay = 6))
	static void BreakBuildConfigurationTD(FGameplayAbilityTargetDataHandle Handle, int32 HandleIndex, int32& Floors, FName& BuildingName);

	UFUNCTION(BlueprintPure)
	static FGameplayAbilityTargetDataHandle MakeBuildConfigurationTargetDataHandle(FName BuildingName, int32 Floors);

	UFUNCTION(BlueprintPure, meta = (NativeBreakFunc, AdvancedDisplay = 6))
	static UCOBuildingAsset* BreakCueEffectContextTargetDataAsBuildConfiguration(FGameplayCueParameters Parameters, FVector& Center, FVector& Direction, int32& Floors);

	UFUNCTION(BlueprintPure, meta = (NativeBreakFunc, AdvancedDisplay = 6))
	static void BreakSelectionTD(FGameplayAbilityTargetDataHandle InSelectionTargetData, int32& Length, int32& Width);
};
