// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainController/C_MainPlayerController.h"
#include "EnhancedInputSubsystems.h"

FGenericTeamId AC_MainPlayerController::GetGenericTeamId() const
{
	return PlayerTeamId;
}

void AC_MainPlayerController::SetGenericTeamId(const FGenericTeamId& TeamID)
{
	PlayerTeamId = TeamID;
}

void AC_MainPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetGenericTeamId(0);
	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}
}
