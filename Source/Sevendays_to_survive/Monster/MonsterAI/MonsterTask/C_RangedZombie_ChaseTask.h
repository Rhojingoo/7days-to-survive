// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterAI/MonsterTask/C_TaskMonsterChase.h"
#include "C_RangedZombie_ChaseTask.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_RangedZombie_ChaseTask : public UC_TaskMonsterChase
{
	GENERATED_BODY()
	
public:
    UC_RangedZombie_ChaseTask();

private:
    bool MonsterRangeTask(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds) override;

    const float RangedAttackCooldown = 5.0f;
};
