// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterAI/MonsterTask/C_BlackBoardBase.h"
#include "C_BossZombie_ChaseTask.generated.h"

/**
 * 
 */
UCLASS()
class SEVENDAYS_TO_SURVIVE_API UC_BossZombie_ChaseTask : public UC_BlackBoardBase
{
	GENERATED_BODY()
	
public:
    UC_BossZombie_ChaseTask();
protected:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

    void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

    FVector RushTargetHorizontalLocation = FVector::ZeroVector;
    const float RushWaitCooldown = 6.0f;
    float RushWaitTimer = 0.0f;
    bool IsRushWaiting = false;
    bool IsFirstTick = true;
};
