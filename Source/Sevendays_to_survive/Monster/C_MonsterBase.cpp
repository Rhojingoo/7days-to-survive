// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/C_MonsterBase.h"

// Sets default values
AC_MonsterBase::AC_MonsterBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_MonsterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_MonsterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_MonsterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

