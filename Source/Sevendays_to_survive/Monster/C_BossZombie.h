// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/C_ZombieBase.h"
#include "C_BossZombie.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_BossZombie : public AC_ZombieBase
{
	GENERATED_BODY()

public:
	AC_BossZombie();

	UFUNCTION(NetMulticast, Reliable)
	void Idle() override final;
	void Idle_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void Attack() override final;
	void Attack_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void RunAttack() override final;
	void RunAttack_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void Rush();
	void Rush_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void Faint();
	void Faint_Implementation();

	bool IsBlocked() const;
	void ConsumeIsBlocked();

	void ApplyRushSpeed();
	void ApplyRunSpeed();
	void ApplyFaintSpeed();

	void AttackCollisionOn();
	void AttackCollisionOff();

private:
	void SetName(FString _Name) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool IsBlockedValue = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float RushSpeed = 1300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float RunSpeed = 600.0f;
};