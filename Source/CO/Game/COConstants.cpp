#include "COConstants.h"
#include "GameplayTagContainer.h"

FGameplayTag UCOGameplayTags::Allocate()
{
	return FGameplayTag().RequestGameplayTag("Action.Allocate");
}

FGameplayTag UCOGameplayTags::AllocateCancel()
{
	return FGameplayTag().RequestGameplayTag("Action.Allocate.Cancel");
}

FGameplayTag UCOGameplayTags::AllocateFinished()
{
	return FGameplayTag().RequestGameplayTag("Action.Allocate.Finished");
}

FGameplayTag UCOGameplayTags::Construct()
{
	return FGameplayTag().RequestGameplayTag("Action.Construct");
}

FGameplayTag UCOGameplayTags::ConstructCancel()
{
	return FGameplayTag().RequestGameplayTag("Action.Construct.Cancel");
}

FGameplayTag UCOGameplayTags::ConstructFinished()
{
	return FGameplayTag().RequestGameplayTag("Action.Construct.Finished");
}
