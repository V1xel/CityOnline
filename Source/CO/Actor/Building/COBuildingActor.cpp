// Fill out your copyright notice in the Description page of Project Settings.


#include "COBuildingActor.h"
#include "CO/Database/Assets/COBuildingAsset.h"
#include "CO/AbilitySystem/COAbilitySystemComponent.h"
#include "CO/Actor/Player/Abilities/DTO/COConstructionDTO.h"

// Sets default values
ACOBuildingActor::ACOBuildingActor()
{
}

void ACOBuildingActor::ApplyChanges()
{
	AbilitySystemComponent->OnGameplayEffectAppliedDelegateToTarget.AddLambda([&](
		UAbilitySystemComponent* Target,
		const FGameplayEffectSpec& SpecApplied,
		FActiveGameplayEffectHandle ActiveHandle)
	{
		for (auto Attribute : SpecApplied.ModifiedAttributes)
		{
			auto value = Attribute.Attribute.GetNumericValue(BuildingAttributeSet);
		}
		
	});
}

void ACOBuildingActor::RemoveActor()
{
	Meshes.Empty();
	Destroy();
}

void ACOBuildingActor::ComposeBuilding()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("ComposeBuilding!"));
	auto floors = Configuration->Floors;
	Meshes.Empty();
	for (size_t i = 0; i <= floors; i++)
	{
		auto Mesh = Cast<UStaticMeshComponent>(AddComponentByClass(UStaticMeshComponent::StaticClass(), false, FTransform::Identity, false));
		if (Mesh)
		{
			Meshes.Add(Mesh);
			if (i == 0) {
				Mesh->SetStaticMesh(BuildingAsset->FirstFloor);
			}
			else if (i <= floors) {
				Mesh->SetStaticMesh(BuildingAsset->MiddleFloor);
				Mesh->SetRelativeLocation(FVector(0, 0, BuildingAsset->FloorHeight * (i - 1)));
			}
		}
	}

	auto Roof = Cast<UStaticMeshComponent>(AddComponentByClass(UStaticMeshComponent::StaticClass(), false, FTransform::Identity, false));
	Roof->SetStaticMesh(BuildingAsset->Roof);
	Roof->SetRelativeLocation(FVector(0, 0, BuildingAsset->FloorHeight * (floors - 1)));
}

void ACOBuildingActor::SelectActor_Implementation()
{
	ICOSelectableActor::SelectActor_Implementation();
}

void ACOBuildingActor::DeselectActor_Implementation()
{
	ICOSelectableActor::DeselectActor_Implementation();
}


