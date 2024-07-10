// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/C_ZombieMan.h"

AC_ZombieMan::AC_ZombieMan()
{
	SetName("BaseZombie");
}

void AC_ZombieMan::BeginPlay()
{
	Super::BeginPlay();
}

void AC_ZombieMan::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AC_ZombieMan::SetName(FString _Name)
{
	MonsterName = _Name;
}

void AC_ZombieMan::Idle()
{
	Super::Idle();
}

void AC_ZombieMan::Attack()
{
	Super::Attack();
}

void AC_ZombieMan::Move(FVector _Location)
{
	Super::Move(_Location);
}