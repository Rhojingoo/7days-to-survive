// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/C_BasicZombie.h"

void AC_BasicZombie::BeginPlay()
{
	Super::BeginPlay();
	SetName("BaseZombie");
}

void AC_BasicZombie::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AC_BasicZombie::SetName(FString _Name)
{
	MonsterName = _Name;
}

void AC_BasicZombie::Idle()
{
	Super::Idle();
}

void AC_BasicZombie::Move(FVector _Location)
{
	Super::Move(_Location);
}
