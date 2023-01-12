// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Actor/Street/Abilities/COCreateStreetCellsAbility.h"
#include <CO/Actor/Street/Components/COStreetCellComponent.h>
#include <CO/Actor/Street/COStreetActor.h>

void UCOCreateStreetCellsAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const auto Owner = Cast<ACOStreetActor>(ActorInfo->OwnerActor);
	const auto HorizontalOffset = Coverage * Scale.X / (Horizontal - 1);
	const auto VerticalOffset = Coverage * Scale.Y / (Vertical - 1);
	const auto Origin = Owner->GetActorLocation();
	const auto WorldOffset = Origin - Coverage * Extent;

	for (int iHorizontal = 0; iHorizontal <= Horizontal - 1; ++iHorizontal)
	{
		for (int iVertical = 0; iVertical <= Vertical - 1; ++iVertical)
		{
			auto CellOffset = FVector(HorizontalOffset * iHorizontal, VerticalOffset * iVertical, 1);
			const FVector Position = CellOffset + WorldOffset;

			auto Cell = Cast<UCOStreetCellComponent>(Owner->AddComponentByClass(UCOStreetCellComponent::StaticClass(), true, FTransform(FRotator::ZeroRotator, Position, FVector(Size, Size, 1)), false));
			Cell->Horizontal = iHorizontal + 1;
			Cell->Vertical = iVertical + 1;
			Cell->IsExtreme = iHorizontal == 0 || iVertical == 0 || iHorizontal == (Horizontal - 1) || iVertical == (Vertical - 1);
			Cell->IsCorner = ((iHorizontal == iVertical) && Cell->IsExtreme) || (iHorizontal == Horizontal - 1 && iVertical == 0) || (iVertical == Vertical - 1 && iHorizontal == 0);
			Cell->SetIsReplicated(true);

			Owner->Cells.Add(Cell);
		}
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UCOCreateStreetCellsAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
