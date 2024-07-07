// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/C_BasicZombie.h"
#include "C_MonsterAnim.h"
AC_BasicZombie::AC_BasicZombie()
{
	SetName("BaseZombie");
}

void AC_BasicZombie::BeginPlay()
{
	Super::BeginPlay();
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

void AC_BasicZombie::Attack_Implementation()
{
	//Super::Attack();
	SetState(MonsterEnum::Idle);
	if (false == AnimInstance->IsPlayMontage()) {
		if (FMath::RandBool())
		{
			AnimInstance->ChangeAnimation(MonsterEnum::Attack);
		}
		else
		{
			AnimInstance->ChangeAnimation(MonsterEnum::RunAttack);
		}
	}
}

void AC_BasicZombie::RunAttack_Implementation()
{
	SetState(MonsterEnum::Run);
	if (false == AnimInstance->IsPlayMontage()) {
		if (FMath::RandBool())
		{
			AnimInstance->ChangeAnimation(MonsterEnum::Attack);
		}
		else
		{
			AnimInstance->ChangeAnimation(MonsterEnum::RunAttack);
		}
	}
}

void AC_BasicZombie::Run(FVector _Location)
{
	Super::Run(_Location);
}

void AC_BasicZombie::Move(FVector _Location)
{
	Super::Move(_Location);
}
