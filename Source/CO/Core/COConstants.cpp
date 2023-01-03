#include "COConstants.h"
#include "GameplayTagContainer.h"

FGameplayTag UCOGameplayTags::Select()
{
	return FGameplayTag().RequestGameplayTag("Action.Select");
}

FGameplayTag UCOGameplayTags::Build()
{
	return FGameplayTag().RequestGameplayTag("Action.Build");
}

FGameplayTag UCOGameplayTags::BuildCancel()
{
	return FGameplayTag().RequestGameplayTag("Action.Build.Cancel");
}

FGameplayTag UCOGameplayTags::BuildFinished()
{
	return FGameplayTag().RequestGameplayTag("Action.Build.Finished");
}

FGameplayTag UCOGameplayTags::Allocate()
{
	return FGameplayTag().RequestGameplayTag("Action.Allocate");
}

FGameplayTag UCOGameplayTags::AllocateCancel()
{
	return FGameplayTag().RequestGameplayTag("Cancel.Action.Allocate");
}

FGameplayTag UCOGameplayTags::AllocateFinished()
{
	return FGameplayTag().RequestGameplayTag("Finished.Action.Allocate");
}

FGameplayTag UCOGameplayTags::UpdatedAllocation()
{
	return FGameplayTag().RequestGameplayTag("Updated.Allocation");
}

FGameplayTag UCOGameplayTags::UpdatedConfiguration()
{
	return FGameplayTag().RequestGameplayTag("Updated.Configuration");
}

FGameplayTag UCOGameplayTags::Construct()
{
	return FGameplayTag().RequestGameplayTag("Action.Construct");
}

FGameplayTag UCOGameplayTags::ConstructCancel()
{
	return FGameplayTag().RequestGameplayTag("Action.Construct.Cancel");
}

FGameplayTag UCOGameplayTags::ConstructConfigurate()
{
	return FGameplayTag().RequestGameplayTag("Action.Construct.Configurate");
}

FGameplayTag UCOGameplayTags::ConstructFinished()
{
	return FGameplayTag().RequestGameplayTag("Action.Construct.Finished");
}


