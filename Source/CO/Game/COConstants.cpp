#include "COConstants.h"
#include "GameplayTagContainer.h"

FGameplayTag UCOGameplayTags::GetAllocate()
{
	return FGameplayTag().RequestGameplayTag("Action.Allocate");
}

FGameplayTag UCOGameplayTags::GetAllocateCancel()
{
	return FGameplayTag().RequestGameplayTag("Action.Allocate.Cancel");
}

FGameplayTag UCOGameplayTags::GetAllocateFinished()
{
	return FGameplayTag().RequestGameplayTag("Action.Allocate.Finished");
}

FGameplayTag UCOGameplayTags::GetConstruct()
{
	return FGameplayTag().RequestGameplayTag("Action.Construct");
}

FGameplayTag UCOGameplayTags::GetConstructCancel()
{
	return FGameplayTag().RequestGameplayTag("Action.Construct.Cancel");
}

FGameplayTag UCOGameplayTags::GetConstructFinished()
{
	return FGameplayTag().RequestGameplayTag("Action.Construct.Finished");
}
