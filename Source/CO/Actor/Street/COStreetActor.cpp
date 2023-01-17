// Fill out your copyright notice in the Description page of Project Settings.


#include "COStreetActor.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayEffectApplied.h"
#include "CO/Core/AbilitySystem/COAbilitySystemComponent.h"
#include "CO/Actor/Building/COBuildingActor.h"


ACOStreetActor::ACOStreetActor()
{
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	AbilitySystemComponent = CreateDefaultSubobject<UCOAbilitySystemComponent>("AbilitySystem");
	SceneComponent->SetMobility(EComponentMobility::Static);
	SetRootComponent(SceneComponent);
}

void ACOStreetActor::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	auto AsyncTask = UAbilityAsync_WaitGameplayEffectApplied::WaitGameplayEffectAppliedToActor(this, FGameplayTargetDataFilterHandle(), FGameplayTagRequirements(), FGameplayTagRequirements());
	AsyncTask->OnApplied.AddDynamic(this, &ACOStreetActor::OnEffectApplied);

	FOnAppliedDelegate DeployEffectAppliedDelegate;
	DeployEffectAppliedDelegate.AddDynamic(this, &ACOStreetActor::PendingDeployEffectApplied);
	OnAppliedMap.Add(ListenBuildingDeployEffectAppliedTag, DeployEffectAppliedDelegate);
}

void ACOStreetActor::OnEffectApplied(AActor* Source, FGameplayEffectSpecHandle SpecHandle, FActiveGameplayEffectHandle ActiveHandle)
{
	auto GameplayEffectSpec = SpecHandle.Data.Get();
	auto EffectContextHandle = GameplayEffectSpec->GetContext();

	FGameplayTagContainer Container;
	GameplayEffectSpec->GetAllGrantedTags(Container);
	TArray<FGameplayTag> TagsArray;
	Container.GetGameplayTagArray(TagsArray);

	for (auto Tag : TagsArray)
	{
		auto AssignedDelegate = OnAppliedMap.Find(Tag);
		AssignedDelegate->Broadcast(EffectContextHandle);
	}
}
