// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterAI/MonsterTask/C_BlackBoardBase.h"
#include "C_JumpTask.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_JumpTask : public UC_BlackBoardBase
{
	GENERATED_BODY()


public:
	UC_JumpTask();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void InitTask(UBehaviorTreeComponent* OwnerComp) override;

	void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

	
};
