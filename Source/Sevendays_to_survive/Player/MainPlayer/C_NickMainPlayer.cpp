// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainPlayer/C_NickMainPlayer.h"
#include "Player/Global/C_GlobalAnimInstance.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"


void AC_NickMainPlayer::PunchAtt_Implementation(const FInputActionValue& Value)
{
	
	IsAttCpp = true;
}

void AC_NickMainPlayer::PunchAttEnd_Implementation(const FInputActionValue& Value)
{
	IsAttCpp = false;
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

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);


		// Moving
		//EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AC_NickMainPlayer::MoveStart);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AC_GlobalPlayer::Move);
		//EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AC_NickMainPlayer::IdleStart);

		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AC_GlobalPlayer::RunStart);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AC_GlobalPlayer::RunEnd);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AC_GlobalPlayer::Look);

		// Looking
		EnhancedInputComponent->BindAction(AttAction, ETriggerEvent::Started, this, &AC_NickMainPlayer::PunchAtt);
		EnhancedInputComponent->BindAction(AttAction, ETriggerEvent::Completed, this, &AC_NickMainPlayer::PunchAttEnd);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

