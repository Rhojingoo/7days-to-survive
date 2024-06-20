// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainPlayer/C_TestChar_Coach.h"

// Sets default values
AC_TestChar_Coach::AC_TestChar_Coach()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void AC_TestChar_Coach::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_TestChar_Coach::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_TestChar_Coach::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

