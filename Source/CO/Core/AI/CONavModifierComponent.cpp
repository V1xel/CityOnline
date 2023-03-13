// Fill out your copyright notice in the Description page of Project Settings.


#include "CONavModifierComponent.h"

void UCONavModifierComponent::GetNavigationData(FNavigationRelevantData& Data) const
{
	Data.Modifiers.Add(FAreaNavModifier(NavExtent, GetOwner()->GetActorTransform(), AreaClass).SetIncludeAgentHeight(bIncludeAgentHeight));
}
