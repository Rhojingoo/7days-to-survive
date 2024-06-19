// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/C_ZombieBase.h"

// Sets default values
AC_ZombieBase::AC_ZombieBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AC_ZombieBase::BeginPlay()
{
	Super::BeginPlay();
	
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

