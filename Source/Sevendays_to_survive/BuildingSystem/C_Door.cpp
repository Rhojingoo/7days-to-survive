// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSystem/C_Door.h"

AC_Door::AC_Door()
{
}

void AC_Door::MapInteract()
{
	if (true == IsOpen())
	{
		Close();
	}
	else
	{
		Open();
	}
}

void AC_Door::Open()
{
    IsOpenValue = true;
}

void AC_Door::Close()
{
    IsOpenValue = false;
}

bool AC_Door::IsOpen() const
{
    return IsOpenValue;
}
