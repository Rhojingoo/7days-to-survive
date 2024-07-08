// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/C_RangedZombie.h"

AC_RangedZombie::AC_RangedZombie()
{
    SetName("RangedZombie");
}

void AC_RangedZombie::Shoot()
{

}

void AC_RangedZombie::Attack_Implementation()
{

}

void AC_RangedZombie::RunAttack_Implementation()
{

}

void AC_RangedZombie::SetName(FString _Name)
{
    MonsterName = _Name;
}
