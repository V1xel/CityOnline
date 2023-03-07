// Fill out your copyright notice in the Description page of Project Settings.


#include "COEQT_GameplayTags.h"

void UCOEQT_GameplayTags::RunTest(FEnvQueryInstance& QueryInstance) const
{
	UObject* QueryOwner = QueryInstance.Owner.Get();
	if (QueryOwner == nullptr)
		return;

	BoolValue.BindData(QueryOwner, QueryInstance.QueryID);
	bool bWantsValid = BoolValue.GetValue();

	//FilterByTag.BindData(QueryOwner, QueryInstance.QueryID);
	const FName TagToFilterName = FilterByTag.GetValue();

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		const AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());
		if (const IGameplayTagAssetInterface* GameplayTagAssetInterface = Cast<const IGameplayTagAssetInterface>(ItemActor))
		{
			bool bSatisfiesTest = GameplayTagAssetInterface->HasAllMatchingGameplayTags(FGameplayTag::RequestGameplayTag(TagToFilterName).GetSingleTagContainer());

			It.SetScore(TestPurpose, FilterType, bSatisfiesTest, bWantsValid);
		}
		else
		{
			It.ForceItemState(EEnvItemStatus::Failed);
		}
	}
}

FText UCOEQT_GameplayTags::GetDescriptionTitle() const
{
	return FText::FromString("Filter by All Gameplay Tags");
}

FText UCOEQT_GameplayTags::GetDescriptionDetails() const
{
	return FText::FromString("Filters the query results using given tags");
}

FAIDataProviderFNameValue::FAIDataProviderFNameValue()
	: DefaultValue()
{
	DataField = FNameProperty::StaticClass()->GetFName();
	PropertyType = FNameProperty::StaticClass();
}

FName FAIDataProviderFNameValue::GetValue() const
{
	FName* PropValue = GetRawValuePtr<FName>();
	return PropValue ? *PropValue : DefaultValue;
}

FString FAIDataProviderFNameValue::ValueToString() const
{
	return DefaultValue.ToString();
}

bool FAIDataProviderFNameValue::Serialize(FArchive& Ar)
{
	return FAIDataProviderTypedValue::Serialize(Ar);
}
