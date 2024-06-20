// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainPlayer/C_NickMainPlayer.h"
#include "Player/Global/C_GlobalAnimInstance.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"


void AC_NickMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	Ani = EPlayerState::Idle;
	GlobalAnim = Cast<UC_GlobalAnimInstance>(GetMesh()->GetAnimInstance());
	GlobalAnim->ChangeAnimation(Ani);
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
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AC_NickMainPlayer::Move);
		//EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AC_NickMainPlayer::IdleStart);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AC_NickMainPlayer::Look);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AC_NickMainPlayer::Move(const FInputActionValue& Value)
{
	Super::Move(Value);
}


void AC_NickMainPlayer::Look(const FInputActionValue& Value)
{
	Super::Look(Value);
}

void AC_NickMainPlayer::IdleStart()
{
	Super::IdleStart();
	Ani = EPlayerState::Idle;
	GlobalAnim->ChangeAnimation(Ani);
}

void AC_NickMainPlayer::MoveStart()
{
	Super::MoveStart();
	Ani = EPlayerState::Walk;
	GlobalAnim->ChangeAnimation(Ani);
}

void AC_NickMainPlayer::JumpStart()
{
	Super::JumpStart();
}
