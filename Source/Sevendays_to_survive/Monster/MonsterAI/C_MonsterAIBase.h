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

	virtual void OnPossess(APawn* InPawn) override;		// AI ��Ʈ�ѷ��� � ������ ��Ʈ���� �Ǿ�� ���� �˾ƾ� �Ѵ�.


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

	FName EnemyKeyId = "TargetActor";			//Key�� map�̶�� �����ص� ��

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
	class UBehaviorTreeComponent* BTC;		// ��� ��Ʈ�� �Ǿ�� ����?	(���� ����)

	UPROPERTY()
	class UBlackboardComponent* BBC;		// � ���� ����Ͽ� ��Ʈ�� �ؾ� ����? (�� ����)

	/// <summary>
	/// ���� ��� ��� ������Ʈ
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

