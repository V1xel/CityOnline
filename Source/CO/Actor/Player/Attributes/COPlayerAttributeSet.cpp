// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Actor/Player/Attributes/COPlayerAttributeSet.h"
#include "COPlayerAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UCOPlayerAttributeSet::OnRep_Money(const FGameplayAttributeData& OldMoney)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCOPlayerAttributeSet, Money, OldMoney);
}

void UCOPlayerAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCOPlayerAttributeSet, Money, COND_None, REPNOTIFY_Always);
}