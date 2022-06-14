// Fill out your copyright notice in the Description page of Project Settings.


#include "COCharacterBase.h"

ACOCharacterBase::ACOCharacterBase()
{
}

void ACOCharacterBase::Select()
{
	IsSelected = true;
}

void ACOCharacterBase::Deselect()
{
	IsSelected = false;
}
