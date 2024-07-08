// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/C_ScreamZombie.h"
#include "C_MonsterAnim.h"

AC_ScreamZombie::AC_ScreamZombie()
{
	SetName("ScreamZombie");
}

void AC_ScreamZombie::BeginPlay()
{
	Super::BeginPlay();
}

void AC_ScreamZombie::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AC_ScreamZombie::SetName(FString _Name)
{
	MonsterName = _Name;
}

void AC_ScreamZombie::Idle()
{
	if (nullptr == AnimInstance) 
	{
		return;
	}
	Super::Idle();
}

void AC_ScreamZombie::ShoutAttack_Implementation()
{
	if (nullptr == AnimInstance)
	{
		return;
	}
	ShoutBegin = true;
	SetState(MonsterEnum::Shout);
	//	if (false == AnimInstance->IsPlayMontage())
	//	{
	//		AnimInstance->ChangeAnimation(MonsterEnum::Shout);
	//	}
}

void AC_ScreamZombie::Attack_Implementation()
{
	if (nullptr == AnimInstance) 
	{
		return;
	}
	//Super::Attack();
	SetState(MonsterEnum::Idle);
	if (false == AnimInstance->IsPlayMontage()) 
	{
		AnimInstance->ChangeAnimation(MonsterEnum::Attack);
	}
}

void AC_ScreamZombie::RunAttack_Implementation()
{
	if (nullptr == AnimInstance) 
	{
		return;
	}
	SetState(MonsterEnum::Run);

	if (false == AnimInstance->IsPlayMontage()) 
	{
		AnimInstance->ChangeAnimation(MonsterEnum::RunAttack);
	}
}

void AC_ScreamZombie::Run(FVector _Location)
{
	if (nullptr == AnimInstance) 
	{
		return;
	}
	Super::Run(_Location);
}

void AC_ScreamZombie::Move(FVector _Location)
{
	if (nullptr == AnimInstance) 
	{
		return;
	}
	Super::Move(_Location);
}

void AC_ScreamZombie::OnAttackNotifyBegin()
{
	Super::OnAttackNotifyBegin();
}

void AC_ScreamZombie::OnAttackNotifyEnd()
{
	Super::OnAttackNotifyEnd();

	if (Shout == false)
	{
		Shout = true;
	}
}
