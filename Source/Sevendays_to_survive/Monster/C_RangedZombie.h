// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/C_ZombieBase.h"
#include "Components/SphereComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "C_RangedZombie.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_RangedZombie : public AC_ZombieBase
{
	GENERATED_BODY()
	
public:
	AC_RangedZombie();

	void Shoot();

	UFUNCTION(NetMulticast, Reliable)
	void Attack() override final;
	void Attack_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void RunAttack() override final;
	void RunAttack_Implementation();

	void OnNotifyBegin() override;
	void OnNotifyEnd() override;

private:
	void SetName(FString _Name) override;
	AActor* GetTargetActor();
	float GetHorizontalDistance(FVector v1, FVector v2);
	float SolveQuadraticEquation(float a, float b, float c);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* SpitTransformComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> BulletClass = nullptr;
};
