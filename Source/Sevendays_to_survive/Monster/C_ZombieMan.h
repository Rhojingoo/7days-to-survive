// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/C_ZombieBase.h"
#include "C_ZombieMan.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_ZombieMan : public AC_ZombieBase
{
	GENERATED_BODY()
	
public:
	AC_ZombieMan();

	void BeginPlay() override final;
	void Tick(float _DeltaTime) override final;
	void SetName(FString _Name) override final;
	void Idle() override final;
	void Attack() override final;
	void Move(FVector _Location) override final;
};
