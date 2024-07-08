// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/C_RangedZombie.h"
#include "Monster/C_ZombieBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Monster/MonsterAI/C_MonsterAIBase.h"
#include "Kismet/KismetMathLibrary.h"
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

    AActor* TargetActor = GetTargetActor();
    FVector TargetLocation = TargetActor->GetActorLocation() + FVector{ 0.0f, 0.0f, TargetHeight };

    float d = GetHorizontalDistanceTo(TargetActor);
    float g = -GetWorld()->GetGravityZ();
    float s = Bullet->GetInitialSpeed();

    float a = (d * d * g) / (2 * s * s);
    float b = -d;
    float c = (d * d * g) / (2 * s * s) + (TargetLocation - GetActorLocation()).Z;

    float tangent = SolveQuadraticEquation(a, b, c);

    FVector Direction2D = TargetLocation - GetActorLocation();
    Direction2D.Z = 0.0f;
    Direction2D.Normalize();

    FVector Direction = Direction2D + FVector{ 0.0f, 0.0f, tangent };
    Direction.Normalize();

    Bullet->SetDirection(Direction);
}

void AC_RangedZombie::OnNotifyEnd()
{
}

void AC_RangedZombie::SetName(FString _Name)
{
    MonsterName = _Name;
}

AActor* AC_RangedZombie::GetTargetActor()
{
    AC_MonsterAIBase* AIController = Cast<AC_MonsterAIBase>(GetController());
    UObject* TargetObject = AIController->GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor"));
    return Cast<AActor>(TargetObject);
}

float AC_RangedZombie::SolveQuadraticEquation(float a, float b, float c)
{
    // x = (-b +- sqrt(b^2 - 4ac)) / 2a;

    float first = (-b + UKismetMathLibrary::Sqrt(b * b - 4 * a * c)) / (2 * a);
    float second = (-b - UKismetMathLibrary::Sqrt(b * b - 4 * a * c)) / (2 * a);

    if (-2 <= first && first <= 2)
    {
        return first;
    }

    return second;
}
