// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/C_ZombieMan.h"
#include "C_MonsterAnim.h"

AC_ZombieMan::AC_ZombieMan()
{
	SetName("ZombieMan");
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

//void AC_ZombieMan::Idle()
//{
//	if (nullptr == AnimInstance) 
//	{
//		return;
//	}
//
//	Super::Idle();
//}

void AC_ZombieMan::Idle_Implementation()
{
	if (nullptr == AnimInstance) 
	{
		return;
	}

	SetState(MonsterEnum::Idle);

	if (false == AnimInstance->IsPlayMontage())
	{
		AnimInstance->ChangeAnimation(MonsterEnum::Idle);
	}
}

//void AC_ZombieMan::Attack()
//{
//	if (nullptr == AnimInstance) 
//	{
//		return;
//	}
//
//	Super::Attack();
//}

void AC_ZombieMan::Attack_Implementation()
{
	if (nullptr == AnimInstance) {
		return;
	}

	SetState(MonsterEnum::Idle);

	if (false == AnimInstance->IsPlayMontage())
	{
		AnimInstance->ChangeAnimation(MonsterEnum::Attack);
	}
}

void AC_ZombieMan::Run(FVector _Location)
{
	if (nullptr == AnimInstance)
	{
		return;
	}

	Super::Run(_Location);
}

void AC_ZombieMan::RunAttack_Implementation()
{
	if (nullptr == AnimInstance) {
		return;
	}

	SetState(MonsterEnum::Run);

	if (false == AnimInstance->IsPlayMontage())
	{
		AnimInstance->ChangeAnimation(MonsterEnum::RunAttack);
	}
}

void AC_ZombieMan::Move(FVector _Location)
{
	if (nullptr == AnimInstance)
	{
		return;
	}

	Super::Move(_Location);
}

void AC_ZombieMan::MonsterJump_Implementation()
{
	if (nullptr == AnimInstance) {
		return;
	}

	SetState(MonsterEnum::Jump);

	AnimInstance->ChangeAnimation(MonsterEnum::Jump);
	Jump();
}