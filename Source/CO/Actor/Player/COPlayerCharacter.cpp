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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Select SUB");
}

void ACOPlayerCharacter::OnActorSelected(FGameplayTag Tag, const FGameplayEventData* EventData)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Select TICK");
	SelectedActor = const_cast<AActor*>(EventData->Target.Get());
}
