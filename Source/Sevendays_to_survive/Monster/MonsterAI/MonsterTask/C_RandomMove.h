// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterAI/MonsterTask/C_BlackBoardBase.h"
#include "C_RandomMove.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_RandomMove : public UC_BlackBoardBase
{
	GENERATED_BODY()

public:
	UC_RandomMove();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	bool SetPath(FVector _MyLocation, FVector _TargetLocation, UMonsterDataObject* _Data, UBlackboardComponent* _BBC);
	bool NaviMove(class UMonsterDataObject* _Data, UBlackboardComponent* _BBC, AAIController* _Controller, UBehaviorTreeComponent& OwnerComp);
};
