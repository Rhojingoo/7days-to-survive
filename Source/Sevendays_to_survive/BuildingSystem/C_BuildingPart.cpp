// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSystem/C_BuildingPart.h"

#include "Net/UnrealNetwork.h"

AC_BuildingPart::AC_BuildingPart()
{
    PrimaryActorTick.bCanEverTick = true;
    bReplicates = true;
}

void AC_BuildingPart::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AC_BuildingPart, Hp);
}

float AC_BuildingPart::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    ReceiveDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    return DamageAmount;
}

void AC_BuildingPart::ReceiveDamage_Implementation(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Hp -= DamageAmount;

    if (Hp <= 0.0f)
    {
        Destroy();
    }
}
