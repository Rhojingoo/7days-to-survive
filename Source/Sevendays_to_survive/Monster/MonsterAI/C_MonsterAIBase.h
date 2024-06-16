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

	uint16 EnemyKeyId;			//Key값 map이라고 생각해도 됨



};
