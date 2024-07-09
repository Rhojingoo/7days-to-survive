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
	void RushWait();
	void RushWait_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void Rush();
	void Rush_Implementation();

private:
	void SetName(FString _Name) override;
};
