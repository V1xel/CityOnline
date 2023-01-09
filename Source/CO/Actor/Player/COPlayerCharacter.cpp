// Fill out your copyright notice in the Description page of Project Settings.

#include "COPlayerCharacter.h"

ACOPlayerCharacter::ACOPlayerCharacter() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACOPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	auto delegate = FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &ACOPlayerCharacter::OnActorSelected);
	_actorSelectedHandle = GetAbilitySystemComponent()->AddGameplayEventTagContainerDelegate(ListenActorSelectedTag.GetSingleTagContainer(), delegate);
}

void ACOPlayerCharacter::OnActorSelected(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	SelectedActor = const_cast<AActor*>(EventData->Target.Get());
}
