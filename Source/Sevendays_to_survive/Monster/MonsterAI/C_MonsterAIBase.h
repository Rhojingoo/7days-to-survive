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

	UPROPERTY(Transient)
	class UBehaviorTreeComponent* BTC;		// 어떻게 컨트롤 되어야 하지?	(로직 저장)

	UPROPERTY(Transient)
	class UBlackboardComponent* BBC;		// 어떤 값에 기반하여 컨트롤 해야 하지? (값 저장)
	
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

	uint16 EnemyKeyId;			//Key값 map이라고 생각해도 됨

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AI")
	float AISightRadius = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AI")
	float AISightDegree = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AI")
	float AIHearingRange = 1000.f;

};

