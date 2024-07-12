// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Player/Global/C_PlayerEnum.h"
#include "C_GlobalAnimInstance.generated.h"

class UAnimMontage;
class AC_GlobalPlayer;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_GlobalAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:

protected:
	void NativeBeginPlay() override;
	void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
private:
	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AC_GlobalPlayer* Player = nullptr;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCharacterMovementComponent* GlobalPlayerMoveMent = nullptr;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsZoomAnim = false;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsFireAnim = false;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsCrouchAnim = false;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsAniRunAnim = false;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsFallAnim = false;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float SpeedAnim = 0.0f;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float ZSpeedAnim = 0.0f;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AniDirAnim = 0.0f;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PitchAnim = 0.0f;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DirAnim = 0.0f;

	UPROPERTY(Category = "Contents", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EWeaponUseState PlayerCurStateAnim = EWeaponUseState::NoWeapon;

};
