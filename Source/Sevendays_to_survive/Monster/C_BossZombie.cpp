// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/C_BossZombie.h"
#include "Monster/C_MonsterAnim.h"

AC_BossZombie::AC_BossZombie()
{
    SetName("BossZombie");
}

void AC_BossZombie::RushWait_Implementation()
{
    if (nullptr == AnimInstance) {
        return;
    }

    SetState(MonsterEnum::RushWait);
    AnimInstance->ChangeAnimation(MonsterEnum::RushWait);
}

void AC_BossZombie::Rush_Implementation()
{
    if (nullptr == AnimInstance) {
        return;
    }

    SetState(MonsterEnum::Rush);
    AnimInstance->ChangeAnimation(MonsterEnum::Rush);
}

bool AC_BossZombie::IsBlocked() const
{
    return IsBlockedValue;
}

void AC_BossZombie::ConsumeIsBlocked()
{
    IsBlockedValue = false;
}

void AC_BossZombie::SetName(FString _Name)
{
    MonsterName = _Name;
}
