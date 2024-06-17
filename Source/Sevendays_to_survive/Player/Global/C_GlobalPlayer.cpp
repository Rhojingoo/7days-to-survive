// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Global/C_GlobalPlayer.h"

// Sets default values
AC_GlobalPlayer::AC_GlobalPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_GlobalPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_GlobalPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_GlobalPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

