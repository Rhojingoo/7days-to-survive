// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/C_BossZombie.h"
#include "Monster/C_MonsterAnim.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"

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

void AC_BossZombie::ApplyRushSpeed()
{
    GetCharacterMovement()->MaxWalkSpeed = RushSpeed;
}

void AC_BossZombie::ApplyRunSpeed()
{
    GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AC_BossZombie::AttackCollisionOn()
{
    AttackComponent->SetCollisionProfileName("OverlapAllDynamic");
}

void AC_BossZombie::AttackCollisionOff()
{
    AttackComponent->SetCollisionProfileName("NoCollision");
}
