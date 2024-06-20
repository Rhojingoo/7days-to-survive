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

	UPROPERTY(Transient)
	class UBehaviorTreeComponent* BTC;		// ��� ��Ʈ�� �Ǿ�� ����?	(���� ����)

	UPROPERTY(Transient)
	class UBlackboardComponent* BBC;		// � ���� ����Ͽ� ��Ʈ�� �ؾ� ����? (�� ����)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAIPerceptionComponent* APC;
	//class percpe

	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig;
	UPROPERTY()
	class UAISenseConfig_Hearing* HearingConfig;

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

	uint16 EnemyKeyId;			//Key�� map�̶�� �����ص� ��

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AI")
	float AISightRadius = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AI")
	float AISightDegree = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AI")
	float AIHearingRange = 1000.f;

};

