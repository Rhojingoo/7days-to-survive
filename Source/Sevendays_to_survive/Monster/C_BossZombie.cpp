// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/C_BossZombie.h"
#include "Monster/C_MonsterAnim.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"

AC_BossZombie::AC_BossZombie()
{
    SetName("BossZombie");
}

void AC_BossZombie::Idle_Implementation()
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

void AC_BossZombie::Attack_Implementation()
{
    if (nullptr == AnimInstance) {
        return;
    }
    SetState(MonsterEnum::Idle);
    if (false == AnimInstance->IsPlayMontage()) {
        AnimInstance->ChangeAnimation(MonsterEnum::Attack);
    }
}

void AC_BossZombie::RunAttack_Implementation()
{
    if (nullptr == AnimInstance) {
        return;
    }
    SetState(MonsterEnum::Run);
    if (false == AnimInstance->IsPlayMontage()) {
        AnimInstance->ChangeAnimation(MonsterEnum::RunAttack);
    }
}

void AC_BossZombie::Faint_Implementation()
{
    if (nullptr == AnimInstance) {
        return;
    }

    SetState(MonsterEnum::Faint);
    AnimInstance->ChangeAnimation(MonsterEnum::Faint);
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

void AC_BossZombie::ApplyFaintSpeed()
{
    GetCharacterMovement()->MaxWalkSpeed = 0.0f;
}

void AC_BossZombie::AttackCollisionOn()
{
    AttackComponent->SetCollisionProfileName("OverlapAllDynamic");
}

void AC_BossZombie::AttackCollisionOff()
{
    AttackComponent->SetCollisionProfileName("NoCollision");
}
