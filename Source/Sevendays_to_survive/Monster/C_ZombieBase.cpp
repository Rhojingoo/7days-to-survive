// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/C_ZombieBase.h"
#include "Net/UnrealNetwork.h"
// Sets default values
AC_ZombieBase::AC_ZombieBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

// Called when the game starts or when spawned
void AC_ZombieBase::BeginPlay()
{
	Super::BeginPlay();
	MonsterState = MonsterEnum::Idle;
}

// Called every frame
void AC_ZombieBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

// Called to bind functionality to input
void AC_ZombieBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AC_ZombieBase::Idle()
{
}

void AC_ZombieBase::Move(FVector _Location)
{
	AddMovementInput(_Location);
}

MonsterEnum AC_ZombieBase::GetState()
{
	return MonsterState;
}

bool AC_ZombieBase::SetState_Validate(MonsterEnum _Enum)
{
	return true;
}

void AC_ZombieBase::SetState_Implementation(MonsterEnum _Enum)
{
	MonsterState = _Enum;
}

void AC_ZombieBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AC_ZombieBase, MonsterState);
}

//void AC_ZombieBase::GetDataFromName()
//{
//}

