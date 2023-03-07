// Fill out your copyright notice in the Description page of Project Settings.

#include "CO/Extensions/GameplayTagExtension.h"
#include "GameplayTagContainer.h"

FString UGameplayTagExtension::GetTagFirstElement(FGameplayTag Tag)
{
	FString Left;
	FString TagString = Tag.GetTagName().ToString();
	TagString.Split(FString("."), nullptr, &Left);

	return Left;
}

FString UGameplayTagExtension::GetTagSecondElement(FGameplayTag Tag)
{
	FString Left, Right;
	FString TagString = Tag.GetTagName().ToString();
	TagString.Split(FString("."), nullptr, &Right);

	return Right;
}

FString UGameplayTagExtension::GetTagThirdElement(FGameplayTag Tag)
{
	FString RightRight, Right;
	FString TagString = Tag.GetTagName().ToString();
	TagString.Split(FString("."), nullptr, &Right);
	TagString.Split(FString("."), nullptr, &RightRight);

	return RightRight;
}

bool UGameplayTagExtension::MatchesTag(FGameplayTag Tag, FString Element)
{
	return Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName(Element)));
}

bool UGameplayTagExtension::MatchesTagExact(FGameplayTag Tag, FString Element)
{
	return Tag.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName(Element)));
}

FGameplayTagContainer UGameplayTagExtension::CreateContainer(FString Tag)
{
	return FGameplayTag::RequestGameplayTag(FName(Tag)).GetSingleTagContainer();
}

FGameplayTagContainer UGameplayTagExtension::CreateContainer(FName Tag)
{
	return FGameplayTag::RequestGameplayTag(Tag).GetSingleTagContainer();
}
