// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainPlayer/C_NickMainPlayer.h"
#include "Player/Global/C_GlobalAnimInstance.h"

void AC_NickMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	GetGlobalAnimInstance()->ChangeAnimation(TEXT("Nick_Idle"));
}

void AC_NickMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_NickMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AC_NickMainPlayer::Move(const FInputActionValue& Value)
{
	Super::Move(Value);
	GetGlobalAnimInstance()->ChangeAnimation(TEXT("Nick_Walk"));
}

void AC_NickMainPlayer::Look(const FInputActionValue& Value)
{
	Super::Look(Value);
}
