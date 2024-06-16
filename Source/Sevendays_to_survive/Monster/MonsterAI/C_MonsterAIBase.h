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

	uint16 EnemyKeyId;			//Key�� map�̶�� �����ص� ��



};
