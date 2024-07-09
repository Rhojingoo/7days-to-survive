// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "C_MonsterAIBase.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API AC_MonsterAIBase : public AAIController
{
	GENERATED_BODY()
	
public:

	AC_MonsterAIBase(const FObjectInitializer& _ObjectInitializer);

	virtual void OnPossess(APawn* InPawn) override;		// AI 컨트롤러는 어떤 식으로 컨트롤이 되어야 할지 알아야 한다.


	//class percpe
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

	UFUNCTION()
	void OnSightUpdated(const TArray<AActor*> &_UpdateActors);

	UFUNCTION()
	void OffSightUpdated(AActor* _ForgotActor);

	UFUNCTION()
	void OnHearingUpdated(const TArray<AActor*>& _UpdateActors);

	UFUNCTION()
	void OffHearingUpdated(AActor* _ForgotActor);

	UFUNCTION()
	bool GetIsFind() {
		return IsFind;
	}

	UFUNCTION()
	bool GetIsSound() {
		return IsSound;
	}

	class AC_ZombieBase* GetMonster() {
		return Monster;
	}

	class UC_MonsterComponent* GetMCP();

	FName EnemyKeyId = "TargetActor";			//Key값 map이라고 생각해도 됨

	FName SoundVec = "SoundVector";

	class UAIPerceptionComponent* GetAPC() { return APC; }

	class UAISenseConfig_Hearing* GetHearingConfig() { return HearingConfig; }




private:
	UPROPERTY()
	float AISightRadius = 1000.f;

	UPROPERTY()
	float AISightDegree = 150.f;

	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY()
	class UAISenseConfig_Hearing* HearingConfig;

	UPROPERTY()
	class UBehaviorTreeComponent* BTC;		// 어떻게 컨트롤 되어야 하지?	(로직 저장)

	UPROPERTY()
	class UBlackboardComponent* BBC;		// 어떤 값에 기반하여 컨트롤 해야 하지? (값 저장)

	/// <summary>
	/// 사운드 듣기 기능 컴포넌트
	/// </summary>
	UPROPERTY()
	class UAIPerceptionComponent* APC;

	UPROPERTY()
	UC_MonsterComponent* MCP;

	UPROPERTY()
	bool IsFind = false;

	UPROPERTY()
	bool IsSound = false;

	UPROPERTY()
	AC_ZombieBase* Monster = nullptr;
};

