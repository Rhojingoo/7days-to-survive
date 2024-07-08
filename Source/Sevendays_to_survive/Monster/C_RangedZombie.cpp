// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/C_RangedZombie.h"
#include "Monster/C_ZombieBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "C_MonsterAnim.h"

AC_RangedZombie::AC_RangedZombie()
{
    SetName("RangedZombie");

    SpitTransformComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Spit Transform Component"));
}

void AC_RangedZombie::Shoot()
{

}

void AC_RangedZombie::Attack_Implementation()
{
    if (nullptr == AnimInstance) {
        return;
    }
    SetState(MonsterEnum::Idle);
    if (false == AnimInstance->IsPlayMontage()) {
        AnimInstance->ChangeAnimation(MonsterEnum::Attack);
    }
}

void AC_RangedZombie::RunAttack_Implementation()
{
    if (nullptr == AnimInstance) {
        return;
    }
    SetState(MonsterEnum::Run);
    if (false == AnimInstance->IsPlayMontage()) {
        AnimInstance->ChangeAnimation(MonsterEnum::RunAttack);
    }
}

void AC_RangedZombie::OnNotifyBegin()
{
    FVector SpawnLocation = GetActorLocation() + SpitTransformComponent->GetRelativeLocation();
    FVector SpawnRotation = FVector::ForwardVector;

    AC_ZombieBullet* Bullet = GetWorld()->SpawnActor<AC_ZombieBullet>(BulletClass, SpawnLocation, SpawnRotation.Rotation());
    Bullet->SetDirection(FVector{ 1.0f, 0.0f, 1.0f });
}

void AC_RangedZombie::OnNotifyEnd()
{
}

void AC_RangedZombie::SetName(FString _Name)
{
    MonsterName = _Name;
}
