// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Global/C_GlobalAnimInstance.h"
#include "Player/Global/C_GlobalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "KismetAnimationLibrary.h"

void UC_GlobalAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	APawn* Pawn = TryGetPawnOwner();

	Player = Cast<AC_GlobalPlayer>(Pawn);
	GlobalPlayerMoveMent = Player->GetCharacterMovement();

}

void UC_GlobalAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (Player == nullptr)
	{
		return;
	}

	IsZoomAnim = Player->GetAImZoomCpp();
	IsFireAnim = Player->GetFireCpp();
	IsAniRunAnim = Player->GetRunCpp();
	IsCrouchAnim = GlobalPlayerMoveMent->IsCrouching();
	IsFallAnim = GlobalPlayerMoveMent->IsFalling();

	SpeedAnim = UKismetMathLibrary::VSizeXY(Player->GetVelocity());
	ZSpeedAnim = Player->GetVelocity().Z;
	PitchAnim = Player->GetPitchCPP();
	DirAnim = UKismetAnimationLibrary::CalculateDirection(Player->GetVelocity(), Player->GetActorRotation());
	PlayerCurStateAnim = Player->GetPlayerCurState();
}
