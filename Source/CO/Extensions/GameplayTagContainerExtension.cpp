// Fill out your copyright notice in the Description page of Project Settings.


#include "CO/Extensions/GameplayTagContainerExtension.h"
#include "GameplayTagContainer.h"

FString UGameplayTagContainerExtension::GetTagFirstElement(FGameplayTag Tag)
{
	FString Left;
	FString TagString = Tag.GetTagName().ToString();
	TagString.Split(FString("."), nullptr, &Left);

	return Left;
}

FString UGameplayTagContainerExtension::GetTagSecondElement(FGameplayTag Tag)
{
	FString Left, Right;
	FString TagString = Tag.GetTagName().ToString();
	TagString.Split(FString("."), nullptr, &Right);

	return Right;
}

FString UGameplayTagContainerExtension::GetTagThirdElement(FGameplayTag Tag)
{
	FString RightRight, Right;
	FString TagString = Tag.GetTagName().ToString();
	TagString.Split(FString("."), nullptr, &Right);
	TagString.Split(FString("."), nullptr, &RightRight);

	return RightRight;
}
