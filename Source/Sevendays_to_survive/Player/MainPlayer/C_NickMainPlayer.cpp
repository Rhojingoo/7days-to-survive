// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainPlayer/C_NickMainPlayer.h"
#include "Player/Global/C_GlobalAnimInstance.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Player/Global/C_PlayerEnum.h"
#include "Player/Input/C_InputActionDatas.h"
#include "Components/ArrowComponent.h"






AC_NickMainPlayer::AC_NickMainPlayer()
{
	LocationComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("LocationComponent"));
	LocationComponent->SetupAttachment(RootComponent); // RootComponent에 부착
}

FVector AC_NickMainPlayer::GetComponentLocation()
{
	FVector Location = LocationComponent->GetComponentLocation();
	return Location;
}

void AC_NickMainPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//DOREPLIFETIME(AC_NickMainPlayer, MontageToPlay);
}

void AC_NickMainPlayer::BeginPlay()
{
	Super::BeginPlay();

}

void AC_NickMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AC_NickMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
}

