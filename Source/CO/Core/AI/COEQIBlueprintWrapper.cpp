// Fill out your copyright notice in the Description page of Project Settings.


#include "COEQIBlueprintWrapper.h"

bool UCOEQIBlueprintWrapper::GetQueryResultsAsFilteredActors(TArray<AActor*>& ResultActors, FGameplayTagContainer AllTagsToFilter) const
{
	TArray<AActor*> QueriedActors;
	auto LocalQueryResult = GetQueryResultsAsActors(QueriedActors);
	ResultActors = QueriedActors.FilterByPredicate([AllTagsToFilter](AActor* ItemActor)
		{
			if (const IGameplayTagAssetInterface* GameplayTagAssetInterface = Cast<const IGameplayTagAssetInterface>(ItemActor))
			{
				return GameplayTagAssetInterface->HasAllMatchingGameplayTags(AllTagsToFilter);
			}

			return false;
		});

	return LocalQueryResult && ResultActors.Num() > 0;
}
