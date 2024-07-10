// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterAI/MonsterTask/C_BlackBoardBase.h"
#include "C_RangedZombie_ChaseTask.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_RangedZombie_ChaseTask : public UC_BlackBoardBase
{
	GENERATED_BODY()
	
public:
    UC_RangedZombie_ChaseTask();
protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

    const float RangedAttackCooldown = 5.0f;
    const float MeleeAttackDistance = 300.0f;
};
